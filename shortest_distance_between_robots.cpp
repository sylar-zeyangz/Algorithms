/*
Find closest 2 points and return their squared distance (Euclidean distance)
distance = 0 will not be considered
*/

#include<iostream>
#include<vector>
#include<utility>  // pair
#include<climits>
#include<algorithm>

//#include<bits/stdc++.h> 

using namespace std;


inline int dist(pair<int, int> p1, pair<int, int> p2) {
    return (p2.first - p1.first)*(p2.first - p1.first) + (p2.second - p1.second)*(p2.second - p1.second);
}

class Solution {
private:
    int shortest_distance_helper(int n, vector<pair<int, int>> cor) {
        if(n < 2) return INT_MAX;
        if(n == 2) return dist(cor[0], cor[1]);
        int left_lo = shortest_distance_helper(n / 2, {cor.begin(), cor.begin() + n / 2});
        int right_lo = shortest_distance_helper(n - n / 2, {cor.begin() + n / 2, cor.end()});                                
        int d = min(left_lo, right_lo);
        int l = cor[n / 2].first;

        for(auto& c : cor) {
            if(c == cor[n / 2]) continue;
            if(c.first + d >= l || c.first - d <= l)
                d = min(dist(c, cor[n / 2]), d);
        }
        
        return d;
    }
public:
    int shortest_distance(int n, vector<int> x, vector<int> y) {
        if(n < 1) {
            cout << "Invalid input!\n";
            return -1;
        }
        if(n == 1) {
            cout << "Only 1 robot! Cannot calculated distance!\n";
            return -1;
        }
        vector<pair<int, int>> cor;
        for(int i = 0; i < n; ++i)
            cor.emplace_back(x[i], y[i]);
        sort(cor.begin(), cor.end());

        return shortest_distance_helper(n, cor);
    }
};

int main() {
    Solution s;
    cout << s.shortest_distance(3, {5, 2, 2}, {3, 2, 5}) << endl; // ANS = 9 -> (2,2) & (2,5) 
    cout << s.shortest_distance(6, {2, 4, 5, 7, 1, 0}, {3, 0, 1, 4, 8, 2}) << endl; // ANS = 2 -> (4,0) & (5, 1)
    cout << s.shortest_distance(2, {7, 1}, {1, 4}) << endl;  // ANS = 45
    
    return 0;
}

