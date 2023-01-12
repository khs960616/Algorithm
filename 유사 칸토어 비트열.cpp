#include <bits/stdc++.h>

using namespace std;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/148652
  유사 칸토어 비트열 
  ---
  재귀 함수, 수학 
  
   먼저 문제를 풀기전, 관찰이 필요하다.
    0번째 칸토어 비트열 0
    1번째 칸토어 비트열 11011
    2번째 칸토어 비트열 11011 11011 00000 11011 11011
    3번째 칸토어 비트열 11011 11011 00000 11011 11011 11011 11011 00000 11011 11011 11011 11011 00000 11011 11011 00000 00000 00000 00000 00000 11011 11011 00000 11011 11011 11011 11011 00000 11011 11011
    ...
    
    칸토어 비트열을 관찰하면 다음의 특성이 존재한다.
    1) n(n>=1)번째 칸토어 비트열은 4^n개의 1을 가진다.
    2) n번째 칸토어 비트열은 (n-1) 번쨰 칸토어비트열 4개와,   5^(n-1)의 연속된 0으로 이루어진 비트열로 구성되어있다. -> 분할정복이 가능해보인다! 
    3) n번째 칸토어 비트열은 크기가 5^n인 비트열이다.
    4) 각 칸토어 비트열은 n의 크기와 상관없이, 동일한 index면 동일한 값을 가진다. 
    
    풀이는 코드내에 주석으로 남깁니다.
*/

// 1부터 current_idx까지의 1의 개수를 구하는 함수
int get_cnt(long long current_idx) {  
    if(current_idx <= 5) {
      // 만약 현재 index가 5이하이면 현재 구하고자하는 패턴은 1번째 칸토어 비트열과 동일한 패턴이므로 리턴합니다.
        return (current_idx < 3) ? current_idx : current_idx-1;
    }
    
    int ret = 0;
    int base = 0; 
    while(pow(5, base) < current_idx) base++;
    
    long long pattern_size = pow(5, base-1);    //현재 index보다 작은 5의 제곱수를 구합니다. 이는 현재 index보다 작은 5의 제곱수 형태의 칸토어 비트열의 패턴과 매칭됩니다.
    long long one_cnt = pow(4, base-1); // n번째 칸토어 비트열은 4^n 인 1의 개수를 가집니다. 
    long long current_block = ceil((double)current_idx / pattern_size); 
  // 현재 인덱스까지 비트열을 pattern_size 크기를 가진 5개의 블록이 이어진 칸토어 비트 형태라고 가정합니다. 이때 3번째 블록은 항상 0으로만 이루어져있는 블록입니다.
    long long remainder = current_idx % pattern_size;  // 현재 속한 블록에서 몇번째 인덱스에 위치하는지에 대한 정보입니다.
    
    for(int i=1; i<current_block; ++i) {
        if(i == 3) continue;  //3번쨰 블록은 문제에서 주어진 조건에 의해 모두 0으로만 이루어진 비트열이므로 제외합니다.
        ret += one_cnt; // 현재 인덱스까지 비트열을 pattern_size 크기를 가진 5개의 블록이라고 가정하였습니다. 따라서 현재 블록 이전의 모든 블록은 4^(base-1) 만큼의 1을 가지므로 더해줍니다.
    }
 
    if(current_block == 3) return ret; //만약 현재 블록이 3번째 블록이라면, 더 이상의 연산은 필요 없습니다.
    else if(remainder == 0) return ret + one_cnt; // 현재 블록이 3번째 블록이 아니고, 인덱스가 블록내에서 마지막에 위치하는 경우 pattern_size크기를 가진 칸토어 비트열의 패턴과 매칭되므로 더해줍니다.
    else return ret + get_cnt(remainder); // 위 두조건에 걸리지 않는다면 remainder만큼의 sub block 만큼을 크기가 더 작은 부분 칸토어 비트열이 됩니다. 따라서 재귀적으로 함수를 호출합니다. 
}

int solution(int n, long long l, long long r) {
    return get_cnt(r) - get_cnt(l-1);
}
