#include <bits/stdc++.h>
using namespace std;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/87946
  피로도
  ---------------
  재귀, 완전 탐색
  - 해당 던전을 도는 순서에 따라 피로도의 영향으로 인해 돌 수 있는 던전의 수가 바뀌게 된다. 따라서 모든 경우를 탐색해봐야함.
  최대 8!만큼 요구한다.  (8개의 던전을 순서대로 줄 세우는(체크하는) 경우와 동일하다. 
*/
int dungeonCnt;

void checkedDungeon(int& answer, 
                    int remainK,
                    int clearCnt,
                    vector<vector<int>>& dungeons,
                    vector<bool> isCheck) {
    if(find(isCheck.begin(), isCheck.end(), false) == isCheck.end()) {
        answer = max(answer, clearCnt);
        return;
    }
    
    for(int i=0; i<dungeonCnt; ++i) {
        int nextRemain = remainK;
        int nextClearCnt = clearCnt;
        
        if(isCheck[i]) continue;
        isCheck[i] = true;
        if(remainK >= dungeons[i][0]) {
            nextRemain -= dungeons[i][1];
            nextClearCnt += 1;
        }
        checkedDungeon(answer, nextRemain, nextClearCnt, dungeons, isCheck);
        isCheck[i] = false;
    }
}

int solution(int k, vector<vector<int>> dungeons) {
    int answer = -1;
    dungeonCnt = dungeons.size();
    vector<bool> isCheck(dungeonCnt, false);
    
    checkedDungeon(answer, k, 0, dungeons, isCheck);
    return answer;
}
