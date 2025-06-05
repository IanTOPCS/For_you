def countColorPieces(chessManuel, player):
    playerPiece = ["X", "O"]
    count = 0
    for x in chessManuel:
        if x == playerPiece[player - 1]:
            count += 1
    return count

if __name__ == "__main__":
    test = int(input())
    for _ in range(test):
        chessManuel = str(input())
        player = int(input())
        print(f"{countColorPieces(chessManuel, player)}")
    