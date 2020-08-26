/*
Find the maximum units a truck can hold

input:
num -> an integer representing number of products (boxes.size())
boxes -> a list of integer representing available boxes for products
unitSize -> an integer representing unit per box  (unitsPerBox.size())
unitsPerBox -> a list of integer representing unit per box
truckSize -> an integer representing the truck space (maximum boxes)

output:
maximum units
*/

#include<iostream>
#include<vector>
#include<utility>  // pair
//#include<queue>
#include<algorithm>

//#include<bits/stdc++.h> 

using namespace std;

class Solution {
public:
    int getMaxUnit(int num, vector<int> boxes, int unitSize, vector<int> unitsPerBox, int truckSize) {
        if(num == 1) 
            return boxes[0] <= truckSize ? boxes[0] * unitsPerBox[0] : truckSize * unitsPerBox[0];

        //priority_queue<int, vector<int>, less<int>> pq;
        vector<pair<int, int>> unitsInBox;
        for(int i = 0; i < unitSize; ++i)
            unitsInBox.emplace_back(unitsPerBox[i], boxes[i]);
        sort(unitsInBox.begin(), unitsInBox.end(), [](auto& a, auto& b) {return  a.first > b.first;});
        
        int max_units = 0;
        for(int i = 0; i < unitsInBox.size() && truckSize > 0; ++i) {
            int curr_unit = unitsInBox[i].first;
            int curr_box = unitsInBox[i].second;
            max_units += curr_unit * min(truckSize, curr_box);
            truckSize -= min(truckSize, curr_box);
            // cout << "max_units = " << max_units << " truckSize = " << truckSize << endl;
        }

        return max_units;
    }
};

int main() {
    Solution s;
    vector<int> boxes{1, 2, 3, 2};
    vector<int> unitPerBox{3, 2, 1, 5};
    cout << s.getMaxUnit(4, boxes, 4, unitPerBox, 4) << endl; // 2*5 + 1*3 + 1*2 = 15
    cout << s.getMaxUnit(3, {1, 2, 3}, 3, {3, 2, 1}, 3) << endl; // 1*3 + 2*2 = 7
    cout << s.getMaxUnit(1, {3}, 2, {4}, 2) << endl; // 2*4 = 8
    return 0;
}

