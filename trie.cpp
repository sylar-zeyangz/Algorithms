/*
    Trie / Prefix tree
*/

#include<iostream>
#include<vector>
#include<memory> // for unique_ptr
using namespace std;

class Trie {
private:
    struct TrieNode {
        bool is_word;
        vector<TrieNode*> children;
        
        TrieNode() : is_word(false), children(26, nullptr) {}
        ~TrieNode() {
            for(TrieNode* child : children)
                if(child)
                    delete child;
        }
    };
    
    unique_ptr<TrieNode> root_;  //std::unique_ptr

public:
    // Initialize the prefix tree
    Trie() : root_(new TrieNode()) {}
    // Since root is a smart pointer (unique_ptr)
    // delete root at destructor is skipped
    ~Trie() {}
    
    // Insert a word into the trie / prefix tree
    void insert(const string& word) {
        TrieNode* p = root_.get();
        for(const char c : word) {
            if(!p->children[c - 'a'])
                p->children[c - 'a'] = new TrieNode();
            p = p->children[c - 'a'];
        }
        p->is_word = true;
    }
    
    // In the trie, if there is a word starting with the prefix
    bool startsWith(const string& prefix) const {
        return find(prefix) != nullptr;
    }
    
    // Returns if the word is in the trie
    bool search(const string& word) {
        const TrieNode* p = find(word);
        return p && p->is_word;
    }
    
    const TrieNode* find(const string& prefix) const {
        const TrieNode* p = root_.get();
        for(const char c : prefix) {
            p = p->children[c - 'a'];
            if(p == nullptr) break;
        }
        return p;
    }        
        
};


int main() {
    
    Trie t;
    t.insert("apple");
    t.insert("application");
    t.insert("time");
    t.insert("tiger");
    t.insert("tigerball");
    cout << t.startsWith("ti") << endl;  // 1
    cout << t.search("ti") << endl;  // 0
    cout << t.search("apple") << endl;  // 1
    
    return 0;
}
