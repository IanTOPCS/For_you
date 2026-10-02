from typing import Optional
from math import ceil

from src.breakLines import Line
from src.myError import assemblerError
from src.myTable import OPCODES, REGISTERS, DIRECTIVES

def coverByteToHex(lineNumber: int, operand: str) -> str:
    errorFlag: bool = False
    # test "X"
    if (operand.startswith(r"X'")):
        # take off X'???' => ???
        operand = operand[2:-1]
        if (len(operand)%2 == 0):
            return operand
        else:
            errorFlag = True
    elif (operand.startswith(r"C'")):
        # must using source case-sensitive
        tmp: str = ""
        for ch in operand[2:-1]:
            tmp += f"{ord(ch):02X}"
        return tmp
    if (errorFlag == True):
        raise assemblerError (f"Invalid byte format {operand} at line {lineNumber}.")

def judge(lineNumber: int, sor: str) -> bool:
    if (len(sor) == 0):
        raise assemblerError (f"Must give a decimal at line {lineNumber}.")
    if (((sor[0] == "-") or (sor[0] == "+")) and (len(sor)>1)):
        sor = sor[1:].strip()
    return sor.isdigit()

def coverInt(sor: str) -> int:
    if ((len(sor)>1) and((sor[0] == "-") or (sor[0] == "+"))):
        return int((sor[0]+sor[1:].strip()), 10)
    return int(sor, 10)

def getSymbolTableValue(operand: str, symbolTable: dict[str, int], lineNumber: int) -> int:
    if (len(operand) == 0):
        raise assemblerError (f"Must has operand at line {lineNumber}.")
    if (judge(lineNumber, operand) == True):
        return coverInt(operand)
    getSymbol: int = symbolTable.get(operand, None)
    if (getSymbol is not None):
        return getSymbol
    raise assemblerError (f"Symbol error, check {operand} at line {lineNumber}.")

def handleFormat34(sicMode: bool, opcode: int, sicOp: bool, ext: bool, line: Line, nextLoc: int, symbolTable: dict[str, int], baseAddr: Optional[int], mRecords: list[str]) -> str:
    errorFlag: bool = False
    realOperator: str = line.operand
    n, i, x, b, p, e = 1, 1, 0, 0, 0, 0
    if (ext == True):
        e = 1
    # immediate
    if (realOperator.startswith("#")):
        # block sic-mode
        if (sicMode == True):
            raise assemblerError (f"SIC has no immediate addressing mode ({realOperator}) at line {line.number}.")
        # set register flag
        n, i = 0, 1
        # avoid only "#"
        if (len(realOperator)>1):
            # ex: label opcode # 4 0 9 6
            realOperator = "".join(realOperator[1:].split(" "))
        else:
            errorFlag = True
    elif (realOperator.startswith("@")):
        # block sic-mode
        if (sicMode == True):
            raise assemblerError (f"SIC has no indirect addressing mode ({realOperator}) at line {line.number}.")
        # set register flag
        n, i = 1, 0
        # avoid only "@"
        if (len(realOperator)>1):
            realOperator = "".join(realOperator[1:].split(" "))
        else:
            errorFlag = True
    if (errorFlag == True):
        raise assemblerError (f"Operand is lost at line {line.number}.")

    # combine opcode with "n" and "i"
    opcode = (((opcode & 0xfc) | (n<<1)) | i)
    # handle "X"
    hasX: bool = any(ch.strip().upper() == "X" for ch in realOperator.split(","))
    if (hasX == True):
        x = 1
        realOperator = realOperator.split(",")[0].strip()
    
    immediateFlag: bool = False
    targetAddr: int = 0
    if ((n == 0) and (i == 1) and (judge(line.number, realOperator) == True)):
        immediateFlag = True
        # enable "- 65" => "-65"
        targetAddr = coverInt(realOperator)
    else:
        # consider RSUB 3 (has decimal)
        targetAddr = getSymbolTableValue(realOperator, symbolTable, line.number)
    
    pcRelative: int = 0
    baseRelative: int = 0
    disp: int = 0
    regFlags: int = 0
    total: int = 0
    # combine format 4 (32 bits)
    if (ext == True):
        if ((immediateFlag == True) and ((targetAddr<-524_288) or (targetAddr>524_287))):
            raise assemblerError (f"Immediate value is out of range at line {line.number}.")
        disp = (targetAddr & 0xfffff)
        # each addressing mode need m-record, except immediate
        if (immediateFlag == False):
            mRecords.append(f"M{(line.loc + 1):06X}05")
        regFlags = (x<<3) | (b<<2) | (p<<1) | e
        total = (opcode<<24) | (regFlags<<20) | disp
        return f"{total:08X}"
    # other format 3 (24 bits)
    # immediate
    if (immediateFlag == True):
        if ((targetAddr<-2048) or (targetAddr>2047)):
            raise assemblerError (f"The immediate must change into format 4 with '+' at line {line.number}.")
        disp = targetAddr
        regFlags = (x<<3) | (b<<2) | (p<<1) | e
        total = (opcode<<16) | (regFlags<<12) | disp
        return f"{total:06X}"
    # program-counter relative
    pcRelative = (targetAddr - nextLoc)
    # base-relative
    if (baseAddr is not None):
        baseRelative = (targetAddr - baseAddr)
    
    if ((sicMode == False) and ((-2048<=pcRelative) and (pcRelative<=2047))):
        p = 1
        disp = (pcRelative & 0xfff)
    # base relative
    elif ((sicMode == False) and (baseAddr is not None) and (0<=baseRelative) and (baseRelative<=4095)):
        b = 1
        disp = baseRelative
    else:
        # consider sic (no immediate, indirect, extend)
        if ((sicMode == True) or
            ((sicOp == True) and (ext == False) and (n == 1) and (i == 1))):
            n, i = 0, 0
            opcode &= 0xfc
            # check range 15-bit (direct)
            if ((0<=targetAddr) and (targetAddr<=32767)):
                disp = (targetAddr & 0x7fff)
                # format sic
                total = (opcode<<16) | disp
                # consider "X"
                if (hasX == True):
                    total |= (1<<15)
                return f"{total:06X}"
            elif (sicMode == True):
                raise assemblerError(f"\"{realOperator}\" is unreachable on SIC with 15-bits direct addressing at line {line.number}.")
        # out of range, had set base?
        if (baseAddr is None):
            # sic/XE set base or format-4 (pc-relative is out of range)
            raise assemblerError (f"PC-relative is unreachable, you must set base register at line {line.number}.")
        else:
            raise assemblerError (f"Base relative is out of range at line {line.number}.")
    # combine format 3 (indirect, sicXE)
    regFlags = (x<<3) | (b<<2) | (p<<1) | e
    total = (opcode<<16) | (regFlags<<12) | disp
    return f"{total:06X}"

