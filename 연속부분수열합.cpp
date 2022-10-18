#include <bits/stdc++.h>
using namespace std;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/131701
  연속 부분 수열 합 
  ---
  구현 
  가능한 모든 연속 부분 수열을 구해서 합을 set에 저장하면 된다.
*/
set<int> st;
int e_size = 0;

void get_sub_set(vector<int> elements, int sub_set_size) {
    int sum = 0;
    for(int i=0; i<sub_set_size; ++i) sum += elements[i];
    st.insert(sum);
    
    for(int i=1; i<e_size; ++i) {
        int next_add_idx = (i+sub_set_size-1) % e_size;
        sum = (sum - elements[i-1] + elements[next_add_idx]);
        st.insert(sum);
    }
}

int solution(vector<int> elements) {
    e_size = elements.size();
    for(int i=1; i<=e_size; ++i) {
        get_sub_set(elements, i);
    }
    
    return st.size();
}
