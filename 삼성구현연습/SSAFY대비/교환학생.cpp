#include<bits/stdc++.h>
using namespace std;

int n;
int arr[7];

int get_value(int n, int idx) {
    int ret = 0;
	while(n > 0) {
        ++ret;
    	if(arr[idx++ % 7] == 1) --n;
    }
    return ret;
}

int main(int argc, char** argv) {
	int test_case;
	int T;
	cin>>T;
    
	for(test_case = 1; test_case <= T; ++test_case) {
    int n = 0;
    cin >> n;
		for(int i=0; i<7; ++i) cin >> arr[i];
        int answer = get_value(n, 0);
        for(int i=1; i<7; ++i) answer = min(answer, get_value(n, i));
        cout << "#" << test_case << ' ' << answer << '\n';
	}
	return 0;
} 
