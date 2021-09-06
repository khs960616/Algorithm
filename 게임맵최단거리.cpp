//프로그래머스 - 게임 맵 최단거리
//간단한 BFS을 이용한 최단경로 문제

#include<vector>
#include<queue>

using namespace std;

pair<int, int> dir[4] = {make_pair(1,0), make_pair(-1,0), make_pair(0, 1), make_pair(0, -1)};

bool isValid(int n, int m, int x, int y){
    return ((x>=0 && x<n)&& (y>=0 && y<m));
}

class min_dist{
private: 
    pair<int, int> coordinate;
    int distance;
    
public:
    min_dist(int x, int y, int d){
        this->coordinate = make_pair(x, y);
        this->distance = d;
    }
    
    pair<int, int> getCoordinate(){
        return this->coordinate;
    }
    
    int getDistance(){
        return this->distance;
    }
};

int solution(vector<vector<int> > maps)
{
    int n = maps.size();
    int m = maps[0].size();
    int answer = -1;
    vector<vector<int>> isVisit(n, vector<int>(m, 0));
    queue<min_dist> bfs;
    bfs.push(min_dist(0,0,1));
    isVisit[0][0] = true;
    
    while(!bfs.empty()){
        min_dist mt = bfs.front();
        bfs.pop();
        pair<int, int> pre_c = mt.getCoordinate();
        int prev_dist = mt.getDistance();
        if(pre_c.first == n-1 && pre_c.second == m-1){
            return prev_dist;
        }
        
        for(pair<int, int> p : dir){
            int cur_x = pre_c.first + p.first;
            int cur_y = pre_c.second + p.second;
            if(isValid(n, m, cur_x, cur_y) && maps[cur_x][cur_y] && !isVisit[cur_x][cur_y]){
                isVisit[cur_x][cur_y]=true;
                bfs.push(min_dist(cur_x, cur_y, prev_dist+1));
            }
        }
    }
    return answer;
}
