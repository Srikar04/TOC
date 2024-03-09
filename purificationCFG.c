/*
*  Group Information :
*  21MCME19 - M.Srikar
*  21MCME06 - TLS Srivatsa
*  21MCME22 - P.Pranav
*/

/*
* Program Description :
* This program takes a CFG and removes and purifies it in the following order
* 1) Removal of lambda producitons
* 2) Removal of unit productions
*/

/*
* Command Line Arguments :
*  S->AB|a should be entered as S-AB|a
*  the end of the input means "." should be entered
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PRODUCTIONS 100
#define MAX_SYMBOLS 100

const char LAMBDA = 'e'; // define lambda as 'e'

typedef struct Production {
    char left;
    char right[MAX_SYMBOLS][MAX_SYMBOLS];
    int num_right;
} Production;

Production productions[MAX_PRODUCTIONS];
int num_productions = 0;


void printProductions() {
    for (int i = 0; i < num_productions; i++) {
        printf("%c -> ", productions[i].left);
        for (int j = 0; j < productions[i].num_right; j++) {
            if (strcmp(productions[i].right[j], "") == 0) {
                printf("%c", LAMBDA);
            } else {
                printf("%s", productions[i].right[j]);
            }
            if (j != productions[i].num_right - 1) {
                printf("|");
            }
        }
        printf("\n");
    }
}

//takes a string and checks whether it contains "e" and return index
int contains_e(char str[],char ch){
    int i = 0;
    while(str[i] != '\0'){
        if(str[i] == ch)
            return i;
        i++;
    }
    return -1;
}

void delete_production(int i,int j){
    for(int k = j;k<productions[i].num_right - j;k++){
        strcpy(productions[i].right[k],productions[i].right[k+1]);
    }
    productions[i].num_right--;
}

void remove_lambda() {
    //Identify all nonterminals that can derive epsilon
    int derives_lambda[num_productions];
    for (int i = 0; i < num_productions; i++){
        derives_lambda[i] = 0;
        for (int j = 0; j < productions[i].num_right; j++) {
            if (strcmp(productions[i].right[j], "e") == 0){
                //removing that production
                delete_production(i,j);
                derives_lambda[i] = 1;
                break;
            }
        }
    }
    for(int i1 = 0;i1 < num_productions;i1++){
        if(derives_lambda[i1] == 1){
            char char_to_replace = productions[i1].left;
            for(int i = 0;i<num_productions;i++){
                for(int j = 0 ; j<productions[i].num_right;j++){
                    int index = contains_e(productions[i].right[j],char_to_replace);
                    if(index != -1){
                        if(index == 0 && productions[i].right[j][1] == 0){
                            //do nothing
                        }
                        else{
                        char temp[MAX_SYMBOLS];
                        int k2 = 0;
                        int k = 0;
                        while(productions[i].right[j][k] != '\0'){
                           if(index != k)
                                temp[k2++] = productions[i].right[j][k];
                            k++;
                        }
                            //adding a production
                            temp[k2] = '\0';
                            strcpy(productions[i].right[productions[i].num_right], temp);
                            productions[i].num_right++;
                        }
                    }
                }
            }
        }
    }
}

int size(char arr[]){
    int index = 0;
    while(arr[index] != '\0'){
        index++;
    }
    return index;
}


void remove_unit() {
    for (int i = 0; i < num_productions; i++) {
        for (int j = 0; j < productions[i].num_right; j++) {
            char temp[MAX_SYMBOLS];
            strcpy(temp, productions[i].right[j]);
            int s = size(temp);
            if ((int)temp[0] <= 95 && s == 1) {
                int index;
                // find index in lhs
                for (int w = 0; w < num_productions; w++) {
                    if (productions[w].left == temp[0]) {
                        index = w;
                        break;
                    }
                }
                // add all productions corresponding to rhs
                for (int k1 = 0; k1 < productions[index].num_right; k1++) {
                    char temp2[MAX_SYMBOLS];
                    strcpy(temp2, productions[index].right[k1]);
                    int size2 = size(temp2);
                    if ((int)temp2[0] >= 97 || size2 != 1) {
                        // check if the symbol is already present in the right-hand side
                        bool found = false;
                        for (int k2 = 0; k2 < productions[i].num_right; k2++) {
                            if (strcmp(temp2, productions[i].right[k2]) == 0) {
                                found = true;
                                break;
                            }
                        }
                        if (!found) {
                            strcpy(productions[i].right[productions[i].num_right], temp2);
                            productions[i].num_right++;
                        }
                    }
                }
                delete_production(i, j);
                j--;
            }
        }
    }
}




int main(){
    // Test Case 1:
    // S-AB
    // A-aA|b|e
    // B-bB|e|A
    // .

    char line[1000];
    printf("Enter the context-free grammar, one production per line. End with a single dot on a line by itself:\n");

    while (fgets(line, sizeof(line), stdin)) {
    if (line[0] == '.') {
        break;
    }

    char *left = strtok(line, "-");
    char *right = strtok(NULL, "\n");

    productions[num_productions].left = left[0];
    productions[num_productions].num_right = 0;

    char *symbol = strtok(right, "|");

    while (symbol != NULL) {
        strcpy(productions[num_productions].right[productions[num_productions].num_right], symbol);
        productions[num_productions].num_right++;
        symbol = strtok(NULL, "|");
    }
    num_productions++;
    }

    printf("The productions are:\n");
    printProductions();
    //removing lamda productions
    remove_lambda();
    printf("The productions after removing lambda productions:\n");
    printProductions();

    remove_unit();
    printf("The productions after removing unit productions:\n");
    printProductions();
    return 0;
}