/*
https://leetcode.com/problems/longest-increasing-subsequence/submissions/

nums 배열이 주어진다. subsequence중 원소가 오름차순으로 증가하는 subsequence중 가장 긴 길이를 return 한다. 
subsequence : 주어진 배열 nums에서 원소끼리의 순서를 바꾸지 않고, 특정 원소를 제거해서 나올 수 있는 배열

nums 배열의 길이는 1이상 2500 이하이다. 
각 배열의 수는 -10000이상, 10000이하이다.

부분 최적해가 뭐가 될까? 

1개 짜리 배열 : nums 배열을 순차적으로 훑으며 현재 최소값과 비교하며 계속 교체
2개 짜리 배열 : (기존에 존재하는 배열 or 1개짜리 배열 + 현재 값) 중 마지막 원소가 더 작은 것 
3개 짜리 배열 : (기존에 존재하는 배열 or 2개짜리 배열 + 현재 값) 중 마지막 원소가 더 작은 것 
...
n개 짜리배열 : 기존에 존재하는 배열값, n-1개짜리 배열 + 현재값 중 마지막 원소가 더 작은 것 
이런 식으로 유지.

v[n] -> v[n-1]번째 원소 보다 현재 원소값이 크고, v[n]값보다는 현재 원소값이 작다면 대입
v[n-1] -> v[n-2]번째 원소보다 현재 원소값이 크고, v[n-1]값보다 현재 원소값이 작다면 대입
....

v[1] -> v[0] 보다 현재 원소값이 더 크고, v[n-1]값보다 현재 원소값이 작다면 대입 
v[0] -> v[0] 보다 현재값이 더 작다면 대입 


*/ 

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int answer = 1;
        vector<int> v;
        v.push_back(nums[0]);
       
        for(int num: nums) {
            for(int i=answer; i>0; i--) {
                if(v[i-1]>=num) continue;
                
                if(i==answer) {
                    v.push_back(num);
                    answer++;
                } else {
                    v[i] = min(v[i], num);
                }
            }
            if(v[0] > num) v[0] = num;
        }
        return answer;
    }
};
