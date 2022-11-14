#include<iostream>
using namespace std;
int main(int argc, char** argv) {
	int test_case;
	int T;
	cin>>T;
	for(test_case = 1; test_case <= T; ++test_case) {
		int n, d;
        cin >> n >> d;
        
        int range = 2*d + 1;
        int answer = n/range;
        if(n % range != 0) answer+=1;
        cout << "#" << test_case << ' ' << answer << '\n';
	}
	return 0;
}
