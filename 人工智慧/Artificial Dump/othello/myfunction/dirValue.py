import math

getDir = [[-1, 0], [-1, 1], [0, 1], [1, 1], [1, 0], [1, -1], [0, -1], [-1, -1]]
playerPiece = ["X", "O"]

def getBoard(chessManuel):
    rowColLen = int(math.sqrt(len(chessManuel)))
    # Convert the chessboard string to a 2D list
    chessBoard = []
    for i in range(rowColLen):
        tmp = []
        for j in range(rowColLen):
            tmp.append(chessManuel[i * rowColLen + j])
        chessBoard.append(tmp)
    return chessBoard, rowColLen

def countFlipPieces(chessManuel, player, position, dir):
    chessBoard, rowColLen = getBoard(chessManuel)
        
    # debug
    # for i in range(rowColLen):
    #     for j in range(rowColLen):
    #         print(chessBoard[i][j], end=" ")
    #     print()
    
    # Convert the position to row and column indices
    row = ord(position[0]) - ord('A')
    col = ord(position[1]) - ord('a')
    
    if row < 0 or row >= rowColLen or col < 0 or col >= rowColLen:
        return 0

    # Check if the position is valid
    if chessBoard[row][col] != "+":
        return 0

    # Initialize the count of flipped pieces
    count = 0

    # Check in the specified direction
    newRow = row + getDir[dir][0]
    newCol = col + getDir[dir][1]
    
    # print(chessBoard[newRow][newCol], newRow, newCol) # debug
    
    for _ in range(rowColLen):
        # Check if the new position is within bounds
        if newRow < 0 or newRow >= rowColLen or newCol < 0 or newCol >= rowColLen or chessBoard[newRow][newCol] == "+": 
            count = 0
            break
        
        if chessBoard[newRow][newCol] == playerPiece[player - 1]:
            break
        
        # print(chessBoard[newRow][newCol], newRow, newCol) # debug
        
        # Check if the piece at the new position is the same as the player's piece
        if chessBoard[newRow][newCol] == playerPiece[player%2]:
            count += 1
        
        # Move to the next position in the specified direction
        newRow += getDir[dir][0]
        newCol += getDir[dir][1]
    
    return count

if __name__ == "__main__":
    test = int(input())
    for _ in range(test):
        chessManuel = str(input())
        player = int(input())
        position = str(input())
        dir = int(input())
        print(countFlipPieces(chessManuel, player, position, dir))