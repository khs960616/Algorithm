// 2017 카카오코드 예선
// 전형적인 bfs 문제 유형 
// queue를 사용한 구현
// 해당 문제에서 bfs에서 queue에 들어가지 않는 조건은 3가지이다. 이미 방문한 점이거나, 이전의 컬러와 다른 컬러의 점이거나(다른영역이거나), 주어진 Index 범위를 초과하거나. 

#include <vector>
#include <queue>
#include <iostream>
using namespace std;

bool isVisit[100][100];

int get_area(vector<vector<int>> &picture, int i, int j, int m, int n){    
    int area = 1;
    int dir[4][2] = {{0,-1}, {0,1}, {-1, 0}, {1,0}};
    int current_color = picture[i][j];
    queue<pair<int, int>> q;
    q.push(make_pair(i, j));
    
    while(!q.empty()){
        pair<int, int> p = q.front();
        int x = p.first;
        int y = p.second;
        q.pop();
        
        for(int k=0; k<4; k++){
            int nx = x + dir[k][0];
            int ny = y + dir[k][1];
            if(nx < 0 || nx >= m || ny < 0 || ny >=n) continue;
            if(isVisit[nx][ny]) continue;
            if(current_color != picture[nx][ny]) continue;
            
            q.push(make_pair(nx,ny));
            area ++;
            isVisit[nx][ny] = true;
        }
    }
    
    return area;
}

vector<int> solution(int m, int n, vector<vector<int>> picture) {
    int number_of_area = 0;
    int max_size_of_one_area = 0;
    for(int i = 0; i  < 100; i++){
        for(int j =0; j< 100; j++){
            isVisit[i][j] = false;
        }
    }
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            if(!isVisit[i][j] && picture[i][j]){
                number_of_area++;
                isVisit[i][j] = true;
                int area = get_area(picture, i, j, m, n);
                if(max_size_of_one_area < area) max_size_of_one_area = area;
            }
        }
    }
    
    vector<int> answer(2);
    answer[0] = number_of_area;
    answer[1] = max_size_of_one_area;
    return answer;
}
