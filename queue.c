/*
    Sylar Zhang - March 2020
   
    (Circular) Queue implenmentation in C (gcc complier)
    a.k.a the Ring Buffer
    (1) enQuene
    (2) deQueue
    (3) displayQueue
    (4) clearQueue

*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
// include stdbool.h for bool in gcc
#include <stdbool.h>
// for INT_MIN / INT_MAX
#include <limits.h>

typedef struct{
    int* item;
    int front, rear;
    int capacity;
}queue;

queue* newQueue(int _capacity) {
    queue* q = (queue*)malloc(sizeof(queue));
    q->capacity = _capacity;
    // Woah, gcc also accepts A = B = C;
    q->rear = q->front = -1;
    q->item = (int*)malloc(sizeof(int)*_capacity);
    return q;
}

bool isEmpty(queue* q) {
    return (q->front == -1) ? 1 : 0;
}

bool isFull(queue* q) {
    if ( (q->front == 0 && q->rear == (q->capacity - 1) ) || 
         (q->front == q->rear + 1 ) )
        return 1;
    else
        return 0;
}

void enQueue(queue* q, int x) {
    assert(!isFull(q));
    // Or..
    if ( isFull(q) ) {
        printf("Full queue!\n");
    }
    // enQuene when not full
    if (q->front == -1) 
        q->front = q->rear = 0;
    else // q->rear + 1 = q->front -> last occupancy
        q->rear = (q->rear + 1) % q->capacity;
    q->item[q->rear] = x;
    printf("%d inserted\n", q->item[q->rear]);
}

int deQueue(queue* q) {
    assert( !isEmpty(q) );
    // Or..
    if ( isEmpty(q) ) {
        printf("Empty queue!\n");
        return INT_MIN;
    }
    int element = q->item[q->front];
    printf("%d deQueued\n", element);
    // deQueue the only element
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    }
    else
        q->front = (q->front + 1) % q->capacity;
    return element;
}

void displayQueue(queue* q) {
    if (isEmpty(q))
        printf("Empty Queue!\n");
    else {
        printf("front_ind=%d\n", q->front);
        if (q->rear >= q->front) 
            for (int i = q->front; i <= q->rear; ++i)
                printf("item[%d]=%d ", i, q->item[i]);
        else {
            for (int i = q->front; i <= q->capacity - 1; ++i)
                printf("item[%d]=%d ", i, q->item[i]);
            for (int i = 0; i <= q->rear; ++i)
                printf("item[%d]=%d ", i, q->item[i]);
        }
        printf("\nrear_ind=%d\n", q->rear);
    }
}

void clearQueue(queue* q) {
    free(q->item);
    free(q);
}


int main (int argc, char** argv) {
    
    queue* myQueue = newQueue(3);
    
    enQueue(myQueue, 0);
    enQueue(myQueue, 1);
    enQueue(myQueue, 2);
    int tmp = deQueue(myQueue);
    enQueue(myQueue, 3);
    printf("!!!:%d\n", myQueue->rear);
    displayQueue(myQueue);
    clearQueue(myQueue);

    return 0;
}






