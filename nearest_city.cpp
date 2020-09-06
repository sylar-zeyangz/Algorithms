/*
Write an algorithm to determine the name of the nearest city 
that shares an x or a y coordinate with the queried city. 
If no cities share an x or y coordinate, return none. 
If two cities have the same distance to the queried city, q[i], 
consider the one with an alphabetically smaller name (e.e 'ab' < 'aba' < 'abb') as the closest choice.

The distance is denoted on a Euclidean plan: the difference in x plus the difference in y.

Input
the input to the function/method consists of six arguments:
numOfCities, an integer representing the number of cities;
cities, a list of strings representing the names of each city[i];
xCoordinates, a list of integers representing the X-coordinates of each city[i];
yCoordinates, a list of integers representing the Y-coordinates of each city[i];
numOfQueries, an integer representing the number of queries;
queries, a list of strings representing the names of the queried cities.

Output
Return a list of strings representing the name of the nearest city 
that shares either an x or a y coordinate with the queried city.

Constraints
1 ≤ numOfCities, numOfQueries ≤ 10^5
1 ≤ xCoordinates[i], yCoordinates[i] <= 10^9
1 ≤ length of queries[i] and cities[i] ≤ 10

Note
Each character of all c[i] and q[i] is in the range ascii[a-z, 0-9,-]
All city name values, c[i] are unique. All cities have unique coordinates.
*/

#include<iostream>
#include<vector>
#include<map>
#include<utility> 
#include<algorithm>
#include<climits>
#include<set>

using namespace std;


class Solution {
    bool mycomp(string a, string b){
        //returns 1 if string a is alphabetically 
        //greater than string b
        //quite similar to strcmp operation
        return a > b;
    }
public:
    // complexity ~ m*n
    vector<string> nearest_city_slow(int numOfCities, vector<string> cities, vector<int> xCoordinates, 
                        vector<int> yCoordinates, int numOfQueries, vector<string> queries) {
        vector<string> ans;                    
        for(auto q : queries) {
            auto it = find(cities.begin(), cities.end(), q);
            if(it == cities.end()) {
                cout << "not find the city " << q << endl;
                continue;
            }
            int index = distance(cities.begin(), it);
            int min_dist = INT_MAX;
            int t = -1;
            for(int i = 0; i < numOfCities; ++i) {
                if(i == index)
                    continue;
                if(xCoordinates[i] == xCoordinates[index] && 
                    abs(yCoordinates[i] - yCoordinates[index]) <= min_dist) {
                    int new_dist = abs(yCoordinates[i] - yCoordinates[index]);
                    if(new_dist == min_dist && mycomp(cities[i], cities[index]))
                        continue;
                    t = i;
                    min_dist = new_dist;
                    continue;
                }
                if(yCoordinates[i] == yCoordinates[index] && 
                    abs(xCoordinates[i] - xCoordinates[index]) <= min_dist) {
                    int new_dist = abs(xCoordinates[i] - xCoordinates[index]);
                    if(new_dist == min_dist && mycomp(cities[i], cities[index]))
                        continue;
                    t = i;
                    min_dist = new_dist;
                    continue;    
                }
            }
            if(t == -1)
                ans.push_back("None");
            else        
                ans.push_back(cities[t]);
        }
        return ans;
    }
    
    // complexity ~ n+m
    vector<string> nearest_city(int numOfCities, vector<string> cities, vector<int> xCoordinates, 
                        vector<int> yCoordinates, int numOfQueries, vector<string> queries) {
        if(numOfCities == 1)
            return {"None"};
        map<string, pair<int, int>> city_map;
        map<int, set<string>> xmap;
        map<int, set<string>> ymap;

        for(int i = 0; i < numOfCities; ++i) {
            city_map[cities[i]] = make_pair(xCoordinates[i], yCoordinates[i]);

            xmap[xCoordinates[i]].insert(cities[i]);
            ymap[yCoordinates[i]].insert(cities[i]);
        }
        // Print a map
        // for(auto c : city_map) {
        //    cout << c.first << c.second.first << c.second.second << endl;
        // }
        
        vector<string> ans;
        for(int i = 0; i < numOfQueries; ++i) {
            int x = city_map[queries[i]].first;
            int y = city_map[queries[i]].second;
            int dist = INT_MAX;
            int tmp_dist = 0;
            if(xmap[x].size() == 1 && ymap[y].size() == 1) {
                ans.push_back("None");
                continue;
            }
            string res = "";
            for(auto c : xmap[x]) {
                if(c == queries[i])
                    continue;
                tmp_dist = abs(y - city_map[c].second); 
                if(tmp_dist < dist) {
                    dist = tmp_dist;
                    res = c;
                }
                
            }
            for(auto c : ymap[y]) {
                if(c == queries[i])
                    continue;
                tmp_dist = abs(x - city_map[c].first); 
                if(tmp_dist < dist) {
                    dist = tmp_dist;
                    res = c;
                }
            }
            ans.push_back(res);
        }
        return ans;
    }
};

ostream& operator<<(ostream& os, vector<string> strs) {
    for(auto s : strs) 
        cout << s << endl;
    return os;
}

int main() {
    Solution s;
    int numOfCities = 3;
    vector<string> cities = {"abb", "aba", "ab"};
    vector<int> xCoordinates = {3, 2, 1};
    vector<int> yCoordinates = {3, 3, 3};
    int numOfQueries = 3;
    vector<string> queries = {"abb", "aba", "ab"};
    cout << s.nearest_city(numOfCities, cities, xCoordinates, yCoordinates, numOfQueries, queries);
    return 0;
}

