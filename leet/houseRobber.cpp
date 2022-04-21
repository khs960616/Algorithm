/*
    https://leetcode.com/problems/house-robber/

    인접한 집끼리 security system이 연결되어있는 있어, 인접한 두 집을 모두 도둑질 하는 경우
    경찰에게 자동으로 연락이 간다.
    
    각 집이 보유하는 금액 nums배열이 주어질 때, 경찰에게 신고당하지 않고 털 수 있는
    가장 큰 금액을 반환하라.
    ---
    이건 점화식을 세워서 풀면 되지 않을까? 
    
    0번째 집의 최대값 = nums[0]
    1번째 집을 선택할때의 최대값 =  max(nums[0], nums[1])
    2번째 집을 선택할떄의 최대값 = max(result[0]+nums[2], result[1])
    3번째 집을 선택할떄의 최대값 = max(result[1]+nums[3], result[2])
    이런식이지 않을까? 
    
    result[0] = 2;
    result[1] = 7;
    result[2] = max(2+9, 7) = 11
    result[3] = max(7+3, 11) = 11
    result[4] = max(11+1, 11) = 12 
  
    ---
    공간복잡도 자체도 nums.size()만큼 배열을 더 잡을 필요없이, i-2번째의 결과와, i-1번째의 결과만을 저장하는 두 변수를 놓고 사용하면 공간복잡도도 더 줄일수 있음!
*/

class Solution {
public:
    int rob(vector<int>& nums) {
        int nSize = nums.size();
        if(nSize == 1) return nums[0];
        
        vector<int> result(nSize, 0);
        result[0] = nums[0];
        result[1] = max(nums[0], nums[1]);
        
        for(int i=2; i<nSize; ++i) {
            result[i] = max(result[i-2]+nums[i], result[i-1]);
        }
        
        return result[nSize-1];
    }
};
