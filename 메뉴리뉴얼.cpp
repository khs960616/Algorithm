/*
  https://programmers.co.kr/learn/courses/30/lessons/72411
  2021 KAKAO BLIND RECRUITMENT
  조합 문제 
  
  --- 
  그동안 조합문제의 경우에도 next_permutation와 set을 혼용해서 사용하거나, {0,0,1,0,0} 등 뽑을 조합을 나타내는 변수를 만들어 
  조합을 흉내내는 식으로 사용해왔는데, 다음과 같이 재귀함수를 이용한 구현방법을 이용하면 시간복잡도가 2^n으로 줄어든다. 
  되도록 진짜 순열 문제가 아닌 이상, 조합문제는 다음과 같이 구현해서 사용하는 편이 더 좋을듯함. 
*/

#include <bits/stdc++.h>
using namespace std;

void getCombination(map<string, int>& combinationCount,
                    string combi, string order, 
                    int startIdx, int num) {
    if(combi.size() == num) {
        sort(combi.begin(), combi.end());
        ++combinationCount[combi];
        return;
    }
    int oSize = order.size();
    
    for(int i=startIdx; i<oSize; i++) {
        getCombination(combinationCount, combi+order[i], order, i+1, num);
    }
}

vector<string> solution(vector<string> orders, vector<int> course) {
    vector<string> answer;
    map<string, int> combinationCount;
    map<int, int> maxCombinationSet;
    
    for (string order: orders) {
        for (int i: course) {
            string s = "";
            getCombination(combinationCount, s, order, 0, i);
        }
    }
    
    for(auto a: combinationCount) {
        int stringSize = a.first.size();
        if (maxCombinationSet[stringSize] < a.second) {
            maxCombinationSet[stringSize] = a.second;
        }
    }

    for(auto a: combinationCount) {
        int stringSize = a.first.size();
        if(find(course.begin(), course.end(), stringSize) == course.end()) continue;
        if(maxCombinationSet[stringSize] == a.second && a.second != 1) {
            answer.push_back(a.first);
        }
    }
    
    return answer;
}
