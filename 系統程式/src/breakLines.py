from pathlib import PosixPath
from dataclasses import dataclass
from typing import Optional

from src.myError import assemblerError
from src.myTable import DIRECTIVES, OPCODES

@dataclass
class Line:
    number: int = 0
    label: str = ""
    opcode: str = ""
    operand: str = ""
    loc: Optional[int] = None
    
def bkline(lineNumber: int, line: str) -> list[str]:
    collection: list[str] = list()
    # take off comment "."
    line = line.rstrip("\n").strip().split(".")[0]
    
    # add space to collect whole element
    if (len(line)>0):
        line += " "
    
    # slice input line
    element: str = ""
    for idx in range(0, len(line), 1):
        # break less than 3 parts
        if (len(collection)<2):
            if ((line[idx].isspace() == True) and (len(element)>0)):
                collection.append(element)
                element = ""
            elif (line[idx].isspace() == False):
                element += line[idx]
        else:
            # avoid last space added by myself
            element = line[idx:].strip()
            if (len(element)>0):
                collection.append(element)
            break
    
    if (len(collection)>2):
        # combine "op @ l a b e l" "op #1 0"(space), "op A ,x" or "op A, x"(space)
        if ((collection[1].startswith("#")) or
            (collection[1].startswith("@")) or
            (collection[1].endswith(",")) or
            (collection[2].startswith(","))):
            collection = [collection[0], "".join(f"{collection[1]}{collection[2]}".split(" "))]
        # combine "c '???' ", notice: except register X and X'???'
        target: str = collection[-1].upper()
        if ((target.startswith("C")) or (target.startswith("X")) and (target.count("'")>0)):
            # check close with '
            if (target.count("'") == 2):
                tarList: list[str] = collection[-1].split("'")
                collection[-1] = f"{tarList[0].strip().upper()}'{tarList[1]}'"
            else:
                raise assemblerError (f"Char or hex need to close by ' at {lineNumber}.")
            # check hex
            target = collection[-1]
            if (target.startswith(r"X'")):
                try:
                    tmp: str = "".join(target[2:-1].strip().split(" "))
                    int(tmp, 16)
                    # combint hex
                    collection[-1] = f"X'{tmp}'"
                except ValueError:
                    raise assemblerError(f"Not legal hex ({target[1:]}) at {lineNumber}.")
    return collection
    
def oneLine(index: int, line: str) -> Line:
    tokens: list[str] = bkline(index, line)
    if (len(tokens) == 1):
        # ex: RSUB
        tmp:str = tokens[0].upper()
        if (tmp in OPCODES):
            return Line(number=index,
                        label="",
                        opcode=tmp,
                        operand="",
                        loc=None)
        else:
            raise assemblerError (f"Invalid command {tokens[0]} at line {index}.")
    elif (len(tokens) == 2):
        tmp0: str = tokens[0].upper()
        tmp1: str = tokens[1].upper()
        if ((tmp0 in DIRECTIVES) or (tmp0.lstrip("+") in OPCODES)):
            # ex: +J rdrec, label can't upper
            # ex: BASE LENGTH
            return Line(number=index,
                        label="",
                        opcode=tmp0,
                        operand=tokens[1],
                        loc=None)
        elif (tmp1 in OPCODES):
            # ex: golabel1 HIO (label+format 1)
            return Line(number=index,
                        label=tokens[0],
                        opcode=tmp1,
                        operand="",
                        loc=None,)
        else:
            # no opcode
            raise assemblerError (f"Invalid opcode in ({line.rstrip("\n").strip(" ")}) at line {index}.")
    elif (len(tokens) == 3):
        # special case "START"
        if (tokens[0].upper() == "START"):
            return Line(number=index,
                        label="",
                        opcode=tokens[0].upper(),
                        operand=f"{tokens[1]}{"".join(tokens[2].split(" "))}",
                        loc=None)
            
        tmp:str = tokens[1].upper()
        # ex: golabel2 ADD ONE, label +J sif
        # ex: THREE WORD 3
        if ((tmp in DIRECTIVES) or (tmp.lstrip("+") in OPCODES)):
            return Line(number=index,
                        label=tokens[0],
                        opcode=tmp,
                        operand=tokens[2],
                        loc=None)
        else:
            raise assemblerError (f"Invalid command {tokens[1]} at line {index}.")

def getLines(sourcePath: PosixPath) -> list[Line]:
    with open(sourcePath, "r", encoding="utf-8") as f:
        rawLines: list[str] = f.readlines()
    
    lines: list[str] = list()
    for i, line in enumerate(rawLines):
        tryLine: Line = oneLine(i+1, line)
        if (tryLine is not None):
            lines.append(tryLine)
    return lines

if __name__ == "__main__":
    # === test oneLine ===
    # test nothing
    # obj2 = oneLine(1, "")
    # print(f"{obj2}")
    # test comment
    # obj3 = oneLine(1, ".sadfsfs")
    # print(f"{obj3}")
    
    # test OP (len=1)
    # obj4 = oneLine(1, "RSUB")
    # print(f"{obj4}")
    # test error
    # obj5 = oneLine(1, "abc")

    # test label OP (len=2)
    # obj6 = oneLine(1, "ENDFIL LDA")
    # print(f"{obj6}")
    # test +OP operand
    # obj7 = oneLine(1, "+J rdrec")
    # print(f"{obj7}")
    # test error
    # obj8 = oneLine(1, "abc iso")

    # test label OPcode operand (len=3)
    # obj9 = oneLine(1, "abc byte jsi")
    # print(f"{obj9}")
    # test error (no opcode or directive)
    # obj10 = oneLine(1, "sid sji sio")
    
    # test ,x
    # obj11 = oneLine(1, "sdf ADD    THREE, x")
    # print(f"{obj11}")
    
    # test (immediate + space)
    # obj12 = oneLine(1, "+LDT # 0 1 5")
    # print(f"{obj12}")
    
    # test (indirect + space)
    # obj13 = oneLine(1, "+LDT @ l a b e l ")
    # print(f"{obj13}")
    
    # test (label register + space)
    obj14 = oneLine(1, "dfj ADDR a , x , jobos")
    print(f"{obj14}")
    
    # test (comment in line)
    # obj15 = oneLine(1, "l@a+b#e,l ADDR a, x , . sifjisa")
    # print(f"{obj15}")
    
    # test char (space)
    # obj16 = oneLine(1, "EOF     BYTE    c ' eof char ' ")
    # print(f"{obj16}")
    
    # test with X label (spetific case register "x" vs label name "x")
    # obj17 = oneLine(1, "CLEAR X , X")
    # print(f"{obj17}")
    
    # test number with space
    # print(f"{oneLine(1, "EOF BYTE x ' A1 2 3 a b c '")}")