/*
    answer 배열을 리턴해야한다.
    answer[i]는 nums[i]를 제외한 모든 원소의 곱을 리턴해야한다. 
    요구사항 : 시간복잡도 n, 나눗셈 사용 x 
    
    나눗셈을 사용하는 방식? -> 아마도 전체 nums를 한번 순회하며 전체 곱을 구해놓고 각 nums[i]값으로 나눈 값을
    answer 벡터에 넣으면 될 것임
    
    nums의 사이즈는 2이상 10^5이하
    nums의 각 값은 -30 이상, 30 이하
    
    추가 요구사항 공간복잡도 1로 문제 해결이 가능한가? 
    즉 answer벡터를 제외하고는 별도의 extra space를 사용하지 않는 방법이 있는가? 
    
    size = n 일 때,
    answer[n] = 1 * (nums[n-1] * nums[n-2] * num[n-3] ...... n[0])
    answer[n-1] = (num[n]) * (nums[n-2] * nums[n-3] * .... n[0])
    answer[n-2] = (num[n] * num[n-1]) * (num[n-3]*num[n-4]* .... * n[0])
    ...
    
    answer[1] = (num[n]*num[n-1]* ........)  * (n[0])
    answer[0] = (num[n] * num[n-1] * .....* n[1])
    
    왼쪽따로 오른쪽 따로 곱하면 2n으로 끝날듯해보임
*/
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> answer(nums.size(), 1);
        
        return answer;
    }
};
