/*
*  Group Information :
*  21MCME19 - M.Srikar
*  21MCME06 - TLS Srivatsa
*  21MCME22 - P.Pranav
*/


/*
* Program Description :
* This program takes a grammar , input string and 
* determines whether the string is accepted by the grammar or not.
*/

#include <stdio.h>
#include <string.h>

#define MAX 100

struct Production {
    char from;
    char to[10];
} typedef Production;

struct String {
    char str[MAX];
    char states[MAX];
} typedef String;

int contains(char states[], char c) {
    for (int i = 0; i < strlen(states); i++) {
        if (states[i] == c) {
            return 1;
        }
    }
    return 0;
}

void CYK(char str[], Production p[],int n) {
    int size = strlen(str);
    String matrix[size][size];

    // Filling up the first row of the matrix
    for (int i = 0; i < size; i++) {
        char ch[] = {str[i], '\0'};
        matrix[0][i].str[0] = str[i];
        matrix[0][i].str[1] = '\0';
        int pos = 0;
        for (int j = 0; j < n; j++) {
            if (strcmp(ch, p[j].to) == 0) {
                matrix[0][i].states[pos] = p[j].from;
                pos++;
            }
        }
        matrix[0][i].states[pos] = '\0';
    }

    // Filling up the rest of the matrix
    for (int i = 1; i < size; i++) {
        int j;
        for (j = 0; j < size - i; j++) {
            // Generating substrings of length i+1
            int k;
            for (k = 0; k < i + 1; k++) {
                matrix[i][j].str[k] = str[j + k];
            }
            matrix[i][j].str[k] = '\0';

            // Initializing the states field of the matrix cell to '\0'
            matrix[i][j].states[0] = '\0';

            // Combining states of two substrings to generate the states of the current substring
            for (int p1 = 0; p1 < i; p1++) {
                int p2 = i - p1 - 1;
                int q1 = 0;
                while (matrix[p1][j].states[q1] != '\0') {
                    int q2 = 0;
                    while (matrix[p2][j + p1 + 1].states[q2] != '\0') {
                        char from[] = {matrix[p1][j].states[q1], matrix[p2][j + p1 + 1].states[q2], '\0'};
                        for (int r = 0; r < n; r++) {
                            if (strcmp(from, p[r].to) == 0) {
                                int pos = strlen(matrix[i][j].states);
                                if (!contains(matrix[i][j].states, p[r].from)) {
                                    matrix[i][j].states[pos] = p[r].from;
                                    matrix[i][j].states[pos + 1] = '\0';
                                }
                            }
                        }
                        q2++;
                    }
                    q1++;
                }
            }
        }
    }

    // Printing the matrix
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - i; j++) {
            // printf("%s\t", matrix[i][j].str);
            printf("%s\t", matrix[i][j].states);
        }
        printf("\n");
    }

    // Printing the last cell of the matrix
    if (strchr(matrix[size - 1][0].states, 'S') != NULL) {
        printf("The input string can be generated by the given grammar.\n");
    } else {
        printf("The input string cannot be generated by the given grammar.\n");
    }
}


int main(void){

    printf("This program only accepts CNF\n\n");

    // printf("Enter the number of productions for the CNF\n");
    // int n; 
    // scanf("%d",&n);
    // Production p[n];
    // for( int i=0;i<n;i++ ){
    //     printf("Enter the productions\n");
    //     scanf("\n");
    //     scanf("%c %s",&p[i].from,p[i].to);
    //     // scanf("%s",p[i].to);
    //     printf("%c -> %s\n",p[i].from,p[i].to);
    // }

    //test case 1
    // For this test case give input baaba it gives positive output
    int n = 8;
    Production p[8] = {
        { .from = 'S', .to = "AB"  },
        { .from = 'S', .to = "BC"},
        { .from = 'A', .to = "BA"},
        { .from = 'A', .to = "a"},
        { .from = 'B', .to = "CC"},
        { .from = 'B', .to = "b"},
        { .from = 'C', .to = "AB"},
        { .from = 'C', .to = "a"},
        
    };


    //test case 2
    //For this test case give input bbaa it gives positive output
    // int n = 7;
    // Production p[7] = {
    //     { .from = 'S', .to = "XY"  },
    //     { .from = 'X', .to = "SY"},
    //     { .from = 'X', .to = "a"},
    //     { .from = 'X', .to = "BB"},
    //     { .from = 'B', .to = "b"},
    //     { .from = 'Y', .to = "AA"},
    //     { .from = 'A', .to = "a"},

    // };

    char str[MAX];
    printf("Enter the input string\n");
    scanf("%s",str);

    CYK( str, p ,n);

}