/*
https://www.acmicpc.net/problem/15650
N과 M
백트래킹, 순열 

dfs 를 이용한 순열 구현, 함수 호출 조건에 
*/

#include <bits/stdc++.h>
using namespace std;
//DEBUG F5
/*
1~n 까지의 수 중 중복없이 M개를 뽑는다.
고른 수열은 오름차순으로 증가하는 수열이여야 한다. -> 이전 n과 m 문제와 구현은 똑같지만, 
백트래킹 함수 호철 조건 해당 오름차순 조건을 추가
*/
int n, m;
bool isVisit[10];
int answer[10];

void solution(int cnt) {
    if(cnt == m) {
        for(int i=0; i<cnt; ++i) {
            cout << answer[i] << ' ';
        }
        cout << '\n';
        return;
    }

    for(int i=1; i<=n; ++i) {
        if(!isVisit[i]) {
            if(cnt!=0 && answer[cnt-1]>=i) continue;
            isVisit[i] = true;
            answer[cnt] = i;
            solution(cnt+1);
            isVisit[i] = false;
        }
    }
}

int main() {
    cin >> n >> m;
    solution(0);
}
