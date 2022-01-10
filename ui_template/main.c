#include <stdio.h>
#include <windows.h>   // WinApi header
#include <conio.h>
#define DEFSIZE 6

typedef struct{
    int x;
    int y;
}tuple;

void changeColor(HANDLE hconsole){
    SetConsoleTextAttribute(hconsole, 64+32+16+1);
}

void resetColor(HANDLE hconsole, WORD savedAttributes){
    SetConsoleTextAttribute(hconsole, savedAttributes);
}

void initGameArray(int n, char gameArray[n][n]){
    for(int i = 0; i < n; i++){
        for(int j = 0; j <n; j++){
            if(i % 2){
                gameArray[i][j] = -1;
            }else{
                if(j % 2){
                    gameArray[i][j] = -1;
                }else{
                    gameArray[i][j] = 0;
                }
            }
        }
    }
}

void printGrid(int n, char gameArray[n][n], tuple index_highlighted, HANDLE hconsole, WORD savedAttributes){
    //n --> actual size not gridDim
    int isColored = 0;
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(i == index_highlighted.x && j == index_highlighted.y){
                    changeColor(hconsole);
                    isColored = 1;
            }

            if(gameArray[i][j] == 0){
                printf("%c ", 'o');
            }else if(gameArray[i][j] == -1){
                printf("  ");
            }else{
                printf("%c ", gameArray[i][j]);
            }

            if(isColored){
                    resetColor(hconsole, savedAttributes);
                }
        }
        printf("\n");
    }
    //clearBuffer(); no char here
}

// int drawLine(tuple p1, tuple p2, int gridDim, char gameArray[][gridDim*2-1]){
//     if(gameArray[p1.x + p2.x][p1.y + p2.y] == -1){
//         if((p1.x+p2.x) % 2){
//             gameArray[p1.x + p2.x][p1.y + p2.y] = '|';
//         }else{
//             gameArray[p1.x + p2.x][p1.y + p2.y] = '-';
//         }
//         return 1;
//     }else{
//         printf("Already joined!\n");
//         return 0;
//     }
// }

int drawLine(tuple lcoord, int gridDim, char gameArray[][gridDim*2-1]){
    if(gameArray[lcoord.x][lcoord.y] == -1){
        if((lcoord.x) % 2){
            gameArray[lcoord.x][lcoord.y] = '|';
        }else{
            gameArray[lcoord.x][lcoord.y] = '-';
        }
        return 1;
    }else{
        printf("Already joined!\n");
        return 0;
    }
}

void humanPlay(int n, char gameArray[n][n], HANDLE hconsole, WORD savedAttributes){
    int i = 0, j = 1;
    tuple th = {0,1};
    int cont = 1;
    printGrid(n, gameArray, th, hconsole, savedAttributes);
    while(cont){
        char c = getch();
        switch(c){
        case 's': //down
            if(i+1 != n){
                if(j-1 < 0){
                    j++;
                }else{
                    j--;
                }
            }
            i = (i+1) % n;
            th.x = i;
            th.y = j;
            system("CLS");
            printGrid(n, gameArray, th, hconsole, savedAttributes);
            break;
        case 'w': //up
            if(i == 0){
                i = n-1;
            }else{
                if(j-1 < 0){
                    j++;
                }else{
                    j--;
                }
                i = (i-1) % n;
            }
            th.x = i;
            th.y = j;
            system("CLS");
            printGrid(n, gameArray, th, hconsole, savedAttributes);
            break;
        case 'd': //right
            if(j == n-2 || j == n-1){
                j = !(i%2);
                // if(i%2){
                //     j = 0;
                // }else{
                //     j = 1;
                // }
            }else{
                j = (j+2) % n;
            }
            th.x = i;
            th.y = j;
            system("CLS");
            printGrid(n, gameArray, th, hconsole, savedAttributes);
            break;
        case 'a': //left
            if(j == 0 ||j == 1){
                j = (i%2) + n - 2;
            }else{
                j = (j-2) % n;
            }
            th.x = i;
            th.y = j;
            system("CLS");
            printGrid(n, gameArray, th, hconsole, savedAttributes);
            break;
        case '\r': //enter
            th.x = i;
            th.y = j;
            system("CLS");
            drawLine(th, (n+1)/2, gameArray);
            printGrid(n, gameArray, th, hconsole, savedAttributes);
            break;
        case 'c': //to exit
            cont = 0;
            break;
        default:
            break;
        }
        printf("%d %d\n", th.x, th.y);
    }
}

int main(){
    HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    GetConsoleScreenBufferInfo(hconsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;
    
    char gameArray[DEFSIZE*2-1][DEFSIZE*2-1];
    initGameArray(DEFSIZE*2-1, gameArray);

    humanPlay(DEFSIZE*2-1, gameArray, hconsole, saved_attributes);

    printf("Press any key to exit...");
    //color();
    //getchar();  // wait
    getch();
    return 0;
}