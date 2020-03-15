/*
    Sylar Zhang - March 2020
   
    Stack implenmentation in C
    (1) push
    (2) pop
    (3) peek
    (4) isEmpty
    (5) isFull
    (6) clearStack
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
// include stdbool.h for bool in gcc
#include <stdbool.h>

// In gcc - "typedef struct{...}stack;" is a must for sparing the keywork - "struct",
//          otherwise "struct stack" is a must.
//          Also bool type doesn't exist in C;
// In g++ - it can just be struct stack {...}; 
typedef struct{
    int capacity;
    int top;
    int* item;
}stack;

stack* newStack(int _capacity) {
    stack* new_s = (stack*)malloc(sizeof(stack*));
    new_s->capacity = _capacity;
    new_s->top = -1;
    new_s->item = (int*)malloc(_capacity * sizeof(int));
    
    return new_s;
}

bool isEmpty(stack* s) {
    return s->top == -1 ? 1 : 0; 
}

bool isFull(stack* s) {
    return s->top == s->capacity - 1 ? 1 : 0;
}

int sizeofStack(stack* s) {
    return s->top + 1;
}

void push(stack* s, int x) {
    // assert(!isFull(s));
    if ( isFull(s) ) {
        printf("Full Stack - Cannot add more element!\n");
        return;
    }
    else
        s->item[++s->top] = x;
}    

int peek(stack* s) {
    assert(!isEmpty(s));
    // printf("Empty Stack!\n");
    return s->item[s->top];
}

int pop(stack* s) {
    assert(!isEmpty(s));
    return s->item[s->top--];
}

void clearStack(stack* s) {
    while( !isEmpty(s) )
        pop(s);
    // free(s->item);
    // free(s);
}

int main (int argc, char** argv) {
    
    stack* myStack = newStack(3);
    push(myStack, 10);
    push(myStack, 20);
    push(myStack, 30);
    int pop1 = pop(myStack);
    push(myStack, 50);
    char s1[] = "pop1=";
    char s2[] = "isEmpty=";
    printf("%s%d %s%d\n", s1, pop1, s2, isEmpty(myStack));
    
    int peek1 = peek(myStack);
    printf("%s%d %s%d\n", "peek1=", peek1, "size=", sizeofStack(myStack));
    
    clearStack(myStack);
    printf("%s%d %s%d\n", "stackAddr", myStack, "size=", sizeofStack(myStack));
    
    free(myStack);

    return 0;
}




