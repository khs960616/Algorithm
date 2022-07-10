#include <bits/stdc++.h>
using namespace std;

/*
  https://www.acmicpc.net/problem/15663
  N과 M(9)
  -------
  조합, 재귀, 콜 스택 
  
  맨 처음에는 map을 이용해 이전에 만들어진 string의 경우에 출력을 하지 않는 방식으로 구성함
  
  그러나 좀 더 효율적으로 현재 answer[i]에 이전에 선택했던 숫자가 중복되어 선택되는 것을 막기 위해 prevNum에 각 숫자를 저장해두면, 중복된 결과 출력을 막을 수 있다.
  
*/

int n, m;
vector<int> v;
vector<int> answer;
vector<bool> isVisit;

void solution(int cnt) {
    if(cnt == m) {
        for(int i: answer) cout << i << ' ';
        cout << '\n';
        return;
    }

    int prevNum = -1;

    for(int i=0; i<n; ++i) {
        if(isVisit[i]) continue;
        if(prevNum == v[i]) continue;
        isVisit[i] = true;
        answer[cnt] = prevNum = v[i];
        solution(cnt+1);
        isVisit[i] = false;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m;
    v = vector<int>(n, 0);
    isVisit = vector<bool>(n, false);
    answer = vector<int>(m, -1);
    for(int i=0; i<n; ++i) cin >> v[i];
    sort(v.begin(), v.end());

    solution(0);
    return 0;
}


/*
#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<int> v;
vector<int> answer;
vector<bool> isVisit;
map<string, bool> mp;

void solution(int cnt) {
    if(cnt == m) {
        string s = "";
        for(int i: answer) {
            s+=to_string(i);
            s+= ' ';
        }

        if(mp.find(s) == mp.end()) {
            cout << s << '\n';
            mp[s] = true;
        }
        return;
    }

    for(int i=0; i<n; ++i) {
        if(isVisit[i]) continue;
        isVisit[i] = true;
        answer[cnt] = v[i];
        solution(cnt+1);
        isVisit[i] = false;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m;
    v = vector<int>(n, 0);
    isVisit = vector<bool>(n, false);
    answer = vector<int>(m, -1);
    for(int i=0; i<n; ++i) cin >> v[i];
    sort(v.begin(), v.end());

    solution(0);
    return 0;
}

*/
