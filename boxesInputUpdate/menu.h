#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <stdio.h>
#include <windows.h>   // WinApi header
#include <conio.h>
#define MAXLENGTH 50




void changeColor(HANDLE hconsole){
    SetConsoleTextAttribute(hconsole, 64+32+16+1);
}

void resetColor(HANDLE hconsole, WORD savedAttributes){
    SetConsoleTextAttribute(hconsole, savedAttributes);
}

void displayMenu(HANDLE hconsole, WORD savedAttributes,int index_highlighted, int length, char items[][MAXLENGTH]){
    int colorChanged = 0;
    for(int i = 0; i < length; i++){
        if(i == index_highlighted){
            changeColor(hconsole);
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

// void startMenu(HANDLE hconsole, WORD savedAttributes, int length){
//     const int START_MENU_LENGTH = 4;
//     char items[][MAXLENGTH] = {"Single player","Two players","Load game", "Leaderboard"};
//     displayMenu(hconsole, savedAttributes, 0, START_MENU_LENGTH, items);
//     int index = 0;
//     while(1){
//         char c = getch();
//         if(c == 'w'){
//             if(index == 0){
//                 index = 2;
//             }else{
//                 index = (index-1)%3;
//             }
//             //fflush(stdin);
//             system("CLS");
//             displayMenu(hconsole, savedAttributes, index, START_MENU_LENGTH, items);
//         }else if(c == 's'){
//             index = (index+1)%3;
//             //fflush(stdin);
//             system("CLS");
//             displayMenu(hconsole, savedAttributes, index, START_MENU_LENGTH, items);
//         }else if(c == '\r'){
//             //displayMenu(hconsole, savedAttributes, index, 3, items);
//             break;
//         }
//         //printf("%d\n", c);
//     }

//     fflush(stdin);
//     system("CLS");

//     switch (index){
//     case 0: //single player

//         break;

//     case 1: //two player
//         printf("Leaderboard will be displayed here!\n");
//         break;

//     case 2: //load
//         //load
//         break;
//     case 3: //leaderbroad
//         //board
//         break;
//     default:
//         break;
//     }
// }

#endif
