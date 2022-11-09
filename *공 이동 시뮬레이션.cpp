#include <bits/stdc++.h>
#define COLUMN_DECREASE 0
#define COLUMN_INCREASE 1
#define ROW_DECREASE 2
#define ROW_INCREASE 3
using namespace std;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/87391
  공 이동 시뮬레이션
  복잡한 시뮬레이션 구현 
  ---
  목적지인 (x, y)로부터 쿼리의 연산을 역순, 역방향으로 실행하며 도착 가능한 지점을 모두 찾아야한다.
  만약 시작점을 찾을 수 없는 쿼리가 나오게 되면 그 즉시 종료한다.
  
  예시를 들며 문제에서 주의해야할 상황을 적으면 다음과 같다.
  우선 예시이다.
  
     ex) 쿼리 : 열이 감소하는 방향으로 10감소 
     n = 5, m = 5,   x=0, y=0
     이면,  
     (0, 0), (0, 1), (0, 2), (0, 3), (0, 4)에서 열이 감소하는 방향으로 10 감소하는 경우 원하는 목적지 (0, 0)에 도착할 수 있으므로 후보군은 총 5가지가 된다.
     
     - 구하고자하는 영역의 y좌표가 영역밖을 벗어났음에도, 실제로 유효한 시작점이 존재한다.
     
     쿼리 : 열이 감소하는 방향으로 10감소 
     n = 5, m = 5, x=0, y =1
     이 경우 (0, 11)에 경우에만 원하는 목적지인 (0, 1)에 정확히 도착할 수 있다. 그러나 해당 좌표는 주어진 n, m에 벗어나며, 
     이는 어떤 시작점에서 출발하더라도, 쿼리들을 수행해서 원하는 목적지에 도착할 수 없음을 의미한다. 
     
  다음의 예시를 살펴보면 다음의 세 가지 사실을 알 수 있다.
  
  1. 목적지의 좌표가 쿼리가 이동하는 방향의 가장 끝 값인 경우, 최대 dx개의 시작점이 유효할 수 있다.
  
     쿼리가 열이 감소하는 방향으로 이동할 때, 목적지의 열이 0인 경우
     쿼리가 열이 증가하는 방향으로 이동할 때, 목적지의 열이 M-1인 경우
     쿼리가 행이 감소하는 방향으로 이동할 때, 목적지의 행이 0인 경우
     쿼리가 행이 증가하는 방향으로 이동할 때, 목적지의 행이 N-1인 경우 
     
  2. 1번 케이스에 해당하지 않는 경우, 유효한 시작점은 반드시 1개이다.
  
  3. 주어진 n, m을 벗어나는 위치에서 출발해야 원하는 목적지에 도착할 수 있는 경우 답은 항상 0이다. 
     
     
*/
long long N, M;

bool is_valid(long long x, long long y) {
    return (x>=0 && x <N) && (y>=0 && y<M);
}

void execute_query(vector<int> query, 
                        long long& left_y, long long& left_x,
                        long long& right_y, long long& right_x) {
    long long ret = 0, dx = query[1];
    int query_type = query[0];

  /*
    만약 열이 감소하는 방향으로 이동하는 쿼리의 경우, 실제 시작점을 구하기 위해서는 
    열이 증가하는 방향을 검사해야한다. 이 떄 right_y 값을 보정해주는 이유는 right_y의 경우 주어진 범위를 벗어나도,
    실제로 유효한 값들이 존재할 수 있기 때문이다. 
    
    ex) 쿼리 : 열이 감소하는 방향으로 10감소 
     n = 5, m = 5,   x=0, y=0  이면  에서 left_y = 0, right_y = 10이 된다.
     (0, 0), (0, 1), (0, 2), (0, 3), (0, 4) 
     다음의 4가지 좌표는 right_y가 격자 범위를 벗어났다하더라도, 실제로 유효한 좌표이므로, 이동하는 방향의 row, column값은 항상 보정되야한다.
  */
    switch(query_type) {
        case COLUMN_DECREASE:
            if(left_y != 0) left_y += dx;
            right_y = min(M-1, right_y+dx);
            return;
        case COLUMN_INCREASE:
            if(right_y != M-1) right_y -= dx;
            left_y = max(0LL, left_y-dx);
            return;
        case ROW_DECREASE:
            if(left_x != 0) left_x += dx;
            right_x = min(N-1, right_x+dx);
            return;
        case ROW_INCREASE:
            if(right_x != N-1) right_x -= dx;
            left_x = max(0LL, left_x-dx);
            return;
    }
}

long long solution(int n, int m, 
                   int x, int y, 
                   vector<vector<int>> queries) {
    N = n, M = m;
    int q_cnt = queries.size();
    // left_x, right_x -> 도착점의 후보가 될 수 있는 row의 시작점, 도착점
    // left_y, right_y -> 도착지의 후보가 될 수 있는 column의 시작점, 도착점
    long long left_x = x, right_x = x, left_y = y, right_y= y; 
    
    for(int i=q_cnt-1; i>=0; --i) {
        execute_query(queries[i], left_y, left_x, right_y, right_x);
        
        if(!is_valid(left_x, left_y) || !is_valid(right_x, right_y)) {
            return 0;
        }
    }

    return (right_y-left_y+1) * (right_x-left_x+1);
}
