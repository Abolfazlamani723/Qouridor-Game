#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
ALLEGRO_EVENT_QUEUE* event_queue = NULL;
ALLEGRO_EVENT ev;
#define CELLSIZE 10
#define max_len 29
int mouseButton;
struct BOARD {
    int board[max_len][max_len];
    int length;
};
struct PLAYER {
    int term;
    int countWall[1][2];
    int pieceCoordinate[8];
};

struct Coordinate {
    int row;
    int col;
};

typedef struct {
    struct Coordinate coord;
    int direction;  // 0: up, 1: down, 2: left, 3: right
} StackItem;
void movePiecePossiblities(struct BOARD* data, struct PLAYER* player) {
    int i = player->pieceCoordinate[2 * (player->term - 1)];
    int j = player->pieceCoordinate[2 * (player->term - 1) + 1];
    if (data->board[i - 1][j] != 7 && data->board[i - 2][j] == 5) {//move up
        data->board[i - 2][j] = 6;
    }
    if (data->board[i + 1][j] != 7 && data->board[i + 2][j] == 5) {//move down
        data->board[i + 2][j] = 6;
    }
    if (data->board[i][j - 1] != 7 && data->board[i][j - 2] == 5) {//move left
        data->board[i][j - 2] = 6;
    }
    if (data->board[i][j + 1] != 7 && data->board[i][j + 2] == 5) {//move right
        data->board[i][j + 2] = 6;
    }

}
void movePiecePossiblities(struct BOARD* data, struct PLAYER* player) {
    int i = player->pieceCoordinate[2 * (player->term - 1)];
    int j = player->pieceCoordinate[2 * (player->term - 1) + 1];
    if (data->board[i - 1][j] != 7 && data->board[i - 2][j] == 5) {//move up
        data->board[i - 2][j] = 6;
    }
    if (data->board[i + 1][j] != 7 && data->board[i + 2][j] == 5) {//move down
        data->board[i + 2][j] = 6;
    }
    if (data->board[i][j - 1] != 7 && data->board[i][j - 2] == 5) {//move left
        data->board[i][j - 2] = 6;
    }
    if (data->board[i][j + 1] != 7 && data->board[i][j + 2] == 5) {//move right
        data->board[i][j + 2] = 6;
    }

}
void movePiecePossiblitiesJump(struct BOARD* data, struct PLAYER* player) {
    //printf("movePiecePossiblitiesJump\n");
    int i = player->pieceCoordinate[2 * (player->term - 1)];
    int j = player->pieceCoordinate[2 * (player->term - 1) + 1];
    if (data->board[i - 1][j] != 7 && data->board[i - 2][j] >= 1 && data->board[i - 2][j] < 5 && data->board[i - 4][j] == 5 && data->board[i - 3][j] != 7) {//move up
        data->board[i - 4][j] = 6;
    }
    if (data->board[i + 1][j] != 7 && data->board[i + 2][j] >= 1 && data->board[i + 2][j] < 5 && data->board[i + 4][j] == 5 && data->board[i + 3][j] != 7) {//move down
        data->board[i + 4][j] = 6;
    }
    if (data->board[i][j - 1] != 7 && data->board[i][j - 2] >= 1 && data->board[i][j - 2] < 5 && data->board[i][j - 4] == 5 && data->board[i][j - 3] != 7) {//move left
        data->board[i][j - 4] = 6;
    }
    if (data->board[i][j + 1] != 7 && data->board[i][j + 2] >= 1 && data->board[i][j + 2] < 5 && data->board[i][j + 4] == 5 && data->board[i][j + 3] != 7) {//move right
        data->board[i][j + 4] = 6;
    }

}

void movePiecePossiblitiesParties(struct BOARD* data, struct PLAYER* player) {
    //printf("%d\n", player->term);
    int i = player->pieceCoordinate[2 * (player->term - 1)];
    int j = player->pieceCoordinate[2 * (player->term - 1) + 1];
    printf("%d\t%d\n", i, j);
    if (data->board[i - 1][j] != 7 && data->board[i - 2][j] >= 1 && data->board[i - 2][j] < 5 && data->board[i - 3][j] == 7 && data->board[i - 2][j + 1] != 7 && data->board[i - 2][j + 2] == 5) {//move up + right
        data->board[i - 2][j + 2] = 6;
    }
    if (data->board[i - 1][j] != 7 && data->board[i - 2][j] >= 1 && data->board[i - 2][j] < 5 && data->board[i - 3][j] == 7 && data->board[i - 2][j - 1] != 7 && data->board[i - 2][j - 2] == 5) {//move up + left
        //printf("Abolfazl");
        data->board[i - 2][j - 2] = 6;
    }
    if (data->board[i + 1][j] != 7 && data->board[i + 2][j] >= 1 && data->board[i + 2][j] < 5 && data->board[i + 3][j] == 7 && data->board[i + 2][j + 1] != 7 && data->board[i + 2][j + 2] == 5) {//move down + right
        data->board[i + 2][j + 2] = 6;
    }if (data->board[i + 1][j] != 7 && data->board[i + 2][j] >= 1 && data->board[i + 2][j] < 5 && data->board[i + 3][j] == 7 && data->board[i + 2][j - 1] != 7 && data->board[i + 2][j - 2] == 5) {//move down + left
        data->board[i + 2][j - 2] = 6;
    }
    if (data->board[i][j + 1] != 7 && data->board[i][j + 2] >= 1 && data->board[i][j + 2] < 5 && data->board[i][j + 3] == 7 && data->board[i - 1][j + 2] != 7 && data->board[i - 2][j + 2] == 5) {//move right + up
        data->board[i - 2][j + 2] = 6;
    }
    if (data->board[i][j + 1] != 7 && data->board[i][j + 2] >= 1 && data->board[i][j + 2] < 5 && data->board[i][j + 3] == 7 && data->board[i + 1][j + 2] != 7 && data->board[i + 2][j + 2] == 5) {//move right + down
        data->board[i + 2][j + 2] = 6;
    }
    if (data->board[i][j - 1] != 7 && data->board[i][j - 2] >= 1 && data->board[i][j - 2] < 5 && data->board[i][j - 3] == 7 && data->board[i - 1][j - 2] != 7 && data->board[i - 2][j - 2] == 5) {//move left + right
        data->board[i - 2][j - 2] = 6;
    }
    if (data->board[i][j - 1] != 7 && data->board[i][j - 2] >= 1 && data->board[i][j - 2] < 5 && data->board[i][j - 3] == 7 && data->board[i - 1][j + 2] != 7 && data->board[i - 2][j + 2] == 5) {//move left + down
        data->board[i + 2][j - 2] = 6;
    }
}