def storeTextRecord(start: Optional[int], data: str, records: list[tuple[int, str]]) -> tuple[None, str]:
    if ((start is not None) and (len(data)>0)):
        records.append((start, data))
    return (None, "")

def passerLevelTwo(sicMode: bool, lines: list[Line], passerOneRecord: dict[int, int, Optional[str], dict[str, int]]) -> list[str]:
    startAddr: int = passerOneRecord["startAddr"]
    programLength: int = passerOneRecord["programLength"]
    programName: Optional[str] = passerOneRecord["programName"]
    symbolTable: dict[str, int] = passerOneRecord["symbolTable"]
    
    baseAddr: Optional[int] = None
    mRecords: list[str] = list()
    tRecords: list[tuple[int, str]] = list()
    totalRecords: list[str] = list()
    
    tStart: Optional[int] = None
    tData: str = ""
    
    sicErrorFlag: bool = False
    
    for line in lines:
        objCode:str = ""
        opOrDir: str = line.opcode
        sicOp: bool = False
        ext: bool = False
        nextLoc: int = (line.loc + 3)
        if (line.opcode.startswith("+")):
            if (sicMode == True):
                sicErrorFlag = True
            ext = True
            opOrDir = line.opcode[1:]
        # START
        if (opOrDir == "START"):
            continue
        tmp: Optional[tuple[str, int, bool]] = OPCODES.get(opOrDir, None)
        if (tmp is not None):
            opcode, fmt, sicOp = tmp
            # format 1
            if (fmt == 1):
                # block sic-mode
                if (sicMode == True):
                    sicErrorFlag = True
                else:
                    objCode = f"{opcode:X}"
            elif (fmt == 2):
                # block sic-mode
                if (sicMode == True):
                    sicErrorFlag = True
                else:
                    # format 2
                    fmt2ErrorFlag: bool = False
                    regOne: int = 0
                    regTwo: int = 0
                    regs: list[str] = list()
                    # take out registers (at most two)
                    if (len(line.operand)>0):
                        regs = [reg.strip(" ").upper() for reg in line.operand.split(",") if (len(reg.strip(" "))>0)]
                    if (len(regs) == 1):
                        regOne = REGISTERS.get(regs[0], None)
                        if (regOne is None):
                            fmt2ErrorFlag = True
                    elif (len(regs) == 2):
                        regOne = REGISTERS.get(regs[0], None)
                        regTwo = REGISTERS.get(regs[1], None)
                        if ((regOne is None) or (regTwo is None)):
                            fmt2ErrorFlag = True
                    else:
                        raise assemblerError (f"Too many register ({line.operand}) at line {line.number}.")
                    # some register not exist
                    if (fmt2ErrorFlag == True):
                        raise assemblerError (f"Invalid register at line {line.number}")
                    else:
                        objCode = f"{opcode:X}{regOne:X}{regTwo:X}"
            elif (fmt == 3):
                # block sic-mode
                if ((sicMode == True) and (sicOp == False)):
                    sicErrorFlag = True
                else:
                    # format 3/4, no operand
                    if (opOrDir == "RSUB"):
                        if (sicMode == True):
                            opcode &= 0xfc
                        else:
                            opcode = ((opcode & 0xfc) | 0x03)
                        if (ext == True):
                            objCode = f"{opcode:X}10000"
                        else:
                            objCode = f"{opcode:X}0000"
                    else:
                        objCode = handleFormat34(sicMode=sicMode,
                                                opcode=opcode,
                                                sicOp=sicOp,
                                                ext=ext,
                                                line=line,
                                                nextLoc=nextLoc,
                                                symbolTable=symbolTable,
                                                baseAddr=baseAddr,
                                                mRecords=mRecords)
        elif (opOrDir in DIRECTIVES):
            if (opOrDir == "WORD"):
                if (judge(line.number, line.operand) == False):
                    raise assemblerError (f"Word need a decimal at line {line.number}")
                # cover into number
                value: int = coverInt(line.operand)
                # check range (3 bytes)
                if ((-8_388_608 <= value) and (value <= 8_388_607)):
                    objCode = f"{value:06X}"
                else:
                    raise assemblerError (f"The number assigned to word is out of range at line {line.number}.")
            elif (opOrDir == "BYTE"):
                objCode = coverByteToHex(line.number, line.operand)
            elif ((opOrDir == "RESB") or (opOrDir == "RESW")):
                # add t-record (change line)
                tStart, tData = storeTextRecord(tStart, tData, tRecords)
                continue
            elif (opOrDir == "BASE"):
                # block sic-mode
                if (sicMode == False):
                    baseAddr = getSymbolTableValue(line.operand, symbolTable, line.number)
                    continue
                else:
                    sicErrorFlag = True
            elif (opOrDir == "END"):
                break
        else:
            raise assemblerError (f"Invalid command {opOrDir} at line {line.number}.")
        # block sic-mode
        if (sicErrorFlag == True):
            raise assemblerError (f"SIC has no opcode {line.opcode} at line {line.number}.")
        # check length object code big than 60?
        if (len(objCode)>0):
            # first command of new t-record
            if (tStart is None):
                tStart = line.loc
            # change line of t-record
            if ((len(tData) + len(objCode))>60):
                tStart, tData = storeTextRecord(tStart, tData, tRecords)
                tStart = line.loc
            # add up t-record
            tData += objCode
            
    # remain t-record
    tStart, tData = storeTextRecord(tStart, tData, tRecords)
    
    # collect all records
    # H-record (H + (6 name) + (6 start address) + (6 program length))
    if (programName is None):
        programName = " "*6
    totalRecords.append(f"H{programName[:6]:<6}{startAddr:06X}{programLength:06X}")
    # t-record (T + (6 start address) + (2 t-record length) + (object code))
    for addr, data in tRecords:
        totalRecords.append(f"T{addr:06X}{ceil(len(data)/2):02X}{data}")
    # m-record
    totalRecords.extend(mRecords)
    # e-record (E + (6 start address))
    totalRecords.append(f"E{startAddr:06X}")
    return totalRecords

if __name__ == "__main__":
    # === test judge ===
    a = "- 35"
    print(judge(1, a))
    print(coverInt(a))
    
    # === test coverByteToHex ===
    # test normal (hex mode)
    # print(f"{coverByteToHex(1, r"X'128c'")}")
    
    # test normal (char mode)
    # print(f"{coverByteToHex(1, r"C' 1 2 8 u '")}")
    