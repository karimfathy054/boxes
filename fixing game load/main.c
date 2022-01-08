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
#include "userInput.h"
#include "leaderboard.h"
#include "menu.h"



//leave gameLoop as the last method before main --->ok
//game loop for single player mode



int main(){
    //logo();

    srand(time(0));
    int gridDim;
    int modeNum ;

    HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    //changing background color
    //changeColor(hconsole, DEF_COLOR);

    GetConsoleScreenBufferInfo(hconsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    //printf("Select mode\n[1]single player\n[2]two players\n[3]load game\n");
    //scanf("%d",&modeNum);

    // int possibleVal[] = {1,2,3,4};
    // modeNum = getIntChoise(
    //     "Select mode\n[1]single player\n[2]two players\n[3]load game\n[4]Leaderboard\n",
    //     possibleVal,
    //     4
    // );

    char startMenuItems[][MAXLENGTH] = {"[1]single player", "[2]two players", "[3]load game", "[4]Leaderboard"};
    modeNum = menu(hconsole, saved_attributes, 4, startMenuItems, "Select Mode\nUse W/S for up/down, ENTER to select.");

    //number of lines = 2*gridDim*(gridDim-1)
    //stores coordinates of last line
    //resets in at the beginning of gameLoop()
    if(modeNum==4){
        print_Leaderboard();
        int possibleVal1[] = {1,2};
        int choice = getIntChoise("[1]back\n[2]exit\nType the number of your choice.",possibleVal1,2);
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
        //gridDim = getIntegerUserInput("Enter dimension(nxn): ");
        char diff[][MAXLENGTH] = {"Easy", "Hard"};
        if(menu(hconsole, saved_attributes, 2, diff, "Choose Difficulty") == 1){
            //2x2 (3x3 dots)
            gridDim = 3;
        }else{
            //5x5 (6x6 dots)
            gridDim = 6;
        }

        //initializing
        int arrayDim = gridDim*2-1;
        char gameArray[arrayDim][arrayDim];
        initGameArray(arrayDim, gameArray);
        int movesArray[2*gridDim*(gridDim-1)][MOVES_ARRAY_WIDTH];
        resetMovesArray(gridDim, movesArray);

        printGrid(arrayDim, gameArray);

        //confirm
        fflush(stdin);
        char conf = askYN("Go back?\nType y/n then hit ENTER.");
        if(conf == 'y'){
            system("CLS");
            main();
        }

        system("CLS");

        if(modeNum == 1){
            int isloaded =0;
            gameLoopVScom(gridDim, gameArray, movesArray, hconsole, saved_attributes);
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
            int isloaded =0;
            gameLoop(gridDim,gameArray,movesArray, hconsole, saved_attributes,isloaded);
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
            movesArray[i][0]=savedgame.moves[i][0];
            movesArray[i][1]=savedgame.moves[i][1];
            movesArray[i][2]=savedgame.moves[i][2];
        }
        for(int i=0;i<(2*gridDim*(gridDim-1));i++){
            printf("%d %d %d\n",movesArray[i][0],movesArray[i][1],movesArray[i][2]);
        }

        //loading gameArray
        for(int i=0;i<arrayDim;i++){
            for(int j=0;j<arrayDim;j++){
                gameArray[i][j]=savedgame.Grid[i][j];
            }
        }
        printGrid(arrayDim, gameArray);
        int isloaded = 1;
        if(savedgame.gamemode==0){
            gameLoopVScom(gridDim, gameArray, movesArray, hconsole, saved_attributes);
        }
        else if (savedgame.gamemode==1){
            gameLoop(gridDim, gameArray, movesArray, hconsole, saved_attributes,isloaded);
        }

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
