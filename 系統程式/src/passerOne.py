from math import ceil
from typing import Optional

from src.breakLines import Line
from src.myError import assemblerError
from src.myTable import OPCODES, DIRECTIVES

def numberCalculater(lineNumber: int, operand: str) -> int:
    num: int = 0
    if (operand.startswith("-")):
        raise assemblerError (f"Can't reserve negative space ({operand}) at line {lineNumber}.")
    calop: str = operand
    # take off "+" and space between + and first number
    if ((len(operand)>1) and (operand.startswith("+"))):
        calop = "".join(operand[1:].strip().split(" "))
    # check decimal number
    if (calop.isdigit() == False):
        raise assemblerError (f"Must reserve space in decimal ({operand}) at line {lineNumber}.")
    # check number range (15 bits = 32767)
    num = int(calop, 10)
    if (num >= 32768):
        raise assemblerError (f"{num} exceeds 15 bits address space ({operand}) at line {lineNumber}.")
    return num
    

def calculateByte(lineNumber: int, operand: str) -> int:
    if (operand.startswith(r"X'")):
        return ceil(len(operand[2:-1])/2)
    elif (operand.startswith(r"C'")):
        return len(operand[2:-1])
    else:
        raise assemblerError(f"Invaild byte {operand} at line {lineNumber}.")

def passerLevelOne(lines: list[Line]) -> dict[int, int, Optional[str], dict[str, int]]:
    locctr:int = 0
    startAddr: int = 0
    programName: Optional[str] = None
    symbolTable: dict[str, int] = dict()
    startFlag: bool = False
    programLength: int = 0
    
    # start with "START"
    if (lines[0].opcode != "START"):
        raise assemblerError (f"Program must start with START.")
    
    for line in lines:
        # start
        if (line.opcode == "START"):
            if (startFlag == False):
                startFlag = True
                # set program name
                if (len(line.label)>0):
                    programName = line.label
                # set start address
                tmp: int = 0
                line.operand = "".join(line.operand.split(" "))
                if (line.operand.isdigit() == True):
                    tmp = int(line.operand, 16)
                    if (tmp>0):
                        startAddr = tmp
                    else:
                        startAddr = 0
                else:
                    raise assemblerError (f"Start address {line.operand} is not legal at line {line.number}.")
                # set location counter
                locctr = startAddr
                line.loc = locctr
                continue
            else:
                raise assemblerError(f"Duplicate start at line {line.number}.")
        # set location counter
        line.loc = locctr
        # check duplicate label
        if (len(line.label)>0):
            tmp: str = symbolTable.get(line.label, None)
            if (tmp is not None):
                raise assemblerError(f"Duplicate label {tmp} at line {line.number}.")
            # store symbol table
            symbolTable[line.label] = locctr
        
        opOrDir: str = line.opcode
        extend: bool = False
        # check format 4
        if (opOrDir.startswith("+")):
            opOrDir = opOrDir[1:]
            extend = True
        tmp: Optional[tuple[int, int, bool]] = OPCODES.get(opOrDir, None)
        if (tmp != None):
            _, fmt, _ = tmp
            if ((fmt == 3) and (extend == True)):
                locctr += 4
            else:
                locctr += fmt
        elif (opOrDir in DIRECTIVES):
            if (opOrDir == "WORD"):
                locctr += 3
            elif (opOrDir == "BYTE"):
                locctr += calculateByte(line.number, line.operand)
            elif (opOrDir == "RESW"):
                locctr += (3 * numberCalculater(line.number, line.operand))
            elif (opOrDir == "RESB"):
                locctr += numberCalculater(line.number, line.operand)
        else:
            raise assemblerError (f"Unknown command at line {line.number}, {line.opcode}")
        # check location counter in 1M
        if ((locctr - startAddr) > 1_048_576):
            raise assemblerError(f"Program size ({locctr-startAddr} bytes) exceeds the SIC/XE 1MB limit at line {line.number}.")
    # save program length
    programLength = (locctr - startAddr)
    return {"startAddr": startAddr,
            "programLength": programLength,
            "programName": programName,
            "symbolTable": symbolTable}
                
if __name__ == "__main__":
    # ==== test calculateByte =====
    # test not legal byte
    # print(calculateByte(1, "q'12a'"))
    
    # test ceilling hex
    # print(calculateByte(1, "X'12a'"))
    
    # test char
    print(calculateByte(1, "C'12au '"))
    
    # ==== test numberCalculater ====
    # test normal version
    # print(numberCalculater(1, "587"))
    
    # test with "+" and space
    # print(numberCalculater(1, "+ 548"))
    
    # test error with negative
    # print(numberCalculater(1, "-548"))
    
    # test with not-decimal
    # print(numberCalculater(1, "+abs"))
    
    # test error out of 15-bits
    # print(numberCalculater(1, "+ 32768"))
    
    # test number with space
    # print(numberCalculater(1, "+ 3 2 7 6 7"))