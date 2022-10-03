#include <bits/stdc++.h>
#define WILD_CARD '*'
using namespace std;

/*
   (10/11 다시 풀어볼것) 
  
  https://school.programmers.co.kr/learn/courses/30/lessons/64064
  2019 카카오 개발자 겨울 인턴십
  불량 사용자
  ---
  순열, 비트마스킹 
  
  
  풀이에 실패했던 코드 구성 
  1. user_id에 속하는 모든 id들에 대해서 한글자씩 *로 바꾸며 나올 수 있는 모든 문자열을 map에 key값으로 하여, count를 센다.  이때 카운트를 n이라하자.
    >> 문제 조건에서 의해 문자열의 길이는 8이하이므로 하나의 문자열에서 나올수 있는 최대의 경우의수는 2^8이며, user_id는 최대 8개까지만 존재하므로
       2^11 였으므로, 해당 방식 선택
       
  2. banned_id에 속하는 문자열에 빈도수를 센다. 이 때 카운트를 r이라 하자.
  3. 모든 banned_id에 대응되는 nCr를 곱하면 답이다.
  
  실패 이유 : 입출력 예제 3번과 같이, banned_id와 user_id를 속하는 과정은 순서에 종속적임. 따라서 앞서 선택한 user_id에 의해, 뒤 순서에 나오는 user_id가 고정되는 케이스가 생기게됨..
  ---
  
  아래 선택 방식 
  1. 현재 선택된 원소를 비트마스킹을 이용해 표현하여, 조합을 만들어냄 
  2. 현재 banned_id (banned_id[cnt]) 와 선택되지 않은 user_id를 비교하며, 두 값이 대응된다면, user_id를 선택함
  3. 나올 수 있는 비트마스킹의 수가 결국 구하고자하는 답과 동일한 값을 가짐 
  
*/
bool is_contain[8];
set<int> candidate_user_comibanations;

void check(vector<string> user_id, vector<string> banned_id, int state, int cnt) {
    if(cnt == banned_id.size()) {
        candidate_user_comibanations.insert(state);
        return;
    }
    
    int user_size = user_id.size();
    for(int i=0; i<user_size; ++i) {
        if(is_contain[i]) continue;
        if(banned_id[cnt].length() != user_id[i].length()) continue;
        
        int j = 0;
        int len = user_id[i].length();
        for(; j<len; ++j) {
            if(banned_id[cnt][j] == WILD_CARD) continue;
            if(user_id[i][j] != banned_id[cnt][j]) break;
        }
        
        if(j == len) {
            is_contain[i] = true;
            check(user_id, banned_id, (state|(1<<i)), cnt+1);
            is_contain[i] = false;
        }
    }
}

int solution(vector<string> user_id, vector<string> banned_id) {
    check(user_id, banned_id, 0, 0);
    return candidate_user_comibanations.size();
}
