/*
    Sylar Zhang - March 2020
    Binary Search Tree:
    (1) add a node
    (2) remove a node
    (3) find a node
    (4) dfs and bfs traverses
    (5) max and min value node
    (6) next successor (next largest node)
    (7) next smallest node
    (8) flatten a tree (like a list)
*/

#include <iostream>
#include <assert.h>
#include <queue>

using namespace std;

/*
struct list {
    list* next;
    int val;
    list(int x) { val = x; next = NULL; }
};
*/

class BST {
    public:
        int val;
        BST* left;
        BST* right;
        
        BST* addNode(BST*, int);
        BST* removeNode(BST*, int);
        // use inOrder to find a node
        BST* findNode(BST*, int);
        // dfs (depth-first search)
        void preOrder(BST*);
        void inOrder(BST*);
        void postOrder(BST*);
        // bfs (breadth-first search) - queue
        void bfs(BST*);
        
        void flatten(BST*);
        BST* nextSmallerNode(BST*, int);
        BST* nextLargerNode(BST*, int);
        BST* minValueNode(BST*);
        BST* maxValueNode(BST*);
        
        BST() : val(0), left(NULL), right(NULL){};
        // Can't believe C++ allows A = B = C now.. 
        BST(int x) {val = x; left = right = NULL;};
        ~BST() {};
    
};

BST* BST::addNode(BST* root, int x) {
    // root == nullptr
    if (!root)
        return new BST(x);
    if (x > root->val)
        // larger value goes to the right subtree
        root->right = addNode(root->right, x);
    else 
        // smaller or equal value goes to the right subtree
        root->left = addNode(root->left, x);
    return root;
}

BST* BST::removeNode(BST* root, int x) {
    if (root == NULL) return root;
    if (x < root->val) 
        root->left = removeNode(root->left, x);
    else if (x > root->val)
        root->right = removeNode(root->right, x);
    // x = root->val, remove the root node 
    else { 
        // removed node with only 1 or 0 child
        if (root->left == NULL) {
            BST* tmp = root->right;
            //free(root);
            return tmp;
        }
        else if (root->right == NULL) {
            BST* tmp = root->left;
            //free(root);
            return tmp;
        }
        else {
            /*
            // removed node with 2 children
            // get the inorder successor (the smallest in the right subtree)
            BST* tmp = minValueNode(root->right);
            // copy the inorder successor's content to this node 
            root->val = tmp->val;
            // remove the inorder successor
            root->right = removeNode(root->right, tmp->val);
            */
            
            // Or..
            
            BST* succParent = root->right; 
          
            // Find successor 
            BST* succ = root->right; 
            while (succ->left != NULL) { 
                succParent = succ; 
                succ = succ->left; 
            } 
      
            // Delete successor.  Since successor 
            // is always left child of its parent 
            // we can safely make successor's right 
            // right child as left of its parent. 
            succParent->left = succ->right; 
      
            // Copy Successor Data to root 
            root->val = succ->val; 
      
            // Delete Successor and return root 
            delete succ;          
        }
    }
    return root;
}

BST* BST::findNode(BST* root, int x) {
    if (root == NULL) return root;
    BST* targetNode = NULL;
    if (x < root->val)
        targetNode = findNode(root->left, x);
    else if (x > root->val)
        targetNode = findNode(root->right, x);
    // x == root->val 
    else
        targetNode = root;
    
    return targetNode;
}

BST* BST::minValueNode(BST* root) {
    BST* curr = root;
    while (curr && curr->left != NULL) {
        curr = curr->left;
    }
    return curr;
}

BST* BST::maxValueNode(BST* root) {
    BST* curr = root;
    while (curr && curr->right != NULL) {
        curr = curr->right;
    }
    return curr;
}

BST* BST::nextSmallerNode(BST* root, int x) {
    // if left subtree of node is not NULL, then smallest lies in left subtree
    BST* targetNode = findNode(root, x);
    
    if (targetNode->left != NULL)
        return maxValueNode(targetNode->left);
    // if left subtree of node is NULL, then start from root
    BST* ret = NULL;
    BST* tmp = root;
    while (tmp != NULL) {
        if (x < tmp->val)
            tmp = tmp->left;
        else if (x > tmp->val) {
            ret = tmp;
            tmp = tmp->right;
        }
        else
            break;
    }
    return ret;
}

