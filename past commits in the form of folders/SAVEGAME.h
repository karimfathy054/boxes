#ifndef SAVEGAME_H_INCLUDED
#define SAVEGAME_H_INCLUDED

#include "movesManager.h"

state game ;
int movescounter=0;
void saveDIMENSIONS(int gridDim){
    game.Dimensions=gridDim;
    FILE *fptr;
    if((fptr=fopen("savedDIMENSIONS.bin","wb")==NULL)){
        printf("error making file\n");
        exit(1);
    }
    if((fwrite(&game.Dimensions,sizeof(int),1,fptr))!=1){
        printf("error saving dimensions\n");
    }
    fclose(fptr);
}
void Savemovesarray(state game ,int movesArray[][3]){
    while(movesArray[movescounter][0]!=-1){
        game.moves[movescounter][0]=movesArray[movescounter][0];
        game.moves[movescounter][1]=movesArray[movescounter][1];
        game.moves[movescounter][2]=movesArray[movescounter][2];
        movescounter++;
    }
    FILE *fptr1 ;
    if((fptr1=fopen("savedmoves.bin","wb")==NULL)){
        printf("error making file\n");
        exit(1);
    }
    if((fwrite(&game.moves,sizeof(int),movescounter*3,fptr1))!=movescounter*3){
        printf("errror saving moves\n");
    }
    fclose(fptr1);
}
void saveGrid(state game, int gridDim ,char gameArray[][gridDim*2-1]){
    for(int i=0;i<gridDim*2-1;i++){
        for(int j=0;j<gridDim*2-1;j++){
            game.Grid[i][j]=gameArray[i][j];
        }
    }
    FILE *fptr2 ;
    if((fptr2=fopen("savedgrid.bin","wb")==NULL)){
        printf("error making file\n");
        exit(1);
    }

    if(fwrite(&game.Grid,sizeof(char),2*(gridDim*2-1),fptr2)!=2*(gridDim*2-1)){
        printf("error saving  grid\n");
    }
    fclose(fptr2);
}
void save (state game ,int movesArray[][3], int gridDim ,char gameArray[][gridDim*2-1]){
    saveDIMENSIONS(gridDim);
    Savemovesarray(game,movesArray);
    saveGrid(game,gridDim,gameArray);
}
void loadmovesarray (state game, int movesArray[][3]){
    FILE *fptr1 ;
    if((fptr1=fopen("savedmoves.bin","rb")==NULL)){
        printf("error reading file\n");
        exit(1);
    }
    if(fread(&game.moves,sizeof(int),movescounter*3,fptr1)!=movescounter*3){
        printf("errror loading moves");
    }
    int i=0;
    while(game.moves[i][0]!=-1){
        movesArray[i][0] = game.moves[i][0];
        movesArray[i][1] = game.moves[i][1];
        movesArray[i][2] = game.moves[i][2];
        i++;
    }
    fclose(fptr1);
}
void loadsavedgrid (state game, int gridDim ,char gameArray[][gridDim*2-1]){
    FILE *fptr2 ;
    if((fptr2=fopen("savedgrid.bin","rb")==NULL)){
        printf("error reading file\n");
        exit(1);
    }

    if(fread(&game.Grid,sizeof(char),2*(gridDim*2-1),fptr2)!=2*(gridDim*2-1)){
        printf("error loading  grid\n");
    }
    for(int i=0;i<gridDim*2-1;i++){
        for(int j=0;j<gridDim*2-1;j++){
            gameArray[i][j] = game.Grid[i][j];
        }
    }

    fclose(fptr2);
}
void loadDIMENSIONS(int gridDim){

    FILE *fptr;
    if((fptr=fopen("savedDIMENSIONS,bin","rb")==NULL)){
        printf("error reading file\n");
        exit(1);
    }
    if((fread(&game.Dimensions,sizeof(int),1,fptr))!=1){
        printf("error loading dimensions\n");
    }
    game.Dimensions=gridDim;
    fclose(fptr);
}
void loadGame (state game, int movesArray[][3],int gridDim ,char gameArray[][gridDim*2-1]){
    loadDIMENSIONS(gridDim);
    loadmovesarray(game,movesArray);
    loadsavedgrid(game,gridDim,gameArray);
}


#endif // SAVEGAME_H_INCLUDED
