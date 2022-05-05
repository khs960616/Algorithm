/*
https://www.acmicpc.net/problem/15652
백트래킹 연습 
*/

#include <bits/stdc++.h>
using namespace std;
//DEBUG F5
/*
1~n 까지의 수 중 중복없이 M개를 뽑는다.
같은 수를 여러번 골라도 된다.
고른 수열은 비내림차순이어야한다. 

A1 <= A2 <= A3 ... <= Am 을 만족하면 비내림차순
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
        if(cnt!=0 && answer[cnt-1]>i) continue;
        answer[cnt] = i;
        solution(cnt+1);
    }
}

int main() {
    cin >> n >> m;
    solution(0);
}
