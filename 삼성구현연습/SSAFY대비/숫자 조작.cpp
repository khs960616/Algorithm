#include<bits/stdc++.h>
using namespace std;

int min_val, max_val;
int arr[2];

string get_swap_string(string s, int i, int j) {
	char tmp = s[i];
    s[i] = s[j];
    s[j] = tmp;
    return s;
}

int main(int argc, char** argv) {
	int test_case;
	int T;
	cin>>T;
	for(test_case = 1; test_case <= T; ++test_case) {
		string s;
        cin >> s;
        int len = s.length();
        min_val = max_val = stoi(s);
        
        for(int i=0; i < len; ++i) {
        	for(int j=i+1; j<len; ++j) {
            	string cv_s = get_swap_string(s, i, j);
                if(cv_s[0] != '0') {
                	min_val = min(min_val, stoi(cv_s));
                    max_val = max(max_val, stoi(cv_s));
                }
            }
        }
        
        cout << '#' << test_case << ' ' << min_val << ' ' << max_val << '\n';
	}
	return 0;
}
