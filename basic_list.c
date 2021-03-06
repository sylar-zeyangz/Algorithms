/*
    Sylar Zhang - March 2020
    
    Basic list operations in C 
    (1) Insert a node
    (2) Delete a node
    (3) Clear the entire list
    (4) Print/Display
    (5) check the missing node
*/

#include <stdio.h>
#include <stdlib.h>

#define GAP 2

struct list {
    list* next;
    int val;
    list(int x) { val = x; }
};

// typedef struct list l;

void addNode(list* head, int x) {
    struct list* new_node = (struct list*)malloc(sizeof(struct list));
    struct list* dummy = head;
    while (dummy->next != NULL)   
        dummy = dummy->next; 
    
    dummy->next = new_node;
    new_node->next = NULL;
    new_node->val = x;
}

void deleteNode(list** head, int x) {
    struct list* prev = NULL;
    struct list* tmp = NULL;
    struct list* curr = *head;
    for (; curr != NULL; ) {
        if (curr->val == x) {
            tmp = curr;
            if (prev == NULL) {
                printf("Deleting the first node\n");
                *head = curr->next;
            }
            else
                prev->next = curr->next;
        }
        else
            prev = curr;
        curr = curr->next;
        if (tmp != NULL)
            free(tmp);
    }

    return;
}

void clearAll(list* head) {
    struct list* currNode = head;
    struct list* nextNode = NULL;
    while (currNode != NULL) { 
       nextNode = currNode->next; 
       free(currNode); 
       currNode = nextNode; 
    }   
    head = NULL;
    free(head);
    printf("Clear Completed!\n");
}

void printList(list* head) {
    const struct list* dummy = head;
    while (dummy != NULL) {
        printf("%d ", dummy->val);
        dummy = dummy->next;
    }
}

int checkMissingNode(list* head) {
    // ret can be a dynamically growing array in case of multiple missing elements
    int ret = -1;
    int count = 0;

    struct list* dummy = head;
    while(dummy != NULL && dummy->next != NULL) {
        //while (dummy->val + GAP*(t++) != dummy->next->val) {
            if (dummy->next->val - dummy->val != GAP)
                ret = dummy->val + GAP;
        //}
        dummy = dummy->next;
        
    }
    return ret;
}

int main(int argc, char **argv)
{
    list* head = (struct list*)malloc(sizeof(struct list));
    head->val = 3;
    head->next = NULL;
    addNode(head, 3); 
    addNode(head, 5); 
    addNode(head, 9); 
    addNode(head, 9); 
    addNode(head, 9); 
    addNode(head, 15); 
    // deleteNode(&head, 5);
    //clearAll(head);
    int missing_val;
    //missing_val = checkMissingNode(head);
    //printf("Missing Element: %d\n", missing_val);
    printList(head);
    
    printf("\nThe End\n");
    return 0;
}
