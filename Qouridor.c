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