/*
    https://leetcode.com/problems/maximum-product-subarray

    nums 배열의 contiguous subArray 중 각 element의 곱이 최대가 되는 결과를 return
    nums 배열의 크기는 1이상, 20000이하  
    (n^2아래로 시간복잡도 떨궈야할듯 -> nums배열을 순회하며 각 원소를 포함하는 subArray중 최대값을 만들어야함)
    각 element의 크기는 -10이상, 10이하
    
    i번째 원소를 포함하는 subArray의 최대 결과
    1. 현재 원소값 
    2. i-1번째 원소를 포함하는 subArray의 최대값 * 현재  원소값 
       - (예외 케이스 존재 가능 : 현재 곱해지는 값이 음수더라도 차후 뒤에 존재하는 음수 원소가 곱해져 최적해가 될 수 있   
       음)
    

    고민했던 방법
    -1 음수인 원소의 갯수가 짝수개라면 nums[i]*이전까지의 최대값, nums[i] 중 최대값인 것이 현재 i번째의 최적해이다.
    -2 음수인 원소의 갯수가 홀수개이고 1개이면 음수를 최대한 포함하지 않는 subArray중 위와 동일한 방법으로 해를 구하며, 1개 이상인 경우,
      맨 앞의 음수와 맨 뒤의 음수중 절대값이 더 큰 값을 포함하도록 하는 subArray를 고른다.
    -3 만일 nums 배열을 순회하며 값을 계산하는 도중 nums[i]가 0인 경우가 존재하면 다음번 계산을 위한 값을 1로 초기화 한다. 
    
    배열의 원소중 0이 포함되어있는 경우를 처리하지 못해서 결국 discussion을 봤다.
    https://leetcode.com/problems/maximum-product-subarray/discuss/1608800/C%2B%2B-or-Discussion-in-detail-or-Easy-to-understand
    
    내가 생각했던 방법중 2번의 경우에도 각 음수인 원소의 index를 기록하는 방식으로 접근했었는데, 해당 풀이에서와 같이 투포인터 알고리즘으로 앞에서부터 곱한값 vs 뒤에서부터 곱한 값을
    비교하는 방식이 시간과 메모리를 더 덜 잡아먹는 것 같았다..
    
    이전에 풀었던 https://github.com/khs960616/Algorithm/blob/master/leet/maximumSubArray.cpp 에서도 굳이 모든 값을 배열로 안가지고, 
    값을 갱신해나가는게 해당 문제 유형에서는 더 좋은 것 같다. (거의 동일한 유형의 문제였는데 응용이 조금 들어가니까 풀지 못한걸 보니 좀 더 공부가 필요할듯)
    
    이러한 유형의 알고리즘을 Kadane's algorithm 이라고 한다. 
*/


class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int answer = INT_MIN;
        int nSize = nums.size();
        int l = 1, r = 1;
        
        for(int i=0; i<nSize; i++) {
            l*=nums[i];
            r*=nums[nSize-1-i];
            answer = max(answer, max(l ,r));
            
            if(nums[i]==0) {
                l=1;
            }
            if(nums[nSize-1-i]==0) {
                r=1;
            }
        }
        
        return answer;
    }
};
