/*
A linked list is given such that each node contains an additional random pointer 
which could point to any node in the list or null.

Return a deep copy of the list.

The Linked List is represented in the input/output as a list of n nodes. 
Each node is represented as a pair of [val, random_index] where:

val: an integer representing Node.val
random_index: the index of the node (range from 0 to n-1) 
where random pointer points to, or null if it does not point to any node.
*/

#include<iostream>
#include<vector>
#include<unordered_map>
#include<climits>
using namespace std;

// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(!head) return nullptr;
        unordered_map<Node*, Node*> map;
        Node* cur = map[head] = new Node(head->val);
        Node* ret = cur;
        
        while(head) {
            if(head->random) {
                auto it = map.find(head->random);
                if(it == map.end())
                    // emplace(iterator pos, Arg& args)
                    // in-place construct an object args at the position pos
                    it = map.emplace(head->random, new Node(head->random->val)).first;
                cur->random = it->second;
            }
            
            if(head->next) {
                auto it = map.find(head->next);
                if(it == map.end())
                    it = map.emplace(head->next, new Node(head->next->val)).first;
                cur->next = it->second;
            }
            
            cur = cur->next;
            head = head->next;
        }
        return ret;
    }
};

ostream& operator<< (ostream& os, const vector<vector<string>> s) {
    for (vector<string> i : s) {
        for (string& a : i)
            cout << a << " ";
        cout << "\n";
    }
    return os;
}

ostream& operator<<(ostream& os, const vector<int> &input)
{
    for (auto const& i: input) {
        os << i << " ";
    }
    return os;
}


int main() {
    
    Solution s;
    s.copyRandomList(new Node(5));

    return 0;
}
