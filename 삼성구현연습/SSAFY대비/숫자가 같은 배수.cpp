#include<bits/stdc++.h>
using namespace std;
/*
  숫자가 10^6 미만 이므로 최대 숫자의 길이는 6자리이다. 
  따라서 6! 정도이므로 단순 순열 사용해도 시간 복잡도 만족
*/
int main(int argc, char** argv)  {
	int test_case;
	int T;
	cin>>T;
	for(test_case = 1; test_case <= T; ++test_case)
	{
		int n;
        cin >> n;
        string s = to_string(n);
        sort(s.begin(), s.end());
        string answer ="impossible";
        do {
            if(s[0] != 0) {
            	int val = stoi(s);
                if(val > n && (val % n == 0)) {
                    answer = "possible";
                	break;
                }
            }
        } while(next_permutation(s.begin(), s.end()));
        
        cout << "#" << test_case << " " << answer << '\n';
	}
	return 0;
}
/*
next_permutation 안쓰고 구현

#include<bits/stdc++.h>
using namespace std;

int n = 0, len = 0;
string answer = "";
bool is_used[8];

void dfs(string current, string s, int cnt) {
	if(cnt == len) {
        if(current[0] != '0') {
        	int value = stoi(current);
            if(value > n && (value % n == 0)) answer = "possible";
        }
    	return;
    }
    
    for(int i=0; i<len; ++i) {
    	if(is_used[i]) continue;
        is_used[i] = true;
        dfs(current+s[i], s, cnt+1);
        is_used[i] = false;
    }
}

int main(int argc, char** argv)  {
	int test_case;
	int T;
	cin>>T;
    
	for(test_case = 1; test_case <= T; ++test_case) {
        cin >> n;
        string s = to_string(n);
        
        len = s.length();
        memset(is_used, 0, sizeof(is_used));
        answer ="impossible";
        dfs("", s, 0);
        cout << "#" << test_case << " " << answer << '\n';
	}
	return 0;
}

*/
