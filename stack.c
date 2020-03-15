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

struct stack {
    int capacity;
    int top;
    int* item;
};

struct stack* newStack(int _capacity) {
    struct stack* new_s = (struct stack*)malloc(sizeof(struct stack*));
    new_s->capacity = _capacity;
    new_s->top = -1;
    new_s->item = (int*)malloc(_capacity * sizeof(int));
    
    return new_s;
}

bool isEmpty(struct stack* s) {
    return s->top == -1 ? 1 : 0; 
}

bool isFull(struct stack* s) {
    return s->top == s->capacity - 1 ? 1 : 0;
}

int sizeofStack(struct stack* s) {
    return s->top + 1;
}

void push(struct stack* s, int x) {
    // assert(!isFull(s));
    if ( isFull(s) ) {
        printf("Full Stack - Cannot add more element!\n");
        return;
    }
    else
        s->item[++s->top] = x;
}    

int peek(struct stack* s) {
    assert(!isEmpty(s));
    // printf("Empty Stack!\n");
    return s->item[s->top];
}

int pop(struct stack* s) {
    assert(!isEmpty(s));
    return s->item[s->top--];
}

void clearStack(struct stack* s) {
    while( !isEmpty(s) )
        pop(s);
    // free(s->item);
    // free(s);
}

int main (int argc, char** argv) {
    
    struct stack* myStack = newStack(3);
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




