/*
https://leetcode.com/problems/contains-duplicate/
  Integer 배열 nums가 주어질때, 모든 value 들중 빈도가 2번 이상인 원소가 있다면 true, 아니면 fasle를 리턴한다
*/

// 1. map을 사용한 풀이 : 각 element의 value를 키로, 빈도수를 세는 맵을 만들면서, 만일 빈도수가 2 이상인 원소가 있다면 return 한다.
// 다른 코드를 보니 굳이 빈도수 자체를 셀 필요도 없이, find 함수에서 찾아졌다면 이미 해당 element가 2개 이상 존재한다는 뜻이므로 true를 리턴하게 하면 된다. 

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        map<int, int> frequencyList;
        for (int num : nums) {
            auto item = frequencyList.find(num);
            if (item == frequencyList.end()) {
                frequencyList[num] = 0;
            }
            frequencyList[num] += 1;
            
            if (frequencyList[num] > 1) return true;
        }
        
        return false;
    }
};

//2. sort를 이용한 풀이 : 주어진 배열 nums를 정렬한다. 정렬된 배열을 순회하며, 인접한 element들의 값이 같은 경우가 존재하면 true를, 아니면 false를 리턴한다. 
// 시간복잡도 자체는 둘다 n으로 동일하나 2번 방식이 124ms로 1번 146ms 보다 조금더 빨랐으며, 공간 복잡도 자체도 덜 요구함.

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        
        int numSize = nums.size();
        int preValue = nums[0];
        for(int i=1; i<numSize; i++) {
            if(preValue == nums[i]) return true;
            preValue = nums[i];
        }
        return false;
    }
};
