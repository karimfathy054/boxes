#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

typedef struct{
    int x;
    int y;
} tuple;

typedef struct{
    //8char name[10];
    char num;
    char letter;
    char color;
    int score;
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
    int gridsize;
};

struct playerdata LB[10]={0};


/*p1={" ",0,0};
p2={" ",0,0};
p3={" ",0,0};
p4={" ",0,0};
p5={" ",0,0};
p6={" ",0,0};
p7={" ",0,0};
p8={" ",0,0};
p9={" ",0,0};
p10={" ",0,0};
temp={" ",0,0};*/

//struct playerdata leaderboard[10]={p1,p2,p3,p4,p5,p6,p7,p8,p9,p10} ;



#endif // STRUCTURES_H_INCLUDED
