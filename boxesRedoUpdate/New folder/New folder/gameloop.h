#ifndef GAMELOOP_H_INCLUDED
#define GAMELOOP_H_INCLUDED

#include "structures.h"
#include "userInput.h"
#include "timer.h"
#include "leaderboard.h"

time_t start;

void humanTurn(int gridDim, char gameArray[][gridDim*2-1], int movesArray[][MOVES_ARRAY_WIDTH], player *playerPointers[2], player *players,int *boxCount, HANDLE hconsole, WORD savedAttributes){

    char currentNum = players[0].num;
    int index;
    if(currentNum == 1){
        index = 0;
    }else{
        index = 1;
    }

    printf("Player %d turn!\n", currentNum);

    tuple lcoords = humanPlay(2*gridDim-1, gameArray, hconsole, savedAttributes);

    appendMove(lcoords, players[0], gridDim, movesArray);

    int newCount = checkBoxes(gridDim, gameArray, playerPointers[index]);

    if(newCount > *boxCount){
        *boxCount = newCount;
    }else{
        //if the player did not score, switch turns
        switchTurns(players);
    }

    printf("boxCount = %d\n", *boxCount);
    fflush(stdin);

    int redoArray[2*gridDim*(gridDim-1)][MOVES_ARRAY_WIDTH];
    resetMovesArray(gridDim, redoArray);
    while(1){
        int selection = optionsMenu(hconsole, savedAttributes, gridDim, gameArray, movesArray, players);
        if(!selection){
            //clear all redo
            //resetMovesArray(gridDim, redoArray);
            break;
        }else if(selection == 1){
            //save
            if (players[1].letter =='C'){
                save(gridDim, gameArray, movesArray, playerPointers[0]->score, playerPointers[1]->score,0,currentNum);
            }
            else{
                save(gridDim, gameArray, movesArray, playerPointers[0]->score, playerPointers[1]->score,1,currentNum);
            }

        }else if(selection == 2){
            //undo
            int lastIndex;
            if((lastIndex = getLastMoveIndex(gridDim, movesArray)) != -1){
                player lastPlayer = getPlayerByNum(movesArray[lastIndex][2], players);
                tuple ulcoor = {movesArray[lastIndex][0], movesArray[lastIndex][1]};
                appendMove(ulcoor, lastPlayer, gridDim, redoArray);
                undo(gridDim, movesArray, gameArray);
                forceTurn(players, lastPlayer.num);
                *boxCount = checkBoxes(gridDim, gameArray, playerPointers[lastPlayer.num - 1]);
            }else{
                printf("Nothing left to undo!\n");
            }
        }else if(selection == 3){
            //redo
            int lastRedoIndex;
            if((lastRedoIndex = getLastMoveIndex(gridDim, redoArray)) != -1){
                player lastPlayer = getPlayerByNum(redoArray[lastRedoIndex][2], players);
                forceTurn(players, lastPlayer.num);
                tuple rlcoor = {redoArray[lastRedoIndex][0], redoArray[lastRedoIndex][1]};
                drawLine(rlcoor, gridDim, gameArray);
                appendMove(rlcoor, lastPlayer, gridDim, movesArray);
                for(int i = 0; i < MOVES_ARRAY_WIDTH; i++){
                    redoArray[lastRedoIndex][i] = -1;
                }
                newCount = checkBoxes(gridDim, gameArray, playerPointers[lastPlayer.num - 1]);
                if(newCount > *boxCount){
                    *boxCount = newCount;
                }else{
                    switchTurns(players);
                }
            }else{
                printf("Nothing left to redo!\n");
            }
        }else if(selection == 4){
            main();
        }
    }


}

