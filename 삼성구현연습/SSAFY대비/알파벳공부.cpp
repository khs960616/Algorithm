#include<iostream>

using namespace std;
int main(int argc, char** argv)
{
	int test_case;
	int T;
	cin>>T;
    
    string SEQ = "abcdefghijklmnopqrstuvwxyz";
	for(test_case = 1; test_case <= T; ++test_case)
	{
        string s;
        cin >> s;
        int len = s.length();
        int i =0;
        for(; i<len; ++i) if(s[i] != SEQ[i]) break;
        cout << "#" << test_case << ' ' << i << '\n';
	}
	return 0;
}
