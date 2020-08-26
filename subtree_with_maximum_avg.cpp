/*
Given an N-ary tree, find the subtree with the maximum average. Return the root of the subtree.
A subtree of a tree is the node which have at least 1 child plus all its descendants. 
The average value of a subtree is the sum of its values, divided by the number of nodes.
*/

#include<iostream>
#include<vector>
#include<utility>  // pair
#include<algorithm>
#include<climits>

using namespace std;

struct Node{
    int val;
    vector<Node*> children; 
    
    Node(int v) : val(v) {}
    Node(int v, vector<Node*> c) : val(v), children(c) {}
};

class Solution {
    int max_avg = INT_MIN;
public:
    double maximumAverageSubtree(Node* root) {
        if(root == nullptr) return 0;
        return dfs_avg(root).first;
    }
    
    pair<double, int> dfs_avg(Node* root) {
        if(root == nullptr) return {0, 0};
        if(root->children.empty()) return {root->val, 1};
        int count = 1;
        int sum = root->val; 

        for(auto& n : root->children) {
            pair<double, int> p = dfs_avg(n);
            sum += p.first;
            count += p.second;
        }
        max_avg = max(max_avg, sum / count);
        return {max_avg, count};
    }
};

int main() {
    Node* root = new Node(10);
    Node* n1 = new Node(20);
    Node* n2 = new Node(30);
    Node* n3 = new Node(40);
    Node* n4 = new Node(10);
    Node* n5 = new Node(0);
    Node* n6 = new Node(100);
    Node* n7 = new Node(50);
    Node* n8 = new Node(60);
    root->children = {n1, n2, n3};
    n1->children = {n4, n5};
    n4->children = {n6};
    n3->children = {n7, n8};
    
    Solution s;
    cout << s.maximumAverageSubtree(root) << endl;
    return 0;
}

