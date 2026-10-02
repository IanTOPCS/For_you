import argparse
from pathlib import Path, PosixPath

from src.myError import assemblerError

def writeObjectFile(record: list[str], outputPath: PosixPath) -> bool:
    try:
        # touch directory
        outputPath.parent.mkdir(parents=True, exist_ok=True)

        with outputPath.open("w", encoding="utf-8", newline="") as f:
            for line in record:
                f.write(line + "\n")
        return True
    except PermissionError:
        raise assemblerError(f"Permission deny with path: {outputPath}")
    except Exception as e:
        raise assemblerError(f"Please check output path {outputPath} is reachable: {e}")

def getArgs() -> dict[str, PosixPath]:
    parser = argparse.ArgumentParser(description="SIC/XE Assembler")
    parser.add_argument("source", help="Input assembly file")
    parser.add_argument("-o", "--output", help="Output object file")
    parser.add_argument("--sic", action="store_true", default=False, help="Use SIC standard mode")
    args = parser.parse_args()

    # source code exist?
    sourcePath = Path(args.source)
    if not sourcePath.exists():
        raise assemblerError(f"Source file not found: {args.source}")
    if sourcePath.suffix != ".asm":
        raise assemblerError(f"Input file {args.source} is not a .asm file")

    # out file
    if args.output is None:
        # output = input's suffix => .obj
        outPath = sourcePath.with_suffix(".obj")
    else:
        outPath = Path(args.output)
        # error suffix
        if outPath.suffix != ".obj":
            raise assemblerError(f"Invalid output format: \"{outPath.suffix}\", Only .obj is allowed.")
    return {
        "source": sourcePath, 
        "output": outPath,
        "sicMode": args.sic
    }
    
if __name__ == "__main__":
    args = getArgs()
    # debug input path, output path
    print(f"{type(args["source"])}, {args["source"]}")
    print(f"{type(args["output"])}, {args["output"]}")