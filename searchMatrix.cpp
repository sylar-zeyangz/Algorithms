/*
Write an efficient algorithm that searches for a value in an m x n matrix. 
This matrix has the following properties:

1. Integers in each row are sorted in ascending from left to right.
2. Integers in each column are sorted in ascending from top to bottom.
*/

#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(matrix.size() == 0) return false;
        const int m = matrix.size();  // total row
        const int n = matrix[0].size();  // total cols
        int r = 0;
        int c = n - 1;
        while(r < m && c >= 0) {
            if(matrix[r][c] == target) return true;
            else if(matrix[r][c] > target) 
                --c;
            else
                ++r;
        }
        return false;
    }
};

int main()
{
    Solution s;
    vector<vector<int>> mat = {{1, 10, 20, 30}, {2, 3, 4, 5}, {5, 15, 20, 25}};
    cout << s.searchMatrix(mat, -15);
    return 0;
}