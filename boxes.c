#include <stdio.h>
#include <math.h>
#include <stdlib.h>

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
}

void drawLine(int x1, int y1, int x2, int y2, int gridDim, char gameArray[][gridDim*2-1]){
    if(gameArray[x1+x2][y1+y2] == -1){
        if((x1+x2) % 2){
            gameArray[x1+x2][y1+y2] = '|';
        }else{
            gameArray[x1+x2][y1+y2] = '-';
        }
    }else{
        printf("Already joined!\n");
    }
}

void joinDots(int x1, int y1, int x2, int y2, int gridDim, char gameArray[][gridDim*2-1]){
    // 0 <= x, y <= n-1
    if(
        x1 >= 0 && x1 <= gridDim
        && y1 >= 0 && y1 <= gridDim
        && x2 >= 0 && x2 <= gridDim
        && y2 >= 0 && y2 <= gridDim
    ){
        if(x1 != x2 && y1 != y2){
            //not horizontal or vertical ie diagonal
            printf("You can't join dots diagonally!\n");
        }else if(x1 == x2 && abs(y1-y2) == 1){
            drawLine(x1, y1, x2, y2, gridDim, gameArray);
        }else if(y1 == y2 && abs(x1-x2) == 1){
            drawLine(x1, y1, x2, y2, gridDim, gameArray);
        }else{
            printf("Can't join these two dots.\n");
        }
    }else{
        printf("Invalid input.\n");
    }
}

int countBoxes(int gridDim, char gameArray[][gridDim*2-1]){
    int boxCount = 0;
    for(int i = 1; i <= gridDim; i += 2){
        for(int j = 1; j <= gridDim; j += 2){
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
                gameArray[i][j] = 'A';
                boxCount++;
            }
        }
        
    }
    return boxCount;
}

void gameLoop(int gridDim, char gameArray[][gridDim*2-1]){
    int boxCount = 0;
    while(1){
        int x1, x2, y1, y2;
        printf("Enter 1st point coordinates (x1 y1): ");
        scanf("%d %d", &x1, &y1);
        printf("Enter 2nd point coordintes (x2 y2): ");
        scanf("%d %d", &x2, &y2);
        joinDots(x1, y1, x2, y2, gridDim, gameArray);

        boxCount = countBoxes(gridDim, gameArray);

        printf("boxCount = %d\n", boxCount);

        printGrid(gridDim*2-1, gameArray);

        getchar();

        if(boxCount == (gridDim-1)*(gridDim-1)){
            break;
        }
    }
}


int main(){
    
    int gridDim;
    printf("Enter dimension(nxn): ");
    scanf("%d", &gridDim);
    //clearing buffer
    getchar();
    int arrayDim = gridDim*2-1;
    char gameArray[arrayDim][arrayDim];
    initGameArray(arrayDim, gameArray);
    printGrid(arrayDim, gameArray);

    // int x1, x2, y1, y2;
    // printf("Enter 1st point coordinates (x1 y1): ");
    // scanf("%d %d", &x1, &y1);
    // printf("Enter 2nd point coordintes (x2 y2): ");
    // scanf("%d %d", &x2, &y2);
    // joinDots(x1, y1, x2, y2, gridDim, gameArray);
    // printGrid(arrayDim, gameArray);

    // getchar();

    gameLoop(gridDim, gameArray);

    printf("Press ENTER to continue...");

    while(getchar() != '\n'){

    }
    return 0;
}
