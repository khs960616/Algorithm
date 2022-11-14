#include<bits/stdc++.h>
using namespace std;

int N, M;
int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
char board[51][51];
bool is_visit[51][51];

bool is_valid(int y, int x) {
	return  (y>=0 && y<N) && (x>=0 && x<M);
}

char get_opposite_color(char c) {
	return (c == '.') ? '#' : '.';
}

string bfs(int y, int x) {
	queue<tuple<int, int, char> > q;
    q.emplace(y, x, board[y][x]);
    while(!q.empty()) {
        auto [cy, cx, c_type] = q.front();
        q.pop();
        for(int i=0; i<4; ++i) {
            int ny = cy + dirs[i][0];
            int nx = cx + dirs[i][1];
            
            if(!is_valid(ny, nx) || is_visit[ny][nx]) continue;
            if(board[ny][nx] == c_type) return "impossible";
            is_visit[ny][nx] = true;
            board[ny][nx] = get_opposite_color(c_type);
            q.emplace(ny, nx, board[ny][nx]);
        }
	}
    return "possible";
}

int main(int argc, char** argv) {
	int test_case;
	int T;
	cin>>T;
    
	for(test_case = 1; test_case <= T; ++test_case) {
        int y = -1, x = -1;
        memset(is_visit, false, sizeof(is_visit));
        cin >> N >> M;    
        for(int i=0; i<N; ++i) {
        	for(int j=0; j<M; ++j) {
            	cin >> board[i][j];
                if(board[i][j] != '?') y = i, x = j;
            }
        }
        
        string answer = "possible";
        if(y!=-1 && x!= -1) answer = bfs(y, x);
        cout << "#" << test_case << " " << answer << "\n";
	}
	return 0;
}
