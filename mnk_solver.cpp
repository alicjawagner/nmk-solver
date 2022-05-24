#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_COMMAND 33

enum Scores {
    WON = 1,
    LOST = -1,
    TIE = 0,
    NONE = 2
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

    int getOppositePlayer() const {
        if (activePlayer == 1)
            return 2;
        else
            return 1;
    }

    int checkWin(const bool& forMe) const {
        int forWho;
        if (forMe)
            forWho = activePlayer;
        else
            forWho = getOppositePlayer();
        
        int i, j, l;

        //horizontal
        for (i = 0; i < m; ++i) {
            for (j = 0; j <= n - k; ++j) {
                for (l = 0; l < k; ++l) {
                    if (l == k - 1 && board[i][j + l] == forWho)
                        return WON;
                    if (board[i][j + l] != forWho)
                        break;
                }
            }
        }
        
        //vertical
        for (j = 0; j < n; ++j) {
            for (i = 0; i <= m - k; ++i) {
                for (l = 0; l < k; ++l) {
                    if (l == k - 1 && board[i + l][j] == forWho)
                        return WON;
                    if (board[i + l][j] != forWho)
                        break;
                }
            }
        }

        //diagonal
        // direction: "/"
        for (i = 0; i <= m - k; ++i) {
            for (j = k - 1; j < n; ++j) {
                for (l = 0; l < k; ++l) {
                    if (l == k - 1 && board[i + l][j - l] == forWho)
                        return WON;
                    if (board[i + l][j - l] != forWho)
                        break;
                }
            }
        }
        // direction: "\"
        for (i = 0; i <= m - k; ++i) {
            for (j = 0; j <= n - k; ++j) {
                for (l = 0; l < k; ++l) {
                    if (l == k - 1 && board[i + l][j + l] == forWho)
                        return WON;
                    if (board[i + l][j + l] != forWho)
                        break;
                }
            }
        }

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
        if (checkWin(false) == WON) {
            printf("0\n");
            return;
        }

        countPossibleMoves();
        printPossibleMoves();
    }

    void genAllMovesCutIfOver() {
        if (checkWin(false) == WON) {
            printf("0\n");
            return;
        }

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] == 0) {
                    board[i][j] = activePlayer;
                    if (checkWin(true) == WON) {
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
            //solve game
        }

        game.deallocateBoard();
    }
}