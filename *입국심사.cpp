#include <bits/stdc++.h>
using namespace std;

/*
  https://programmers.co.kr/learn/courses/30/lessons/43238
  입국심사
  -------
  이진 탐색
  
  > 이진 탐색의 대상이 무엇이 될 것인가?  -> 처리하는데 걸리는 시간의 범위
  최소값 : 1 최대값: 가장 입국심사가 오래걸리는 심사관에게 모든 사람이 받는 경우
  이진 탐색을 통해 시간을 줄여가며, 각 심사관별로 해당 시간에 처리할 수 있는 사람의 수를 구한다.
*/
long long solution(int n, vector<int> times) {
    sort(times.begin(), times.end());
    long long answer = 0;
    
    long long start = 1;
    long long end = (long long) n * times.back();
    while(start<=end) {
        long long cnt = 0;
        long long mid = (start+end) / 2;
        // mid시간만큼 걸릴때, 각 심사관별로 처리할 수 있는 사람의 수
        for(int time: times) {
            cnt += (mid/time);
        }
        
        if(cnt < n) {
            start = mid + 1;
        } else {
            end = mid - 1;
            answer = mid;
        }
    }
    return answer;
}