void gameLoopVScom(int gridDim, char gameArray[][gridDim*2-1], int movesArray[][MOVES_ARRAY_WIDTH], HANDLE hconsole, WORD savedAttributes ){
    int boxCount = 0;
    struct gamedata savedgame;
    //resetting movesArray
    resetMovesArray(gridDim, movesArray);
    //players
    player player1 = {1, 'A', PLAYER1_COLOR, 0};
    int playermoves=0;
    player com = {2, 'C', PLAYER2_COLOR, 0};
    int computermoves=0;
    int remaininglines=(gridDim-1)*gridDim*2;
    player players[] = {player1, com};
    player *playerPointers[] = {&player1, &com};
    //recording start time
    start = getTime();
    /*if (isloaded==1){
        players[0].num=savedgame.turn;
    }*/
    while(1){
        //points' coordinates
        //int x1, x2, y1, y2;

        if(players[0].num==1){
            humanTurn(gridDim, gameArray, movesArray, playerPointers, players, &boxCount, hconsole, savedAttributes);
            playermoves = getPlayerMoves(1, gridDim, movesArray);
            remaininglines = getRemainingLines(gridDim, movesArray);
        }else{
            printf("computer turn\n");
            tuple lcoor = randomline(gridDim , gameArray);
            appendMove(lcoor, players[0], gridDim, movesArray);

            computermoves = getPlayerMoves(2, gridDim, movesArray);
            remaininglines = getRemainingLines(gridDim, movesArray);
            int newCount = checkBoxes(gridDim, gameArray, &com);
            if(newCount > boxCount){
                boxCount = newCount;
            }else{
                //if the player did not score, switch turns
                switchTurns(players);
            }
            printf("boxCount = %d\n", boxCount);
            //printGrid(gridDim*2-1, gameArray);
            printColoredGrid(gridDim*2-1, gameArray, players, movesArray, hconsole, savedAttributes);
            //clearBuffer();

        }
        //score
        printf("P1 %d - %d COM\n", player1.score, com.score);
        printf("player moves:%d\tcomputer moves:%d\n",playermoves,computermoves);
        printf("remaining lines:%d\n",remaininglines);
        //time
        printTime(start);
        if(boxCount == (gridDim-1)*(gridDim-1)){
            int score = winnerVScom(player1.score,com.score);
            add_to_leaderboard(score);
            //clearBuffer();
            break;
        }
    }
}

//game loop for 2 players mode
void gameLoop(int gridDim, char gameArray[][gridDim*2-1], int movesArray[][MOVES_ARRAY_WIDTH], HANDLE hconsole, WORD savedAttributes,int isloaded){
    int boxCount = 0;
    int remaininglines=(gridDim-1)*gridDim*2;
    //resetting movesArray
    resetMovesArray(gridDim, movesArray);
    //players
    player player1 = {1, 'A', PLAYER1_COLOR, 0};
    int player1moves=0;
    player player2 = {2, 'B', PLAYER2_COLOR, 0};
    int player2moves =0;
    player players[] = {player1, player2};
    player *playerPointers[] = {&player1, &player2};
    //start time
    start = getTime();
    if((isloaded==1)&&(players[1].num!=savedgame.turn)){
            switchTurns(players);
            printf("is loaded\n");
    }


    while(1){

        humanTurn(gridDim, gameArray, movesArray, playerPointers, players, &boxCount, hconsole, savedAttributes);
        if(players[0].num==1){
            player1moves = getPlayerMoves(1, gridDim, movesArray);
            remaininglines = getRemainingLines(gridDim, movesArray);
        }
        else{
            player2moves = getPlayerMoves(2, gridDim, movesArray);
            remaininglines = getRemainingLines(gridDim, movesArray);
        }
        //clearing buffer
        //clearBuffer();
        //score
        printf("P1 %d - %d P2\n", player1.score, player2.score);
        printf("player1 moves:%d - player2 moves:%d\n",player1moves,player2moves);
        printf("remaining lines:%d\n",remaininglines);
        //time
        printTime(start);
        if(boxCount == (gridDim-1)*(gridDim-1)){
            int score = winner(player1.score,player2.score);
            add_to_leaderboard(score);
            //clearBuffer();
            break;
        }
    }
}

#endif // GAMELOOP_H_INCLUDED
