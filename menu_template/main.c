#include <stdio.h>
#include <windows.h>   // WinApi header
#include <conio.h>
#define MAXLENGTH 20



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

void menu(HANDLE hconsole, WORD savedAttributes){
    char items[][MAXLENGTH] = {"start","leaderboard","exit"};
    displayMenu(hconsole, savedAttributes, 0, 3, items);
    int index = 0;
    while(1){
        char c = getch();
        if(c == 'w'){
            if(index == 0){
                index = 2;
            }else{
                index = (index-1)%3;
            }   
            //fflush(stdin);
            system("CLS");
            displayMenu(hconsole, savedAttributes, index, 3, items);
        }else if(c == 's'){
            index = (index+1)%3;
            //fflush(stdin);
            system("CLS");
            displayMenu(hconsole, savedAttributes, index, 3, items);
        }else if(c == '\r'){
            //displayMenu(hconsole, savedAttributes, index, 3, items);
            break;
        }
        //printf("%d\n", c);
    }

    fflush(stdin);
    system("CLS");
    
    switch (index){
    case 0:
        printf("Game Started!\n");
        break;

    case 1:
        printf("Leaderboard will be displayed here!\n");
        break;

    default:
        break;
    }
}

int main(){

    HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    GetConsoleScreenBufferInfo(hconsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;
    
    menu(hconsole, saved_attributes);

    printf("Press any key to exit...");
    
    getch();
    return 0;
}