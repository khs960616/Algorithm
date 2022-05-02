/*
https://www.acmicpc.net/problem/15649
DFS를 이용한 순열 구현

BOJ 문제 풀시 cin, cout 사용하는 경우 endl 사용하지 말 것. 
ios_base::sync_with_stdio(false); cin.tie(null); 추가해서 사용하자 ... 이거 때문에 시간만 버리네 
*/

#include <bits/stdc++.h>
using namespace std;

void printCombination(vector<bool>& isVisit, vector<int>& answer, const int n, const int m, const int cnt) {
    if(cnt==m) {
        for(int i=0; i<m; ++i) {
            cout << answer[i] << ' ';
        }
        cout << '\n';
        return;
    }

    for(int i=1; i<=n; ++i) {
        if(!isVisit[i]) {
            isVisit[i] = true;
            answer[cnt] = i;
            printCombination(isVisit, answer, n, m, cnt+1);
            isVisit[i] = false;
        }
    } 
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> answer(m, 0);
    vector<bool> isVisit(n+1, false);
    printCombination(isVisit, answer, n, m, 0);
    return 0;
}
