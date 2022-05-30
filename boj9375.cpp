#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/9375
패션왕 신해빈
수학 
------------
*/
int main() {
    int t;
    cin >> t; 

    while(t--) {
        int n, result = 1;
        cin >> n;
        map<string, int> m;
        for(int i=0; i<n; ++i) {
            string name, type;
            cin >> name >> type;
            ++m[type];  //각 종류별 갯수 
        }
        
        for(auto a: m) result *= (a.second+1);  // (해당 옷 종류들을 선택했을 때 증가하는 경우의 수 + 1 (선택하지 않는 경우의 수) 
        cout  << result-1 << '\n';
    }
    return 0;   
}
