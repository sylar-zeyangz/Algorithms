/*
Given a map Map<String, List<String>> userSongs with user names as keys 
and a list of all the songs that the user has listened to as values.

Also given a map Map<String, List<String>> songGenres, 
with song genre as keys and a list of all the songs within that genre as values. 
The song can only belong to only one genre.

The task is to return a map Map<String, List<String>>, 
where the key is a user name and the value is a list of the user's favorite genre(s). 
Favorite genre is the most listened to genre. 
A user can have more than one favorite genre 
if he/she has listened to the same number of songs per each of the genres.
*/

#include<iostream>
#include<unordered_map>
#include<vector>
using namespace std;

class Solution {
public:
    unordered_map<string,vector<string>> songsAndGenre(
    unordered_map<string,vector<string>>& users, unordered_map<string,vector<string>>& genres){
        unordered_map<string,string> stg;  // song to genre map
        // genres.first -> genres
        // genres.second - > songs
        for(auto i : genres) // iterate all genres
            for(string s : i.second) // iterate songs (s) in each genres
                stg[s] = i.first; // map the songs to genres
        
        unordered_map<string,unordered_map<string,int>> utg; // user to genre freq map
        // users.first -> user name
        // users.second -> songs
        for(auto i : users){  // iterate all users
            unordered_map<string,int> tm; // temp map
            for(string s : i.second)  // iterate songs that a user listened
                ++tm[stg[s]];  // find the genre of a song and put into the counter map tm
            utg[i.first] = tm;  // user name to genres' count 
            tm.clear();  // clear temp map for each user
        }
        unordered_map<string,vector<string>> ans;  // ans.first -> user, ans.second 
        // utg:
        // utg.first -> user name
        // utg.second -> genres' count
        for(auto i : utg) {  // iterate all users
            int mxf = 0; // max freq
            for(auto j : i.second)
                mxf = max(mxf, j.second);  // find the genre(s) with highest freq
            for(auto j : i.second){
                if(j.second == mxf)
                    ans[i.first].emplace_back(j.first);
            }
        }
        return ans;
    }
};

int main()
{
    unordered_map<string,vector<string>> users;
    users["David"] = {"song1", "song2", "song3", "song4", "song8"};
    users["Emma"] = {"song5", "song6", "song7"};
    
    unordered_map<string,vector<string>> songs;
    songs["Rock"] = {"song1", "song3"};
    songs["Dubstep"] = {"song7"};
    songs["Techno"] = {"song2", "song4"};
    songs["Pop"] = {"song5", "song6"};
    songs["Jazz"] = {"song8", "song9"};
    Solution s;
    auto result = s.songsAndGenre(users, songs);

    for(auto i : result)
    {
        cout << i.first << " -> ";
        for(string s : i.second)
            cout << s << " ";
        cout << endl;
    }
    return 0;
}
