#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <stdio.h>
#include <windows.h>   // WinApi header
#include <conio.h>
#include <limits.h>
#define MAXLENGTH 50


#define DEF_COLOR 0 //white fg with black bg
#define CURSOR_COLOR 64+32+16+1 // blue fg with yellow bg
#define PLAYER1_COLOR 3 //blue fg with black bg
#define PLAYER2_COLOR 4 //red fg with black bg




void changeColor(HANDLE hconsole, int color){
    SetConsoleTextAttribute(hconsole, color);
}

void resetColor(HANDLE hconsole, WORD savedAttributes){
    SetConsoleTextAttribute(hconsole, savedAttributes);
}

void displayMenu(HANDLE hconsole, WORD savedAttributes,int index_highlighted, int length, char items[][MAXLENGTH]){
    int colorChanged = 0;
    for(int i = 0; i < length; i++){
        if(i == index_highlighted){
            changeColor(hconsole, CURSOR_COLOR);
            colorChanged = 1;
        }
        int j = 0;
        while(items[i][j] != '\0'){
            printf("%c", items[i][j]);
            j++;
        }
        printf("\n");
        if(colorChanged){
            resetColor(hconsole, savedAttributes);
        }
    }
}

int menu(HANDLE hconsole, WORD savedAttributes, int length, char items [][MAXLENGTH], char *title){
    displayMenu(hconsole, savedAttributes, 0, length, items);
    short esc = 0;
    int index = 0;
    while(1){
        printf(title);
        printf("\n");
        char c = getch();
        esc = GetAsyncKeyState ( VK_ESCAPE );
        if(c == 'w'||c=='W'||GetAsyncKeyState ( VK_UP ) & SHRT_MAX){
            if(index == 0){
                index = length - 1;
            }else{
                index = (index-1)%length;
            }
            //fflush(stdin);
            system("CLS");
            displayMenu(hconsole, savedAttributes, index, length, items);
        }else if(c == 's'||c =='S'||GetAsyncKeyState ( VK_DOWN ) & SHRT_MAX){
            index = (index + 1) % length;
            //fflush(stdin);
            system("CLS");
            displayMenu(hconsole, savedAttributes, index, length, items);
        }else if(c == '\r'){
            //displayMenu(hconsole, savedAttributes, index, 3, items);
            break;
        }
        //printf("%d\n", c);
    }

    fflush(stdin);
    system("CLS");
    //to be consistent with choice numbers, 1 is added
    return index+1;
}

void printColoredGrid(int n, char gameArray[n][n], player *players, int movesArray[][MOVES_ARRAY_WIDTH], HANDLE hconsole, WORD savedAttributes){
    int colorChanged = 0;
    int playerColor = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(gameArray[i][j] == 0){
                printf("%c ", 'o');
            }else if(gameArray[i][j] == -1){
                printf("  ");
            }else{
                if(gameArray[i][j] == '|' || gameArray[i][j] == '-'){
                    tuple lcoor = {i, j};
                    playerColor = getPlayerByLine(lcoor, players, (n+1)/2, movesArray).color;
                    changeColor(hconsole, playerColor);
                    colorChanged = 1;
                }else{
                    playerColor = getPlayerByLetter(gameArray[i][j], players).color;
                    changeColor(hconsole, playerColor);
                    colorChanged = 1;
                }
                printf("%c ", gameArray[i][j]);
                //color reset
                if(colorChanged){
                    resetColor(hconsole, savedAttributes);
                }
            }
        }
        printf("\n");
    }
    //clearBuffer(); no char here
}

int optionsMenu(HANDLE hconsole, WORD savedAttributes, int gridDim, char gameArray[][2*gridDim-1], int movesArray[][MOVES_ARRAY_WIDTH], player *players){
    printColoredGrid(2*gridDim-1, gameArray, players, movesArray, hconsole, savedAttributes);
    int length = 5;
    char items[][MAXLENGTH] = {"Continue", "Save", "Undo", "Redo","Back to main menu"};
    displayMenu(hconsole, savedAttributes, 0, length, items);
    short esc = 0;
    int index = 0;
    while(1){
        printf("\n");
        char c = getch();
        esc = GetAsyncKeyState ( VK_ESCAPE );
        if(c == 'w'||c=='W'||GetAsyncKeyState ( VK_UP ) & SHRT_MAX){
            if(index == 0){
                index = length - 1;
            }else{
                index = (index-1)%length;
            }
            //fflush(stdin);
            system("CLS");
            printColoredGrid(2*gridDim-1, gameArray, players, movesArray, hconsole, savedAttributes);
            displayMenu(hconsole, savedAttributes, index, length, items);
        }else if(c == 's'||c =='S'||GetAsyncKeyState ( VK_DOWN ) & SHRT_MAX){
            index = (index + 1) % length;
            //fflush(stdin);
            system("CLS");
            printColoredGrid(2*gridDim-1, gameArray, players, movesArray, hconsole, savedAttributes);
            displayMenu(hconsole, savedAttributes, index, length, items);
        }else if(c == '\r'){
            //displayMenu(hconsole, savedAttributes, index, 3, items);
            break;
        }
        //printf("%d\n", c);
    }

    fflush(stdin);
    system("CLS");
    //to be consistent with choice numbers, 1 is added
    return index;
}



#endif
