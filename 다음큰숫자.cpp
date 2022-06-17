#include <bits/stdc++.h>
using namespace std;

/*
  https://programmers.co.kr/learn/courses/30/lessons/12911
  다음 큰 숫자
  ---
  비트 마스킹, 구현
*/
int getOneCnt(int n) {
    int ret = 0;
    unsigned int mask = 0x01;
    
    while(mask <= n) {  
        if(n & mask) ++ret;
        mask <<= 1;
    }
    
    return ret;
} 

int solution(int n) {
    int answer = 0;
    int cnt = getOneCnt(n);
    
    while(1) {
        if(cnt == getOneCnt(++n)) {
            answer = n;
            break;
        }
    }
    
    return answer;
}
