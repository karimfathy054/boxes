#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

typedef struct{
    int x;
    int y;
} tuple;

typedef struct{
    //char name[10];
    char num;
    char letter;
    char color;
} player;

struct gamedata {
    int Dimensions;
    char Grid[100][100];
    int moves[100][3];
    int turn;
    int score1;
    int score2;




}savedgame,loadgame;

struct playerdata {
    char name[10];
    int score ;
    int maxscore;
    int gridsize;
};

struct playerdata leaderboard[10]={NULL} ;



#endif // STRUCTURES_H_INCLUDED
