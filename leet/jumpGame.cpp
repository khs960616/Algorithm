/*
    https://leetcode.com/problems/jump-game/
    Jump Game
    DP
    ----
    integer 배열 nums가 주어진다. 
    처음 위치 : 배열의 첫번쨰 index
    각 nums[i]  (i>=0) 에는 maximum jump 거리가 주어진다. 
    마지막 index까지 갈 수 있는지 여부를 반환하라.
*/

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int nSize = nums.size();
        int maxReachableIdx = 0;
        
        for(int i=0; i<nSize; ++i) {
            if(i>maxReachableIdx) return false;
            maxReachableIdx = max(maxReachableIdx, i+nums[i]);
        }
        return true;
    }
};
