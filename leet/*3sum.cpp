/*

https://leetcode.com/problems/3sum/submissions/

index가 서로 다른 3개의 원소들 중, 합이 0인 것들의 값을 모아서 return 해야한다.
또한 결과값은 중복되는 triple이 없어야한다.

차후 다시 풀어볼 것 (sorting까지는 생각했으나 그 이후 풀이를 찾지 못해, discussion 보고 이해함)

사용 알고리즘 : Sort, two-pointer 알고리즘, 

1. 0 <= nums.length <= 3000 이므로 시간복잡도가 n^3인 풀이 (3중 for문 통한 브루트포스)는 불가, 최소 시간복잡도 n^2인 방안을 찾아야한다. 
2. 배열을 오름차순으로 정렬한다.
3. 배열을 순회하며 현재 배열의값, 배열의 오른편에 있는 원소들의 순서쌍의 합을 구한다.  (이때 투포인터 approach를 이용해서 남은 배열중 가장 작은값과 큰값을 더해준다.)
   -  만일 현재 원소가 양수라면, 이후에 나오는 모든 배열의 원소도 양수기 때문에 합이 0이 될 수 없으므로 더 이상 반복문을 돌 필요가 없다.
   -  만약 현재원소가 이전 원소와 크기가 같다면 현재 원소에서 구할수 있는 triple은 이전 원소에서 구할수 있는 값이므로 값이 중복되는 것을 피하기 위해 continue한다.
4. 3번 과정에서 구한 합이 0보다 크다면, 합을 줄여야 하므로, 가장 큰 값으로 더 한 index를 왼쪽으로 한칸 이동, 0보다 작다면 가장 작은값으로 더한 index보다 오른쪽으로 한칸 이동한후 3번 과정을 반복한다.
   - 만일 3개의 원소의 합이 0이라면, answer vector에 답을 추가해주고, 중복되는 값을 제외하고 3번의 과정을 반복한다.
    

*/

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> answer;
        sort(nums.begin(), nums.end());
    
        int lastIndex = nums.size()-1;
        for(int i=0; i<lastIndex-1; ++i) {
            if(nums[i]>0) break;
            if(i>0 && nums[i] == nums[i-1]) continue;
            
            int left = i+1;
            int right = lastIndex;
            
            while(left<right) {
                int sum = nums[i] + nums[left] + nums[right];
                
                if(sum>0) {
                    --right;
                } else if(sum<0) {
                    ++left;
                } else {
                    int leftValue = nums[left];
                    int rightValue = nums[right];
                    answer.push_back({nums[i], leftValue, rightValue});

                    while(left<right && nums[left] == leftValue) {
                        ++left;
                    }
                    while(left<right && nums[right] == rightValue) {
                        --right;
                    }
                }
            }
        }       
        return answer;
    }
};
