#include<iostream>
using namespace std;

// unordered_map, 또는 해쉬 쓰면 좀 더 빠름.
string days[8] = { "", "SAT", "FRI", "THU", "WED", "TUE", "MON", "SUN"};

int get_next_sun(string s) {
	for(int i=1; i<8; ++i) {
    	if(days[i] == s) return i;
    }
    return 0;
}

int main(int argc, char** argv) {
	int test_case;
	int T;
	cin>>T;
	for(test_case = 1; test_case <= T; ++test_case) {
		string s;
        cin >> s;
        cout << "#" << test_case << ' ' << get_next_sun(s) << '\n';
	}
	return 0;
}
