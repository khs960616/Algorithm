#include <bits/stdc++.h>
using namespace std;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/12920
  선입 선출 스케줄링
  ---
  이진탐색 
  많이 봐왔던 유형이였지만, 다음의 조건에 의해서  값처리에 있어 일부 까다로운 부분이 존재함
  - CPU에는 여러 개의 코어가 있고, 코어별로 한 작업을 처리하는 시간이 다릅니다.
  - 한 코어에서 작업이 끝나면 작업이 없는 코어가 바로 다음 작업을 수행합니다.
  - 2개 이상의 코어가 남을 경우 앞의 코어부터 작업을 처리 합니다.
  
  1. 이진 탐색의 기준이 될 작업 시간의 범위를 정한다.
     -> 탐색하고자 하는 구간의 시작 범위는 0부터 시작한다. (0시에 모든 작업을 시작할 수 있는 경우, 작업의 갯수가 코어의 갯수보다 작은 경우에 해당함)
     -> 가장 작업 시간이 오래걸리는 코어 1개만 이용해서 모든 작업을  처리하는 경우를 오른쪽 끝 범위로 설정한다.
     
  2. 1에서 구한 범위를 이용해서 작업 시간을 이진탐색을 한다.
     mid : 현재 시간을 의미한다.
     prev_start_cnt : mid 이전의 시작된 작업의 갯수를 저장하는 변수이다.
     mid_start_cnt : mid 시간에 시작된 작업의 갯수를 저장하는 변수이다. 
     
     prev_start_cnt와 mid_start_cnt를 이용해서 구하고자하는 값을 도출한다.
     prev_start_cnt가 작업의 갯수와 동일한 경우에는 마지막의 작업을 한 코어의 갯수를 구할 수 없다. (이미 이전에 완료되서 작업의 순서를 도출해 낼 수 없기 때문)
     
     따라서 이 문제가 구하고자하는 구간은 
     현재 시간이 mid일 때,  mid 시간 이전에 작업량은 총 작업의 갯수 n보다 작고,
     mid 시간 이전에 작업량 + mid 시간에 시작할 수 있는 작업의 갯수는 n보다 큰 범위이다. 
     (이렇게 되면, 현재 작업이 가능한 코어를 순차적으로 순회하며 마지막에 완료된 코어의 갯수를 구할 수 있다.)
     
     ---
     풀면서 느낀 점 
     1. 이전에 풀어봤던 유형이여서 시간을 이용해 이진 탐색으로 접근하는 방법은 금방 생각해냈으나, 
     이를 이용해서 값처리를 하는데 많은 어려움을 겪었음 (최소시간, 최대시간을 구하는 것이 아닌 순차적으로 코어값을 탐색해야하므로)
     
     2. 이진 탐색 문제라는 것이 생각이 들었다면 다음의 것을 차분히 생각해봐야될 것 같음.
        1) 이진 탐색의 대상이 되는 것은 무엇인가?   -> 문제에서 주어진 시간, 객체 등등.. 잘못 정하면 풀이가 산으로 감.. 
        
        2) 이진 탐색의 시작 범위, 끝 범위는 어떻게 지정할 것인가?  
            --> (최악의 경우 10,000 * 50,000 이라 max값 해당 값으로 두고 시작하니까 시간초과남.. 사실 이것도 통과해야 적합한 알고리즘이 아닌가? 싶음..)
            
        3) 이진 탐색에서 답을 도출해낼 수 있는 구간은 어디인가?
            --> 항상 여기서 많이 헤매는 것 같음.. 사실 좀더 많이 풀어보면서 감을 잡아야 할듯 
*/

int solution(int n, vector<int> cores) {
    int core_cnt = cores.size();
    int max_core = -1;
    for(int core: cores) {
        max_core = max(max_core, core);
    }
    
    int left = 0, right = n*max_core;
    while(left <= right) {
        int mid = (left+right)/2;
        int prev_start_cnt = 0;
        int mid_start_cnt = 0;
        
        for(int core: cores) {
            prev_start_cnt += (mid / core);
            if(mid % core != 0) prev_start_cnt += 1;
            else mid_start_cnt += 1;
        }
        
        if(prev_start_cnt >= n) {
            right = mid-1;
            continue;
        }
        
        if(prev_start_cnt+mid_start_cnt < n) {
            left = mid+1;
            continue;
        }
        
        for(int i=0; i<core_cnt; ++i) {
            if(mid % cores[i] == 0) prev_start_cnt++;
            if(prev_start_cnt == n) return i+1;
        }
        
        if(left == right) break;
    }
    
    return -1;
}
