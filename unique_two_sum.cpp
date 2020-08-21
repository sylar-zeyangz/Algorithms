/*
Given an int array nums and an int target, 
find how many unique pairs in the array such that their sum is equal to target. 

Return the number of pairs.
*/

#include<iostream>
#include<vector>
#include<climits>
#include<algorithm>
using namespace std;

int countUniquePairs(vector<int> nums, int target){
	sort(nums.begin(), nums.end());

	int lastValidPairLarger = INT_MIN;
	int left = 0, right = nums.size() -1;
	int count = 0;

	while(left < right){
		int currSum = nums[left] + nums[right];
		if (currSum == target){
			if(lastValidPairLarger != nums[right]){
				count++;
			}
			lastValidPairLarger = nums[right];
			left++; right--;
		} else if (currSum < target){
			left++;
		} else{
			right--;
		}
	}

	return count;
}

int main() {
    vector<int> src{1, 1, 2, 45, 46, 46};
    int target = 47;
    cout << countUniquePairs(src, target) << endl;
    return 0;
}

