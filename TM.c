/*
*  Group Information :
*  21MCME19 - M.Srikar
*  21MCME06 - TLS Srivatsa
*  21MCME22 - P.Pranav
*/

/*
* Program Description :
* This is an implementation of a Turing Machine to check if input string is in form a^nb^na^n,
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define delta (char)30
#define arrow (char)24

int pos = 0;
int halt = 0;

void state_1( char str[] );
void state_2( char str[] );
void state_3( char str[] );
void state_4( char str[] );
void state_5( char str[] );
void state_6( char str[] );
void state_7( char str[] );
void state_8( char str[] );
void print_status( char str[] );

void TuringMachine(char str[]);

int main(void){
    printf("Note : The string should include only a's and b's\n");
    printf("Enter the string to check( also take null string ) \n");

    char str[100];
    scanf("%[^\n]%*c", str);
    int last_pos = strlen(str);
    str[ last_pos ] = delta;
    str[ last_pos +1 ] = '\0';
    print_status(str);
    TuringMachine(str);

}

void TuringMachine(char str[]){

    state_1(str);

    if( halt == 1){
        printf("The given string is accepted by the turing machine \n");
    }
    else if( halt == 0 ){
        printf("The given string is rejected by the turing machine\n");
    }

}

void print_status( char str[] ){

    printf("%s\n",str);
        for( int i=0;i<pos;i++ ){
            printf(" ");
        }
        printf("%c\n",arrow);

}

void state_1( char str[] ){

    if( str[pos] == 'a' ){
        str[pos] = '*';
        print_status(str);
        pos++;
        state_2(str);
    }
    else if( str[pos] == delta ){
        str[pos] = delta;
        print_status(str);
        pos++;
        halt = 1;
    }
}

void state_2( char str[] ){
    if( str[pos] == 'a' ){
        str[pos] = 'a';
        print_status(str);
        pos++;
        state_2(str);
    }        
    else if( str[pos] == 'b' ){
        str[pos] = 'b';
        print_status(str);
        pos++;
        state_3(str);
    }
}

void state_3( char str[] ){
    
    if( str[pos] == 'b' ){
        str[pos] = 'b';
        print_status(str);
        pos++;
        state_3(str);
    }        
    else if( str[pos] == 'a' ){
        str[pos] = 'a';
        print_status(str);
        pos--;
        state_4(str);
    }

}

void state_4( char str[] ){

    if( str[pos] == 'b' ){
        str[pos] = 'a';
        print_status(str);
        pos++;
        state_5(str);
    }   

}

void state_5( char str[] ){

    if( str[pos] == 'a' ){
        str[pos] = 'a';
        print_status(str);
        pos++;
        state_5(str);
    }        
    else if( str[pos] == delta ){
        str[pos] = delta;
        print_status(str);
        pos--;
        state_6(str);
    }

}

void state_6( char str[] ){

    if( str[pos] == 'a' ){
        str[pos] = delta;
        print_status(str);
        pos--;
        state_7(str);
    } 

}

void state_7( char str[] ){

    if( str[pos] == 'a' ){
        str[pos] = delta;
        print_status(str);
        pos--;
        state_8(str);
    }

}

void state_8( char str[] ){

    if( str[pos] == 'a' ){
        str[pos] = 'a';
        print_status(str);
        pos--;
        state_8(str);
    }        
    else if( str[pos] == 'b' ){
        str[pos] = 'b';
        print_status(str);
        pos--;
        state_8(str);
    }
    else if( str[pos] == '*' ){
        str[pos] = '*';
        print_status(str);
        pos++;
        state_1(str);
    }

}