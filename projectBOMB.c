#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 10
#define NUM_MINES 15

void print_board(char board[][BOARD_SIZE]);
void place_mines(char board[][BOARD_SIZE]);
int count_adjacent_mines(char board[][BOARD_SIZE], int row, int col);
int reveal_square(char board[][BOARD_SIZE], char visible_board[][BOARD_SIZE], int row, int col);

int main() {
	
    char board[BOARD_SIZE][BOARD_SIZE];
    char visible_board[BOARD_SIZE][BOARD_SIZE];
    int row, col, num_revealed;

    srand(time(NULL));
    place_mines(board);

    for (row = 0; row < BOARD_SIZE; row++) {
        for (col = 0; col < BOARD_SIZE; col++) {
            visible_board[row][col] = '_';
        }
    }

    print_board(visible_board);

    while (1) {
        printf("Enter row and column (e.g., 3 5): ");
        scanf("%d %d", &row, &col);

        if (board[row][col] == '*') {
            printf("BOOM! You hit a mine. Game over.\n");
            break;
        }

        num_revealed = reveal_square(board, visible_board, row, col);
        print_board(visible_board);

        if (num_revealed == BOARD_SIZE * BOARD_SIZE - NUM_MINES) {
            printf("Congratulations! You found all the mines.\n");
            break;
        }
    }

    return 0;
}

void print_board(char board[][BOARD_SIZE])
{
    int row, col;

    printf("  ");
    for (col = 0; col < BOARD_SIZE; col++) {
        printf("%d ", col);
    }
    printf("\n");

    printf("  ");
    for (col = 0; col < BOARD_SIZE; col++) {
        printf("_ ");
    }
    printf("\n");

    for (row = 0; row < BOARD_SIZE; row++) {
        printf("%d|", row);
        for (col = 0; col < BOARD_SIZE; col++) {
            printf("%c ", board[row][col]);
        }
        printf("\n");
    }
}

void place_mines(char board[][BOARD_SIZE])
{
    int row, col, i, j;

    for (row = 0; row < BOARD_SIZE; row++) {
        for (col = 0; col < BOARD_SIZE; col++) {
            board[row][col] = '.';
        }
    }

    for (i = 0; i < NUM_MINES; i++) {
        do {
            row = rand() % BOARD_SIZE;
            col = rand() % BOARD_SIZE;
        } while (board[row][col] == '*');
        board[row][col] = '*';
    }
}

int count_adjacent_mines(char board[][BOARD_SIZE], int row, int col)
{
    int i, j, count = 0;

    for (i = row - 1; i <= row + 1; i++) {
        for (j = col - 1; j <= col + 1; j++) {
            if (i >= 0 && i < BOARD_SIZE && j >= 0 && j < BOARD_SIZE && board[i][j] == '*') {
                count++;
            }
        }
    }

    return count;
}

int reveal_square(char board[][BOARD_SIZE], char visible_board[][BOARD_SIZE], int row, int col)
{
    if (visible_board[row][col] != '_') {
        return 0;
    }

    visible_board[row][col] = '0' + count_adjacent_mines(board, row, col);

    if (visible_board[row][col] == '0') {
        int i, j;
        for (i = row - 1; i <= row + 1; i++) {
            for (j = col - 1; j <= col + 1; j++) {
                if (i >= 0 && i < BOARD_SIZE && j >= 0 && j < BOARD_SIZE) {
                    reveal_square(board, visible_board, i, j);
                }
            }
        }
    }

    return 1;
}
