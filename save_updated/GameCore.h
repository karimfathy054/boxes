#ifndef GAMECORE_H_INCLUDED
#define GAMECORE_H_INCLUDED
#include "structures.h"
void initGameArray(int n, char gameArray[n][n]){
    for(int i = 0; i < n; i++){
        for(int j = 0; j <n; j++){
            if(i % 2){
                gameArray[i][j] = -1;
            }else{
                if(j % 2){
                    gameArray[i][j] = -1;
                }else{
                    gameArray[i][j] = 0;
                }
            }
        }
    }
}

void printGrid(int n, char gameArray[n][n]){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(gameArray[i][j] == 0){
                printf("%c ", 'o');
            }else if(gameArray[i][j] == -1){
                printf("  ");
            }else{
                printf("%c ", gameArray[i][j]);
            }
        }
        printf("\n");
    }
    //clearBuffer(); no char here
}

void switchTurns(player players[2]){
    player temp = players[0];
    players[0] = players[1];
    players[1] = temp;
}

int drawLine(tuple p1, tuple p2, int gridDim, char gameArray[][gridDim*2-1]){
    if(gameArray[p1.x + p2.x][p1.y + p2.y] == -1){
        if((p1.x+p2.x) % 2){
            gameArray[p1.x + p2.x][p1.y + p2.y] = '|';
        }else{
            gameArray[p1.x + p2.x][p1.y + p2.y] = '-';
        }
        return 1;
    }else{
        printf("Already joined!\n");
        return 0;
    }
}

int joinDots(tuple p1, tuple p2, int gridDim, char gameArray[][gridDim*2-1]){
    // 0 <= x, y < n-1
    if(
        p1.x >= 0 && p1.x < gridDim
        && p1.y >= 0 && p1.y < gridDim
        && p2.x >= 0 && p2.x < gridDim
        && p2.y >= 0 && p2.y < gridDim
    ){
        if(p1.x != p2.x && p1.y != p2.y){
            //not horizontal or vertical ie diagonal
            printf("You can't join dots diagonally!\n");
            return 0;
        }else if(p1.x == p2.x && abs(p1.y-p2.y) == 1){
            return drawLine(p1, p2, gridDim, gameArray);
        }else if(p1.y == p2.y && abs(p1.x-p2.x) == 1){
            return drawLine(p1, p2, gridDim, gameArray);
        }else{
            printf("Can't join these two dots.\n");
            return 0;
        }
    }else{
        printf("Invalid input.\n");
        return 0;
    }
}

int checkBoxes(int gridDim, char gameArray[][gridDim*2-1], player currentPlayer){
    int boxCount = 0;
    for(int i = 1; i <= gridDim*2-2; i += 2){
        for(int j = 1; j <= gridDim*2-2; j += 2){
            int u = gameArray[i-1][j];
            int d = gameArray[i+1][j];
            int l = gameArray[i][j-1];
            int r = gameArray[i][j+1];
            if(
                u != -1 &&
                d != -1 &&
                l != -1 &&
                r != -1
            ){
                if(gameArray[i][j] == -1){
                    gameArray[i][j] = currentPlayer.letter;
                }
                boxCount++;
            }else{
                //to remove a letter if the box was undone
                gameArray[i][j] = -1;
            }
        }
    }
    return boxCount;
}


void undo(int gridDim, int movesArray[][MOVES_ARRAY_WIDTH], char gameArray[][2*gridDim-1]){
    //lastX, lastY: coordinates of last joined line
    int lastX, lastY, i = 0;
    i = getLastMoveIndex(gridDim, movesArray);
    lastX = movesArray[i][0];
    lastY = movesArray[i][1];
    for(int j = 0; j < 4; j++){
        movesArray[i][j] = -1;
    }
    gameArray[lastX][lastY] = -1;
}


#endif // GAMECORE_H_INCLUDED