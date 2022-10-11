#include <bits/stdc++.h>
#define MAX_SIZE 1000001
/*  

  https://school.programmers.co.kr/learn/courses/30/lessons/68646
  풍선 터트리기 
  ---
  DP
  
    문제 조건에 의해 항상 크기가 큰 풍선이 먼저 터진다는 제약조건이 존재한다. 따라서 문제를 단순화 시키면 특정 index에서 살펴봐야 할 값은 다음의 3가지이다.
    [?, ?, ?]  current_target  [?, ?, ?] 
    (좌측 값중 작은 값)  현재 값  (우측값중 가장 작은 값)  
    
    이 중 좌측 최솟값과, 우측 최솟값 모두 현재 index값보다 작다면, 현재 값은 최후까지 남아있을 수 없다. 
    
    ex)
    [-16,27,65,-2,58,-92,-71,-68,-61,-33]   answer : 6
    
    left[i] : 0~i번째 까지 원소중 가장 작은 값 
    right[i] :  i~n까지 원소중 가장 작은 값
    
    left : [-16, -16, -16, -16, -16, -92, -92, -92, -92, -92]
    right : [-92, -92, -92, -92, -92, -92,-71,-68,-61,-33]
    

    left[i-1], i번째 수, right[i+1]     
    i=0 가능
    i=1  -16, 27, -92   -> 불가능 
    i=2  -16, 65, -92   -> 불가능
    i=3  -16, -2   ,-92 -> 불가능 
    i=4  -16, 58, -92 -> 불가능 
    i=5 -16, -92, -71  -> 가능 
    i=6 -92, -71, -68  -> 가능 
    i=7 -92, -68, -61 -> 가능
    i=8 -92, -61, -33 -> 가능 
    i=9 -92, -33  (가능)
*/

using namespace std;

int n = 0;
int left_min[MAX_SIZE];
int right_min[MAX_SIZE];

void init_min_left_right_array(vector<int> a) {
    left_min[0] = a[0];
    right_min[n-1] = a[n-1];
    
    for(int i=1; i<n; ++i) {
        left_min[i] = min(left_min[i-1], a[i]);
        right_min[n-1-i] = min(right_min[n-i], a[n-1-i]);
    }
}

int solve(vector<int> a) {
    if(n==1) return 1;
    // 양쪽 끝값은 항상 최후까지 남아있을 수 있다. 
    int  answer = 2;
    for(int i=1; i<n-1; ++i) {
        int max_adj_idx_value = max(left_min[i-1], right_min[i+1]);
        if(a[i] < max_adj_idx_value) answer++;
    }
    return answer;
}

int solution(vector<int> a) {
    n = a.size();
    init_min_left_right_array(a);
    return solve(a);
}
