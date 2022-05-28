#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND 33
#define MIN -10
#define MAX 10

enum Scores {
    WON = 1,
    LOST = -1,
    TIE = 0,
    NONE = 3
};

class Game {
public:
    int m, n, k, activePlayer;
    int** board;

    Game() {
        m = -1;
        n = -1;
        k = -1;
        activePlayer = -1;
        board = nullptr;
    }

    ~Game() {
    }

    void allocateBoard() {
        board = (int**)malloc(m * sizeof(int*));
        for (int i = 0; i < m; ++i)
            board[i] = (int*)malloc(n * sizeof(int));
    }

    void deallocateBoard() {
        if (board != nullptr) {
            for (int i = 0; i < m; ++i)
                free(board[i]);

            free(board);
        }
    }

    void scanBoard() const {
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                scanf_s("%d", &(board[i][j]));
    }

    void printBoard() const {
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j)
                printf("%d ", board[i][j]);
            printf("\n");
        }
    }

    int getOpponent() const {
        if (activePlayer == 1)
            return 2;
        else
            return 1;
    }

    bool isTie() const {
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                if (board[i][j] == 0)
                    return false;

        return true;
    }

    int checkWin() const {
        int i, j, l;

        //horizontal
        for (i = 0; i < m; ++i) {
            for (j = 0; j <= n - k; ++j) {
                for (l = 1; l < k; ++l) {
                    if (board[i][j] == 0 || board[i][j + l] != board[i][j])
                        break;
                    if (l == k - 1 && board[i][j + l] == board[i][j])
                        return board[i][j];
                }
            }
        }

        //vertical
        for (j = 0; j < n; ++j) {
            for (i = 0; i <= m - k; ++i) {
                for (l = 1; l < k; ++l) {
                    if (board[i][j] == 0 || board[i + l][j] != board[i][j])
                        break;
                    if (l == k - 1 && board[i + l][j] == board[i][j])
                        return board[i][j];
                }
            }
        }

        //diagonal
        // direction: "/"
        for (i = 0; i <= m - k; ++i) {
            for (j = k - 1; j < n; ++j) {
                for (l = 1; l < k; ++l) {
                    if (board[i][j] == 0 || board[i + l][j - l] != board[i][j])
                        break;
                    if (l == k - 1 && board[i + l][j - l] == board[i][j])
                        return board[i][j];
                }
            }
        }
        // direction: "\"
        for (i = 0; i <= m - k; ++i) {
            for (j = 0; j <= n - k; ++j) {
                for (l = 1; l < k; ++l) {
                    if (board[i][j] == 0 || board[i + l][j + l] != board[i][j])
                        break;
                    if (l == k - 1 && board[i + l][j + l] == board[i][j])
                        return board[i][j];
                }
            }
        }

        if (isTie())
            return TIE;
        else
            return NONE;
    }

    void countPossibleMoves() const {
        int possibleMovesCount = 0;
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                if (board[i][j] == 0)
                    possibleMovesCount++;
        printf("%d\n", possibleMovesCount);
    }

    void printPossibleMoves() {
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] == 0) {
                    board[i][j] = activePlayer;
                    printBoard();
                    board[i][j] = 0;
                }
            }
        }
    }

    void genAllMoves() {
        if (checkWin() != NONE) {
            printf("0\n");
            return;
        }

        countPossibleMoves();
        printPossibleMoves();
    }

    void genAllMovesCutIfOver() {
        if (checkWin() != NONE) {
            printf("0\n");
            return;
        }

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] == 0) {
                    board[i][j] = activePlayer;
                    if (checkWin() == activePlayer) {
                        printf("1\n");
                        printBoard();
                        return;
                    }
                    board[i][j] = 0;
                }
            }
        }

        countPossibleMoves();
        printPossibleMoves();
    }

    static void printWhoWon(const int& who) {
        if (who == 1)
            printf("FIRST_PLAYER_WINS\n");
        else if (who == 2)
            printf("SECOND_PLAYER_WINS\n");
        else if (who == TIE)
            printf("BOTH_PLAYERS_TIE\n");
    }

    void solveGame() {
        int result = minimax(true);

        if (result == WON)
            printWhoWon(activePlayer);
        else if (result == LOST)
            printWhoWon(getOpponent());
        else if (result == TIE)
            printWhoWon(TIE);
    }

    int minimax(bool isMaximazing) {
        int whoWon = checkWin();
        if (whoWon != NONE) {
            if (whoWon == TIE)
                return TIE;
            else if (whoWon == activePlayer)
                return WON;
            else
                return LOST;
        }

        if (isMaximazing) {
            int bestVal = MIN;
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (board[i][j] == 0) {
                        board[i][j] = activePlayer;
                        int moveVal = minimax(false);
                        board[i][j] = 0;

                        if (moveVal == WON) {
                            return moveVal;
                        }

                        if (moveVal > bestVal)
                            bestVal = moveVal;
                    }
                }
            }
            return bestVal;
        }
        else {
            int bestVal = MAX;
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (board[i][j] == 0) {
                        board[i][j] = getOpponent();
                        int moveVal = minimax(true);
                        board[i][j] = 0;

                        if (moveVal == LOST) {
                            return moveVal;
                        }

                        if (moveVal < bestVal)
                            bestVal = moveVal;
                    }
                }
            }
            return bestVal;
        }
    }
};



int main() {
    char command[MAX_COMMAND];

    Game game;

    while (scanf_s("%s", command, MAX_COMMAND) != EOF) {
        scanf_s("%d %d %d %d", &(game.m), &(game.n), &(game.k), &(game.activePlayer));

        game.allocateBoard();
        game.scanBoard();

        if (strcmp(command, "GEN_ALL_POS_MOV") == 0) {
            game.genAllMoves();
        }
        else if (strcmp(command, "GEN_ALL_POS_MOV_CUT_IF_GAME_OVER") == 0) {
            game.genAllMovesCutIfOver();
        }
        else if (strcmp(command, "SOLVE_GAME_STATE") == 0) {
            game.solveGame();
        }

        game.deallocateBoard();
    }
}