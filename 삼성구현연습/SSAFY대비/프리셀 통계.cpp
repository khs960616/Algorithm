#include<iostream>
using namespace std;

bool is_valid_today(long long n, long long pd) {
	if(n >= 100) return true;
    for(long long i=1; i<=n; ++i) {
    	long long cur_val = i*pd;
        if(cur_val % 100 == 0) return true;
    }
    return false;
}

bool is_total_valid(long long pd, long long pg) {
	if(pd > 0 && pg == 0) return false;
    if(pg == 100 && pd != 100) return false;
    return true;
}

int main(int argc, char** argv) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
	int test_case;
	int T;
	cin>>T;

	for(test_case = 1; test_case <= T; ++test_case) {
		long long n, pd, pg;
        cin >> n >> pd >> pg;
        
        bool today_flag = is_valid_today(n, pd);
        bool total_flag = is_total_valid(pd, pg);
        string answer = (today_flag && total_flag) ? "Possible" : "Broken";
        cout << "#" << test_case << ' ' << answer << '\n';
	}
	return 0;
}
