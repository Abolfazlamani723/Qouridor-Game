#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
int jumpOverPiece1(char Board[][57], int piece[], int length, int sw){
    if(sw == 0){
        if(Board[4 * piece[sw * 2] + 2 - 2][4 * piece[sw * 2 + 1] + 2] != '#' && Board[4 * piece[sw * 2] + 2 - 4][4 * piece[sw * 2 + 1] + 2] == '^' && Board[4 * piece[sw * 2] + 2 - 6][4 * piece[sw * 2 + 1] + 2] != '#' && piece[sw * 2] >= 2) return 1;//w
        else if(Board[4 * piece[sw * 2] + 2][4 * piece[sw * 2 + 1] + 2 + 2] != '#' && Board[4 * piece[sw * 2] + 2][4 * piece[sw * 2 + 1] + 2 + 4] == '^' && Board[4 * piece[sw * 2] + 2][4 * piece[sw * 2 + 1] + 2 + 6] != '#' && piece[sw * 2 + 1] < length - 2) return 3;//d
        else if(Board[4 * piece[sw * 2] + 2 + 2][4 * piece[sw * 2 + 1] + 2] != '#' && Board[4 * piece[sw * 2] + 2 + 4][4 * piece[sw * 2 + 1] + 2] == '^' && Board[4 * piece[sw * 2] + 2 + 6][4 * piece[sw * 2 + 1] + 2] != '#' && piece[sw * 2] < length - 2) return 2;//s
        else if(Board[4 * piece[sw * 2] + 2][4 * piece[sw * 2 + 1] + 2 - 2] != '#' && Board[4 * piece[sw * 2] + 2][4 * piece[sw * 2 + 1] + 2 - 4] == '^' && Board[4 * piece[sw * 2] + 2][4 * piece[sw * 2 + 1] + 2 - 6] != '#' && piece[sw * 2 + 1] >= 2) return 4;//a
        else return 0;
    }else if(sw == 1){
        if(Board[4 * piece[sw * 2] + 2 - 2][4 * piece[sw * 2 + 1] + 2] != '#' && Board[4 * piece[sw * 2] + 2 - 4][4 * piece[sw * 2 + 1] + 2] == '*' && Board[4 * piece[sw * 2] + 2 - 6][4 * piece[sw * 2 + 1] + 2] != '#' && piece[sw * 2] >= 2) return 1;//w
        else if(Board[4 * piece[sw * 2] + 2][4 * piece[sw * 2 + 1] + 2 + 2] != '#' && Board[4 * piece[sw * 2] + 2][4 * piece[sw * 2 + 1] + 2 + 4] == '*' && Board[4 * piece[sw * 2] + 2][4 * piece[sw * 2 + 1] + 2 + 6] != '#' && piece[sw * 2 + 1] < length - 2) return 3;//d
        else if(Board[4 * piece[sw * 2] + 2 + 2][4 * piece[sw * 2 + 1] + 2] != '#' && Board[4 * piece[sw * 2] + 2 + 4][4 * piece[sw * 2 + 1] + 2] == '*' && Board[4 * piece[sw * 2] + 2 + 6][4 * piece[sw * 2 + 1] + 2] != '#' && piece[sw * 2] < length - 2) return 2;//s
        else if(Board[4 * piece[sw * 2] + 2][4 * piece[sw * 2 + 1] + 2 - 2] != '#' && Board[4 * piece[sw * 2] + 2][4 * piece[sw * 2 + 1] + 2 - 4] == '*' && Board[4 * piece[sw * 2] + 2][4 * piece[sw * 2 + 1] + 2 - 6] != '#' && piece[sw * 2 + 1] >= 2) return 4;//a
        else return 0;
    }
}
int jumpOverPiece2(char Board[][57], int piece[], int length, int sw){
    if(sw == 0){
        if(Board[4 * piece[sw * 2] + 2 - 2][4 * piece[sw * 2 + 1] + 2] != '#' && Board[4 * piece[sw * 2] + 2 - 4][4 * piece[sw * 2 + 1] + 2] == '^' && Board[4 * piece[sw * 2] + 2 - 6][4 * piece[sw * 2 + 1] + 2] == '#' && piece[sw * 2] >= 2) return 1;//w
        else if(Board[4 * piece[sw * 2] + 2][4 * piece[sw * 2 + 1] + 2 + 2] != '#' && Board[4 * piece[sw * 2] + 2][4 * piece[sw * 2 + 1] + 2 + 4] == '^' && Board[4 * piece[sw * 2] + 2][4 * piece[sw * 2 + 1] + 2 + 6] == '#' && piece[sw * 2 + 1] < length - 2) return 3;//d
        else if(Board[4 * piece[sw * 2] + 2 + 2][4 * piece[sw * 2 + 1] + 2] != '#' && Board[4 * piece[sw * 2] + 2 + 4][4 * piece[sw * 2 + 1] + 2] == '^' && Board[4 * piece[sw * 2] + 2 + 6][4 * piece[sw * 2 + 1] + 2] == '#' && piece[sw * 2] < length - 2) return 2;//s
        else if(Board[4 * piece[sw * 2] + 2][4 * piece[sw * 2 + 1] + 2 - 2] != '#' && Board[4 * piece[sw * 2] + 2][4 * piece[sw * 2 + 1] + 2 - 4] == '^' && Board[4 * piece[sw * 2] + 2][4 * piece[sw * 2 + 1] + 2 - 6] == '#' && piece[sw * 2 + 1] >= 2) return 4;//a
        else return 0;
    }else if(sw == 1){
        if(Board[4 * piece[sw * 2] + 2 - 2][4 * piece[sw * 2 + 1] + 2] != '#' && Board[4 * piece[sw * 2] + 2 - 4][4 * piece[sw * 2 + 1] + 2] == '*' && Board[4 * piece[sw * 2] + 2 - 6][4 * piece[sw * 2 + 1] + 2] == '#' && piece[sw * 2] >= 2) return 1;//w
        else if(Board[4 * piece[sw * 2] + 2][4 * piece[sw * 2 + 1] + 2 + 2] != '#' && Board[4 * piece[sw * 2] + 2][4 * piece[sw * 2 + 1] + 2 + 4] == '*' && Board[4 * piece[sw * 2] + 2][4 * piece[sw * 2 + 1] + 2 + 6] == '#' && piece[sw * 2 + 1] < length - 2) return 3;//d
        else if(Board[4 * piece[sw * 2] + 2 + 2][4 * piece[sw * 2 + 1] + 2] != '#' && Board[4 * piece[sw * 2] + 2 + 4][4 * piece[sw * 2 + 1] + 2] == '*' && Board[4 * piece[sw * 2] + 2 + 6][4 * piece[sw * 2 + 1] + 2] == '#' && piece[sw * 2] < length - 2) return 2;//s
        else if(Board[4 * piece[sw * 2] + 2][4 * piece[sw * 2 + 1] + 2 - 2] != '#' && Board[4 * piece[sw * 2] + 2][4 * piece[sw * 2 + 1] + 2 - 4] == '*' && Board[4 * piece[sw * 2] + 2][4 * piece[sw * 2 + 1] + 2 - 6] == '#' && piece[sw * 2 + 1] >= 2) return 4;//a
        else return 0;
    }
}

