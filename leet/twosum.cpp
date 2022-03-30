/*
여러개의 정수가 들어있는 벡터 num이 주어진다. 
이 떄 벡터에서 2가지 수를 더해 target이 되는 index 2개를 return 하라.

정확히 한가지 답만이 주어지며, 똑같은 요소를 두 번 사용할 수 없다. 

제약조건 
벡터 nums의 길이는 2보다 크며 10^4보다작다. 
>> 브루트 포스시 10^8
target 또는 nums는 10^9 보다 작다. 
숫자가 음수도 될 수 있음.
*/

#include <algorithm>
#include <vector>
#include <map>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> answer;
        
        map<int, int> m;
        int numSize = nums.size();
        for (int i=0; i<numSize; i++) {
            m[nums[i]] = i;
        }
        
        for (int i=0; i<numSize; i++) {
            auto pairItem = m.find(target-nums[i]);
            if (pairItem != m.end()) {
                answer.push_back(i);
                answer.push_back(pairItem->second);
                break;
            }
        }
        
        return answer;
    }
};
