/*
https://www.acmicpc.net/problem/15651
N과 M (3)
백트래킹
같은 depth만큼 진행된 경우 어쩌피 수열이 중복되서 출력될 수 없다. (함수 스택 쌓이는 거 그려보면 어쩌피 중복될수가없음..)

*/


#include <bits/stdc++.h>
using namespace std;
//DEBUG F5
/*
1~n 까지의 수 중 중복없이 M개를 뽑는다.
같은 수를 여러번 골라도 된다.

*/
int n, m;
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
        answer[cnt] = i;
        solution(cnt+1);
    }
}

int main() {
    cin >> n >> m;
    solution(0);
}