// inorder succssor
BST* BST::nextLargerNode(BST* root, int x) {
    // if right subtree of node is not NULL, then succ lies in right subtree
    BST* targetNode = findNode(root, x);
    
    if (targetNode->right != NULL)
        return minValueNode(targetNode->right);
    // if right subtree of node is NULL, then start from root
    BST* succ = NULL;
    BST* tmp = root;
    while (tmp != NULL) {
        if (x < tmp->val) {
            succ = tmp;
            tmp = tmp->left;
        }
        else if (x > tmp->val)
            tmp = tmp->right;
        else
            break;
    }
    return succ;
}

void BST::flatten(BST* root) {
    BST* tree_list = NULL;
    if (root == NULL || root->left == NULL && root->right == NULL)
        return;
    BST* curr = NULL;
    // if root has left subtree, make it to a right subtree
    if (root->left != NULL) {
        flatten(root->left);
        // replace root->right with flattened root->left 
        BST* tmp = root->right;
        root->right = root->left;
        root->left = NULL;
        
        // insert the old right subtree
        curr = root->right;
        while (curr->right != NULL)
            curr = curr->right;
        curr->right = tmp;
    }

    flatten(root->right);
    
    //return tree_list;
}

void BST::preOrder(BST* root) {
    if (!root) return;
    cout << root->val << "\n";
    preOrder(root->left);
    preOrder(root->right);
}

void BST::inOrder(BST* root) {
    if (!root) return;
    inOrder(root->left);
    cout << root->val << "\n";
    inOrder(root->right);
}

void BST::postOrder(BST* root) {
    if (!root) return;
    postOrder(root->left);
    postOrder(root->right);
    cout << root->val << "\n";
}

void BST::bfs(BST* root) {
    queue<BST*> q;
    BST* tmp = root;
    q.push(tmp);
    while ( !q.empty() ) {
        q.pop();
        cout << tmp->val << "\n";
        // Enqueue
        if (tmp->left != NULL)
            q.push(tmp->left);
        if (tmp->right != NULL)
            q.push(tmp->right);
        // Dequeue
        tmp = q.front();
    }        
}

int main (int argc, char** argv) {
    // Initialization:
    /*
    BST root{5};
    root.addNode(&root, 7);
    root.addNode(&root, 2);
    root.addNode(&root, 3);
    root.addNode(&root, 6);
    root.addNode(&root, 1);
    root.addNode(&root, 4);
    */
    // Or ...
    BST* root = NULL;
    BST bst{};
    root = bst.addNode(root, 5);
    bst.addNode(root, 7);
    bst.addNode(root, 2);
    bst.addNode(root, 3);
    bst.addNode(root, 6);
    bst.addNode(root, 1);
    bst.addNode(root, 4);
    /*
              5
           /     \
          2       7
         / \     /
        1   3   6
             \
              4
    */
    
    // preOrder: 5 2 1 3 4 7 6
    // bst.preOrder(root);
    // inOrder: 1 2 3 4 5 6 7
    // bst.inOrder(root);
    // postOrder: 1 4 3 2 6 7 5
    // bst.postOrder(root);
    
    // bfs: 5 2 7 1 3 6 4
    // bst.bfs(root);
    // cout << "!!";
    root = bst.removeNode(root, 3);
    /*  Remove 3            Remove 5
              5                 6
           /     \          /       \
          2       7        2         7
         / \     /        / \
        1   4   6        1   3          
                              \
                               4
    */
    // bfs: 5 2 7 1 4 6, 6 2 7 1 3 4
    bst.bfs(root);
    // bst.inOrder(root);
    // cout << "findNode: " << bst.findNode(root, 4)->val << endl;
    cout << "nextLargerNode: " << bst.nextLargerNode(root, 4)->val << endl;
    cout << "nextSmallerNode: " << bst.nextSmallerNode(root, 4)->val << endl;
    
    BST* tree_list = NULL;
    bst.flatten(root);
    // flattend (tree list): 5 2 1 4 7 6
    bst.preOrder(root);
    
    return 0;
}
    
    