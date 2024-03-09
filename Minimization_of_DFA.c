/*
*  Group Information :
*  21MCME19 - M.Srikar
*  21MCME06 - TLS Srivatsa
*  21MCME22 - P.Pranav
*/


/*
* Program Description :
* This program takes a DFA transition table as input and minimizes the DFA
* and gives the newly formed states as ouput
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATES 100
#define MAX_ALPHABET 100

int num_states, num_symbols;
int transition_table[MAX_STATES][MAX_ALPHABET];
char symbols[MAX_ALPHABET];

int num_of_non_accepting_states;
int num_of_accepting_states;
int non_accepting_states[MAX_ALPHABET];
int accepting_states[MAX_STATES];

int state_class[MAX_STATES];
int num_of_classes;

typedef struct set{
    int arr[MAX_STATES];
    int length;
}set;

set* helper[MAX_STATES]; // contains the pointers to the sets in array
int len_of_helper;


set* create_set(){
    set* s = (set*)malloc(sizeof(set));
    s->length = 0;
}

void add_element(set* s,int val){
    s->arr[s->length++] = val;
}

void delete_element(set* s,int index){
    for(int i = index;i< s->length - 1;i++){
        s->arr[i] = s->arr[i+1];
    }
    s->length--;
}

void printTransitionTable(){
    for(int i = 0;i<num_states;i++){
        for(int j = 0;j<num_symbols;j++){
            printf("%d\t",transition_table[i][j]);
        }
        printf("\n");
    }
}

void printSet(set* s){
    for(int i = 0;i<s->length;i++){
        printf("%d ",s->arr[i]);
    }
}

void printHelper(){
    for(int i = 0;i<len_of_helper;i++){
        printSet(helper[i]);
        printf("\n");
    }
}

void initialize(){
    len_of_helper = 2;
    set* s = create_set();
    for(int i = 0 ; i< num_of_non_accepting_states;i++){
        add_element(s,non_accepting_states[i]);
        state_class[non_accepting_states[i]] = 1;
    }
    helper[0] = s;
    s = create_set();
    for(int i = 0 ; i< num_of_accepting_states;i++){
        add_element(s,accepting_states[i]);
        state_class[accepting_states[i]] = 2;
    }
    helper[1] = s;
    printHelper();
}

int check(int temp[],int state){ //Checks if a new state can be added into the buffer array
    int sample_state = temp[0];
    for(int i = 0;i<num_symbols;i++){
        if(state_class[transition_table[sample_state][i]] != state_class[transition_table[state][i]]){
            return 0;
        }
    }
    return 1;
}

void minimize(){
    initialize();
    int changed;
    while(1 == 1){
        changed = 0;
        for(int i = 0;i<len_of_helper;i++){
            set* temp_set = helper[i];
            int state1 = temp_set->arr[0];
            int temp[MAX_STATES]; //temp array for buffer
            int len_of_temp = 0;
            for(int j = 1; j < temp_set->length ;j++){
                int state2 = temp_set->arr[j];
                for(int k = 0; k < num_symbols;k++){
                    if(state_class[transition_table[state1][k]] != state_class[transition_table[state2][k]]){ 
                        if(len_of_temp == 0){
                            temp[len_of_temp] = state2;
                            len_of_temp++;
                            num_of_classes++;
                        }
                        else if(check(temp,state2) == 1){
                            printf("%d\n",state2);
                            temp[len_of_temp++] = state2;
                        }
                        else{
                            set* s = create_set();
                            add_element(s,state2);
                            helper[len_of_helper++] = s;
                            num_of_classes++;
                            state_class[state2] = num_of_classes;
                        }
                        //delete original element from the parent set
                        delete_element(temp_set,j);
                        changed = 1;
                        break;
                    }
                }
            }
            //finally add temp
            if(changed == 1 && len_of_temp != 0){
                set* s = create_set();
                for(int l = 0;l<len_of_temp;l++){
                    add_element(s,temp[l]);
                    state_class[temp[l]] = num_of_classes;
                }
                helper[len_of_helper++] = s;  
            }
            if(changed == 1)
                break;
        }
        printf("After one iteration:\n");
        printHelper();
        if(changed == 0)
            break;
    }
    printf("After minimization the final sets are:\n");
    printHelper();
}

int main(){
    // printf("Enter the number of states : ");
    // scanf("%d",&num_states);

    // //taking non accepting states input from user
    // printf("Enter the number of non accepting states : ");
    // scanf("%d",&num_of_initial_states);
    // printf("Enter the states\n");
    // for(int i = 0;i<num_of_initial_states;i++){
    //     scanf("%d",&non_final_states[i]);
    // }

    // //taking final states input from user
    // printf("Enter the number of accepting states : ");
    // scanf("%d",&num_of_final_states);
    // printf("Enter the states\n");
    // for(int i = 0;i<num_of_final_states;i++){
    //     scanf("%d",&final_states[i]);
    // }

    // printf("Enter the number of symbols : ");
    // scanf("%d",&num_symbols);


    // //taking all symbols input from user
    // for(int i = 0;i<num_symbols;i++){
    //     char temp;
    //     scanf("%c",&temp);
    //     printf("Enter the symbol %d : ",i);
    //     scanf("%c",&symbols[i]);
    // }

    // //taking the transitions input from user
    // for(int i = 0;i<num_states;i++){
    //     for(int j = 0;j<num_symbols;j++){
    //         printf("Enter the transition table for state %d and symbol %c : ",i,symbols[j]);
    //         scanf("%d",&transition_table[i][j]);
    //     }
    // }

    // taking state classes input from user
    // printf("Enter the number of state classes: ");
    // scanf("%d", &num_of_classes);

    // printf("Enter the state classes: ");
    // for (int i = 0; i < num_of_classes; i++) {
    //     scanf("%d", &state_class[i]);
    // }

    // Test Case 1:
    // num_states = 5;
    // num_of_non_accepting_states = 4;
    // num_of_accepting_states = 1;
    // non_accepting_states[0] = 0;
    // non_accepting_states[1] = 1;
    // non_accepting_states[2] = 2;
    // non_accepting_states[3] = 3;
    // accepting_states[0] = 4;
    // num_symbols = 2;
    // transition_table[0][0] = 1;
    // transition_table[0][1] = 3;
    // transition_table[1][0] = 1;
    // transition_table[1][1] = 2;
    // transition_table[2][0] = 1;
    // transition_table[2][1] = 4;
    // transition_table[3][0] = 1;
    // transition_table[3][1] = 3;
    // transition_table[4][0] = 1;
    // transition_table[4][1] = 3;

    // num_of_classes = 2;
    // state_class[0] = 1;
    // state_class[1] = 1;
    // state_class[2] = 1;
    // state_class[3] = 1;
    // state_class[4] = 2;

    // Test Case 2:
    // num_states = 5;
    // num_of_non_accepting_states = 4;
    // num_of_accepting_states = 1;
    // non_accepting_states[0] = 0;
    // non_accepting_states[1] = 1;
    // non_accepting_states[2] = 2;
    // non_accepting_states[3] = 3;
    // accepting_states[0] = 4;
    // num_symbols = 2;
    // transition_table[0][0] = 1;
    // transition_table[0][1] = 2;
    // transition_table[1][0] = 2;
    // transition_table[1][1] = 4;
    // transition_table[2][0] = 3;
    // transition_table[2][1] = 2;
    // transition_table[3][0] = 2;
    // transition_table[3][1] = 4;
    // transition_table[4][0] = 1;
    // transition_table[4][1] = 4;

    // Test Case 3: Multiple accepting states
    num_states = 6;
    num_of_non_accepting_states = 4;
    num_of_accepting_states = 2;
    non_accepting_states[0] = 0;
    non_accepting_states[1] = 1;
    non_accepting_states[2] = 3;
    non_accepting_states[3] = 4;
    accepting_states[0] = 2;
    accepting_states[1] = 5;
    num_symbols = 2;
    transition_table[0][0] = 1;
    transition_table[0][1] = 5;
    transition_table[1][0] = 0;
    transition_table[1][1] = 2;
    transition_table[2][0] = 1;
    transition_table[2][1] = 3;
    transition_table[3][0] = 3;
    transition_table[3][1] = 1;
    transition_table[4][0] = 3;
    transition_table[4][1] = 4;
    transition_table[5][0] = 4;
    transition_table[5][1] = 3;

    num_of_classes = 2;
    state_class[0] = 1;
    state_class[1] = 1;
    state_class[2] = 2;
    state_class[3] = 1;
    state_class[4] = 1;
    state_class[5] = 2;

    printTransitionTable();

    minimize();
}
