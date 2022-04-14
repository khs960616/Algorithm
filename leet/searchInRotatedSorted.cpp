/*
https://leetcode.com/problems/search-in-rotated-sorted-array/submissions/

nums배열은 오름차순으로 정렬되어있고, 각 값이 unique한 배열이다.
함수로 전달되기전 nums 배열은 특정 pivot index로 rotated된 이후에 전달된다.

pivot index인 k는 1이상, nums배열의 길이 미만이다.만약 pivot index가 k라면, 배열은
nums[k], num[k+1] .... nums[n-1] ... nums[0] 형태로 변화한다. 

target이 nums 배열에 존재하는 경우 해당 배열의 index를 없는 경우 -1을 반환한다.

작성 알고리즘은 log n의 시간 복잡도를 가져야한다.

---
1. pivot 지점을 찾아 낸다.(이진 탐색으로 찾을수 있음)
2. pivot 지점을 찾았다면 해당 인덱스를 기준으로 2개의 subArray로 분리해서 생각한다.
3. 각 subArray들은 오름차순으로 정렬되어있기 때문에 이진 탐색으로 값을 log(n)의 시간복잡도로 찾을 수 있다.

*/

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int lastIndex = nums.size()-1;
        if (lastIndex == 0 && nums[0] == target) {
            return 0;
        }
        
        int pivot = 0;
        findPivotIndex(nums, pivot, 0, lastIndex);
        
        int answer = -1;
        findValue(nums, answer, target, 0, pivot-1);
        findValue(nums, answer, target, pivot, lastIndex);
        return answer;
    }
    
private :
    void findPivotIndex(vector<int>& nums, int &pivot, int l, int r) {
        if(l>=r) return;
        int middle = (l+r)/2;
        checkSiblings(nums, pivot, l);
        checkSiblings(nums, pivot, middle+1);
        
        findPivotIndex(nums, pivot, l, middle);
        findPivotIndex(nums, pivot, middle+1, r);
    }
    
    void checkSiblings(vector<int>& nums, int& pivot, int index) {
        int lIndex = index-1 >= 0 ? index-1 : nums.size()-1;
        int rIndex = index+1 < nums.size() ? index+1 : 0;
        if(nums[lIndex]>nums[index] && nums[rIndex] > nums[index]){
            pivot = index;
            return; 
        }
    }
    
    void findValue(vector<int>& nums, int& answer,int target, int l, int r) {
        if(l>=r) {
            if(nums[l] == target) answer = l;
            return;
        }
        
        int middle = (l+r) / 2;
        if(nums[middle] == target) {
            answer = middle;
            return;
        } else if(nums[middle] > target) {
            findValue(nums, answer, target, l, middle);
        } else if(nums[middle] < target) {
            findValue(nums, answer, target, middle+1, r);
        }
    }
};
