#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <windows.h>
#include "movesManager.c"


void clearBuffer(){
    while(getchar() != '\n'){}
}

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
    // 0 <= x, y <= n-1
    if(
        p1.x >= 0 && p1.x <= gridDim
        && p1.y >= 0 && p1.y <= gridDim
        && p2.x >= 0 && p2.x <= gridDim
        && p2.y >= 0 && p2.y <= gridDim
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
    for(int i = 1; i <= gridDim; i += 2){
        for(int j = 1; j <= gridDim; j += 2){
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

//leave gameLoop as the last method before main
void gameLoop(int gridDim, char gameArray[][gridDim*2-1], int movesArray[][MOVES_ARRAY_WIDTH]){
    int boxCount = 0;
    //resetting movesArray
    resetMovesArray(gridDim, movesArray);
    //players
    player player1 = {1, 'A', 3};
    player player2 = {2, 'B', 4};
    player players[] = {player1, player2};

    while(1){
        //points' coordinates
        //int x1, x2, y1, y2;
        printf("Player %d turn!\n", players[0].num);
        tuple p1, p2;
        printf("Enter 1st point coordinates (x1 y1): ");
        scanf("%d %d", &p1.x, &p1.y);
        printf("Enter 2nd point coordintes (x2 y2): ");
        scanf("%d %d", &p2.x, &p2.y);
        //if joining is successful, save the move
        if(joinDots(p1, p2, gridDim, gameArray)){
            
            tuple lcoords = {p1.x + p2.x, p1.y + p2.y};
            
            appendMove(lcoords, players[0], gridDim, movesArray);
            
            int newCount = checkBoxes(gridDim, gameArray, players[0]);

            if(newCount > boxCount){
                boxCount = newCount;
            }else{
                //if the player did not score, switch turns
                switchTurns(players);
            }
            

            printf("boxCount = %d\n", boxCount);
            printGrid(gridDim*2-1, gameArray);
            clearBuffer();

            //***undo loop***
            int lastIndex;
            while(lastIndex = getLastMoveIndex(gridDim, movesArray)){
                //getchar(); no char here
                printf("Undo last move? (y/n)");
                char ans = getchar();
                //getchar(); no char here
                if(ans == 'y'){
                    undo(gridDim, movesArray, gameArray);
                    boxCount = checkBoxes(gridDim, gameArray, players[0]);
                    //updating lastIndex after deleting the last row bu undo()
                    lastIndex = getLastMoveIndex(gridDim, movesArray);
                    //if turns were not switched up above, this means that the player had an extra turn after he scored
                    if(movesArray[lastIndex][2] == players[0].num){
                        //to cancel the switch up above
                        switchTurns(players);
                    }
                    
                    clearBuffer();
                    printGrid(gridDim*2-1, gameArray);
                    //buffer will be clean here
                    continue;
                }else if(ans == 'n'){
                    //buffer will be clean here
                    break;
                }else{
                    clearBuffer();
                    continue;
                }
            }
        }
        //clearing buffer
        //clearBuffer();

        if(boxCount == (gridDim-1)*(gridDim-1)){
            clearBuffer();
            break;
        }
    }
}



int main(){
    
    //HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    //SetConsoleTextAttribute(handle, FOREGROUND_RED);
    

    int gridDim;
    printf("Enter dimension(nxn): ");
    scanf("%d", &gridDim);
    //clearing buffer
    getchar();
    int arrayDim = gridDim*2-1;
    char gameArray[arrayDim][arrayDim];
    initGameArray(arrayDim, gameArray);
    printGrid(arrayDim, gameArray);

    //number of lines = 2*gridDim*(gridDim-1)
    //stores coordinates of last line
    //resets in at the beginning of gameLoop()
    int movesArray[2*gridDim*(gridDim-1)][MOVES_ARRAY_WIDTH];

    gameLoop(gridDim, gameArray, movesArray);

    printf("Press ENTER to continue...");

    while(getchar() != '\n'){

    }
    return 0;
}
