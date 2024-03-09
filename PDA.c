/*
*  Group Information :
*  21MCME19 - M.Srikar
*  21MCME06 - TLS Srivatsa
*  21MCME22 - P.Pranav
*/

/*
* Program Description :
* This program takes an input string and determines whether it is has equal number of a's and b's 
* or not using Push Down Automata
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100 //Maximum size of the stack

typedef struct Stack{
    char array[MAX];
    int top;
}Stack;

int isEmpty(Stack* s){
    if(s->top == -1)
        return 1;
    return 0;
}

int isFull(Stack* s){
    if(s->top == MAX)
        return 1;
    return 0;
}

void push(Stack* s,char newChar){
    if(isFull(s) != 1){
        s->top++;
        s->array[s->top] = newChar;
    }else{
        printf("Stack is full\n");
    }
}

char pop(Stack *s){
    if(isEmpty(s) != 1){
        char ch = s->array[s->top];
        s->top--;
        return ch;
    }else{
        printf("Stack is Empty\n");
        return -1;
    }
}

char peek(Stack *s){
    if(isEmpty(s) != 1){
        char ch = s->array[s->top];
        return ch;
    }else{
        printf("Stack is Empty\n");
        return -1;
    }

}

void PDA(Stack *stack,char input[]){
    int index = 0;
    while(index < strlen(input)){
        char ch = input[index];
        if(isEmpty(stack) == 1){
            push(stack,ch);
        }else{
            if(peek(stack) == 'a'){
                if(ch == 'b')
                    pop(stack);
                else
                    push(stack,ch);
            }
            else if(peek(stack) == 'b'){
                if(ch == 'a')
                    pop(stack);
                else
                    push(stack,ch);
            }else{
                printf("Given string does not contain equal number of a's and b's\n");
                return;
            }
        }
        index++;
    }
    if(isEmpty(stack) == 1)
        printf("Given string contains equal number of a's and b's\n");
    else 
        printf("Given string does not contain equal number of a's and b's\n");
}


int main(){
    Stack* stack;
    stack = (Stack*)malloc(sizeof(Stack));
    stack->top = -1; //intialize top as -1 meaning stack is empty
    char input[100];
    printf("Enter the input string(also takes null string): ");
    //Takes input until enter is pressed
    scanf("%[^\n]%*c", input);
    printf("%s\n",input);
    if((int)input[0] == 1){
        printf("Given string contains equal number of a's and b's\n");
    }
    else{
        PDA(stack,input);
    }
    
}