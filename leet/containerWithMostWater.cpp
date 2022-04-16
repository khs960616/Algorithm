/*
https://leetcode.com/problems/container-with-most-water/

n개의 수직라인이 그려져있으며, 각 i번째 수직라인은 0~height[i] 만큼의 길이를 가지고 있다. 
컨테이너가 가장 많은 물을 포함하도록 하는 두개의 라인을 찾아서 컨테이너가 저장할수 있는 물의 최대양을 리턴한다.

최소 시간복잡도 n에 해결이 가능한 로직을 만들어야함

높이는 투 컨테이너 중에 더 작은쪽에 맞춰질것임 

1 10000 1 1 1 1 1 1 1 ......    1   이런식이면

가장 높은 y축을 선택하더라도 맨 처음 원소와 맨 마지막 원소를 고르는 것이 더 많은 양의 물을 저장할 수 있다.

접근방법 1)
two-pointer approach를 이용해서 너비가 가장 큰 컨테이너부터 시작, 왼쪽으로 하나 당긴것, 오른쪽으로 하나 당긴것
중 더 값이 큰쪽으로 이동하며 area값을 갱신해나가자. 
<< 예외 터짐 area를 아예 두개로 쪼개서 비교하는 방식은 어느한쪽에 최적해가 되는 높이를 가진 line이 있음을 보장해주지 않는다. 

class Solution {
public:
    int maxArea(vector<int>& height) {
        int nSize = height.size();
        int left = 0;
        int right = nSize-1;
        int answer = right * (min(height[0], height[right]));
        
        while(left<right) {
            int xAxis = right-left-1;
            int rightSubArea = min(height[left+1], height[right])* xAxis;
            int leftSubArea = min(height[left], height[right-1])* xAxis;
            
            if(rightSubArea>=leftSubArea) {
                answer = max(answer, rightSubArea);
                ++left;
            } else {
                answer = max(answer, leftSubArea);
                --right;   
            }
        }
        
        return answer;
    }
};  

실패한 코드

접근방법 2)
two-pointer approach를 이용하는 것은 유지하되, 방식을 바꾼다.
1. 맨처음원소와, 맨 마지막 원소를 포함하는 컨테이너부터 시작,
2. 둘중에 더 짧은 높이를 가지는 컨테이너의 index를 한칸씩 줄이면서 넓이의 최대값을 갱신한다. 

*/


class Solution {
public:
    int maxArea(vector<int>& height) {
        int nSize = height.size();
        int left = 0; 
        int right = nSize-1;
        int answer = right * (min(height[0], height[right]));
        
        while(0 < right-left-1) {
            int xAxis = right-left-1;

            if(height[left] <= height[right]) {
                answer = max(answer, xAxis* min(height[++left], height[right]));
            } else {
                answer = max(answer, xAxis*min(height[--right], height[left]));
            }
        }
        
        return answer;
    }
};
