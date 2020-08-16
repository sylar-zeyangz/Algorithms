/*
Merge two sorted linked lists and return it as a new sorted list. 
The new list should be made by splicing together the nodes of the first two lists.

Example:

Input: 1->2->4, 1->3->4
Output: 1->1->2->3->4->4
*/

#include<iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (l1 == nullptr) return l2;
        if (l2 == nullptr) return l1;
        
        ListNode* ret(nullptr);
        // Initialize the head
        if (l1 && l2) {
            if (l1->val <= l2->val) {
                ret = l1;
                l1 = l1->next;
            }
            else {
                ret = l2;
                l2 = l2->next;
            }
        }
        ListNode* final_ret = ret;    
        while (l1 && l2) {
            if (l1->val <= l2->val) {
                ret->next = l1;
                ret = l1;
                l1 = l1->next;
            } 
            else {
                ret->next = l2;
                ret = l2;
                l2 = l2->next;
            }
        }
        if (l1 == nullptr) ret->next = l2;
        if (l2 == nullptr) ret->next = l1;
        return final_ret;
    }
    
};

void printList(ListNode* n) 
{ 
    while (n != nullptr) { 
        cout << n->val << " "; 
        n = n->next; 
    } 
} 

int main()
{
    Solution S;
    ListNode* n1 = new ListNode(1);
    ListNode* n2 = new ListNode(2);
    ListNode* n3 = new ListNode(10);
    ListNode* na = new ListNode(2);
    ListNode* nb = new ListNode(3);
    ListNode* nc = new ListNode(8);
    ListNode* nd = new ListNode(200);
    n1->next = n2;
    n2->next = n3;
    na->next = nb;
    nb->next = nc;
    nc->next = nd;
    ListNode* result = S.mergeTwoLists(n1, na);
    printList(result); 
    //cout << "The answer is: " << result->val << endl;
    return 0;
}