#ifndef GAMECORE_H_INCLUDED
#define GAMECORE_H_INCLUDED
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "menu.h"
#include "structures.h"

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

void printGrid(int n, char gameArray[n][n]){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(gameArray[i][j] == 0){
                printf("%c ", 'o');
            }else if(gameArray[i][j] == -1){
                printf("  ");
            }else{
                printf("%c ", gameArray[i][j]);
            }
        }
        printf("\n");
    }
    //clearBuffer(); no char here
}

void switchTurns(player players[2]){
    player temp = players[0];
    players[0] = players[1];
    players[1] = temp;
}

int connectDots(tuple p1, tuple p2, int gridDim, char gameArray[][gridDim*2-1]){
    if(gameArray[p1.x + p2.x][p1.y + p2.y] == -1){
        if((p1.x+p2.x) % 2){
            gameArray[p1.x + p2.x][p1.y + p2.y] = '|';
        }else{
            gameArray[p1.x + p2.x][p1.y + p2.y] = '-';
        }
        return 1;
    }else{
        printf("Already joined!\n");
        return 0;
    }
}

int joinDots(tuple p1, tuple p2, int gridDim, char gameArray[][gridDim*2-1]){
    // 0 <= x, y < n-1
    if(
        p1.x >= 0 && p1.x < gridDim
        && p1.y >= 0 && p1.y < gridDim
        && p2.x >= 0 && p2.x < gridDim
        && p2.y >= 0 && p2.y < gridDim
    ){
        if(p1.x != p2.x && p1.y != p2.y){
            //not horizontal or vertical ie diagonal
            printf("You can't join dots diagonally!\n");
            return 0;
        }else if(p1.x == p2.x && abs(p1.y-p2.y) == 1){
            return connectDots(p1, p2, gridDim, gameArray);
        }else if(p1.y == p2.y && abs(p1.x-p2.x) == 1){
            return connectDots(p1, p2, gridDim, gameArray);
        }else{
            printf("Can't join these two dots.\n");
            return 0;
        }
    }else{
        printf("Invalid input.\n");
        return 0;
    }
}

int checkBoxes(int gridDim, char gameArray[][gridDim*2-1], player *currentPlayer){
    int boxCount = 0;
    currentPlayer->score = 0;
    for(int i = 1; i <= gridDim*2-2; i += 2){
        for(int j = 1; j <= gridDim*2-2; j += 2){
            int u = gameArray[i-1][j];
            int d = gameArray[i+1][j];
            int l = gameArray[i][j-1];
            int r = gameArray[i][j+1];
            if(
                u != -1 &&
                d != -1 &&
                l != -1 &&
                r != -1
            ){
                if(gameArray[i][j] == -1){
                    gameArray[i][j] = currentPlayer->letter;
                    currentPlayer->score++;
                }else if(gameArray[i][j] == currentPlayer->letter){
                    currentPlayer->score++;
                }
                boxCount++;
            }else{
                //to remove a letter if the box was undone
                gameArray[i][j] = -1;
            }
        }
    }
    return boxCount;
}

void printGridWithCursor(int n, char gameArray[n][n], tuple index_highlighted, HANDLE hconsole, WORD savedAttributes){
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

tuple humanPlay(int n, char gameArray[n][n], HANDLE hconsole, WORD savedAttributes){
    int i = 0, j = 1;
    //line coordinate
    tuple th = {0,1};
    int cont = 1;
    printGridWithCursor(n, gameArray, th, hconsole, savedAttributes);
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
            break;
        case 'd': //right
            if(j == n-2 || j == n-1){
                j = !(i%2);
                //alternative for:
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
            break;
        case 'a': //left
            if(j == 0 ||j == 1){
                j = (i%2) + n - 2;
            }else{
                j = (j-2) % n;
            }
            th.x = i;
            th.y = j;
            break;
        case '\r': //enter
            th.x = i;
            th.y = j;
            if(drawLine(th, (n+1)/2, gameArray)){
                cont = 0;
            }
            break;
        default:
            break;
        }
        system("CLS");
        printGridWithCursor(n, gameArray, th, hconsole, savedAttributes);
        //printf("%d %d\n", th.x, th.y);
    }
    return th;
}



void undo(int gridDim, int movesArray[][MOVES_ARRAY_WIDTH], char gameArray[][2*gridDim-1]){
    //lastX, lastY: coordinates of last joined line
    int lastX, lastY, i = 0;
    i = getLastMoveIndex(gridDim, movesArray);
    lastX = movesArray[i][0];
    lastY = movesArray[i][1];
    for(int j = 0; j < 4; j++){
        movesArray[i][j] = -1;
    }
    gameArray[lastX][lastY] = -1;
}
int winner(int score1,int score2){
    if(score1>score2){
        printf("PLAYER 1 WINS!\n");
        return score1;
    }
    else if(score1<score2){
        printf("PLAYER 2 WINS!\n");
        return score2;
    }
    else{
        printf("IT'S A TIE\n");
        return 0;
    }

}
// void logo(){
//     printf("                  _,.---._      ,--.--------.     ,-,--.                  ,---.--.                                   _,.---._              ,-.--,       ,----.     ,-,--.  \n");
//     printf("  _,..---._     ,-.' , -  `.   /==/,  -   , -\  ,-.'-  _\                /  -_ \==\                    _..---.     ,-.' , -  `.   .--.-.  /=/, .'    ,-.--` , \  ,-.'-  _\ \n");
//     printf("/==/,   -  \   /==/_,  ,  - \  \==\.-.  - ,-./ /==/_ ,_.'                |` / \/==/                  .' .'.-. \   /==/_,  ,  - \  \==\ -\/=/- /     |==|-  _.-` /==/_ ,_.' \n");
//     printf("|==|   _   _\ |==|   .=.     |  `--`\==\- \    \==\  \                    \ \ /==/                  /==/- '=' /  |==|   .=.     |  \==\ `-' ,/      |==|   `.-. \==\  \    \n");
//     printf("|==|  .=.   | |==|_ : ;=:  - |       \==\_ \    \==\ -\                   /  \==/                   |==|-,   '   |==|_ : ;=:  - |   |==|,  - |     /==/_ ,    /  \==\ -\   \n");
//     printf("|==|,|   | -| |==| , '='     |       |==|- |    _\==\ ,\                 /. / \==\                  |==|  .=. \  |==| , '='     |  /==/   ,   \    |==|    .-'   _\==\ ,\  \n");
//     printf("|==|  '='   /  \==\ -    ,_ /        |==|, |   /==/\/ _ |               | _ \_/\==\                 /==/- '=' ,|  \==\ -    ,_ /  /==/, .--, - \   |==|_  ,`-._ /==/\/ _ | \n");
//     printf("|==|-,   _`/    '.='. -   .'         /==/ -/   \==\ - , /               \ . -  /\==\               |==|   -   /    '.='. -   .'   \==\- \/=/ , /   /==/ ,     / \==\ - , / \n");
//     printf("`-.`.____.'       `--`--''           `--`--`    `--`---'                 '----`-`--`               `-._`.___,'       `--`--''      `--`-'  `--`    `--`-----``   `--`---'  \n");
//     printf("");
//     printf("");
//     printf("");
//     printf("");
//     printf("");
//     printf("");
// }

#endif // GAMECORE_H_INCLUDED