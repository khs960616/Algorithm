/*
    https://leetcode.com/problems/house-robber-ii/
    
    인접한 두집을 도둑질하는 경우 경찰에게 알람이 간다.
    경찰에게 알람이 가지 않도록 하는 선에서 도둑질 할 수 있는 최대 금액을 구하라.
    이 경우 [0]번째 index와 [n-1]번째 인덱스도 인접함
    
    --- 
    
    이 경우 이렇게 접근하면 되지 않을까?
    점화식을 이용해 푸는 것은 그대로 두되,
    (0 ~ n-2), (n-2 ~ 1), 2개의 subArray로 나누어서 각각의 max값을 비교한다.
    
*/

class Solution {
public:
    int rob(vector<int>& nums) {
        int nSize = nums.size();
        if(nSize == 1) return nums[0];
        
        vector<int> leftResult(nSize, 0);
        vector<int> rightResult(nSize, 0);
        
        leftResult[0] = nums[0];
        leftResult[1] = max(nums[0], nums[1]);
        rightResult[nSize-1] = nums[nSize-1];
        rightResult[nSize-2] = max(nums[nSize-1], nums[nSize-2]);
        
        for(int i=2; i<nSize-1; ++i) {
            leftResult[i] = max(leftResult[i-2]+nums[i], leftResult[i-1]);
            rightResult[nSize-1-i] = max(rightResult[nSize+1-i]+nums[nSize-1-i], rightResult[nSize-i]);
        }
        

        return max(leftResult[nSize-2], rightResult[1]);
    }
};
