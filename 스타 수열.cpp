#include <bits/stdc++.h>
using namespace std;

/*  
  https://school.programmers.co.kr/learn/courses/30/lessons/70130
  스타 수열
  백트래킹 
  구현
  ---
  1. 주어진 수열 a에 나오는 숫자들과, 각 숫자들의 빈도 수를 저장한다. 
  
  2. 수열에 존재하는 수를 1개 고정하고(이 때 고정된 숫자를 t라 하자), 
     해당 숫자를 모든 부분집합에 포함하는 스타 수열의 길이를 원래 수열 a를 순회하며 구한다.
     스타 수열의 길이를 증가시키는 패턴은 [t, t가 아닌 다른 수],  [t가 아닌 다른수, t]의 형태 두 가지를 고려해야한다. 따라서 flag변수를 사용해서 t와, t가 아닌 수 모두 
     존재하는 경우 스타수열의 길이를 늘린다.
     
  3. 2번의 과정을 1에서 구한 모든 숫자들에 적용하면 최대 시간복잡도는 500,000 * 500,000이 된다.
     따라서 답이 될 수 없는 숫자의 경우는 수열 a를 순회하는 과정을 생략하도록 해야한다.
     특정 숫자를 고정하였을 때, 해당 숫자를 고정된 스타수열의 길이는 최대 (해당 숫자의 빈도수 * 2) 까지 밖에 될 수 없다.
*/
int solution(vector<int> a) {
    int answer = 0;
    unordered_map<int, int> frequency_map;
    
    for(int i: a) frequency_map[i]++;
    
    for(auto freq_info : frequency_map) {
        int i = freq_info.first;
        int freq = freq_info.second;
        if(freq*2 <= answer) continue;
        
        int len = 0;
        bool fix_flag = false;
        bool non_fix_flag = false; 
        for(int num: a) {
            if(num == i) fix_flag = true;
            else non_fix_flag = true;
            if(fix_flag && non_fix_flag) {
                len+=2;
                fix_flag = non_fix_flag = false;
            }
        }
        answer = max(answer, len);
    }
    
    return answer;
}
