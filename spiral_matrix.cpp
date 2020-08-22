/*
Given a positive integer n, generate a square matrix filled with elements from 1 to n2 in spiral order.

Example:

Input: 3
Output:
[
 [ 1, 2, 3 ],
 [ 8, 9, 4 ],
 [ 7, 6, 5 ]
]
*/

#include<iostream>
#include<vector>

using namespace std;

vector<vector<int>> spiral_matrix(int num) {
    int dir = 0;
    int max_x = num - 1; 
    int max_y = num - 1;
    int min_x = 0;
    int min_y = 1;
    int i = 0,x = 0, y = 0;
    vector<vector<int>> ans(num, vector<int>(num));
    while(++i <= num * num) {
        ans[y][x] = i;
        switch (dir) {
            // right
            case 0: if(++x == max_x) {dir = 1; --max_x;} break;
            // down
            case 1: if(++y == max_y) {dir = 2; --max_y;} break;
            // left
            case 2: if(--x == min_x) {dir = 3; ++min_x;} break;
            //up:
            case 3: if(--y == min_y) {dir = 0; ++min_y;} break;
        }
    }
    return ans;
}

// matrix output
ostream& operator<<(ostream& os, const vector<vector<int>> v) {
    for(auto i : v) {
        for(auto j : i) 
            cout << j << " ";
        cout << endl;
    }
    return os;
}

int main() {
    cout << spiral_matrix(5);
    return 0;
}


