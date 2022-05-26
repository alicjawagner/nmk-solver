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

    //returns NONE or who
    int checkPreWin(const int& who) const {

        bool isWidthMoreThanK = false, isHeightMoreThanK = false;
        if (n > k)
            isWidthMoreThanK = true;
        if (m > k)
            isHeightMoreThanK = true;

        int i, j, l;

        //horizontal
        if (isWidthMoreThanK) {
            for (i = 0; i < m; ++i) {
                for (j = 1; j <= n - k; ++j) {
                    if (board[i][j] != who)
                        continue;

                    for (l = 1; l < k - 1; ++l) {
                        if (board[i][j + l] != who)
                            break;
                        if (l == k - 2)
                            if (board[i][j - 1] == 0 && board[i][j + l + 1] == 0)
                                return who;
                    }
                }
            }
        }

        //vertical
        if (isHeightMoreThanK) {
            for (j = 0; j < n; ++j) {
                for (i = 1; i <= m - k; ++i) {
                    if (board[i][j] != who)
                        continue;

                    for (l = 1; l < k - 1; ++l) {
                        if (board[i + l][j] != who)
                            break;
                        if (l == k - 2)
                            if (board[i - 1][j] == 0 && board[i + l + 1][j] == 0)
                                return who;
                    }
                }
            }
        }

        //diagonal
        if (isWidthMoreThanK && isHeightMoreThanK) {
            // direction: "/"
            for (i = 1; i <= m - k; ++i) {
                for (j = k - 1; j < n - 1; ++j) {
                    if (board[i][j] != who)
                        continue;

                    for (l = 1; l < k - 1; ++l) {
                        if (board[i + l][j - l] != who)
                            break;
                        if (l == k - 2)
                            if (board[i - 1][j + 1] == 0 && board[i + l + 1][j - l - 1] == 0)
                                return who;
                    }
                }
            }

            // direction: "\"
            for (i = 1; i <= m - k; ++i) {
                for (j = 1; j <= n - k; ++j) {
                    if (board[i][j] != who)
                        continue;

                    for (l = 1; l < k - 1; ++l) {
                        if (board[i + l][j + l] != who)
                            break;
                        if (l == k - 2)
                            if (board[i - 1][j - 1] == 0 && board[i + l + 1][j + l + 1] == 0)
                                return who;
                    }
                }
            }
        }

        return NONE;
    }

    int checkWin() const {
        int i, j, l, who;

        //horizontal
        for (i = 0; i < m; ++i) {
            for (j = 0; j <= n - k; ++j) {
                who = board[i][j];
                if (who == 0)
                    continue;

                for (l = 1; l < k; ++l) {
                    if (board[i][j + l] != who)
                        break;
                    if (l == k - 1)
                        return who;
                }
            }
        }

        //vertical
        for (j = 0; j < n; ++j) {
            for (i = 0; i <= m - k; ++i) {
                who = board[i][j];
                if (who == 0)
                    continue;

                for (l = 1; l < k; ++l) {
                    if (board[i + l][j] != who)
                        break;
                    if (l == k - 1)
                        return who;
                }
            }
        }

        //diagonal
        // direction: "/"
        for (i = 0; i <= m - k; ++i) {
            for (j = k - 1; j < n; ++j) {
                who = board[i][j];
                if (who == 0)
                    continue;

                for (l = 1; l < k; ++l) {
                    if (board[i + l][j - l] != who)
                        break;
                    if (l == k - 1)
                        return who;
                }
            }
        }
        // direction: "\"
        for (i = 0; i <= m - k; ++i) {
            for (j = 0; j <= n - k; ++j) {
                who = board[i][j];
                if (who == 0)
                    continue;

                for (l = 1; l < k; ++l) {
                    if (board[i + l][j + l] != who)
                        break;
                    if (l == k - 1)
                        return who;
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
        int opponent = getOpponent();
        if (isMaximazing) {
            if (checkPreWin(activePlayer) == activePlayer)
                return WON;
        }
        else {
            if (checkPreWin(opponent) == opponent)
                return LOST;
        }

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

                        if (moveVal > bestVal)
                            bestVal = moveVal;

                        if (moveVal == WON) {
                            return bestVal;
                        }
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
                        board[i][j] = opponent;
                        int moveVal = minimax(true);
                        board[i][j] = 0;

                        if (moveVal < bestVal)
                            bestVal = moveVal;

                        if (moveVal == LOST) {
                            return bestVal;
                        }
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