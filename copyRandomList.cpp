/*
Given a list of positive integers nums and an int target, 
return indices of the two numbers such that they add up to a target - 30.

Conditions:

You will pick exactly 2 numbers.
You cannot pick the same element twice.
If you have muliple pairs, select the pair with the largest number.
*/

#include<iostream>
#include<vector>
#include<unordered_map>
#include<climits>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        if (nums.size() == 0) return {};
        unordered_map<int, int> imap;
        vector<int> result;
        int curMax = INT_MIN;

        for (int i = 0; i < nums.size() ; ++i) {
            int toLook = target - 30 - nums[i];
            auto it = imap.find(toLook);

            if (it != imap.end()) {
                curMax = curMax > nums[i] ? curMax : nums[i];
                result = {imap[toLook], i};
            }

            imap[nums[i]] = i;
        }
        return result;
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
    
    Solution S;
    vector<int> input = {20, 50, 40, 25, 30, 10};
    vector<int> result;
    result = S.twoSum(input, 90);
    cout<<"The answer is: "<< result << endl;
    return 0;
}
