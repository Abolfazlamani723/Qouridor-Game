
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

ALLEGRO_EVENT_QUEUE* event_queue = NULL;
ALLEGRO_EVENT ev;
#define CELLSIZE 10
#define max_len 29
int mouseButton;
ALLEGRO_BITMAP* player1;
struct BOARD {
    int board[max_len][max_len];
    int length;
};
struct PLAYER {
    int term;
    int countWall[4];
    int pieceCoordinate[8];
};

struct CHARM {
    int delet_all_wall;
    int reduce_wall_2;
    int reduce_wall_3;
    int reduce_wall_5;
    int block;
};

struct PRESENT {
    int increas_wall_2;
    int increas_wall_3;
    int increas_wall_5;
    int gain_wall_from_opponent_1;
    int gain_wall_from_opponent_2;
};
struct Button {
    int posX;
    int posY;
    int width;
    int height;
    char name[max_len];
};
typedef struct Button Button;
void initializeCharm(struct CHARM* charm) {
    charm->delet_all_wall = 2;
    charm->reduce_wall_2 = 10;
    charm->reduce_wall_3 = 5;
    charm->reduce_wall_5 = 3;
    charm->block = 7;
}

void initializePresent(struct PRESENT* present) {
    present->increas_wall_2 = 10;
    present->increas_wall_3 = 5;
    present->increas_wall_5 = 3;
    present->gain_wall_from_opponent_1 = 12;
    present->gain_wall_from_opponent_1 = 6;
}

void luck_charm(struct BOARD* data, struct PLAYER* player, struct CHARM* charm) {
    srand(time(NULL));

    int chooseCharm = rand() % 5;

    if (chooseCharm == 0 && charm->delet_all_wall >= 0) { // delete all walls
        for (int i = 0; i < 2 * data->length - 1; i++) {
            for (int j = 0; j < 2 * data->length - 1; j++) {
                if (i % 2 == 1 || j % 2 == 1) {
                    data->board[i][j] = 0;
                    if (i % 2 == 1 && j % 2 == 1) {
                        data->board[i][j] = 9;
                    }
                }
            }
        }

        charm->delet_all_wall--;
        printf("");
    }
    else if (chooseCharm == 1 && charm->reduce_wall_2 >= 0) { // reduce 2 walls
        player->countWall[player->term - 1] -= 2;
        charm->reduce_wall_2--;
        printf("reduce 2 walls\n");
    }
    else if (chooseCharm == 2 && charm->reduce_wall_3 >= 0) { // reduce 3 walls
        player->countWall[player->term - 1] -= 3;
        charm->reduce_wall_3--;
        printf("reduce 3 walls\n");
    }
    else if (chooseCharm == 3 && charm->reduce_wall_5 >= 0) { // reduce 5 walls
        player->countWall[player->term - 1] -= 5;
        charm->reduce_wall_5--;
        printf("reduce 5 walls\n");
    }
    else if (chooseCharm == 4 && charm->block >= 0) { // blocking the player
        player->term++;
        charm->block--;
        printf("blocking the player\n");
    }

}

void luck_present(struct BOARD* data, struct PLAYER* player, struct PRESENT* present, int Multiplayer) {
    srand(time(NULL));
    int choosePresent = rand() % 5;

    if (choosePresent == 0 && present->increas_wall_2 >= 0) { // increas 2 walls
        player->countWall[player->term - 1] += 2;
        present->increas_wall_2--;
        printf("increas 2 walls\n");
    }
    else if (choosePresent == 1 && present->increas_wall_3) { // increas 3 walls
        player->countWall[player->term - 1] += 3;
        present->increas_wall_3--;
        printf("increas 3 walls\n");
    }
    else if (choosePresent == 2 && present->increas_wall_5 >= 0) { // increas 5 walls
        player->countWall[player->term - 1] += 5;
        present->increas_wall_5--;
        printf("increas 5 walls\n");
    }
    else if (choosePresent == 3 && present->gain_wall_from_opponent_1 >= 0) { // gain 1 wall from opponent
        if (Multiplayer == 4) {
            if (player->term == 4) {
                player->countWall[3]++;
                player->countWall[0]--;
            }
            else {
                player->countWall[player->term - 1]++;
                player->countWall[player->term]--;
            }
        }
        else if (Multiplayer == 2) {
            if (player->term == 2) {
                player->countWall[1]++;
                player->countWall[0]--;
            }
            else {
                player->countWall[0]++;
                player->countWall[1]--;
            }
        }
        present->gain_wall_from_opponent_1--;
        printf("gain 1 wall from opponent\n");

    }
    else if (choosePresent == 4 && present->gain_wall_from_opponent_2 >= 0) { // gain 2 wals from opponent
        if (Multiplayer == 4) {
            if (player->term == 4) {
                player->countWall[3] += 2;
                player->countWall[0] -= 2;
            }
            else {
                player->countWall[player->term - 1] += 2;
                player->countWall[player->term] -= 2;
            }
        }
        else if (Multiplayer == 2) {
            if (player->term == 2) {
                player->countWall[1] += 2;
                player->countWall[0] -= 2;
            }
            else {
                player->countWall[0] += 2;
                player->countWall[1] -= 2;
            }
        }
        present->gain_wall_from_opponent_1--;
        printf("gain 2 wall from opponent\n");
    }
}

void luck(struct BOARD* data, struct PLAYER* player, struct CHARM* charm, struct PRESENT* present, int Multiplayer) {
    printf("luck");
    srand(time(NULL));
    int choice = rand() % 2;

    if (choice == 0) { // charm
        luck_charm(data, player, charm);
    }
    else if (choice == 1) {
        luck_present(data, player, present, Multiplayer);
    }
}

