#ifndef GAMELOOP_H_INCLUDED
#define GAMELOOP_H_INCLUDED
#include "structures.h"
void gameLoopVScom(int gridDim, char gameArray[][gridDim*2-1], int movesArray[][MOVES_ARRAY_WIDTH]){
    int boxCount = 0;
    struct gamedata savedgame;
    //resetting movesArray
    resetMovesArray(gridDim, movesArray);
    //players
    player player1 = {1, 'A', 3};
    player com = {2, 'C', 4};
    player players[] = {player1, com};

    while(1){
        //points' coordinates
        //int x1, x2, y1, y2;

        tuple p1, p2;

        //if joining is successful, save the move
        if(players[0].num==1){
            printf("Player %d turn!\n", players[0].num);
            printf("Enter 1st point coordinates (x1 y1): ");
            scanf("%d %d", &p1.x, &p1.y);
            printf("Enter 2nd point coordintes (x2 y2): ");
            scanf("%d %d", &p2.x, &p2.y);

            if(joinDots(p1, p2, gridDim, gameArray)==0){
                continue;
            }

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

            printf("want to save?(y/n)");
            char result = getchar();
            if(result=='y' || result=='Y'){
                save(gridDim,gameArray,movesArray);
            }


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
        }else{
            printf("computer turn\n");
            randomline(gridDim , gameArray);
            int newCount = checkBoxes(gridDim, gameArray, players[0]);
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
        //clearing buffer
        //clearBuffer();

        if(boxCount == (gridDim-1)*(gridDim-1)){
            clearBuffer();
            break;
        }
    }
}
//game loop for 2 players mode
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

#endif // GAMELOOP_H_INCLUDED
