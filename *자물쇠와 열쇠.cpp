#include <bits/stdc++.h>
using namespace std;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/60059
  2020 KAKAO BLIND RECRUITMENT
  자물쇠와 열쇠 
  ---
  시뮬레이션
  
  lock에 대해 key를 적용시킬 수 있는 모든 경우를 시뮬레이션한다.
  필요 기능
  
  1. 배열 시계 방향 회전
  2. key를 lock에 대해서 슬라이딩 윈도우 형식으로 값을 더하는 기능
  3. lock이 모두 해제가 가능한지 확인하는 기능
*/

int n = 0, m = 0;
vector<vector<int> > board;

/*
  key의 모든 원소를 시계방향으로 90도 회전 시킨다.
*/
vector<vector<int>> lotate_key(vector<vector<int>> key) {
    int key_size = key.size();
    vector<vector<int> > ret(key_size, vector<int>(key_size, 0));
    for(int i=0; i<key_size; ++i) {
        for(int j=0; j<key_size; ++j) {
            ret[j][i] = key[key_size-1-i][j];
        }
    }
    return ret;
}

/* 
  key의 가장 오른쪽 아래 grid가, lock의 가장 왼쪽 위 grid와 겹치는 부분부터,
  key의 가장 왼쪽 위 grid가 lock의 가장 오른쪽 아래 grid와 겹치는 부분까지를 범위로 한다.
*/

void init_board(vector<vector<int>> lock) {
    int board_size = n + (m-1)*2;
    board = vector<vector<int> >(board_size, vector<int>(board_size, 0));
    for(int i=m-1; i<m+n-1; ++i) {
        for(int j=m-1; j<m+n-1; ++j) {
            board[i][j] = lock[i-m+1][j-m+1];
        }
    }
}

/*
  board에서 lock에 해당하는 부분을 확인한다.
  해당 구간에서 board[i][j] = 0 이면, 아직 열쇠가 자물쇠의 홈을 다 채우지 못한 상태이며,
  board[i][j] = 2 이면, 홈과 홈이 부딛친 경우 이다.
*/
bool is_resolvable() {
    for(int i=m-1; i<m+n-1; ++i) {
        for(int j=m-1; j<m+n-1; ++j) {
            if(board[i][j] != 1) return false;
        }
    }
    return true;
}

bool check(vector<vector<int>> key, int y, int x) {
    bool ret = true;
    
    for(int i=y; i<y+m; ++i) {
        for(int j=x; j<x+m; ++j) {
            board[i][j] += key[i-y][j-x];
        }
    }
    
    ret = is_resolvable();
    
    for(int i=y; i<y+m; ++i) {
        for(int j=x; j<x+m; ++j) {
            board[i][j] -= key[i-y][j-x];
        }
    }
    return ret;
}

bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
    n = lock.size(), m = key.size();
    init_board(lock);
    
    for(int i=0; i<4; ++i) {
        for(int j=0; j<m+n-1; ++j) {
            for(int k=0; k<m+n-1; ++k) {
                if(check(key, j, k)) return true;
            }
        }
        key = lotate_key(key);
    } 
    return false;
}

/*
  처음 시도해서 실패한 코드
  
  이 코드에서는 패턴이 일치하는 지 여부로 판단을 시도했다.
  
  1. lock의 모든 값을 반전시킨다. 
  2. key를 lock과 동일한 크기로 만든 다.(크기가 동일하지 않은 상태에서  패턴 매칭을 하면 홈과 홈이 부딛치는 케이스를 고려하지 못하기 때문에 이렇게 구성했다.)
  3. key를 90도씩 회전시키며 상하좌우로 이동시키며 lock 과 비교하면 답이 나올것이라 생각했다.
     (lock 값이 반전 됬으므로)
  
  >> 반례를 찾으려고 노력했지만 아직 찾지못함.. 
  >> 답이 아닌데 답으로 판단하는 case가 존재할 것 같으나 아직 찾지못함.. 
  
  >> 사실 처음에 슬라이딩 윈도우 방식을 생각했었는데, 이 방식이 좀 더 코드가 간결하게 나올줄 알고 이렇게 구성했는데.. 답을 구하지도 못했고, 코드도 좀 더 복잡해지게 된 것 같음
  >> 항상 문제를 단순화 하려고 노력하자.
  
#include <bits/stdc++.h>
using namespace std;

int N = 0, M = 0;

bool is_valid(int y, int x, int max) {
    return (y>=0 && y<max) && (x>=0 && x<max);
}

vector<vector<int>> lotate_key(vector<vector<int>> key) {
    vector<vector<int> > ret(N, vector<int>(N, 0));
    for(int i=0; i<N; ++i) {
        for(int j=0; j<N; ++j) {
            ret[j][i] = key[N-1-i][j];
        }
    }
    return ret;
}

vector<vector<int>> move_key(vector<vector<int>> key, int y, int x) {
    vector<vector<int> > ret(N, vector<int>(N, 0));
    for(int i=0; i<N; ++i) {
        for(int j=0; j<N; ++j) {
            int ny = i+y, nx = j+x;
            if(is_valid(ny, nx, N)) ret[i+y][j+x] = key[i][j];
        }
    }
    return ret;
}

vector<vector<int> > make_key(vector<vector<int>> key) {
    vector<vector<int> > new_key(N, vector<int>(N, 0));
    for(int i=0; i<N; ++i) {
        for(int j=0; j<N; ++j) {
            if(is_valid(i, j, M)) new_key[i][j] = key[i][j];
        }
    }
    return new_key;
}

bool is_answer(vector<vector<int>> key, vector<vector<int>> lock) {
    for(int i=0; i<N; ++i) {
        for(int j=0; j<N; ++j) {
            if(key[i][j] != lock[i][j]) return false;
        }
    }
    return true;
}

void reverse_lock(vector<vector<int>>& lock) {
    for(int i=0; i<N; ++i) {
        for(int j=0; j<N; ++j) {
            lock[i][j] = abs(lock[i][j]-1);
        }
    }
}

bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
    M = key.size();
    N = lock.size();
    key = make_key(key);
    reverse_lock(lock);
    
    for(int i=0; i<4; ++i) {
        for(int j=0; j<=N; ++j) {
            for(int k=0; k<=N; ++k) {
                vector<vector<int>> positive_key = move_key(key, j, k);
                vector<vector<int>> negative_key = move_key(key, -j, -k);
                if(is_answer(positive_key, lock) || is_answer(negative_key, lock)) return true;
            }
        }
        key = lotate_key(key);
    }
    return false;
}

*/