void makePrimaryBoard(struct BOARD* data) {
    //printf("%d", data->length);
    for (int i = 0; i < data->length * 2; i++) {
        for (int j = 0; j < data->length * 2; j++) {
            if (i % 2 == 0 && j % 2 == 0) data->board[i][j] = 5; // place for pieces 
            else if (i % 2 == 1 && j % 2 == 1) data->board[i][j] = 9;
            else data->board[i][j] = 0;
        }
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
    //printf("%d\t%d\n", i, j);
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
void showBoard(struct BOARD data) {
    al_clear_to_color(al_map_rgb(144, 202, 249));
    al_draw_filled_rectangle((5 * data.length + 1) * CELLSIZE, 0, (5 * data.length + 1) * CELLSIZE + 20 * CELLSIZE, (5 * data.length + 1) * CELLSIZE, al_map_rgb(38, 50, 56));
    for (int i = 0; i < data.length * 2; i++) {
        for (int j = 0; j < data.length * 2; j++) {
            if (data.board[i][j] == 5 && i % 2 == 0 && j % 2 == 0) {
                int Xpiece = ((j / 2) * 5 + 1) * CELLSIZE;
                int Ypiece = ((i / 2) * 5 + 1) * CELLSIZE;
                int widthPiece = 4 * CELLSIZE;
                int heightPiece = 4 * CELLSIZE;

                al_draw_filled_rectangle(Xpiece, Ypiece, Xpiece + widthPiece, Ypiece + heightPiece, al_map_rgb(0, 150, 136));
            }
            else if (j % 2 == 0 && data.board[i][j] == 7 && (data.board[i][j + 2] == 7 || data.board[i][j - 2] == 7)) { // horizontal walls
                int wallX = ((j / 2) * 5 + 1) * CELLSIZE;
                int wallY = (i / 2 + 1) * 5 * CELLSIZE;
                int widthWall = (4 * CELLSIZE);
                int heightWall = CELLSIZE;
                al_draw_filled_rectangle(wallX, wallY, wallX + widthWall, wallY + heightWall, al_map_rgb(255, 0, 0));
            }
            else if (i % 2 == 0 && data.board[i][j] == 7 && (data.board[i + 2][j] == 7 || data.board[i - 2][j] == 7)) { // vertical walls
                int Xwall = (j / 2 + 1) * 5 * CELLSIZE;
                int Ywall = ((i / 2) * 5 + 1) * CELLSIZE;
                int widthWall = CELLSIZE;
                int heightWall = (4 * CELLSIZE);
                al_draw_filled_rectangle(Xwall, Ywall, Xwall + widthWall, Ywall + heightWall, al_map_rgb(255, 0, 0));
            }
            else if (i % 2 == 1 && j % 2 == 1 && data.board[i][j] == 7) {
                int Xwall = ((j + 1) / 2) * 5 * CELLSIZE;
                int Ywall = ((i + 1) / 2) * 5 * CELLSIZE;
                int widthWall = CELLSIZE;
                int heightWall = CELLSIZE;

                al_draw_filled_rectangle(Xwall, Ywall, Xwall + widthWall, Ywall + heightWall, al_map_rgb(255, 0, 0));

            }
            else if (data.board[i][j] == 1) {
                int Xpiece = ((j / 2) * 5 + 1) * CELLSIZE;
                int Ypiece = ((i / 2) * 5 + 1) * CELLSIZE;
                int widthPiece = 4 * CELLSIZE;
                int heightPiece = 4 * CELLSIZE;

                al_draw_filled_rectangle(Xpiece, Ypiece, Xpiece + widthPiece, Ypiece + heightPiece, al_map_rgb(0, 150, 136));
                float centerX = ((j / 2) * 5 + 3) * CELLSIZE;
                float centerY = ((i / 2) * 5 + 3) * CELLSIZE;
                float redius = (3 * CELLSIZE) / 2;
                //al_draw_filled_circle(centerX, centerY, redius, al_map_rgb(255, 0, 0));
                al_draw_scaled_bitmap(player1, 0, 0, al_get_bitmap_width(player1), al_get_bitmap_height(player1), Xpiece, Ypiece, widthPiece, heightPiece, 0);
            }
            else if (data.board[i][j] == 2) {
                int Xpiece = ((j / 2) * 5 + 1) * CELLSIZE;
                int Ypiece = ((i / 2) * 5 + 1) * CELLSIZE;
                int widthPiece = 4 * CELLSIZE;
                int heightPiece = 4 * CELLSIZE;

                al_draw_filled_rectangle(Xpiece, Ypiece, Xpiece + widthPiece, Ypiece + heightPiece, al_map_rgb(0, 150, 136));
                float centerX = ((j / 2) * 5 + 3) * CELLSIZE;
                float centerY = ((i / 2) * 5 + 3) * CELLSIZE;
                float redius = (3 * CELLSIZE) / 2;
                al_draw_filled_circle(centerX, centerY, redius, al_map_rgb(0, 0, 255));
            }
            else if (data.board[i][j] == 3) {
                int Xpiece = ((j / 2) * 5 + 1) * CELLSIZE;
                int Ypiece = ((i / 2) * 5 + 1) * CELLSIZE;
                int widthPiece = 4 * CELLSIZE;
                int heightPiece = 4 * CELLSIZE;

                al_draw_filled_rectangle(Xpiece, Ypiece, Xpiece + widthPiece, Ypiece + heightPiece, al_map_rgb(0, 150, 136));
                float centerX = ((j / 2) * 5 + 3) * CELLSIZE;
                float centerY = ((i / 2) * 5 + 3) * CELLSIZE;
                float redius = (3 * CELLSIZE) / 2;
                al_draw_filled_circle(centerX, centerY, redius, al_map_rgb(0, 255, 0));
            }
            else if (data.board[i][j] == 4) {
                int Xpiece = ((j / 2) * 5 + 1) * CELLSIZE;
                int Ypiece = ((i / 2) * 5 + 1) * CELLSIZE;
                int widthPiece = 4 * CELLSIZE;
                int heightPiece = 4 * CELLSIZE;

                al_draw_filled_rectangle(Xpiece, Ypiece, Xpiece + widthPiece, Ypiece + heightPiece, al_map_rgb(0, 150, 136));
                float centerX = ((j / 2) * 5 + 3) * CELLSIZE;
                float centerY = ((i / 2) * 5 + 3) * CELLSIZE;
                float redius = (3 * CELLSIZE) / 2;
                al_draw_filled_circle(centerX, centerY, redius, al_map_rgb(023, 45, 123));
            }
            else if (data.board[i][j] == 6 && i % 2 == 0 && j % 2 == 0) {
                int Xpiece = ((j / 2) * 5 + 1) * CELLSIZE;
                int Ypiece = ((i / 2) * 5 + 1) * CELLSIZE;
                int widthPiece = 4 * CELLSIZE;
                int heightPiece = 4 * CELLSIZE;

                al_draw_filled_rectangle(Xpiece, Ypiece, Xpiece + widthPiece, Ypiece + heightPiece, al_map_rgb(0, 150, 136));
                int centerX = ((j / 2) * 5 + 3) * CELLSIZE;
                int centerY = ((i / 2) * 5 + 3) * CELLSIZE;
                float redius = (3 * CELLSIZE) / 2;

                al_draw_filled_circle(centerX, centerY, redius, al_map_rgb(224, 224, 224));
            }
            else if (j % 2 == 0 && data.board[i][j] == 0) { // horizontal walls
                int wallX = ((j / 2) * 5 + 1) * CELLSIZE;
                int wallY = (i / 2 + 1) * 5 * CELLSIZE;
                int widthWall = (4 * CELLSIZE);
                int heightWall = CELLSIZE;
                al_draw_filled_rectangle(wallX, wallY, wallX + widthWall, wallY + heightWall, al_map_rgb(144, 202, 249));
            }
            else if (i % 2 == 0 && data.board[i][j] == 0) { // vertical walls
                int Xwall = (j / 2 + 1) * 5 * CELLSIZE;
                int Ywall = ((i / 2) * 5 + 1) * CELLSIZE;
                int widthWall = CELLSIZE;
                int heightWall = (4 * CELLSIZE);
                al_draw_filled_rectangle(Xwall, Ywall, Xwall + widthWall, Ywall + heightWall, al_map_rgb(144, 202, 249));
            }
            else if (i % 2 == 1 && j % 2 == 1 && data.board[i][j] == 0) {
                int Xwall = ((j + 1) / 2) * 5 * CELLSIZE;
                int Ywall = ((i + 1) / 2) * 5 * CELLSIZE;
                int widthWall = CELLSIZE;
                int heightWall = CELLSIZE;

                al_draw_filled_rectangle(Xwall, Ywall, Xwall + widthWall, Ywall + heightWall, al_map_rgb(144, 202, 249));

            }
        }
    }
}

int calculatePieceCoordinate(float number, int length) {
    int i = 0;
    while (25 * i + 50 <= (5 * length + 1) * 10) {
        if (number > 25 * i + 10 && number < 25 * i + 50) return i;
        if (number > 25 * i + 50 && number < 25 * i + 60) return -1;
        i += 2;
    }
    return -1;
}

int find_HoV(float X, float Y, int length) {//This function show horizontal and vertical for walls.
    //squares for pieces
    if (calculatePieceCoordinate(X, length) >= 0 && calculatePieceCoordinate(Y, length) >= 0) return 0;

    // squares between walls
    if (calculatePieceCoordinate(X, length) == -1 && calculatePieceCoordinate(Y, length) == -1) return 1;

    // vertical walls
    if (calculatePieceCoordinate(X, length) == -1 && calculatePieceCoordinate(Y, length) >= 0) return 2;

    // horizontal walls
    if (calculatePieceCoordinate(X, length) >= 0 && calculatePieceCoordinate(Y, length) == -1) return 3;
}
int calculateWallCoordinate(float number, int length, int HoV, char XoY) {
    if (HoV == 0) return -1;
    else if (HoV == 1) {
        int a;
        a = (int)number / 50;
        return (2 * a - 1);
    }
    else if (HoV == 2) {
        if (XoY == 'x') {
            int a;
            a = (int)number / 50;
            return (2 * a - 1);
        }
        else if (XoY == 'y') {
            int b;
            b = (int)number / 50;
            return (2 * b);
        }
    }
    else if (HoV == 3) {
        if (XoY == 'x') {
            int a;
            a = (int)number / 50;
            return (2 * a);
        }
        else if (XoY == 'y') {
            int b;
            b = (int)number / 50;
            return (2 * b - 1);
        }
    }
}
void movePiece(struct BOARD* data, struct PLAYER* player, ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_EVENT ev, int x_coordinate, int y_coordinate, bool *checkingPut) {
    
    float pos_X = x_coordinate, pos_Y = y_coordinate;
    
        
    
        
    if (data->board[calculatePieceCoordinate(pos_Y, data->length)][calculatePieceCoordinate(pos_X, data->length)] == 6 && calculatePieceCoordinate(pos_Y, data->length) != -1 && calculatePieceCoordinate(pos_X, data->length) != -1) {
        
        int coordinate_i = player->pieceCoordinate[(player->term - 1) * 2], coordinate_j = player->pieceCoordinate[(player->term - 1) * 2 + 1];
        data->board[coordinate_i][coordinate_j] = 5;
        data->board[calculatePieceCoordinate(pos_Y, data->length)][calculatePieceCoordinate(pos_X, data->length)] = player->term;
        player->pieceCoordinate[(player->term - 1) * 2] = calculatePieceCoordinate(pos_Y, data->length);

        player->pieceCoordinate[(player->term - 1) * 2 + 1] = calculatePieceCoordinate(pos_X, data->length);
        *checkingPut = 1;
    }
    
    

    for (register int i = 0; i < 2 * data->length; i++) {
        for (register int j = 0; j < 2 * data->length; j++) {
            if (data->board[i][j] == 6 && i % 2 == 0 && j % 2 == 0) data->board[i][j] = 5;
        }
        //printf("\n");
    }
    

}

struct Coordinate {
    int row;
    int col;
};

typedef struct {
    struct Coordinate coord;
    int direction;  // 0: up, 1: down, 2: left, 3: right
} StackItem;

StackItem pop(StackItem stack[], int* top) {
    if (*top >= 0) {
        return stack[(*top)--];
    }
    else {
        printf("Stack underflow!\n");
        exit(EXIT_FAILURE);
    }
}

void push(StackItem stack[], int* top, StackItem item) {
    if (*top < max_len * max_len - 1) {
        stack[++(*top)] = item;
    }
    else {
        printf("Stack overflow!\n");
        exit(EXIT_FAILURE);
    }
    //pop(stack, &top);
}



bool isEmpty(int top) {
    return top == -1;
}

bool isValidMove(struct BOARD data, int row, int col) {
    return (row >= 0 && row < 2 * data.length - 1 && col >= 0 && col < 2 * data.length - 1 && (data.board[row][col] == 5 || data.board[row][col] == 0 || data.board[row][col] == 1 || data.board[row][col] == 2 || data.board[row][col] == 6 || data.board[row][col] == 3 || data.board[row][col] == 4));
}



int dfs_vertical(struct BOARD data, int term, int start_row, int start_col, int help[][max_len], int* index) {
    int validPlacementPiece1 = 0, validPlacementPiece2 = 0, validPlacementPiece3 = 0, validPlacementPiece4 = 0;
    StackItem stack[max_len * max_len];
    int top = -1;

    struct Coordinate start_coord = { start_row, start_col };
    StackItem start_item = { start_coord, 0 };

    push(stack, &top, start_item);


    //StackItem current = pop(stack, &top);
    while (!(isEmpty(top))) {

        StackItem current = pop(stack, &top);

        int row = current.coord.row;
        int col = current.coord.col;

        if (!help[row][col]) {
            help[row][col] = 1;  // Mark cell as visited
            //printf("Visited cell: (%d, %d)\n", row, col);

            // Push unvisited neighbors onto the stack
            for (int i = 3; i >= 0; i--) {
                StackItem neighbor;
                neighbor.direction = i;

                switch (i) {
                case 0:  // Up
                    neighbor.coord.row = row - 1;
                    neighbor.coord.col = col;
                    break;
                case 1:  // Down
                    neighbor.coord.row = row + 1;
                    neighbor.coord.col = col;
                    break;
                case 2:  // Left
                    neighbor.coord.row = row;
                    neighbor.coord.col = col - 1;
                    break;
                case 3:  // Right
                    neighbor.coord.row = row;
                    neighbor.coord.col = col + 1;
                    break;
                }

                if (isValidMove(data, neighbor.coord.row, neighbor.coord.col)) {

                    push(stack, &top, neighbor);

                }
            }
        }
        if (term == 1) {
            for (int i = 0; i < 2 * data.length - 1; i += 2) {
                if (help[2 * data.length - 2][i] == 1) {
                    //printf("Yes1\n");
                    *index = 1;
                    top = -1;
                    return;
                }
            }
        }
        else if (term == 2) {
            for (int i = 0; i < 2 * data.length - 1; i += 2) {
                if (help[0][i] == 1) {
                    // printf("Yes2\n");
                    *index = 1;
                    top = -1;
                    return;
                }
            }
        }
        else if (term == 3) {
            for (int i = 0; i < 2 * data.length - 1; i += 2) {
                if (help[i][2 * data.length - 2] == 1) {
                    //printf("Yes3\n");
                    *index = 1;
                    top = -1;
                    return;
                }
            }
        }
        else if (term == 4) {
            for (int i = 0; i < 2 * data.length - 1; i += 2) {
                if (help[i][0] == 1) {
                    //printf("Yes4\n");
                    *index = 1;
                    top = -1;
                    return;
                }
            }
        }

    }

    printf("No\n");
    *index = 0;
    top = -1;

}


void delete_wall(struct BOARD* data) {
    for (register int i = 0; i < 2 * data->length; i++) {
        for (int j = 0; j < 2 * data->length; j++) {
            if (data->board[i][j] == 8) data->board[i][j] = 0;
            if (data->board[i][j] == 10) data->board[i][j] = 9;
        }
    }
}
void putWalls(struct BOARD* data, struct PLAYER* player, ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_EVENT ev, int* go, int Multiplayer, int x_coodinate, int y_coordinate, bool submit, bool *checkingPut) {
    
    int HoV;
    float pos_X = -1, pos_Y = -1;
    int i = 0;
    
        
        
    if (!submit){
        delete_wall(data);
        pos_X = x_coodinate;
        pos_Y = y_coordinate;
        HoV = find_HoV(pos_X, pos_Y, data->length);
        if (pos_X > 10 && pos_Y > 10 && pos_X <= 50 * data->length - 10 && pos_Y <= 50 * data->length - 10 && (HoV == 2 || HoV == 3)) {
            HoV = find_HoV(pos_X, pos_Y, data->length);
            int index_i = calculateWallCoordinate(pos_Y, data->length, HoV, 'y'), index_j = calculateWallCoordinate(pos_X, data->length, HoV, 'x');
            if (HoV == 2) {//vertical wall
                if (index_i == 0 && data->board[index_i][index_j] != 7 && data->board[index_i - 1][index_j] != 7 && data->board[index_i - 2][index_j] != 7 && index_i + 1 < 2 * data->length) {

                    if (data->board[index_i][index_j] != 7) {
                        data->board[index_i][index_j] = 8;
                    }

                    if (data->board[index_i + 1][index_j] != 7) {
                        data->board[index_i + 1][index_j] = 10;
                    }

                    if (data->board[index_i + 2][index_j] != 7) {
                        data->board[index_i + 2][index_j] = 8;
                    }

                }
                else if (index_i > 0 && data->board[index_i][index_j] != 7  /* && data->board[index_i - 1][index_j] != 7 */ && data->board[index_i - 2][index_j] != 7 && index_i + 1 < 2 * data->length && (data->board[index_i - 1][index_j] != 7 || data->board[index_i - 1][index_j + 1] == 7)) {
                    if (data->board[index_i][index_j] != 7) {
                        data->board[index_i][index_j] = 8;
                    }

                    if (data->board[index_i - 1][index_j] != 7) {
                        data->board[index_i - 1][index_j] = 10;
                    }

                    if (data->board[index_i - 2][index_j] != 7) {
                        data->board[index_i - 2][index_j] = 8;
                    }

                }
            }
            else if (HoV == 3) {//horizontal wall
                if (index_j == 0 && data->board[index_i][index_j] != 7 && data->board[index_i][index_j + 1] != 7 && data->board[index_i][index_j + 2] != 7 && index_j + 1 < 2 * data->length) {
                    if (data->board[index_i][index_j] != 7) {
                        data->board[index_i][index_j] = 8;
                    }

                    if (data->board[index_i][index_j + 1] != 7) {
                        data->board[index_i][index_j + 1] = 10;
                    }

                    if (data->board[index_i][index_j + 2] != 7) {
                        data->board[index_i][index_j + 2] = 8;
                    }

                }
                else if (index_j > 0 && data->board[index_i][index_j] != 7 && /*data->board[index_i][index_j - 1] != 7 &&*/ data->board[index_i][index_j - 2] != 7 && index_j + 1 < 2 * data->length && (data->board[index_i][index_j - 1] != 7 || data->board[index_i - 1][index_j - 1] == 7)) {
                    if (data->board[index_i][index_j] != 7) {
                        data->board[index_i][index_j] = 8;
                    }

                    if (data->board[index_i][index_j - 1] != 7) {
                        data->board[index_i][index_j - 1] = 10;
                    }

                    if (data->board[index_i][index_j - 2] != 7) {
                        data->board[index_i][index_j - 2] = 8;
                    }

                }
            }
            int validPlacementPiece1 = 0, validPlacementPiece2 = 0, validPlacementPiece3 = 0, validPlacementPiece4 = 0;
            int help[max_len][max_len];
            if (Multiplayer == 4) {
                validPlacementPiece1 = validPlacementPiece2 = validPlacementPiece3 = validPlacementPiece4 = 0;

                memset(help, 0, sizeof(help));
                dfs_vertical(*data, 1, player->pieceCoordinate[0], player->pieceCoordinate[1], help, &validPlacementPiece1);
                memset(help, 0, sizeof(help));
                dfs_vertical(*data, 2, player->pieceCoordinate[2], player->pieceCoordinate[3], help, &validPlacementPiece2);
                memset(help, 0, sizeof(help));
                dfs_vertical(*data, 3, player->pieceCoordinate[4], player->pieceCoordinate[5], help, &validPlacementPiece3);
                memset(help, 0, sizeof(help));
                dfs_vertical(*data, 4, player->pieceCoordinate[6], player->pieceCoordinate[7], help, &validPlacementPiece4);
            }
            else if (Multiplayer == 2) {
                validPlacementPiece1 = validPlacementPiece2 = 0;
                validPlacementPiece3 = validPlacementPiece4 = 1;

                memset(help, 0, sizeof(help));
                dfs_vertical(*data, 1, player->pieceCoordinate[0], player->pieceCoordinate[1], help, &validPlacementPiece1);
                memset(help, 0, sizeof(help));
                dfs_vertical(*data, 2, player->pieceCoordinate[2], player->pieceCoordinate[3], help, &validPlacementPiece2);
            }
            if (validPlacementPiece1 == 1 && validPlacementPiece2 == 1 && validPlacementPiece3 == 1 && validPlacementPiece4 == 1) {
                //printf("*******\n");

                if (HoV == 2) {//vertical wall
                    if (index_i == 0 && data->board[index_i][index_j] != 7 && data->board[index_i + 1][index_j] != 7 && data->board[index_i + 2][index_j] != 7 && index_i + 1 < 2 * data->length) {
                        /*if (data->board[index_i][index_j] != 7) {
                            data->board[index_i][index_j] = 8;
                        }*/

                        int Xwall = (index_j / 2 + 1) * 5 * CELLSIZE;
                        int Ywall = ((index_i / 2) * 5 + 1) * CELLSIZE;
                        int widthWall = CELLSIZE;
                        int heightWall = (4 * CELLSIZE);
                        al_draw_filled_rectangle(Xwall, Ywall, Xwall + widthWall, Ywall + heightWall, al_map_rgb(38, 50, 56));
                        /*if (data->board[index_i + 1][index_j] != 7) {
                            data->board[index_i + 1][index_j] = 8;
                        }*/
                        index_i++;
                        Xwall = ((index_j + 1) / 2) * 5 * CELLSIZE;
                        Ywall = ((index_i + 1) / 2) * 5 * CELLSIZE;
                        widthWall = CELLSIZE;
                        heightWall = CELLSIZE;

                        al_draw_filled_rectangle(Xwall, Ywall, Xwall + widthWall, Ywall + heightWall, al_map_rgb(38, 50, 56));
                        index_i--;
                        /*if (data->board[index_i + 2][index_j] != 7) {
                            data->board[index_i + 2][index_j] = 8;
                        }*/
                        index_i += 2;
                        Xwall = (index_j / 2 + 1) * 5 * CELLSIZE;
                        Ywall = ((index_i / 2) * 5 + 1) * CELLSIZE;
                        widthWall = CELLSIZE;
                        heightWall = (4 * CELLSIZE);
                        al_draw_filled_rectangle(Xwall, Ywall, Xwall + widthWall, Ywall + heightWall, al_map_rgb(38, 50, 56));
                        index_i -= 2;
                    }
                    else if (index_i > 0 && data->board[index_i][index_j] != 7  /* && data->board[index_i - 1][index_j] != 7 */ && data->board[index_i - 2][index_j] != 7 && index_i + 1 < 2 * data->length && (data->board[index_i - 1][index_j] != 7 || data->board[index_i - 1][index_j - 1] == 7)) {
                        /*if (data->board[index_i][index_j] != 7) {
                            data->board[index_i][index_j] = 8;
                        }*/
                        int Xwall = (index_j / 2 + 1) * 5 * CELLSIZE;
                        int Ywall = ((index_i / 2) * 5 + 1) * CELLSIZE;
                        int widthWall = CELLSIZE;
                        int heightWall = (4 * CELLSIZE);
                        al_draw_filled_rectangle(Xwall, Ywall, Xwall + widthWall, Ywall + heightWall, al_map_rgb(38, 50, 56));
                        /*if (data->board[index_i - 1][index_j] != 7) {
                            data->board[index_i - 1][index_j] = 8;
                        }*/
                        index_i--;
                        Xwall = ((index_j + 1) / 2) * 5 * CELLSIZE;
                        Ywall = ((index_i + 1) / 2) * 5 * CELLSIZE;
                        widthWall = CELLSIZE;
                        heightWall = CELLSIZE;

                        al_draw_filled_rectangle(Xwall, Ywall, Xwall + widthWall, Ywall + heightWall, al_map_rgb(38, 50, 56));
                        index_i++;
                        /*if (data->board[index_i - 2][index_j] != 7) {
                            data->board[index_i - 2][index_j] = 8;
                        }*/
                        index_i -= 2;
                        Xwall = (index_j / 2 + 1) * 5 * CELLSIZE;
                        Ywall = ((index_i / 2) * 5 + 1) * CELLSIZE;
                        widthWall = CELLSIZE;
                        heightWall = (4 * CELLSIZE);
                        al_draw_filled_rectangle(Xwall, Ywall, Xwall + widthWall, Ywall + heightWall, al_map_rgb(38, 50, 56));
                        index_i += 2;
                    }
                }
                else if (HoV == 3) {//horizontal wall
                    if (index_j == 0 && data->board[index_i][index_j] != 7  /* && data->board[index_i][index_j + 1] != 7 */ && data->board[index_i][index_j + 2] != 7 && index_j + 1 < 2 * data->length && (data->board[index_i][index_j + 1] != 7)) {
                        /*if (data->board[index_i][index_j] != 7) {
                            data->board[index_i][index_j] = 8;
                        }*/
                        int wallX = ((index_j / 2) * 5 + 1) * CELLSIZE;
                        int wallY = (index_i / 2 + 1) * 5 * CELLSIZE;
                        int widthWall = (4 * CELLSIZE);
                        int heightWall = CELLSIZE;
                        al_draw_filled_rectangle(wallX, wallY, wallX + widthWall, wallY + heightWall, al_map_rgb(38, 50, 56));
                        /*if (data->board[index_i][index_j + 1] != 7) {
                            data->board[index_i][index_j + 1] = 8;
                        }*/
                        index_j++;
                        wallX = ((index_j + 1) / 2) * 5 * CELLSIZE;
                        wallY = ((index_i + 1) / 2) * 5 * CELLSIZE;
                        widthWall = CELLSIZE;
                        heightWall = CELLSIZE;

                        al_draw_filled_rectangle(wallX, wallY, wallX + widthWall, wallY + heightWall, al_map_rgb(38, 50, 56));
                        index_j--;
                        /*if (data->board[index_i][index_j + 2] != 7) {
                            data->board[index_i][index_j + 2] = 8;
                        }*/
                        index_j += 2;
                        wallX = ((index_j / 2) * 5 + 1) * CELLSIZE;
                        wallY = (index_i / 2 + 1) * 5 * CELLSIZE;
                        widthWall = (4 * CELLSIZE);
                        heightWall = CELLSIZE;
                        al_draw_filled_rectangle(wallX, wallY, wallX + widthWall, wallY + heightWall, al_map_rgb(38, 50, 56));
                        index_j -= 2;
                    }
                    else if (index_j > 0 && data->board[index_i][index_j] != 7 && /*data->board[index_i][index_j - 1] != 7 &&*/ data->board[index_i][index_j - 2] != 7 && index_j + 1 < 2 * data->length && (data->board[index_i][index_j - 1] != 7 || data->board[index_i - 1][index_j - 1] == 7)) {
                        /*if (data->board[index_i][index_j] != 7) {
                            data->board[index_i][index_j] = 8;
                        }*/
                        int wallX = ((index_j / 2) * 5 + 1) * CELLSIZE;
                        int wallY = (index_i / 2 + 1) * 5 * CELLSIZE;
                        int widthWall = (4 * CELLSIZE);
                        int heightWall = CELLSIZE;
                        al_draw_filled_rectangle(wallX, wallY, wallX + widthWall, wallY + heightWall, al_map_rgb(38, 50, 56));
                        /*if (data->board[index_i][index_j - 1] != 7) {
                            data->board[index_i][index_j - 1] = 8;
                        }*/
                        index_j--;
                        wallX = ((index_j + 1) / 2) * 5 * CELLSIZE;
                        wallY = ((index_i + 1) / 2) * 5 * CELLSIZE;
                        widthWall = CELLSIZE;
                        heightWall = CELLSIZE;

                        al_draw_filled_rectangle(wallX, wallY, wallX + widthWall, wallY + heightWall, al_map_rgb(38, 50, 56));
                        index_j++;
                        /*if (data->board[index_i][index_j - 2] != 7) {
                            data->board[index_i][index_j - 2] = 8;
                        }*/
                        index_j -= 2;
                        wallX = ((index_j / 2) * 5 + 1) * CELLSIZE;
                        wallY = (index_i / 2 + 1) * 5 * CELLSIZE;
                        widthWall = (4 * CELLSIZE);
                        heightWall = CELLSIZE;
                        al_draw_filled_rectangle(wallX, wallY, wallX + widthWall, wallY + heightWall, al_map_rgb(38, 50, 56));
                        index_j += 2;
                    }
                }

            }
            else {
                for (int i = 0; i < 2 * data->length - 1; i++) {
                    for (int j = 0; j < 2 * data->length - 1; j++) {
                        if (data->board[i][j] == 8) {                        
                            data->board[i][j] = 0;
                        }
                        if (data->board[i][j] == 10) {
                            data->board[i][j] = 9;
                        }
                    }
                }
            }
                

        }
    }
        
                
    if (submit) {
        for (register int i = 0; i < 2 * data->length; i++) {
            for (register int j = 0; j < 2 * data->length; j++) {
                if (data->board[i][j] == 8) {
                    data->board[i][j] = 7;
                    *checkingPut = 1;
                }
                if (data->board[i][j] == 10) {
                    data->board[i][j] = 7;
                }
            }

        }
        
    }
    
    al_flip_display();

    for (register int i = 0; i < 2 * data->length; i++) {
        for (int j = 0; j < 2 * data->length; j++) {
            if (data->board[i][j] == 0 && i % 2 == 1 && j % 2 == 1) data->board[i][j] = 9;
        }
    }
    
}
void computerMove(struct BOARD* data, struct PLAYER* player) {
    srand(time(NULL));
    int count = 0;
    for (int i = 0; i < 2 * data->length - 1; i++) {
        for (int j = 0; j < 2 * data->length - 1; j++) {
            if (data->board[i][j] == 6) {
                count++;
                data->board[i][j] = 6 * 10 + count;
            }
        }
    }
    int choose, varBreak = 0;
    choose = rand() % count + 1;

    for (int i = 0; i < 2 * data->length - 1; i++) {
        for (int j = 0; j < 2 * data->length - 1; j++) {
            if (data->board[i][j] > 60) {
                if (choose == data->board[i][j] % 10) {
                    data->board[player->pieceCoordinate[(player->term - 1) * 2]][player->pieceCoordinate[(player->term - 1) * 2 + 1]] = 5;
                    data->board[i][j] = player->term;
                    player->pieceCoordinate[(player->term - 1) * 2] = i;
                    player->pieceCoordinate[(player->term - 1) * 2 + 1] = j;
                    varBreak = 1;
                    break;
                }
            }
        }
        if (varBreak == 1) break;
    }
    for (int i = 0; i < 2 * data->length - 1; i++) {
        for (int j = 0; j < 2 * data->length - 1; j++) {
            //printf("$");
            if (data->board[i][j] > 60) {
                data->board[i][j] = 5;
            }
        }
    }

    

    for (register int i = 0; i < 2 * data->length; i++) {
        for (register int j = 0; j < 2 * data->length; j++) {
            if (data->board[i][j] == 6 && i % 2 == 0 && j % 2 == 0) data->board[i][j] = 5;
        }
        //printf("\n");
    }
}
void computerWall(struct BOARD* data, struct PLAYER* player, int Multiplayer) {
    while (1) {
        srand(time(NULL));
        int choose = rand() % 2;
        int index_i, index_j;
        if (choose == 1) { //horizontall --> HoV = 3;
            index_i = rand() % (2 * data->length - 1);
            index_j = rand() % (2 * data->length - 1);
            //if (data->board[index_i][index_j] == 9) {
              //  continue;
            //}eles{
            if (index_i == 0 && data->board[index_i][index_j] != 7 && data->board[index_i + 1][index_j] != 7 && data->board[index_i + 2][index_j] != 7 && index_i + 1 < 2 * data->length) {
                //if (data->board[index_i][index_j] != 7) {
                data->board[index_i][index_j] = 8;
                //}

                //if (data->board[index_i][index_j + 1] != 7) {
                data->board[index_i + 1][index_j] = 8;
                //}

                //if (data->board[index_i][index_j + 2] != 7) {
                data->board[index_i + 2][index_j] = 8;
                //}

            }
            else if (index_j > 0 && data->board[index_i][index_j] != 7 && data->board[index_i - 2][index_j] != 7 && index_i + 1 < 2 * data->length && (data->board[index_i - 1][index_j] != 7 || data->board[index_i - 1][index_j - 1] == 7)) {
                //if (data->board[index_i][index_j] != 7) {
                data->board[index_i][index_j] = 8;
                //}

                //if (data->board[index_i][index_j - 1] != 7) {
                data->board[index_i - 1][index_j] = 8;
                //}

                //if (data->board[index_i][index_j - 2] != 7) {
                data->board[index_i - 2][index_j] = 8;
                //}

            }

        }
        else if (choose == 0) { // verticall --> HoV = 2;
            index_i = rand() % (2 * data->length);
            index_j = rand() % (2 * data->length);
            if (index_i == 0 && data->board[index_i][index_j] != 7 && data->board[index_i][index_j + 1] != 7 && data->board[index_i][index_j + 2] != 7 && index_j + 1 < 2 * data->length) {

                //if (data->board[index_i][index_j] != 7) {
                data->board[index_i][index_j] = 8;
                //}

                //if (data->board[index_i + 1][index_j] != 7) {
                data->board[index_i][index_j + 1] = 8;
                //}

                //if (data->board[index_i + 2][index_j] != 7) {
                data->board[index_i][index_j + 2] = 8;
                //}

            }
            else if (index_i > 0 && data->board[index_i][index_j] != 7  /* && data->board[index_i - 1][index_j] != 7 */ && data->board[index_j][index_j - 2] != 7 && index_j + 1 < 2 * data->length && (data->board[index_i][index_j - 1] != 7 || data->board[index_i - 1][index_j - 1] == 7)) {
                //if (data->board[index_i][index_j] != 7) {
                data->board[index_i][index_j] = 8;
                //}

                //if (data->board[index_i][index_j] != 7) {
                data->board[index_i][index_j - 1] = 8;
                //}

                //if (data->board[index_i - 2][index_j] != 7) {
                data->board[index_i][index_j - 2] = 8;
                //}
            }

        }
        else {
            //printf("again\n");
            continue;
        }

        int validPlacementPiece1 = 0, validPlacementPiece2 = 0, validPlacementPiece3 = 0, validPlacementPiece4 = 0;
        int help[max_len][max_len];
        if (Multiplayer == 4) {
            validPlacementPiece1 = validPlacementPiece2 = validPlacementPiece3 = validPlacementPiece4 = 0;

            memset(help, 0, sizeof(help));
            dfs_vertical(*data, 1, player->pieceCoordinate[0], player->pieceCoordinate[1], help, &validPlacementPiece1);
            memset(help, 0, sizeof(help));
            dfs_vertical(*data, 2, player->pieceCoordinate[2], player->pieceCoordinate[3], help, &validPlacementPiece2);
            memset(help, 0, sizeof(help));
            dfs_vertical(*data, 3, player->pieceCoordinate[4], player->pieceCoordinate[5], help, &validPlacementPiece3);
            memset(help, 0, sizeof(help));
            dfs_vertical(*data, 4, player->pieceCoordinate[6], player->pieceCoordinate[7], help, &validPlacementPiece4);
        }
        else if (Multiplayer == 2) {
            validPlacementPiece1 = validPlacementPiece2 = 0;
            validPlacementPiece3 = validPlacementPiece4 = 1;

            memset(help, 0, sizeof(help));
            dfs_vertical(*data, 1, player->pieceCoordinate[0], player->pieceCoordinate[1], help, &validPlacementPiece1);
            memset(help, 0, sizeof(help));
            dfs_vertical(*data, 2, player->pieceCoordinate[2], player->pieceCoordinate[3], help, &validPlacementPiece2);
        }
        if (validPlacementPiece1 == 1 && validPlacementPiece2 == 1 && validPlacementPiece3 == 1 && validPlacementPiece4 == 1) {
            //printf("*******\n");

            for (register int i = 0; i < 2 * data->length; i++) {
                for (register int j = 0; j < 2 * data->length; j++) {
                    if (j % 2 == 0 && data->board[i][j] == 7 && (data->board[i][j + 2] == 7 || data->board[i][j - 2] == 7)) { // horizontal walls
                        int wallX = ((j / 2) * 5 + 1) * CELLSIZE;
                        int wallY = (i / 2 + 1) * 5 * CELLSIZE;
                        int widthWall = (4 * CELLSIZE);
                        int heightWall = CELLSIZE;
                        al_draw_filled_rectangle(wallX, wallY, wallX + widthWall, wallY + heightWall, al_map_rgb(38, 50, 56));
                    }
                    else if (i % 2 == 0 && data->board[i][j] == 7 && (data->board[i + 2][j] == 7 || data->board[i - 2][j] == 7)) { // vertical walls
                        int Xwall = (j / 2 + 1) * 5 * CELLSIZE;
                        int Ywall = ((i / 2) * 5 + 1) * CELLSIZE;
                        int widthWall = CELLSIZE;
                        int heightWall = (4 * CELLSIZE);
                        al_draw_filled_rectangle(Xwall, Ywall, Xwall + widthWall, Ywall + heightWall, al_map_rgb(38, 50, 56));
                    }
                    else if (i % 2 == 1 && j % 2 == 1 && data->board[i][j] == 7) {
                        int Xwall = ((j + 1) / 2) * 5 * CELLSIZE;
                        int Ywall = ((i + 1) / 2) * 5 * CELLSIZE;
                        int widthWall = CELLSIZE;
                        int heightWall = CELLSIZE;

                        al_draw_filled_rectangle(Xwall, Ywall, Xwall + widthWall, Ywall + heightWall, al_map_rgb(38, 50, 56));

                    }
                }
            }

            for (register int i = 0; i < 2 * data->length; i++) {
                for (register int j = 0; j < 2 * data->length; j++) {
                    if (data->board[i][j] == 8 /* && validPlacementPiece1 == 1 && validPlacementPiece2 == 1*/) {
                        data->board[i][j] = 7;
                    }
                }

            }

        }
        for (int i = 0; i < 2 * data->length - 1; i++) {
            for (int j = 0; j < 2 * data->length - 1; j++) {
                if (data->board[i][j] == 8) {
                    if (i % 2 == 1 && j % 2 == 1) {
                        data->board[i][j] = 9;
                    }
                    else {
                        data->board[i][j] = 0;
                    }
                }
            }
        }


        

        break;
    }
}

void computerPlayer(struct BOARD* data, struct PLAYER* player, int Multiplayer) {
    srand(time(NULL));
    int choose = rand() % 2;
    if (choose == 0) {//move piece
        computerMove(&data, &player);

    }
    else if (choose == 1) {// computer wall
        computerWall(&data, &player, Multiplayer);
    }
}
void showButton(Button* show) {
    ALLEGRO_FONT* font = al_create_builtin_font();
    al_draw_filled_rectangle(show->posX, show->posY, show->width, show->height, al_map_rgb(253, 216, 53));
    al_draw_text(font, al_map_rgb(0, 0, 0), (show->posX + show->width) / 2, (show->posY + show->height) / 2, ALLEGRO_ALIGN_CENTRE, show->name);
}
int checkButton(Button* show, int x_coordinate, int y_coordinate) {
    return (x_coordinate >= show->posX && x_coordinate <= show->width && y_coordinate >= show->posY && y_coordinate <= show->height);
}

int main() {
    int count, go = 0, pointer;
    bool checkingWall = 0, checkingPiece = 0;
    struct BOARD data;
    struct PLAYER player;
    struct CHARM charm;
    struct PRESENT present;
    int Multiplayer;
    printf("enter the length of the board: ");

    scanf_s("%d", &data.length);
    printf("Do you want to play for two or four players?");
    scanf_s("%d", &Multiplayer);
    // Initialize Allegro
    al_init();
    al_init_primitives_addon();
    al_init_image_addon();
    al_install_mouse();
    event_queue = al_create_event_queue();
    player1 = al_load_bitmap("./iran.png");
    // Create a display
    ALLEGRO_EVENT event;
    ALLEGRO_BITMAP* Player;
    ALLEGRO_DISPLAY* display = al_create_display((5 * data.length + 1) * CELLSIZE + 20 * CELLSIZE, (5 * data.length + 1) * CELLSIZE);
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    //al_hide_mouse_cursor(display);
    // Set the background color

    int width = (5 * data.length + 1) * CELLSIZE + 20 * CELLSIZE;
    int height = (5 * data.length + 1) * CELLSIZE;
    
     makePrimaryBoard(&data);
     Button save;
     save.posX = width * 80 / 100;
     save.posY = height * 10 / 100;
     save.width = width * 90 / 100;
     save.height = height * 15 / 100;
     strcpy_s(save.name, 5, "SAVE");
     
     
     Button load;
     load.posX = width * 80 / 100;
     load.posY = height * 30 / 100;
     load.width = width * 90 / 100;
     load.height = height * 35 / 100;
     strcpy_s(load.name, 5, "LOAD");

     showBoard(data);
     showButton(&save);
     showButton(&load);
     ALLEGRO_BITMAP* oldDisplay;

    if (Multiplayer == 4) {
        //printf("%d\n", data.length);
        data.board[0][data.length - data.length % 2] = 1;
        data.board[data.length * 2 - 2][data.length - data.length % 2] = 2;
        data.board[(data.length - data.length % 2)][0] = 3;
        data.board[(data.length - data.length % 2)][data.length * 2 - data.length % 2 - 2] = 4;
        //player.term = 1;
        //if (data.length % 2 == 0) {
        player.pieceCoordinate[0] = 0;
        player.pieceCoordinate[1] = data.length - data.length % 2;
        player.pieceCoordinate[2] = data.length * 2 - 2;
        player.pieceCoordinate[3] = data.length - data.length % 2;
        player.pieceCoordinate[4] = data.length - data.length % 2;
        player.pieceCoordinate[5] = 0;
        player.pieceCoordinate[6] = data.length - data.length % 2;
        player.pieceCoordinate[7] = data.length * 2 - data.length % 2 - 2;
        //}

       
        

        int m = 0;

        
        while (1) {
            checkingWall = 0;
            checkingPiece = 0;
            //luck(&data, &player, &charm, &present, Multiplayer);
            
            if (m % 4 == 0)player.term = 1;
            else if (m % 4 == 1) player.term = 2;
            else if (m % 4 == 2) player.term = 3;
            else if (m % 4 == 3)player.term = 4;

            //showBoard(data);
            movePiecePossiblities(&data, &player);
            movePiecePossiblitiesJump(&data, &player);
            movePiecePossiblitiesParties(&data, &player);
            //putWalls(&data, &player, event_queue, ev);
            
            showBoard(data);
            showButton(&save);
            showButton(&load);
            al_flip_display();
            oldDisplay = al_clone_bitmap(al_get_backbuffer(display));
            
            while (1) {
                printf("****\n");
                al_wait_for_event(event_queue, &event);

                if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                    return 0;
                }

                if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                    if (event.mouse.button == 1) {

                        if(checkButton(&save, event.mouse.x, event.mouse.y)){
                            FILE *file;
                            fopen_s(&file,"./Save.dat", "wb");
                            fwrite(&data, sizeof(data), 1, file);
                            fwrite(&player, sizeof(player), 1, file);
                            fclose(file);
                            continue;
                        }
                        if(checkButton(&load, event.mouse.x, event.mouse.y)){
                            FILE *file;
                            fopen_s(&file,"./Save.dat", "rb");
                            if (!file) continue;
                            fread(&data, sizeof(data), 1, file);
                            fread(&player, sizeof(player), 1, file);
                            al_unregister_event_source(event_queue, al_get_display_event_source(display));

                            al_destroy_display(display);
                            display = al_create_display((5 * data.length + 1) * CELLSIZE + 20 * CELLSIZE, (5 * data.length + 1) * CELLSIZE);
                            al_register_event_source(event_queue, al_get_display_event_source(display));
                            width = (5 * data.length + 1) * CELLSIZE + 20 * CELLSIZE;
                            height = (5 * data.length + 1) * CELLSIZE;

                            Button save;
                            save.posX = width * 80 / 100;
                            save.posY = height * 10 / 100;
                            save.width = width * 90 / 100;
                            save.height = height * 15 / 100;
                            strcpy_s(save.name, 5, "SAVE");


                            Button load;
                            load.posX = width * 80 / 100;
                            load.posY = height * 30 / 100;
                            load.width = width * 90 / 100;
                            load.height = height * 35 / 100;
                            strcpy_s(load.name, 5, "LOAD");

                            showBoard(data);
                            showButton(&save);
                            showButton(&load);
                            al_flip_display();
                            oldDisplay = al_clone_bitmap(al_get_backbuffer(display));

                          
                            
                            fclose(file);
                            continue;
                        }


                        
                        putWalls(&data, &player, event_queue, ev, &go, 4, event.mouse.x, event.mouse.y, 1, &checkingWall);
                        //printf("%d\n", putWalls(&data, &player, event_queue, ev, &go, 4, event.mouse.x, event.mouse.y, 1));
                        movePiece(&data, &player, event_queue, ev, event.mouse.x, event.mouse.y, &checkingPiece);
                       // printf("%d\n", movePiece(&data, &player, event_queue, ev, event.mouse.x, event.mouse.y));
                        m = m + (checkingPiece + checkingWall);
                        
                        showBoard(data);
                        showButton(&save);
                        showButton(&load);
                        
                        al_flip_display();
                        
                        break;
                    }
                }

                if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
                    al_draw_bitmap(oldDisplay, 0, 0, 0);
                    putWalls(&data, &player, event_queue, ev, &go, 4, event.mouse.x, event.mouse.y, 0, &checkingWall);
                    
                }
                
                

            }
            
            //movePiece(&data, &player, event_queue, ev);


            //showBoard(data);
            



        }
        al_flip_display();
        // Wait for a key press before closing the window
        al_rest(50.0);

        // Destroy the display
        al_destroy_display(display);
        al_destroy_display(display);

        return 0;
    }

    //------------------------------------------------------------------------------------------------------------------------------------------------

    /*if (Multiplayer == 2) {
        data.board[0][data.length - data.length % 2] = 1;
        data.board[data.length * 2 - 2][data.length - data.length % 2] = 2;
        player.pieceCoordinate[0] = 0;
        player.pieceCoordinate[1] = data.length - data.length % 2;
        player.pieceCoordinate[2] = data.length * 2 - 2;
        player.pieceCoordinate[3] = data.length - data.length % 2;
        int k = 0;


        while (1) {
            luck(&data, &player, &charm, &present, Multiplayer);

            for (register int i = 0; i < 2 * data.length; i++) {
                for (int j = 0; j < 2 * data.length; j++) {
                    if (data.board[i][j] == 6) data.board[i][j] = 5;
                }
            }
            showBoard(data);
            if (k % 2 == 0) {//player
                player.term = 1;

                showBoard(data);
                movePiecePossiblities(&data, &player);
                movePiecePossiblitiesJump(&data, &player);
                movePiecePossiblitiesParties(&data, &player);


                while (1) {
                    //showBoard(data);
                    delete_wall(&data);
                    showBoard(data);
                    putWalls(&data, &player, event_queue, ev, &go, 2);
                    showBoard(data);
                    al_flip_display();

                    if (go == 1) {

                        break;
                    }
                    showBoard(data);
                }
                //showBoard(data);

                movePiece(&data, &player, event_queue, ev);


                showBoard(data);
            }
            else if (k % 2 == 1) {//computer
                player.term = 2;
                for (register int i = 0; i < 2 * data.length; i++) {
                    for (int j = 0; j < 2 * data.length; j++) {
                        if (data.board[i][j] == 6) data.board[i][j] = 5;
                    }
                }
                //showBoard(data);
                movePiecePossiblities(&data, &player);
                movePiecePossiblitiesJump(&data, &player);
                movePiecePossiblitiesParties(&data, &player);
                //showBoard(data);
                //computerPlayer(&data, &player, 2);
                //delete_wall(&data);
                srand(time(NULL));
                int choose = rand() % 2;
                printf("%d, \n", choose);
                if (choose == 0) {//move piece

                    computerMove(&data, &player);

                }
                else if (choose == 1) {// computer wall
                    computerWall(&data, &player, 2);
                }
                //showBoard(data);
            }

            k++;
            al_flip_display();



        }
        al_flip_display();

        // Wait for a key press before closing the window
        al_rest(50.0);

        // Destroy the display
        al_destroy_display(display);

        return 0;
    }*/
}