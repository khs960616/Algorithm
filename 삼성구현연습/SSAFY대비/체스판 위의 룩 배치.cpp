#include<iostream>
#include<cstring>
using namespace std;
int main(int argc, char** argv) {
	int test_case;
	int T;
	cin>>T;
    char board[8][8];
    bool row_chk[8];
    bool col_chk[8];

	for(test_case = 1; test_case <= T; ++test_case) {
        memset(col_chk, false, sizeof(col_chk));
    	memset(row_chk, false, sizeof(row_chk));
    	
        int cnt = 0;
        bool flag = true;
		for(int i=0; i<8; ++i) {
        	for(int j=0; j<8; ++j) {
            	cin >> board[i][j];
                if(board[i][j] == 'O') {
                    cnt++;
                    if(row_chk[i] || col_chk[j]) flag = false;
                	row_chk[i] = col_chk[j] = true;
                }
            }
        }
        string answer = flag && (cnt == 8) ? "yes" : "no";
        cout << "#" << test_case << ' ' << answer << '\n';
	}
	return 0;
}
