#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/11659
구간 합 구하기 4
DP
*/
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<int> v(n, 0);
    vector<int> ret(n, 0);  // ret[i] :  0~i번째 인덱스까지의 구간 합 

    for(int i=0; i<n; ++i) {
        cin >> v[i];
        if(i == 0) ret[i] = v[0];
        else ret[i] = ret[i-1] + v[i]; 
    }

    while(m--) {
        int i, j;
        cin >> i >> j;

        int result = ret[j-1];
        if(i-2>=0) result -= ret[i-2];  
        cout << result << '\n';
    }
    return 0;   
}
