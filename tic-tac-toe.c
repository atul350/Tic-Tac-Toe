#include <stdio.h>

char board[3][3];
char currentPlayer = 'X';

void resetBoard() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
}

void printBoard() {
    printf("\n");
    printf("  0   1   2\n");
    for (int i = 0; i < 3; i++) {
        printf("%d ", i);
        for (int j = 0; j < 3; j++) {
            printf("%c", board[i][j]);
            if (j < 2) printf(" | ");
        }
        printf("\n");
        if (i < 2) printf("  ---------\n");
    }
    printf("\n");
}

int checkWin() {
    // Rows & Columns
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == currentPlayer &&
            board[i][1] == currentPlayer &&
            board[i][2] == currentPlayer)
            return 1;

        if (board[0][i] == currentPlayer &&
            board[1][i] == currentPlayer &&
            board[2][i] == currentPlayer)
            return 1;
    }

    // Diagonals
    if (board[0][0] == currentPlayer &&
        board[1][1] == currentPlayer &&
        board[2][2] == currentPlayer)
        return 1;

    if (board[0][2] == currentPlayer &&
        board[1][1] == currentPlayer &&
        board[2][0] == currentPlayer)
        return 1;

    return 0;
}

int checkDraw() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return 0;
    return 1;
}

void switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

int main() {
    int row, col;
    resetBoard();

    while (1) {
        printBoard();
        printf("Player %c, enter row and column (0-2): ", currentPlayer);
        scanf("%d %d", &row, &col);

        // Validate move
        if (row < 0 || row > 2 || col < 0 || col > 2) {
            printf("Invalid position! Try again.\n");
            continue;
        }
        if (board[row][col] != ' ') {
            printf("Spot already taken! Try again.\n");
            continue;
        }

        board[row][col] = currentPlayer;

        // Check win
        if (checkWin()) {
            printBoard();
            printf("Player %c WINS!\n", currentPlayer);
            break;
        }

        // Check draw
        if (checkDraw()) {
            printBoard();
            printf("It's a DRAW!\n");
            break;
        }

        switchPlayer();
    }

    return 0;
}