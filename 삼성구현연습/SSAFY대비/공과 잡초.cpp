#include<iostream>
using namespace std;
int main(int argc, char** argv)
{
	int test_case;
	int T;
	cin>>T;
	for(test_case = 1; test_case <= T; ++test_case)
	{
		string s;
        cin >> s;
        
        int len = s.length(), cnt = 0;
        bool flag = false;
		for(int i=0; i<len-1; ++i) {
            bool is_ball = (s[i] == '(' && s[i+1] == '|') || (s[i] == '|' && s[i+1] == ')') || (s[i] =='(' && s[i+1] == ')');
        	if(is_ball) ++cnt;
        }
        cout << "#" << test_case << ' ' << cnt << '\n';
	}
	return 0;
}
