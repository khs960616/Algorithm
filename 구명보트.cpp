#include <bits/stdc++.h>
using namespace std;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/42885
  구명보트
  ----
  그리디
  
  
*/
int solution(vector<int> people, int limit) {
    int answer = 0;
    int pSize = people.size();
    sort(people.begin(), people.end());
    
    int lp = 0, rp = pSize-1;
    while(lp <= rp) {
        ++answer;
        if(people[lp] + people[rp--] <= limit) lp++;
    }
    return answer;
}
