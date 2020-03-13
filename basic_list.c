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

#define GAP 1

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

void deleteNode(list* head, int x) {
    struct list* dummy = head;
    struct list* prev = NULL;
    while (dummy != NULL) { 
        if (dummy->val == x) {
            prev->next = dummy->next;
            // tmp = dummy; 
            free(dummy);
            break;
        }
        prev = dummy;
        dummy = dummy->next; 
        
        if (dummy == NULL)
            printf("Can't find node with val = %d\n", x);
    }
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
        int t = 0;
        while (dummy->val + GAP*(t++) != dummy->next->val) {
            if (dummy->next->val - dummy->val != GAP)
                ret = dummy->val + GAP * t - 1;
        }
        dummy = dummy->next;
        
    }
    return ret;
}

int main(int argc, char **argv)
{
    list* head = (struct list*)malloc(sizeof(struct list));
    head->val = 3;
    head->next = NULL;
    addNode(head, 4); 
    addNode(head, 5); 
    addNode(head, 6); 
    addNode(head, 7); 
    addNode(head, 8); 
    addNode(head, 9); 
    deleteNode(head, 7);
    //clearAll(head);
    int missing_val;
    missing_val = checkMissingNode(head);
    printf("Missing Element: %d\n", missing_val);
    printList(head);
    
    printf("\nThe End\n");
    return 0;
}