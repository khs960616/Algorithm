#include <bits/stdc++.h>
using namespace std;

/*
  https://www.acmicpc.net/problem/7453
  합이 0인 네 정수
  ---
  투포인터, Meet in the middle 
*/
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n = 0;
    cin >> n;
    vector<vector<int>> input(n, vector<int>(4, 0));
    vector<int> abSum, cdSum;

    for(int i=0; i<n; ++i) {
        cin >> input[i][0] >> input[i][1] >> input[i][2] >> input[i][3];
    }

    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            abSum.push_back(input[i][0]+input[j][1]);
            cdSum.push_back(input[i][2]+input[j][3]);
        }
    }
    sort(abSum.begin(), abSum.end());
    sort(cdSum.begin(), cdSum.end());

    long long answer = 0;
    int left = 0, right = n*n -1;

    while (left< n*n && right >=0) {
        long long sum = abSum[left] + cdSum[right];
        int cnt = 0;
        if(sum > 0) {
            --right;
            continue;
        }

        if(sum < 0) {
            ++left;
            continue;
        }

        int currentL = left; 
        while (1) {
            if(left == n*n) break;
            if(abSum[currentL] != abSum[++left]) break;
        }

        int currentR = right; 
        while (1) {
            if(right == -1) break;
            if(cdSum[currentR] != cdSum[--right]) break;
        }
        
        answer += ((long long)(left - currentL) * (currentR - right)); 
    }
    
    cout << answer;
    return 0;
}
