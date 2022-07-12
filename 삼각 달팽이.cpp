#include <bits/stdc++.h>
using namespace std;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/68645
  삼각 달팽이
  -------
  배열, 구현
*/

void insertNum(vector<vector<int>>& v, 
               pair<int, int>& position,
               int& num,
               int size) {
    if(size == 1) {
        v[position.first][position.second] = num;
        return;
    }
    
    for(int i=0; i<size-1; ++i) {
        v[position.first][position.second] = num++;
        position.first += 1;
    }
    
    for(int i=0; i<size-1; ++i) {
        v[position.first][position.second] = num++;
        position.second+=1;
    }
    
    for(int i=0; i<size-1; ++i) {
        v[position.first][position.second] = num++;
        position.first -= 1;
        position.second -= 1;
    }
    
    position.first += 2;
    position.second += 1;
}

vector<int> solution(int n) {
    vector<int> answer;
    vector<vector<int>> v;
    for(int i=0; i<n; ++i) {
        v.push_back(vector<int>(i+1, 0));
    }
    
    int num = 1;
    int currentSize = n;
    pair<int, int> currentPosition = {0, 0};
    
    while(currentSize > 0) {
        insertNum(v, currentPosition, num, currentSize);
        currentSize -= 3;
    }
    
    for(vector<int> edge : v) {
        for(int n: edge) {
            answer.push_back(n);
        }
    }
    
    return answer;
}
