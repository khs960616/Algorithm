/*
https://programmers.co.kr/learn/courses/30/lessons/81302#fn1
2021 카카오 채용연계형 인턴십
BFS
*/

#include <bits/stdc++.h>

using namespace std;

int getManhattan(int r1, int c1, int r2, int c2) {
    return abs(r1-r2) + abs(c1-c2);
}

bool isValid(int x, int y) {
    return (x>=0 && x<5) && (y>=0 && y<5);
}

const vector<pair<int, int>> calc = {{1,0}, {-1, 0}, {0, 1}, {0, -1}};

vector<int> solution(vector<vector<string>> places) {
    vector<int> answer;

    for(int i=0; i<5; ++i) {
        //각 place별로 응시생의 위치를 기록해둠
        int result = 1;
        vector<pair<int, int>> personList;
        for(int j=0; j<5; ++j) {
            for(int k=0; k<5; ++k) {
                if(places[i][j][k] == 'P') {
                    personList.push_back(make_pair(j, k));
                }
            }
        }
        
        //각 place별 응시생의 위치를 기준으로 BFS를 실행함
        for(pair<int, int> person: personList) {
            vector<vector<bool>> isVisit(5, vector<bool>(5, false));
            queue<pair<int, int>> q;
            q.push(person);
            isVisit[person.first][person.second] = true;
 
            while(!q.empty()) {
                pair<int, int> p = q.front();
                q.pop();
                int distance = getManhattan(p.first, p.second, person.first, person.second);
  
                //BFS이므로 Distance가 3이상이 되는 시점까지 해당 반복문을 탈출하지 못했다면, 해당 응시생은 거리두기가 잘 지켜진 응시생임.
                if(distance > 2) break;
                else {
                    if(distance != 0 && places[i][p.first][p.second] == 'P') {
                        result = 0;
                        break;
                    }
                    
                    for(pair<int, int> c: calc) {
                        int x = p.first-c.first;
                        int y = p.second-c.second;
                        if(isValid(x, y) && !isVisit[x][y]) {
                            isVisit[x][y] = true;
                            /*
                              X인 경우 BFS에 넣지 않음 (만약 두 응시생이 파티션에 의해 막혀있는 경우 
                              ex) PXP,   P     PX    XP
                                         X     XP    PX     예로 다음 4가지 케이스의 경우 BFS를 통해 두 응시생이 서로 도달할 수 없는 상태이므로. 
                                         P
                             */
                            if(places[i][x][y] != 'X') {
                                q.push(make_pair(x, y));
                            }
                        }
                    }
                }
            }
            if(result==0) break;
        }
        answer.push_back(result);
    }
    return answer;
}
