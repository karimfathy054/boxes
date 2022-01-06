#ifndef LEADERBOARD_H_INCLUDED
#define LEADERBOARD_H_INCLUDED

#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "structures.h"


int comparator(const void *p, const void *q)
{
    int l = ((struct playerdata *)p)->score;
    int r = ((struct playerdata *)q)->score;
    return (r - l);
}
//struct playerdata LB[10]={0};
//qsort(LB,10,sizeof(LB[0]),comparator);

void add_to_leaderboard (int score){
    struct playerdata lb[10]={0};
    FILE* fpointer;
    fpointer=fopen("lb.bin","rb");
    if(fpointer==NULL){
        printf("error creating file\n");
        //exit(1);
    }
    fread(lb,sizeof(struct playerdata),10,fpointer);
    fclose(fpointer);
    //char name[16];

    if(score>lb[9].score){
        char name[20];
        printf("type your name\n");
        gets(name);
        int i;
        int found=0;
        for (i=0;i<10;i++){
            char name_sch[20];
            char lb_name_sch[20];
            strcpy(name_sch,name);
            strcpy(lb_name_sch,lb[i].name);
            allsmall(name_sch);
            allsmall(lb_name_sch);
            int x= strcmp(name_sch,lb_name_sch);
            if(x==0){
                found=1;
                break;
            }
        }
        if(found==0){
            strcpy(lb[9].name,name);
            lb[9].score=score;
        }
        else{
            if(score>lb[i].score){
                //strcpy(lb[i].name,name);
                lb[i].score=score;
            }
            else{
                printf("you couldn't beat your last highscore.\n");
            }
        }
        /*strcpy(lb[9].name,name);
        lb[9].score=score;*/
    }
    else{
        printf("unfortunately you are not one of the top players.\n");
        return;
    }
    qsort(lb,10,sizeof(lb[0]),comparator);
    FILE* fptr;
    fptr=fopen("lb.bin","wb");
    if(fptr==NULL){
        printf("error creating file\n");
        exit(1);
    }
    fwrite(lb,sizeof(struct playerdata),10,fptr);
    fclose(fptr);
    for(int i=0;i<10;i++){
        printf("name:%s\tscore:%d\n",lb[i].name,lb[i].score);
    }

}
void print_Leaderboard(){
    struct playerdata lb[10]={0};
    FILE* fptr;
    fptr=fopen("lb.bin","rb");
    if(fptr==NULL){
        printf("error reading file\n");
        exit(1);
    }
    fread(lb,sizeof(struct playerdata),10,fptr);
    for(int i=0;i<10;i++){
        printf("name:%s\tscore:%d\n",lb[i].name,lb[i].score);
    }
}






#endif // LEADERBOARD_H_INCLUDED