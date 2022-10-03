#include <bits/stdc++.h>
using namespace std;

/*
https://school.programmers.co.kr/learn/courses/30/lessons/12987
숫자게임
--
정렬, 이진탐색 
*/

int solution(vector<int> A, vector<int> B) {
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    
    int answer = 0;
    auto iter = B.begin();
    
    for(int a: A) {
        if(iter == B.end()) break;
            
        iter = upper_bound(iter, B.end(), a);
        if(iter != B.end()) {
            answer++;
            iter+=1;
        }
    }
    return answer;
}
