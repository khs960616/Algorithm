#include<bits/stdc++.h>

using namespace std;

/*
사탕 가방 (이진 탐색)
----------------
(1 ≤ N ≤ 100, 1 ≤ M ≤ 10^18)

모든 사탕 가방은 이루는 사탕의 개수와 종류가 같아야 한다. 
초기 가방의 개수의 최소값은 1, 최대값은 개수가 가장 많은 사탕과 같다.

사탕 가방의 개수를 이분 탐색으로 줄여나간다.
이때 사탕 가방의 개수로 각 사탕을 나눈 몫을 모두 더하면 사탕 가방에 든 사탕의 개수가 나온다.
이 값이 주어진 input M과 동일한 시점이 될때까지 (구간의 범위가 1이 될때까지) 반복하면 해당 값이 답이 된다.

*/
int main(int argc, char** argv) {
	int test_case;
	int T;
	cin>>T;
	for(test_case = 1; test_case <= T; ++test_case) {
		int n;
        long long m;
        cin >> n >> m;  // n = 사탕의 종류, m = 한 가방안에 들어가야하는 사탕의 개수
        
        vector<long long> v(n); // 사탕배열 
        for(int i=0; i<n; ++i) cin >> v[i];
        sort(v.begin(), v.end());
        
        long long mn = 1;
        long long mx = v[v.size()-1];
        
        while(mn <= mx) {
        	long long mid = (mn + mx) / 2;
            long long cnt = 0;
            for(long long candy: v) cnt += (candy / mid);
            if(cnt < m) mx = mid-1;
            else mn = mid+1;
        }
        
        cout << '#' << test_case << ' ' << mx << '\n';
	}
	return 0;
}
