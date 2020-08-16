/*
Given an array of strings products and a string searchWord. 
We want to design a system that suggests at most three product names from products,
after each character of searchWord is typed. 
Suggested products should have common prefix with the searchWord. 
If there are more than three products with a common prefix,
return the three lexicographically minimums products.

Return list of lists of the suggested products after each character of searchWord is typed. 
*/

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Trie {
public:
    Trie() : nodes(26, nullptr) {}
    ~Trie() {
        for(auto n : nodes)
            delete n;
    }
    
    vector<Trie*> nodes;
    vector<const string*> words;
    
    static void addWord(Trie* root, const string& word) {
        for(auto c : word) {
            if(!root->nodes[c - 'a'])
                root->nodes[c - 'a'] = new Trie();
            root = root->nodes[c - 'a'];
            if(root->words.size() < 3)
                root->words.push_back(&word);
        }
    }
    
    static vector<vector<string>> getWords(Trie* root, const string& prefix) {
        vector<vector<string>> ans(prefix.size());
        for (int i = 0; i < prefix.size(); ++i) {
          char c = prefix[i];
          root = root->nodes[c - 'a'];
          if (root == nullptr) break;
          for (auto* word : root->words)
            ans[i].push_back(*word);
        }
        return ans;
    }
};

class Solution {
public:
    // Method 1: Trie (Prefix tree)
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
        sort(products.begin(), products.end());
        Trie root;
        for(const auto& p : products)
            Trie::addWord(&root, p);
        return Trie::getWords(&root, searchWord);
    }  
    
    // Method 2: Binary search (When only one searchWord is given)
    vector<vector<string>> suggestedProductsBS(vector<string>& products, string searchWord) {
        vector<vector<string>> ans;
        sort(products.begin(), products.end());
        string key = "";
        for(const char& c : searchWord) {
            key += c;
            auto l = lower_bound(products.begin(), products.end(), key);
            auto r = upper_bound(products.begin(), products.end(), key += "~");
            key.pop_back();  // remove the "~"
            ans.emplace_back(l, min(l + 3, r));
        }
        while(ans.size() != searchWord.length()) ans.push_back({});
        return ans;
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


int main() {
    
    vector<string> products{"mobile", "mouse", "moneypot", "monitor", "mousepad"};
    Solution s;
    // Trie
    cout << s.suggestedProducts(products, "mouse");
    // BS
    cout << s.suggestedProductsBS(products, "mouse");
    
    return 0;
}
