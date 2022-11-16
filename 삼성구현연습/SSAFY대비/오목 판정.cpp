#include<bits/stdc++.h>
using namespace std;

int n;
vector<pair<int, int> > dirs = {{-1, -1}, {1, 1}, {1, 0},  {-1, 0}, {-1, 1}, {1, -1},  {0, -1}, {0, 1}};

bool is_valid(int y, int x) {
	return (y>=0 && y<n) && (x>=0 && x<n); 
}

void cnt_dirs(int i, int cy, int cx, int& cnt, vector<vector<char>>& boards) {
    while(1) {
        cy += dirs[i].first;
        cx += dirs[i].second;
        if(!is_valid(cy, cx) || boards[cy][cx] == '.') break;
        cnt++;
    }
}

bool chk(vector<vector<char> >& boards, int y, int x) {
    int cnt;
	for(int i=0; i<8; i+=2) {
        cnt = 0;
        cnt_dirs(i, y, x, cnt, boards);
        cnt_dirs(i+1, y, x, cnt, boards);
        cnt += 1;
        if(cnt >=5) return true;
    }
    return false;
}

int main(int argc, char** argv) {
	int test_case;
	int T;
	cin>>T;

	for(test_case = 1; test_case <= T; ++test_case) {
        cin >> n;
        vector<vector<char> > boards(n, vector<char>(n));
        for(int i=0; i<n; ++i) {
        	for(int j=0; j<n; ++j) {
            	cin >> boards[i][j];
            }
        }
        
        string answer = "NO";
        for(int i=0; i<n; ++i) {
        	for(int j=0; j<n; ++j) {
            	if(boards[i][j] == '.') continue;
                if(chk(boards, i, j)) answer = "YES";
            }
        }
        cout << '#' << test_case << ' ' << answer << '\n';
	}
	return 0;
}
