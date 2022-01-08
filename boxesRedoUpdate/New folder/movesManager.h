#ifndef MOVESMANAGER_H_INCLUDED
#define MOVESMANAGER_H_INCLUDED

#include "structures.h"
#define MOVES_ARRAY_WIDTH 3

/*movesArray structure:

x  y  player  scoredBoxRank

scoredBox: rank of scored box at a player's turn

note:
rank of box  = order of box starting from zero, increasing horizontally
0 1 2
3 4 5 etc

rank of box at [i][j] = ((i-1)/2)*(gridDim-1)+j

to get i from rank: 2*(rank/(gridDim-1))+1   --> normal integer division
to get j from rank: rank % (gridDim-1)

ANOTHER NOTE:
number of lines in a grid = 2*n*(n-1) where in is gridDim(dots)

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
    while(movesArray[i][0] != -1){
        i++;
    }
    return i-1;
}

void appendMove(tuple lp, player currentPlayer, int gridDim, int movesArray[][MOVES_ARRAY_WIDTH]){
    int i = getLastMoveIndex(gridDim, movesArray) + 1;
    movesArray[i][0] = lp.x;
    movesArray[i][1] = lp.y;
    movesArray[i][2] = currentPlayer.num;
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
