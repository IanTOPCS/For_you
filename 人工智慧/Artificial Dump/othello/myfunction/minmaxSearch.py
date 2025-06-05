from dirValue import getDir, playerPiece, countFlipPieces, getBoard
from countColorPieces import countColorPieces
from isValidMove import isValidMove, passTurn, gameOver, flipPieces
import heapq

# 產生所有合法落子
def genMoves(chessManuel, player):
    N = int(len(chessManuel) ** 0.5)
    moves = []
    for i in range(N):
        for j in range(N):
            pos = chr(ord('A') + i) + chr(ord('a') + j)
            if isValidMove(chessManuel, player, pos):
                moves.append(pos)
    return moves

# 啟發式函數：己方棋數 - 對方棋數
def heuristic(chessManuel, player):
    me = countColorPieces(chessManuel, player)
    opp = countColorPieces(chessManuel, 3 - player)
    return me - opp

# minimax 遞迴 (negamax 寫法，方便簡潔)
def minimax(chessManuel, player, depth, maximizing_player, alpha, beta):
    if depth == 0 or gameOver(chessManuel):
        return heuristic(chessManuel, maximizing_player), None

    validMoves = genMoves(chessManuel, player)
    if not validMoves:  # 必須 pass
        val, _ = minimax(chessManuel, 3 - player, depth - 1, maximizing_player, -beta, -alpha)
        return -val, None

    bestMove = None
    heap = []

    for move in validMoves:
        newBoard = flipPieces(chessManuel, player, move)
        val, _ = minimax(newBoard, 3 - player, depth - 1, maximizing_player, -beta, -alpha)
        val = -val
        heapq.heappush(heap, (-val, move))  # max heap：用 -val 保證最大在前
        if val > alpha:
            alpha = val
            bestMove = move
        if alpha >= beta:
            break

    # heapsort：選擇最大分數，若同分選擇字典序最小的（左上優先）
    bestVal, bestPos = heapq.heappop(heap)
    return -bestVal, bestPos

# 主函數：minimax 搜尋
def minimaxSearch(gameboard, player, depth):
    _, bestMove = minimax(gameboard, player, depth, player, -float('inf'), float('inf'))
    return bestMove

if __name__ == "__main__":
    test = int(input())
    for _ in range(test):
        chessManuel = str(input())
        player = int(input())
        depth = int(input())
        print(f"{minimaxSearch(chessManuel, player, depth)}")
