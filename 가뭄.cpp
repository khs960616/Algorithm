#include <bits/stdc++.h>
using namespace std;

double answer[3];

/*
  https://www.acmicpc.net/problem/19572
  가뭄
  ---
  문제는 쉬우나,
  cout << fixed;
  cout.precision(1);   다음 두 내장함수로 특정 유효숫자 아래의 숫자로 반올림 하는 것, 
  
  answer[0] = (v[0] - v[1] + v[2]) / 2;를 구할 때 나누는 수가 2이므로, 
  2^-1을 곱하는 것과 같으므로 유효숫자 관련된 처리를 별도로 하지 않아도 되는 것 등 부동소수점에 대해 생각해봄
*/
int main() {
    vector<double> v(3, 0);
    for(int i=0; i<3; ++i) cin >> v[i];

    answer[0] = (v[0] - v[1] + v[2]) / 2; // b
    answer[2] = v[2] - answer[0]; // c
    answer[1] = v[1] - answer[2]; // a 

    if(answer[0] <= 0 || answer[1] <= 0 || answer[2] <= 0) cout << -1;
    else {
        cout << 1 << '\n';
        cout << fixed;
        cout.precision(1);
        cout << answer[1] << ' ' << answer[0] << ' ' << answer[2];
    }
    return 0;
}
