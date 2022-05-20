#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/42860#
조이스틱
브루트포스 
------------
1. 알파벳을 바꾸는 코스트를 먼저 계산한다.
2. 왼쪽으로만 이동하는 경우, 오른쪽으로만 이동하는 경우의 움직이는 cost를 계산한다.
3. 중간에 방향이 바뀌어야 하는 cost를 계산하며, 2번을 포함해서 움직이는 cost가 가장 작은 경우를 선택한다. 
*/

vector<int> v;
int nSize;

int calcChangeCost(char c) {
    int up = c - 'A';
    int down = 'Z' - c + 1;
    return min(up, down);
}

/*
  중간에 방향이 바뀌어야 하는 cost를 계산하는 경우 반드시 인접한 두개의 idx만을 포함해야한다.
  만일 그렇지 않은 경우는 A가 아닌 모든 알파뱃을 순회하지 않는다.
*/

int calcMoveCost() {
    int vSize = v.size();
    if(0 == v.size()) return 0;
    //1. 왼쪽으로 쭉가는 경우, 오른쪽으로 쭉 가능 경우
    int ret = min(v[vSize-1], nSize-v[0]);  //nSize -> 마지막 index 보다 1큰값이므로 따로+1을 안해도됨/
    
    for(int i=0; i<vSize-1; ++i) {
        //오른쪽으로 갔다가 왼쪽으로 한번 꺾는 경우의 case
        int rightFirst = v[i]*2 + nSize-v[i+1];
        //왼쪽우로 갔다가 오른쪽으로 한번 꺾는 case
        int leftFirst = (nSize-v[i+1])*2 + v[i];
        
        ret = min(ret, min(rightFirst, leftFirst));
    }
    return ret;
}

int solution(string name) {
    int answer = 0;
    nSize = name.size();
        
    for(int i=0; i<nSize; ++i) {
        if(name[i] == 'A') continue;
        answer+=calcChangeCost(name[i]);
        v.push_back(i);
    }
    
    answer+=calcMoveCost();
    
    return answer;
}
