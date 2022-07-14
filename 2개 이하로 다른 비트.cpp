#include <bits/stdc++.h>
using namespace std;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/77885#
  2개 이하로 다른 비트
  -----------------
  비트연산 연습 
  
  1. 짝수인 경우 항상 첫번째 비트가 0이므로 +1 또는 bit or 1 을 통해 1개 증가된 number
  2. 홀수인 경우 
     case 1: 11111
     case 2: 11101111
     
     만일 해당 숫자를 비트로 바꾸었을때 0이 없는 경우 : 가장 왼쪽에 있는 1의 bit에 해당 하는 숫자만큼 더하면 된다 (case 1의 경우 101111을 리턴함)
     만일 해당 숫자를 비트로 바꾸었을 때 가장 왼쪽 비트에 도달하기전 0을 만난 경우 : 0 우측에 bit에 해당하는 숫자만큼 더해주면 (11110111) 된다.
     
     두 케이스를 별도 처리할 필요 없이 동시 처리가 가능함.
*/
long long calcBits(long long num) {
    long long currentNum = num;
    long long cnt = 0;
    
    while(currentNum) {
        if(currentNum % 2 == 0) break;
        cnt++;
        currentNum /= 2;
    }

    return num + ((long long) 1<<(cnt-1)); 
}
vector<long long> solution(vector<long long> numbers) {
    vector<long long> answer;
    
    for(long long number: numbers) {
        if(number % 2 == 0) {
            answer.push_back(number+1);
            continue;
        }
        answer.push_back(calcBits(number));
    }
    return answer;
}
