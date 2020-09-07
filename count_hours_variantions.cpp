/*
Given a generic digital clock, having h number of hours and m number of minutes, 
the task is to find how many times the clock shows identical time. 
The parameters were 4 integers A,B,C,D. 
The valid time should be somewhere between 00:00 and 24:00. 
If the integers don't fulfil the requirements the function should return 0.

Restrictions: A,B,C,D are integers between [0,9]

Testcase#1 (1,0,0,2) => (00:12) (00:21) (01: 02) (01:20) (02:10) (02:01) (10:02) (10:20) (12:00) (20:01) (20:10) (21:00) => should return 12
Testcase#2 (2,1,2,1) => should return 6
Testcase#3 (1,4,8,2) => should return 5
Testcase#4 (4,4,4,4) => should return 0
*/

#include<iostream>
#include<vector>
#include<set>

using namespace std;


class Solution {
    void dfs(vector<int>& v, vector<bool>& u, int id, int hr, int mi, set<int>& a) {
        if(hr >= 24 || mi >= 60)
            return;
        if(id >= v.size()) {
            a.insert(hr * 60 + mi);
            return;
        }
        for(int i = 0; i < v.size(); ++i) {
            if(u[i] == false) {
                u[i] = true;
                if(id < 2) 
                    dfs(v, u, id + 1, hr * 10 + v[i], mi, a);
                else
                    dfs(v, u, id + 1, hr, mi * 10 + v[i], a);
                u[i] = false;
            }
                
        }
    }
public:
    // DFS method
    int count_hours_variations(int A, int B, int C, int D) {
        int count = 0;
        set<int> ans;
        vector<int> digits{A, B, C, D};
        vector<bool> used(4, false);
        dfs(digits, used, 0, 0, 0, ans);
        return ans.size();
    }
};

int main() {
    Solution s;
    cout << s.count_hours_variations(1, 0, 0, 2) << endl;
    cout << s.count_hours_variations(2, 1, 2, 1) << endl;;
    cout << s.count_hours_variations(1, 4, 8, 2) << endl;;
    cout << s.count_hours_variations(4, 4, 4, 4) << endl;;
    return 0;
}

