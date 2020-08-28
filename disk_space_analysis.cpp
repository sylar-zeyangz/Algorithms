/*
Input:
The input to the function/method consists of 3 arguments:
numComputer, an integer representing the number of computers;
hardDiskSpace, a list of integers representing the hard disk space of the computers;
segmentLength, an integer representing the length of the contiguous segment of computers to
be consider in each iterations.

Output:
Return an integer representing the maximum available disk space 
among all the minima that are found during the analysis.

Constraints:
1 ≤ numComputer ≤ 10^6
1 ≤ segmentLength ≤ numComputer
1 ≤ hardDiskSpace[i] ≤ 10^9
0 ≤ i < numComputer

Example:
Input:
numComputer = 3
hardDiskSpace = [8,2,4]
segmentLength = 2

Output:
2
*/

#include<iostream>
#include<vector>
#include<deque>
#include<algorithm>
#include<climits>

using namespace std;

// Ascending MonotonicQueue
class MonotonicQueue {
private:
    deque<int> data;
public:
    void push(int a) {
        while(!data.empty() && a < data.back()) {
            data.pop_back();
        }
        data.push_back(a);
    }
    
    void pop() {
        data.pop_front();
    }
    
    int max() const { return data.back(); }
    int min() const { return data.front(); }
    int size() const { return data.size(); }
};

class Solution {
public:
    int sliding_windows(int computerNumber, int* computerSpace, int segmentLength) {
        MonotonicQueue mq;
        int ans = 0; // 1 ≤ hardDiskSpace[i]
        for(int i = 0; i < computerNumber; ++i) {
            mq.push(computerSpace[i]);
            // cout << "{" << mq.min() << ", " << mq.max() << "}" << endl;
            if(i - segmentLength + 1 >= 0) {
                ans = max(ans, mq.min());
                if(computerSpace[i - segmentLength + 1] == mq.min()) {
                    mq.pop();
                }
            }                
        }
        return ans;
    }
};

int main() {
    Solution s;
    int a[] = {8, 2, 4};
    int b[] = {8, 2, 1, 7, 4, 8};
    cout << s.sliding_windows(3, a, 2) << endl;  // ans = 2
    cout << s.sliding_windows(6, b, 2) << endl;  // ans = 4
    cout << s.sliding_windows(6, b, 3) << endl;  // ans = 4
    cout << s.sliding_windows(6, b, 1) << endl;  // ans = 8
    return 0;
}

