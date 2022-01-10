#ifndef USERINPUT_H_INCLUDED
#define USERINPUT_H_INCLUDED

#define MAXSIZE 100

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char readChar(){
    int c = getchar();
    fflush(stdin);
    return c;
}

//(positive) ints only
int charArrayToInt(char *array, int length){
    int n = 0, i = 0;
    while(i < length){
        //'0' --> 48 to '9' --> 57
        //printf("%c\n", array[i]);
        n = n*10 + (array[i++] - 48);
    }
    return n;
}

//getting a single (positive) integer from the user
int getIntegerUserInput(char message[]){
    
    int data;
    
    while(1){
        char input, array[MAXSIZE], isValid = 1;
        int index = 0;
        printf(message);

        while((input = getchar()) != '\n'){
            if(isdigit(input)){
                array[index++] = input;
            }else if(input == 0){
                continue;
            }else{
                printf("Please enter valid input.\n");
                isValid = 0;
                break;
            }
        }
        if(isValid){
            //index will be off by 1 so dont add =
            data = charArrayToInt(array, index);
            break; 
        }else{
            //prompt the user again to input sth
            fflush(stdin);
            continue;
        }

        //clearing input buffer before moving on
        fflush(stdin);
    }
    
    return data;
}

int getIntChoise(char message[], int *possibleVal, int length){
    int choice, isValid = 1;
    while(1){
        choice = getIntegerUserInput(message);
        for(int i = 0; i < length; i++){
            if(choice == possibleVal[i]){
                return choice;
            }
        }
        printf("Please enter valid input.\n");
    }
}

void getCoords(char *message, int *x, int *y){
    //assuming format: "%d %d"
    //ignores leading spaces
    //ignores any trailing characters after second number
    //loop until user inputs 2 ints in the correct format
    while(1){

        printf(message);

        char input, firstArray[MAXSIZE], secondArray[MAXSIZE], isValid = 1;
        int i1 = 0, i2 = 0;
        
        //getting first number
        while(isValid){
            input = getchar();
            
            if(isdigit(input)){
                firstArray[i1++] = input;
            }else if(input == 0){
                //escaping null character
                continue;
            }else if(input == ' ' && i1 == 0){
                //escaping spaces
                continue;
            }else if(input == ' ' && i1 != 0){
                //separating space
                break;
            }else{
                //neither a space nor a number
                //a letter or '\n' for example
                isValid = 0;
            }
        }
        //getting second number
        while(isValid){
            input = getchar();

            if(isdigit(input)){
                secondArray[i2++] = input;
            }else if((input == ' ' || input == '\n')&& i2 == 0){
                //skip and continue searching for digits
                continue;
            }else if(input == 0){
                continue;
            }else if((input == ' ' || input == '\n')&& i2 != 0){
                //end of search
                break;
            }else{
                //other characters
                isValid = 0;
            }
        }
        if(isValid){
            *x = charArrayToInt(firstArray, i1);
            *y = charArrayToInt(secondArray, i2);
            fflush(stdin);
            break;
        }else{
            //reprompt the user to input coords
            printf("Please enter valid input.\n");
            fflush(stdin);
            continue;
        }
    }
}

char askYN(char *message){
    fflush(stdin);
    //returns only 'y' or 'n' to avoid confusion with capital letters
    printf(message);
    char ans = getchar();
    while(ans != 'y' && ans != 'Y' && ans != 'n' && ans != 'N'){
        printf("Entered %c\n", ans);
        printf(message);
        fflush(stdin);
        ans = getchar();
    }
    printf("out\n");
    if(ans == 'Y'){
        ans = 'y';
    }else if(ans == 'N'){
        ans = 'n';
    }
    return ans;
}

#endif