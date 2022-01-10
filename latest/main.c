#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "movesManager.h"
#include "RandomLineGen.h"
#include "SAVEGAME.h"
#include "GameCore.h"
#include "gameloop.h"
#include "userInput.h"



//leave gameLoop as the last method before main --->ok
//game loop for single player mode



int main(){

    srand(time(0));
    int gridDim;
    int modeNum ;
    
    //printf("Select mode\n[1]single player\n[2]two players\n[3]load game\n");
    //scanf("%d",&modeNum);
    
    int possibleVal[] = {1,2,3};
    modeNum = getIntChoise(
        "Select mode\n[1]single player\n[2]two players\n[3]load game\n",
        possibleVal,
        3
    );

    //number of lines = 2*gridDim*(gridDim-1)
    //stores coordinates of last line
    //resets in at the beginning of gameLoop()
    
    
    if(modeNum != 3){

        //new game
        gridDim = getIntegerUserInput("Enter dimension(nxn): ");
        
        //initializing
        int arrayDim = gridDim*2-1;
        char gameArray[arrayDim][arrayDim];
        initGameArray(arrayDim, gameArray);
        int movesArray[2*gridDim*(gridDim-1)][MOVES_ARRAY_WIDTH];
        resetMovesArray(gridDim, movesArray);
        
        printGrid(arrayDim, gameArray);
        
        if(modeNum == 1){
            gameLoopVScom(gridDim, gameArray, movesArray);
        }else if(modeNum == 2){
            gameLoop(gridDim,gameArray,movesArray);
        }
    }else if(modeNum == 3){
        printf("loading...\n");
        FILE* filepointer;
        filepointer = fopen("data.bin","rb");
        
        if(filepointer==NULL){
            printf("error reading file\n");
            exit(1);
        }
        fread(&savedgame,sizeof(struct gamedata),1,filepointer);
        
        printf("done loading\n");

        //loading dims
        int gridDim=savedgame.Dimensions;
        int arrayDim = gridDim*2-1;
        char gameArray[arrayDim][arrayDim];
        initGameArray(arrayDim, gameArray);
        int movesArray[2*gridDim*(gridDim-1)][MOVES_ARRAY_WIDTH];
        resetMovesArray(gridDim, movesArray);

        //loading moves
        for(int i=0;i<(2*gridDim*(gridDim-1));i++){
            for(int j=0;j<MOVES_ARRAY_WIDTH;j++){
                movesArray[i][j]=savedgame.moves[i][j];
            }
        }

        //loading gameArray
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