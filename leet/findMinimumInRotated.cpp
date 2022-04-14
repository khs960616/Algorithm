/*
https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/submissions/

    길이가 n인 배열 nums가 주어진다.
    본래 배열은 오름차순으로 정렬되어있는데, 1~n번 rotated되어져서 순서가 섞여있다.
    (rotated: 맨 뒤의 원소를 맨 앞으로 당겨오는 연산)
    각 element들은 unique하다.
    nums배열중 가장 크기가 작은 원소를 return 해야한다.
    
    ---
    로그 n만큼의 시간복잡도를 가지는 알고리즘을 작성해야한다.
    >> 정렬되어있는 배열은 아니지만, 이분 탐색을 잘 응용하면 풀 수 있지 않을까? 
    >> 만일 i번쨰 원소가, i-1번쨰 원소와, i+1번째 원소보다 작다면 i번째 원소가 가장 작은 원소일 것이다. (rotate되기 이전의 배열이 오름차순으로 정렬되어있었을 것이므로)
    
    
1. 절반씩 쪼갬 
2. subArray로 나뉜 두개의 배열에서 가장 왼쪽 원소를 선택한다. 
3. 해당 원소의 좌측, 우측 원소를 검사한다. 만일 좌측 우측 원소 모두 자기 자신보다 크다면 해당 원소가 정답이다.
*/


class Solution {
public:
    int findMin(vector<int>& nums) {
        int answer=nums[0];
        int lastIndex = nums.size()-1;
        searchVector(nums, answer, 0, lastIndex);
        return answer;
    }
    
    void searchVector(vector<int>& nums, int &answer, int l, int r) {
        if(l>=r) return;
        int middle = (l+r)/2;
        checkSiblings(nums, answer, l);
        checkSiblings(nums, answer, middle+1);
        
        searchVector(nums, answer, l, middle);
        searchVector(nums, answer, middle+1, r);
    }
    
    void checkSiblings(vector<int>& nums, int& answer, int index) {
        int lIndex = index-1 >= 0 ? index-1 : nums.size()-1;
        int rIndex = index+1 < nums.size() ? index+1 : 0;
        if(nums[lIndex]>nums[index] && nums[rIndex] > nums[index]){
            answer = nums[index];
            return; 
        }
    }
};
