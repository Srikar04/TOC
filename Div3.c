/*
*  Group Information :
*  21MCME19 - M.Srikar
*  21MCME06 - TLS Srivatsa
*  21MCME22 - P.Pranav
*/


/*
* Program Description :
* This program takes a number and tells if the number is divisible by 3 or not.
*/

#include <stdio.h>

void fromA(char* present_state,char input ){
    int ia = input - '0';
    if( ia%3 == 0 ){
        return;
    }
    else if( ia%3 == 1 ){
        *present_state = 'B';
    }
    else{
        *present_state = 'C';
    }
}

void fromB( char* present_state,char input ){
    int ia = input - '0';
    if( ia%3 == 0 ){
        return;
    }
    else if( ia%3 == 1 ){
        *present_state = 'C';
    }
    else{
        *present_state = 'A';
    }
}

void fromC( char* present_state,char input ){
    int ia = input - '0';
    if( ia%3 == 0 ){
        return;
    }
    else if( ia%3 == 1 ){
        *present_state = 'A';
    }
    else{
        *present_state = 'B';
    }
}


void transition( char* present_state, int input ){
    if( *present_state == 'A' ){
        fromA( present_state, input );
    }
    else if( *present_state == 'B' ){
        fromB( present_state, input );
    }
    else if( *present_state == 'C' ){
        fromB( present_state, input );
    }
}

int main(void){
    char present_state = 'A';
    char input[100];
    printf("Enter the input\n");
    scanf("%s", input);
    int i =0;
    while(input[i] != '\0'){
        transition( &present_state, input[i] );
        i++;
    }
    if( present_state == 'A' ){
        printf("The input is accepted by the Finite Automata\n");
    }
    else{
        printf("The input is not accepted by the Finite Automata\n");
    }

}