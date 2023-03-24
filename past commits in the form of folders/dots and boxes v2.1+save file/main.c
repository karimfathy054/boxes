#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "movesManager.h"
#include "RandomLineGen.h"
#include "SAVEGAME.h"
#include "GameCore.h"
#include "gameloop.h"
void clearBuffer(){
    while(getchar() != '\n'){}
}


//leave gameLoop as the last method before main --->ok
//game loop for single player mode



int main(){

    //HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    //SetConsoleTextAttribute(handle, FOREGROUND_RED);

    srand(time(0));
    int gridDim;
    int modeNum ;
    printf("Select mode\n[1]single player\n[2]two players\n[3]load game\n");
    scanf("%d",&modeNum);
    printf("Enter dimension(nxn): ");
    scanf("%d", &gridDim);
    //clearing buffer
    getchar();
    int arrayDim = gridDim*2-1;
    char gameArray[arrayDim][arrayDim];
    initGameArray(arrayDim, gameArray);
    //printGrid(arrayDim, gameArray);

    //number of lines = 2*gridDim*(gridDim-1)
    //stores coordinates of last line
    //resets in at the beginning of gameLoop()
    int movesArray[2*gridDim*(gridDim-1)][MOVES_ARRAY_WIDTH];
    if(modeNum==1){
        printGrid(arrayDim, gameArray);
        gameLoopVScom(gridDim, gameArray, movesArray);
    }
    else if(modeNum==2){
        printGrid(arrayDim, gameArray);
        gameLoop(gridDim,gameArray,movesArray);
    }
    else if(modeNum==3){
        FILE* filepointer;
        filepointer = fopen("data.bin","rb");
        if(filepointer==NULL){
            printf("error reading file\n");
            exit(1);
        }
        fread(&savedgame,sizeof(struct gamedata),1,filepointer);
        int gridDim=savedgame.Dimensions;
        int arrayDim = gridDim*2-1;
        for(int i=0;i<(2*gridDim*(gridDim-1));i++){
            for(int j=0;j<MOVES_ARRAY_WIDTH;j++){
                movesArray[i][j]=savedgame.moves[i][j];
            }
        }
        for(int i=0;i<arrayDim;i++){
            for(int j=0;j<arrayDim;j++){
                gameArray[i][j]=savedgame.Grid[i][j];
            }
        }
        printGrid(arrayDim, gameArray);
        gameLoopVScom(gridDim, gameArray, movesArray);
    }
    else
    printf("not a valid option\n");
    printf("Press ENTER to continue...");

    while(getchar() != '\n'){

    }
    return 0;
}
