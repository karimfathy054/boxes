#ifndef SAVEGAME_H_INCLUDED
#define SAVEGAME_H_INCLUDED

#include "structures.h"

void save (struct gamedata savedgame ,int gridDim,char gameArray[][gridDim*2-1],int movesArray[][3]){
    savedgame.Dimensions=gridDim;
    for(int i=0;i<(gridDim*2-1);i++){
        for(int j=0;j<(gridDim*2-1);j++){
            savedgame.Grid[i][j]=gameArray[i][j];
        }
    }
    for(int i=0;i<(2*gridDim*(gridDim-1));i++){
            savedgame.moves[i][0]=movesArray[i][0];
            savedgame.moves[i][1]=movesArray[i][1];
            savedgame.moves[i][2]=movesArray[i][2];
    }
    FILE* fptr;
    fptr =fopen("data.txt","w");
    if(fptr==NULL){
        printf("error making file\n");
    }
    fprintf(fptr,"%d",savedgame.Dimensions);
    for(int i=0;i<(gridDim*2-1);i++){
        for(int j=0; j<(gridDim*2-1) ; j++){
            fprintf(fptr,"%d",savedgame.Grid[i][j]);
        }
    }
    for(int i=0;i<(2*gridDim*(gridDim-1));i++){
        for(int j=0; j<3 ; j++){
            fprintf(fptr,"%d",savedgame.moves[i][j]);
        }
    }
    fclose(fptr);
}

#endif // SAVEGAME_H_INCLUDED
