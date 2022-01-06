#ifndef SAVEGAME_H_INCLUDED
#define SAVEGAME_H_INCLUDED

#include "structures.h"
#include "userInput.h"

void save (int gridDim,char gameArray[][gridDim*2-1],int movesArray[][3],int scoreP1, int scoreP2){

    savedgame.Dimensions=gridDim;
    savedgame.score1=scoreP1;
    savedgame.score2=scoreP2;
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
    int possibleVal[] = {1,2,3};
    int choice = getIntChoise("choose a save slot:\n[1]slot1\n[2]slot2\n[3]slot3\n",possibleVal,3);
    switch (choice){
    case 1:
        fptr =fopen("data.bin","wb");
        break;
    case 2:
        fptr =fopen("data2.bin","wb");
        break;
    case 3:
        fptr =fopen("data3.bin","wb");
        break;
    default:
        printf("no more save slots\n");
        break;
    }
    if(fptr==NULL){
        printf("error making file\n");
        exit(1);
    }
    fwrite(&savedgame,sizeof(struct gamedata),1,fptr);
    fclose(fptr);
}


#endif // SAVEGAME_H_INCLUDED