#ifndef MOVESMANAGER_H_INCLUDED
#define MOVESMANAGER_H_INCLUDED

#include "structures.h"
#define MOVES_ARRAY_WIDTH 3

/*movesArray structure:
x  y  player

number of lines in a grid = 2*gridDim*(gridDim-1)
*/

void resetMovesArray(int gridDim, int movesArray[][MOVES_ARRAY_WIDTH]){
    for(int i = 0; i < (2*gridDim*(gridDim-1)); i++){
        for(int j = 0; j < MOVES_ARRAY_WIDTH; j++){
            movesArray[i][j] = -1;
        }
    }
}

//get index of last move in movesArray
int getLastMoveIndex(int gridDim, int movesArray[][MOVES_ARRAY_WIDTH]){
    int i = 0;
    while(movesArray[i][0] != -1 && i < 2*gridDim*(gridDim - 1)){
        i++;
    }
    //i will be zero only if movesArray[0][0] = -1 (empty)
    if(!i){
        return -1;
    }
    return i-1;
}

void appendMove(tuple lp, player currentPlayer, int gridDim, int movesArray[][MOVES_ARRAY_WIDTH]){
    int i = getLastMoveIndex(gridDim, movesArray) + 1;
    movesArray[i][0] = lp.x;
    movesArray[i][1] = lp.y;
    movesArray[i][2] = currentPlayer.num;
}

player getPlayerByLine(tuple lcoor, player *players, int gridDim, int movesArray[][MOVES_ARRAY_WIDTH]){
    int length = getLastMoveIndex(gridDim, movesArray) + 1;
    int playerIndex = 0;
    for(int i = 0; i < length; i++){
        if(movesArray[i][0] == lcoor.x && movesArray[i][1] == lcoor.y){
            playerIndex = movesArray[i][2];
        }
    }
    if(playerIndex == players[0].num){
        return players[0];
    }
    return players[1];
}

player getPlayerByLetter(char letter, player *players){
    if(letter == players[0].letter){
        return players[0];
    }
    return players[1];
}

player getPlayerByNum(int num, player *players){
    if(num == players[0].num){
        return players[0];
    }
    return players[1];
}

/*returns an array containing number of the player who drew that line as the first element,
and rank of scored box(if scored) as second element
*/
/* int * getLineData(tuple lcoor, int gridDim, int movesArray[][MOVES_ARRAY_WIDTH]){
    int data[2];
    for(int i = 0; i < 2*gridDim*(gridDim-1); i++){
        if(movesArray[i][0] == lcoor.x && movesArray[i][1] == lcoor.y){
            //playerNUm
            data[0] = movesArray[i][3];
            //scoredBox
            data[1] = movesArray[i][4];
            break;
        }
    }
    return data;
} */

#endif // MOVESMANAGER_H_INCLUDED