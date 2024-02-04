#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
void Delete(char Board[][57], int rowWall, int colWall, char direction);
void putWalls(char Board[][57], int rowWall, int colWall, char direction);
int bfs(char Board[][57], int piece[], int sw, int startRow, int startCol, int destRow, int destCol, int length) {
    int visited[57][57] = {0};
    int queue[57 * 57][2];
    int front = 0, rear = 0;

    queue[rear][0] = startRow;
    queue[rear][1] = startCol;
    rear++;
    visited[startRow][startCol] = 1;

    while (front < rear) {
        int row = queue[front][0];
        int col = queue[front][1];
        front++;

        if (row == destRow && col == destCol) {
            return 1;  // Destination reached
        }

        int moves[][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        for (int i = 0; i < 4; i++) {
            int newRow = row + moves[i][0];
            int newCol = col + moves[i][1];

            if (newRow >= 0 && newRow < 4 * length && newCol >= 0 && newCol < 4 * length &&
                Board[newRow][newCol] != '#' && !visited[newRow][newCol] && (newRow % 4 != 0 || newCol % 4 != 0)) {
                queue[rear][0] = newRow;
                queue[rear][1] = newCol;
                rear++;
                visited[newRow][newCol] = 1;
            }
        }
    }

    return 0;  // Destination not reachable
}

// Function to check if a wall placement is valid using BFS
int isWallPlacementValid(char Board[][57], int piece[], int sw, int rowWall, int colWall, char direction, int length) {
    putWalls(Board, rowWall, colWall, direction);

    int player1CanReach = bfs(Board, piece, 0, piece[0] * 4 + 2, piece[1] * 4 + 2, 4 * (length - 1), piece[1] * 4 + 2, length);
    int player2CanReach = bfs(Board, piece, 1, piece[2] * 4 + 2, piece[3] * 4 + 2, 0, piece[3] * 4 + 2, length);

    Delete(Board, rowWall, colWall, direction);

    return player1CanReach && player2CanReach;
}
