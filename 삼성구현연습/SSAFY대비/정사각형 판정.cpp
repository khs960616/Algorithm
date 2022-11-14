#include<bits/stdc++.h>
using namespace std;

char board[21][21];

string chk_area(int min_y, int min_x, int max_y, int max_x) {
    for(int i=min_y; i<=max_y; ++i) {
        for(int j=min_x; j<=max_x; ++j) {
            if(board[i][j] != '#') return "no";
        }
    }
    return "yes";
}

int main(int argc, char** argv) {
	int test_case;
	int T;
	cin>>T;
	
	for(test_case = 1; test_case <= T; ++test_case) {
        int min_y = INT_MAX, min_x = INT_MAX;
        int max_y = -1, max_x = -1;
        int n;
        cin >> n;
        for(int i=0; i<n; ++i) {
        	for(int j=0; j<n; ++j) {
            	cin >> board[i][j];
                if(board[i][j] == '#') {
                	min_y = min(min_y, i), min_x = min(min_x, j);
                    max_y = max(max_y, i), max_x = max(max_x, j);
                }
            }
        }
		
        bool same_len = ((max_x - min_x + 1) == (max_y - min_y +1)) ;
        string answer = same_len ? "yes" : "no";
        if(same_len) answer = chk_area(min_y, min_x, max_y, max_x);
        cout << '#' << test_case  << ' ' << answer << '\n';
	}
	return 0;
}
