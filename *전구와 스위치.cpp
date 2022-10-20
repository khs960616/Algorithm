#include <bits/stdc++.h>
using namespace std;

/*
  https://www.acmicpc.net/problem/2138
  전구와 스위치
  그리디
  ---
  참고 : https://staticvoidlife.tistory.com/143
  
  브루트포스 방식말고는 생각하지 못했는데, 다음과 같이 케이스를 쪼개니 그리디 알고리즘으로 해결이 가능한 문제임. 
  첫 번째 전구의 상태를 고정하고나면, 다음 전구의 스위치를 눌러야되는지 말아야되는지 여부도 고정이 된다는 것이 주된 아이디어.
  
  차후 그리디 알고리즘을 풀 때, 만일 특정 조건(상태)를 고정하는 경우 문제가 단순화 될 수 있는지를 추가적으로 고민해볼 필요가 있음.
  (그리디 알고리즘뿐 아니라 다른 문제 풀때도, 시뮬레이션 문제가 아니라면, 무조건 case 다 쪼개서만 풀려하지말고 최대한 여러방식을 활용해 문제를 단순화시킬 수 있는지 계속 고민해보자.)
*/
int n = 0;

void click_button(string& s, int i) {
    if(i-1 >=0)s[i-1] = s[i-1] == '0' ? '1' : '0';
    s[i] = s[i] == '0' ? '1' : '0';
    if(i+1 < n) s[i+1] = s[i+1] == '0' ? '1' : '0';
}

int get_button_cnt(string current_state, string target, int type) {
    int cnt = 0;
    if(type == 1) {
        click_button(current_state, 0);
        cnt = 1;
    }

    for(int i=1; i<n; ++i) {
        if(current_state[i-1] == target[i-1]) continue;
        cnt++;
        click_button(current_state, i);
    }

    if(current_state != target) cnt = INT_MAX;
    return cnt;
}

int main() {
    cin >> n;
    string current_state, target;
    cin >> current_state >> target;

    int answer = get_button_cnt(current_state, target, 0);
    answer = min(answer, get_button_cnt(current_state, target, 1));
    answer = (answer != INT_MAX) ? answer : -1;
    cout << answer;
    return 0;
}
