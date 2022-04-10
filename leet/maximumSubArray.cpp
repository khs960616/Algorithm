/*
https://leetcode.com/problems/maximum-subarray/submissions/

    합이 최대가 되는 최소 1개 이상의 원소를 가지는 subArray를 리턴한다.
    
    nums[i]는 10000이하, -10000 이상
    nums배열의 길이는 1이상, 100000 이하 
    
    k>=0, k<100001 일때 nums[k]까지의 합의 최대값은 num[0]~nums[k]까지의 합, nuns[k] 중 큰 값이 최대값이다. (문제에서 요구하는 subArray가 연속적인 인덱스를 가져야하므로)
    
    따라서 아래와 같이 코드를 사용하면 N의 시간복잡도로 해결이 됨.
    (max_element -> 배열 전체의 원소를 순회함 시간복잡도 n) 
    for문 내부에 if문을 두는 것보다 맨 마지막에 max_element 한번 돌리는게 결과적으로는 더 빠르게 나옴.
*/

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int answer = 0;
        int nSize = nums.size();
        vector<int> sum(nSize, 0);
        sum[0] = nums[0];
        
        for(int i=1; i<nSize; i++) {
            sum[i] = max(sum[i-1]+nums[i], nums[i]);
        }
        answer = *max_element(sum.begin(), sum.end());
        return answer;
    }
};
