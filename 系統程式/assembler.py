from pathlib import PosixPath
from typing import Optional

from src.myError import assemblerError
from src.fileChecker import getArgs, writeObjectFile
from src.breakLines import getLines, Line
from src.passerOne import passerLevelOne
from src.passerTwo import passerLevelTwo

def assembler(sicMode: bool, sourcePath: PosixPath, outputPath: PosixPath) -> None:
    lines:list[Line] = getLines(sourcePath=sourcePath)
    passerOneRecord: dict[int, int, Optional[str], dict[str, int]] = passerLevelOne(lines=lines)
    outputRecord: list[str] = passerLevelTwo(sicMode=sicMode, lines=lines, passerOneRecord=passerOneRecord)
    status: bool = writeObjectFile(outputRecord, outputPath)
    if (status == True):
        print(f"Please check output file {outputPath}.")

if __name__ == "__main__":
    try:
        args = getArgs()
        assembler(sicMode=args["sicMode"], sourcePath=args["source"], outputPath=args["output"])
    except assemblerError as e:
        print(f"Error: {e}")
        raise SystemExit(1)
    