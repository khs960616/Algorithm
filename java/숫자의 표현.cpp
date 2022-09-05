/*
  https://school.programmers.co.kr/learn/courses/30/lessons/12924
  숫자의 표현
  10,000 이하의 숫자 n을 연속된 자연수의 합으로 표현하면 최대 몇개의 경우의 수가 나오는가? 
  
  ---
  임의의 자연수를 k라 하면, k부터 연속된 자연수 j개의 합은 다음과 같다.
  k + (k+1) + (k+2) + (k+3) .... +(k+j-1) = j*k + (1+2+3+ .... j-1) = j*k + j(j-1)/2 
  
  이 때 우리가 구하고자하는 것은 임의의 자연수 k로부터 연속된 자연수 j개를 더해서 n이 되는 경우의 수이다.
  
  즉 j*k + j(j-1)/2 = n 해당 식을 만족하는 (j, k) 순서쌍의 갯수이다.
  이때 1부터 j-1까지의 합을 나타내는 항을 우항으로 이항하면 식은 
  
  j*k = (n-(j(j-1)/2)이 된다.
  이 때 양변을 j로 나눈 나머지는 (n-(j(j-1)/2) % j = 0을 만족해야한다. 
  
  즉 구하고자하는 답 "10,000 이하의 숫자 n을 연속된 자연수의 합으로 표현하면 최대 몇개의 경우의 수" 는 결국 
  (n-(j(j-1)/2) % j = 0 다음의 수식을 만족하는 j값을 구하는 것이다.
*/

class Solution {
    public int solution(int n) {
        int answer = 1; // 모든 수는 1개의 연속된 자연수 표현을 가진다. (자기 자신)
        int continuousCnt = 2; // 따라서 연속된 2개의 수부터 검사한다.
        int checkValue = n - getApSum(continuousCnt); // 위에서 설명한 구하고자하는 값 (n-(j(j-1)/2) % j = 0 이다.
        
        /* 
          구하고자하는값은 continuousCnt * k = (n-(continuousCnt(continuousCnt-1)/2)을 만족하는 j,k의 순서쌍이다. 
          이때 (n-(j(j-1)/2) == 0 이 되면, continuousCnt != 0 이므로 k=0 이다. 이는 문제 조건과 일치하지 않으므로 제외한다. 
          (음수가 되는 경우는 구하고자하는 수를 초과한 범위이므로 마찬가지로 제외한다.)
        */
        while(checkValue>0) {
            if(checkValue % continuousCnt == 0) ++answer;
            checkValue = n - getApSum(++continuousCnt);
        }
        return answer;
    }
    
    // sum 1,2,3,4 .... (continuousCnt-1)
    private int getApSum(int continuousCnt) {
        return (continuousCnt*(continuousCnt-1))/2;
    }
}
