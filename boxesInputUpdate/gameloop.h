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
    //points' coordinates
    //tuple p1, p2;
    //reading first point
    // getCoords(
    //     "Enter 1st point coordinates (x1 y1): ",
    //     &p1.x,
    //     &p1.y
    // );
    // //reading second point
    // getCoords(
    //     "Enter 2nd point coordinates (x1 y1): ",
    //     &p2.x,
    //     &p2.y
    // );
    // //if joining is successful, save the move
    // //if(joinDots(p1, p2, gridDim, gameArray)){

    tuple lcoords = humanPlay(2*gridDim-1, gameArray, hconsole, savedAttributes);

    appendMove(lcoords, *playerPointers[index], gridDim, movesArray);

    int newCount = checkBoxes(gridDim, gameArray, playerPointers[index]);

    if(newCount > *boxCount){
        *boxCount = newCount;
    }else{
        //if the player did not score, switch turns
        switchTurns(players);
    }


    printf("boxCount = %d\n", *boxCount);
    printGrid(gridDim*2-1, gameArray);
    //clearBuffer();

    printf("want to save?(y/n)");
    char result = readChar();
    if(result=='y' || result=='Y'){
        save(gridDim,gameArray,movesArray);
    }

    //***undo loop***
    int lastIndex;
    while(lastIndex = getLastMoveIndex(gridDim, movesArray)){
        //getchar(); no char here
        printf("Undo last move? (y/n)");
        char ans = readChar();
        //getchar(); no char here
        if(ans == 'y'){
            undo(gridDim, movesArray, gameArray);
            *boxCount = checkBoxes(gridDim, gameArray, playerPointers[index]);
            //updating lastIndex after deleting the last row bu undo()
            lastIndex = getLastMoveIndex(gridDim, movesArray);
            //if turns were not switched up above, this means that the player had an extra turn after he scored
            if(movesArray[lastIndex][2] == playerPointers[index]->num){
                //to cancel the switch up above
                switchTurns(players);
            }

            //clearBuffer();
            printGrid(gridDim*2-1, gameArray);
            //buffer will be clean here
            continue;
        }else if(ans == 'n'){
            //buffer will be clean here
            break;
        }else{
            //clearBuffer();
            continue;
        }
    }
    //}
}

void gameLoopVScom(int gridDim, char gameArray[][gridDim*2-1], int movesArray[][MOVES_ARRAY_WIDTH], HANDLE hconsole, WORD savedAttributes){
    int boxCount = 0;
    struct gamedata savedgame;
    //resetting movesArray
    resetMovesArray(gridDim, movesArray);
    //players
    player player1 = {1, 'A', 3, 0};
    player com = {2, 'C', 4, 0};
    player players[] = {player1, com};
    player *playerPointers[] = {&player1, &com};
    //recording start time
    start = getTime();

    while(1){
        //points' coordinates
        //int x1, x2, y1, y2;

        if(players[0].num==1){
            humanTurn(gridDim, gameArray, movesArray, playerPointers, players, &boxCount, hconsole, savedAttributes);
        }else{
            printf("computer turn\n");
            randomline(gridDim , gameArray);
            int newCount = checkBoxes(gridDim, gameArray, &com);
            if(newCount > boxCount){
                boxCount = newCount;
            }else{
                //if the player did not score, switch turns
                switchTurns(players);
            }
            printf("boxCount = %d\n", boxCount);
            printGrid(gridDim*2-1, gameArray);
            //clearBuffer();

        }
        //score
        printf("P1 %d - %d COM\n", player1.score, com.score);
        //time
        printTime(start);
        if(boxCount == (gridDim-1)*(gridDim-1)){
            int score =winner(player1.score,com.score);
            add_to_leaderboard(score);
            //clearBuffer();
            break;
        }
    }
}

//game loop for 2 players mode
void gameLoop(int gridDim, char gameArray[][gridDim*2-1], int movesArray[][MOVES_ARRAY_WIDTH], HANDLE hconsole, WORD savedAttributes){
    int boxCount = 0;
    //resetting movesArray
    resetMovesArray(gridDim, movesArray);
    //players
    player player1 = {1, 'A', 3};
    player player2 = {2, 'B', 4};
    player players[] = {player1, player2};
    player *playerPointers[] = {&player1, &player2};
    //start time
    start = getTime();
    while(1){

        humanTurn(gridDim, gameArray, movesArray, playerPointers, players, &boxCount, hconsole, savedAttributes);
        //clearing buffer
        //clearBuffer();
        //score
        printf("P1 %d - %d P2\n", player1.score, player2.score);
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