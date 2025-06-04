#!/usr/bin/env python3

"""A simple Tic Tac Toe game for two players in the terminal."""


def print_board(board):
    print("\nCurrent board:")
    for row in board:
        print(" | ".join(cell or " " for cell in row))
        print("-" * 9)


def check_winner(board):
    lines = (
        board[0], board[1], board[2],  # rows
        [board[r][0] for r in range(3)],
        [board[r][1] for r in range(3)],
        [board[r][2] for r in range(3)],  # columns
        [board[i][i] for i in range(3)],  # diag1
        [board[i][2 - i] for i in range(3)]  # diag2
    )
    for line in lines:
        if line[0] and all(cell == line[0] for cell in line):
            return line[0]
    return None


def is_full(board):
    return all(all(cell for cell in row) for row in board)


def main():
    board = [["" for _ in range(3)] for _ in range(3)]
    players = ["X", "O"]
    turn = 0

    while True:
        print_board(board)
        player = players[turn % 2]
        move = input(f"Player {player}, enter your move (row and column 1-3 separated by space): ")
        try:
            r, c = [int(x) - 1 for x in move.split()]
            if not (0 <= r < 3 and 0 <= c < 3) or board[r][c]:
                raise ValueError
        except ValueError:
            print("Invalid move, try again.")
            continue
        board[r][c] = player

        winner = check_winner(board)
        if winner:
            print_board(board)
            print(f"Player {winner} wins!")
            break
        if is_full(board):
            print_board(board)
            print("It's a draw!")
            break
        turn += 1


if __name__ == "__main__":
    main()
