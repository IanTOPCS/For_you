# from othello.myfunction.dirValue import getDir, playerPiece, countFlipPieces, getBoard
from dirValue import getDir, playerPiece, countFlipPieces, getBoard

# 判斷是否可以移動 (起碼需要翻對手一顆棋稱為合法)
def isValidMove(chessManuel, player, position):
    for dir in range(8):
        count = countFlipPieces(chessManuel, player, position, dir)
        if count > 0:
            return True
    return False
    
# 是否需要pass (沒有任何可移動的步即需要pass)
def passTurn(chessManuel, player):
    for i in range(len(chessManuel)):
        for j in range(len(chessManuel)):
            position = chr(i + ord('A')) + chr(j + ord('a'))
            if isValidMove(chessManuel, player, position):
                return False
    return True

# 自己與對手都pass (雙方都動不了，即結束)
def gameOver(chessManuel):
    return passTurn(chessManuel, 1) and passTurn(chessManuel, 2)

def flipPieces(chessManuel, player, position):
    if isValidMove(chessManuel, player, position):
        chessBoard, rowColLen = getBoard(chessManuel)
        # Convert the position to row and column indices
        row = ord(position[0]) - ord('A')
        col = ord(position[1]) - ord('a')
        
        # Flip the pieces in all directions
        for dir in range(8):
            count = countFlipPieces(chessManuel, player, position, dir)
            if count > 0:
                newRow = row + getDir[dir][0]
                newCol = col + getDir[dir][1]
                for _ in range(count):
                    chessBoard[newRow][newCol] = playerPiece[player - 1]
                    newRow += getDir[dir][0]
                    newCol += getDir[dir][1]
        
        # Place the player's piece at the specified position
        chessBoard[row][col] = playerPiece[player - 1]
        
        # Convert the 2D list back to a string
        chessManuel = ''.join([''.join(row) for row in chessBoard])
    return chessManuel
    
if __name__ == "__main__":
    test = int(input())
    for _ in range(test):
        chessManuel = str(input())
        player = int(input())
        position = str(input())
        print(f"{flipPieces(chessManuel, player, position)}")