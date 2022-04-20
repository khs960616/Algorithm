/*
    차후 다시 풀어볼것
    https://leetcode.com/problems/combination-sum-iv/
    
    각 원소의 값이 고유한 integer원소 nums가 주어진다.
    이 때 nums의 원소들의 합으로 target을 구할 수 있는 가지수를 구해야한다.

    ---
    i번째까지 오는 개수를 memorization으로 구하도록 dP코드를 작성해야한다. 
    
    i가 n번째라고 가정할때,    i까지 도달할수 있는 케이스는 i-nums[0] ~  i-nums[n-1] 번째 케이스의 모든 합이다.  // (i-nums[0]) + nums[0] = i 이므로.
    
*/

class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        vector<long long> v(target+1, 0);
        v[0] = 1;
        
        for(int i=1; i<target+1; i++) {
            int cnt=0;
            for(int num: nums) {
                int index = i-num;
                if(index<0) break;
                cnt+=v[index];
            }
            v[i] = cnt;
        }
        
        return v[target];
    }
};
