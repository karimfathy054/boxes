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
#include "leaderboard.h"



//leave gameLoop as the last method before main --->ok
//game loop for single player mode



int main(){
    //logo();

    srand(time(0));
    int gridDim;
    int modeNum ;

    //printf("Select mode\n[1]single player\n[2]two players\n[3]load game\n");
    //scanf("%d",&modeNum);

    int possibleVal[] = {1,2,3,4};
    modeNum = getIntChoise(
        "Select mode\n[1]single player\n[2]two players\n[3]load game\n[4]Leaderboard\n",
        possibleVal,
        4
    );

    //number of lines = 2*gridDim*(gridDim-1)
    //stores coordinates of last line
    //resets in at the beginning of gameLoop()
    if(modeNum==4){
        print_Leaderboard();
        int possibleVal1[] = {1,2};
        int choice = getIntChoise("[1]back\n[2]exit\n",possibleVal1,2);
        switch(choice){
            case 1:
                main();
            case 2:
                exit(0);
            default:
                exit(0);
        }
    }


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
            int possibleVal1[] = {1,2};
            int choice = getIntChoise("[1]back\n[2]exit\n",possibleVal1,2);
            switch(choice)
            {
            case 1:
                main();
            case 2:
                exit(0);
            default:
                exit(0);
            }

        }else if(modeNum == 2){
            gameLoop(gridDim,gameArray,movesArray);
            int possibleVal1[] = {1,2};
            int choice = getIntChoise("[1]back\n[2]exit\n",possibleVal1,2);
            switch(choice)
            {
            case 1:
                main();
            case 2:
                exit(0);
            default:
                exit(0);
            }
        }
    }else if(modeNum == 3){
        printf("loading...\n");
        FILE* filepointer;
        int possibleVal[] = {1,2,3};
        int choice = getIntChoise("choose a save slot:\n[1]slot1\n[2]slot2\n[3]slot3\n",possibleVal,3);
        switch (choice){
        case 1:
            filepointer =fopen("data.bin","rb");
            break;
        case 2:
            filepointer =fopen("data2.bin","rb");
            break;
        case 3:
            filepointer =fopen("data3.bin","rb");
            break;
        default:
        printf("no more save slots\n");
        break;
        }
        //filepointer = fopen("data.bin","rb");

        if(filepointer==NULL){
            printf("empty slot\n");
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
        int possibleVal1[] = {1,2};
        int choice2 = getIntChoise("[1]back\n[2]exit\n",possibleVal1,2);
        switch(choice2)
        {
            case 1:
                main();
            case 2:
                exit(0);
            default:
                exit(0);
        }
    }
    else
    printf("not a valid option\n");
    printf("Press ENTER to continue...");

    while(getchar() != '\n'){

    }
    return 0;
}
