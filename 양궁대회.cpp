#include <bits/stdc++.h>
using namespace std;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/92342
  양궁대회
  -----
  DFS 활용 완전 탐색
*/
int maxDiff;

void getTopPriorityVector(vector<int> currentLion, vector<int>& answer) {
  // 라이언과 어피치의 점수차이가 동일한 경우, 더 적은 점수를 많이 맞춘 것이 우선순위가 더 높다.
    for(int i=10; i>=0; --i) {
        if(currentLion[i] > answer[i]) break;
        if(currentLion[i] < answer[i]) return;
    }
    
    answer = currentLion;
}

void compareLionApeach(vector<int> lion, vector<int> apeach, vector<int>& answer) {
    int lionScore = 0, apeachScore = 0;
    
    for(int i=0; i<11; ++i) {
        if(lion[i] > apeach[i]) {
            lionScore += (10-i);
        } else if(apeach[i]){
            apeachScore += (10-i);
        }
    }
    
    if(lionScore <= apeachScore) return;
    
    int currentDiff = lionScore - apeachScore;
    if(currentDiff < maxDiff) return;
    
    if(currentDiff > maxDiff) {
        maxDiff = currentDiff;
        answer = lion;
        return;
    }
    
    getTopPriorityVector(lion, answer);
}

void dfs(int scoreIdx, 
         int remainArrow, 
         vector<int> lion, vector<int> apeach,
         vector<int>& answer) {
    
    if(scoreIdx == 11 || remainArrow == 0) {  //만일 마지막 index까지 다 확인했거나 더 이상 쏠 수 있는 화살이 남지 않은 경우
        lion[10] += remainArrow;
        compareLionApeach(lion, apeach, answer);
        return;
    }
    
    int diff = remainArrow - apeach[scoreIdx] - 1;
    if(diff>=0) {
        lion[scoreIdx] += (apeach[scoreIdx] + 1);
        dfs(scoreIdx+1, diff, lion, apeach, answer);  //라이언이 현재 Score를 얻는 경우
        lion[scoreIdx] -= (apeach[scoreIdx] + 1);
    }
    
    dfs(scoreIdx+1, remainArrow, lion, apeach, answer); // 어피치가 현재 Score를 얻는 경우
}

vector<int> solution(int n, vector<int> info) {
    maxDiff = 0;
    vector<int> answer;
    
    dfs(0, n, vector<int>(11, 0), info, answer);
    if(answer.empty()) answer.push_back(-1);
    return answer;
}
