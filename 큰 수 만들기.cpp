#include <bits/stdc++.h>
using namespace std;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/42883
  큰 수 만들기
  -----------
  그리디 알고리즘, 스택
  
  k개의 숫자를 제거하는 경우, 되도록 앞자리 수가 크도록 제거해야 제거 후에 가장 큰 수가 남는다.

  1. number의 각 char를 순차적으로 탐색하며 stack에 넣는다.
  2. 만일 현재 스택이 비어있지 않고, j개만큼의 문자열을 더 제거할 수 있다면 스택 top()이 현재 원소보다 작은 지 비교해서, j개만큼의 원소를 pop() 시킨다.
     (만일 스택에 j개 만큼의 원소가 없다면 남은 원소의 수를 t라 하면, t만큼의 원소를 제거하고, 제거 가능한 원소의 수를 j-t로 갱신한다.) 
  
  3. 만일 더 이상 문자를 제거할 수 없는 상태가 되었다면 (k=0), 현재 index를 기준으로 number의 서브스트링을 저장해둔다.
  4. 스택의 각 원소들을 answer 문자열에 더한다.
  5. 4의 문자열과 3의 문자열을 더한다.
  6. 5번까지 진행하였는데 k가 아직 0이 아니라면 다음의 케이스와 같다.
    (ex number = "765555555", k = 2 와 같이 k개의 문자를 제거하기전 이미, 내림차순으로 정렬이 완료 되는 경우)
    따라서 이 경우 5번 문자열의 뒤에서 남은 k의 숫자만큼 문자를 제거하면 구하고자하는 정답이 된다.
*/

string solution(string number, int k) {
    string answer = "";
    string remain = "";
    
    int nLength = number.size();
    stack<char> st;
    st.push(number[0]);
    
    for(int i=1; i<nLength; ++i) {
        if(k == 0) {
            remain = number.substr(i);
            break;
        }
        
        if(k != 0) {
            while(!st.empty()) {
                char c = st.top();
                if(k == 0) break;
                if(c >= number[i]) break;
                
                st.pop();
                --k;
            }
        }
        st.push(number[i]);
    }
    
    while(!st.empty()) {
        answer = (st.top() + answer);
        st.pop();
    }
    answer += remain;
    
    while(k>0) {
        --k;
        answer.pop_back();
    }
    
    return answer;
}
