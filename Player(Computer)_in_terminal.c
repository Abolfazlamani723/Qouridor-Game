#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

int jumpOverPiece1(char Board[][57], int piece[], int length, int sw);
int jumpOverPiece2(char Board[][57], int piece[], int length, int sw);
int isWallPlacementValid(char Board[][57], int piece[], int sw, int rowWall, int colWall, char direction, int length);
void putWalls(char Board[][57], int rowWall, int colWall, char direction);
void Delete(char Board[][57], int rowWall, int colWall, char direction);
void playerComputer(char Board[][57], int piece[], int sw, int length, int countWalls[][1]){
	sw = 0;
    srand(time(NULL));
    int valueble_break = 0;
    while(valueble_break == 0){
        int option = rand();
        if (option % 2 == 0) {
            while (1) {
                int  movement = rand();
                if (movement % 4 == 0) {
                    if(jumpOverPiece1(Board, piece, length, 0) == 1){
                        piece[ sw * 2] -= 2;
                        valueble_break = 1;
                        break;
                    }
                    else if(jumpOverPiece2(Board, piece, length, sw) == 1) {
                        int movement = rand();
                        if (movement % 2 == 0) {//rigth piece
                            if ((piece[sw * 2 + 1] + 1 <= length - 1) && (piece[sw * 2] - 1 >= 0) &&
                                Board[4 * (piece[sw * 2] - 1) + 2][4 * piece[sw * 2 + 1] + 2 + 2] != '#') {
                                piece[sw * 2]--;
                                piece[sw * 2 + 1]++;
                                valueble_break = 1;
                                break;
                            }
                        } else if (movement % 2 == 1) {//left piece
                            if ((piece[sw * 2 + 1] - 1 >= 0) && piece[sw * 2] - 1 >= 0 &&
                                Board[4 * (piece[sw * 2] - 1) + 2][4 * piece[sw * 2 + 1]] != '#') {
                                piece[sw * 2]--;
                                piece[sw * 2 + 1]--;
                                valueble_break = 1;
                                break;
                            }
                        }
                        else {
                            continue;
                        }
                    }
                    else if (piece[sw * 2] - 1 >= 0 && Board[4 * piece[sw * 2] + 2 - 2][4 * piece[sw * 2 + 1] + 2] != '#' && Board[4 * piece[sw * 2] + 2 - 4][4 * piece[sw * 2 + 1] + 2] == '.') {
                        piece[sw * 2]--;
                        valueble_break = 1;
                        break;
                    } else {
                        continue;
                    }
                } else if (movement % 4 == 1) {
                    if(jumpOverPiece1(Board, piece, length, sw) == 2){
                        piece[sw * 2] += 2;
                        valueble_break = 1;
                        break;
                    }
                    else if(jumpOverPiece2(Board, piece, length, sw) == 2){
                        int movement = rand();
                        if (movement % 2 == 0) {
                            if ((piece[sw * 2 + 1] + 1 <= length - 1) && (piece[sw * 2] + 1 < length) &&
                                Board[4 * (piece[sw * 2] + 1) + 2][4 * piece[sw * 2 + 1] + 2 + 2] != '#') {
                                piece[sw * 2]++;
                                piece[sw * 2 + 1]++;
                                valueble_break = 1;
                                break;
                            }
                        }else if (movement % 2 == 1) {//left piece
                            if ((piece[sw * 2 + 1] - 1 >= 0) && piece[sw * 2] + 1 < length &&
                                Board[4 * (piece[sw * 2] + 1) + 2][4 * piece[sw * 2 + 1]] != '#') {
                                piece[sw * 2]++;
                                piece[sw * 2 + 1]--;
                                valueble_break = 1;
                                break;
                            }
                        }
                        else {
                            continue;
                        }
                    }
                    else if ((piece[sw * 2] + 1 <= length - 1) &&
                             (Board[4 * piece[sw * 2] + 2 + 2][4 * piece[sw * 2 + 1] + 2] != '#') && Board[4 * piece[sw * 2] + 2 + 4][4 * piece[sw * 2 + 1] + 2] == '.') {
                        piece[sw * 2]++;
                        valueble_break = 1;
                        break;
                    } else {
                        continue;
                    }
                } else if (movement % 4 == 2) {
                    if(jumpOverPiece1(Board, piece, length, sw) == 3){
                        piece[sw * 2 + 1] += 2;
                        valueble_break = 1;
                        break;
                    }
                    else if(jumpOverPiece2(Board, piece, length, sw) == 3){
                        int movement = rand();
                        if (movement % 2 == 0) {
                            if ((piece[sw * 2 + 1] + 1 <= length - 1) && (piece[sw * 2] + 1 < length) &&
                                Board[4 * piece[sw * 2] + 2 + 2][4 * (piece[sw * 2 + 1] + 1) + 2] != '#') {
                                piece[sw * 2]++;
                                piece[sw * 2 + 1]++;
                                valueble_break = 1;
                                break;
                            }
                        }else if (movement % 2 == 1) {//left piece
                            if ((piece[sw * 2 + 1] - 1 >= 0) && piece[sw * 2] - 1 >= 0 &&
                                Board[4 * (piece[sw * 2] + 1) + 2 - 2][4 * piece[sw * 2 + 1] + 2] != '#') {
                                piece[sw * 2]--;
                                piece[sw * 2 + 1]++;
                                valueble_break = 1;
                                break;
                            }
                        }
                        else {
                            continue;
                        }

                    }
                    else if ((piece[sw * 2 + 1] + 1 <= length - 1) &&
                             (Board[4 * piece[sw * 2] + 2][4 * piece[sw * 2 + 1] + 2 + 2] != '#') && Board[4 * piece[sw * 2] + 2][4 * piece[sw * 2 + 1] + 2 + 4] == '.') {
                        piece[sw * 2 + 1]++;
                        valueble_break = 1;
                        break;
                    } else {
                        continue;
                    }
                } else if (movement % 4 == 3) {
                    if(jumpOverPiece1(Board, piece, length, sw) == 4){
                        piece[sw * 2 + 1] -= 2;
                        valueble_break = 1;
                        break;
                    }
                    else if(jumpOverPiece2(Board, piece, length, sw) == 4){
                        int movement = rand();
                        if (movement % 2 == 0) {
                            if ((piece[sw * 2 + 1] - 1 >= 0) && (piece[sw * 2] - 1 >= 0) &&
                                Board[4 * piece[sw * 2] + 2 - 2][4 * (piece[sw * 2 + 1] - 1) + 2] != '#') {
                                piece[sw * 2]--;
                                piece[sw * 2 + 1]--;
                                valueble_break = 1;
                                break;
                            }
                        }else if (movement % 2 == 1) {//left piece
                            if ((piece[sw * 2 + 1] + 1 < length) && piece[sw * 2] - 1 >= 0 &&
                                Board[4 * piece[sw * 2] + 2 + 2][4 * (piece[sw * 2 + 1] - 1) + 2] != '#') {
                                piece[sw * 2]++;
                                piece[sw * 2 + 1]--;
                                valueble_break = 1;
                                break;
                            }
                        }
                        else {
                            continue;
                        }

                    }
                    if ((piece[sw * 2 + 1] - 1 >= 0) && (Board[4 * piece[sw * 2] + 2][4 * piece[sw * 2 + 1] + 2 - 2] != '#') && Board[4 * piece[sw * 2] + 2][4 * piece[sw * 2 + 1] + 2 - 4] == '.') {
                        piece[sw * 2 + 1]--;
                        valueble_break = 1;
                        break;
                    } else {
                        continue;
                    }
                } else {
                    continue;
                }
            }
        } else if ((option % 2 == 1) && countWalls[0][0] > 0) { // Puting wall
            countWalls[0][0]--;
            int rowWall, colWall;
            int swWallPlacement = 0;
            while (swWallPlacement == 0) {
                int direction = rand();
                if (direction % 2 == 0) {//H
                    rowWall = rand() % (length - 2);
                    colWall = rand() % (length - 1);

                } else if (direction % 2 == 1) {//V
                    rowWall = rand() % (length - 2);
                    colWall = rand() % (length - 1);
                }
                if (direction   % 2 == 0) {
                    int row = 4 * (rowWall + 1);
                    int col1 = 4 * colWall + 1;
                    int col2 = 4 * (colWall + 1) + 3;
                    if (Board[row][col1] == '#' || Board[row][col2] == '#') {
                        continue;
                    }
                }else if(direction   % 2 == 1) {
                    int row1 = 4 * (rowWall + 1) + 3;
                    int row2 = 4 * rowWall + 1;
                    int col = 4 * (colWall + 1);
                    if (Board[row1][col] == '#' || Board[row2][col] == '#') {
                        continue;
                    }
                }
                char operation;
                if(direction % 2 == 0) operation = 'H';
                else if (direction % 2 == 1) operation = 'V';
                if (isWallPlacementValid(Board, piece, 0, rowWall, colWall, operation, length) == 1) {
                    putWalls(Board, rowWall, colWall, operation);
                    swWallPlacement = 1;
                    valueble_break = 1;
                } else {
                    Delete(Board, rowWall, colWall, operation);
                }
            }
        }else if(countWalls[0][0] == 0){
            continue;
        }
    }
}