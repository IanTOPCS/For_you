import argparse
from pathlib import Path, PosixPath

def checker(source: PosixPath, target: PosixPath) -> bool:
    # get source code
    with open(source, "r", encoding="utf-8") as f:
        sourceCode: list[str] = f.readlines()
        
    # get target code
    with open(target, "r", encoding="utf-8") as f:
        targetCode: list[str] = f.readlines()
    
    # not same lines
    if (len(sourceCode) != len(targetCode)):
        return False
    
    codeLen: int = len(sourceCode)
    
    # skip new line at last line
    if (sourceCode[-1].endswith("\n")):
        sourceCode[-1] = sourceCode[-1].rstrip("\n")
    if (targetCode[-1].endswith("\n")):
        targetCode[-1] = targetCode[-1].rstrip("\n")
        
    for idx in range(0, codeLen, 1):
        # not same at line idx
        if (len(sourceCode[idx]) != len(targetCode[idx])):
            print(f"There are not same at line {idx+1}.")
            return False
        
        lineLen: int = len(sourceCode[idx])
        for lineIdx in range(0, lineLen, 1):
            if (sourceCode[idx][lineIdx] != targetCode[idx][lineIdx]):
                print(f"There are not same at index {lineIdx+1} of line {idx+1}.")
                return False
    return True
        

def parserArg() -> dict[str, PosixPath]:
    parser=  argparse.ArgumentParser()
    parser.add_argument("source")
    parser.add_argument("target")
    args = parser.parse_args()
    
    sourcePath: PosixPath = Path(args.source)
    targetPath: PosixPath = Path(args.target)
    if (not sourcePath.exists()):
        raise FileNotFoundError (f"The path {sourcePath} is not exist.")
    if (not targetPath.exists()):
        raise FileNotFoundError (f"The path {targetPath} is not exist.")
    
    return {"source": sourcePath, "target": targetPath}

if __name__ == "__main__":
    try:
        args:dict[str, PosixPath] = parserArg()
        status: bool = checker(source=args["source"], target=args["target"])
        if (status == True):
            print(f"Correct: The source file {args["source"]} is as same as target file {args["target"]}")
        else:
            print(f"Error: The source file {args["source"]} is not as same as target file {args["target"]}.")
    except Exception as e:
        print(f"{e}")
        raise SystemExit(1)