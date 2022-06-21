#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/11660
구간합 구하기 5
--
DP
*/
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> partialSum(n+1, vector<int>(n+1, 0)); // partialSum[i][j] -> (1, 1) ~ (i,j) 까지의 부분합
    for(int i=1; i<=n; ++i) {
        for(int j=1; j<=n; ++j) {
            int num;
            cin >> num;
            partialSum[i][j] = (partialSum[i-1][j] + partialSum[i][j-1] - partialSum[i-1][j-1] + num);
            // (1) 자기자신보다 높이가 1작은 사각형의 부분합  + (2) 자기보다 너비가 1칸 적은 사각형의 부분합  + (1)과 (2)의 교집합의 너비 + 현재 값
        }
    }

    for(int i=0; i<m; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        cout << (partialSum[x2][y2]-partialSum[x1-1][y2]-partialSum[x2][y1-1]+partialSum[x1-1][y1-1]) << '\n';
    }
    return 0;   
}
