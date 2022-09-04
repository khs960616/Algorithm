import java.util.*;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/12936
  줄 서는 방법
  -----------------------------------------
  구하고자하는 것 n개로 이루어진 순열중, 오름차순으로 k번째의 순열 
  
  Navie 풀이 : 재귀함수를 이용해 모든 순열의 경우의 수를 만든다. 이 때 count를 두어, 만약 count와 k가 일치하는 경우의 순열을 출력한다.
             -> 이 경우 최악의 경우 20! 만큼의 시간복잡도를 요구하며 이는 너무 큰 숫자 이다.
             
  ----
  특성 
  1. 순열의 순서는 정렬되어있다.
  2. 첫 번째 숫자를 고정하고 나면, 그 이후에 올 수 있는 경우의 수는 (n-1)!이 된다. 
  
  ----
  k를 (n-1)!로 나눴을때 첫 번째 자리가 유추가 가능할까?
  
  ((n-1)!로 나눈 몫, 만일 나머지가 존재하다면 +1 한 값이 k번째 순열의 맨 처음 자리 숫자이다.) 이를 다른 나머지 숫자를 구하기 위해 일반화하면 다음과 같다.
  
  구하고자하는 자리를 (p라 하자, 이 때 p는 1이상, n이하의 숫자이다.) 
  
  1. 나머지가 존재하는 경우
  -> (n-p)!로 현재의 k값을 나눈몫을 quo라 하자.
  -> 이때 (n-p)!로 k를 나눈 나머지값이 0보다 크다면  quo값에 1을 더한다.
  -> 이 후, k값은 k를 (n-p)!로 나눈 나머지로 갱신한다.
  -> [1,2,3,.....n] 까지 순열을 이루는 원소중, 아직 사용되지 않은 원소 중 quo번째 숫자가 현재 p자리에 올 숫자이다. 
        
  2. 1의 과정에서 quo값이 0인 경우 (k를 (n-p)!로 나눈 나머지와 몫이 모두 0인 경우) 
  -> 현재 남은 k값이 20!~1! 의 숫자중 하나인 경우이다. 이 경우 고정된 다른 자리수를 제외하고, 가장 사전순으로 우선순위가 낮은 순열이 답이 된다. 
  
*/
class Solution {
    private long[] factorials = new long[21];
    
    {
        initFactorials();
    }
    
    public int[] solution(int n, long k) {
        boolean[] isUsed = new boolean[n];
        int[] answer = new int[n];
        
        int idx = n;
        long rem = k;
        
        for(; idx>0; --idx) {
            int quo = (int) (rem/factorials[idx-1]);
            rem %= factorials[idx-1];
            if(rem != 0) quo+=1;
            if(quo == 0) break;
            
            int cnt = 0;
            for(int j=0; j<n; ++j) {
                if(isUsed[j]) continue;
                ++cnt;
                if(cnt == quo) {
                    answer[n-idx] = j+1;
                    isUsed[j] = true;
                    break;
                }
            }
        }
        
        for(int i=n-1; i>=0; --i) {
            if(!isUsed[i]) {
                answer[n-idx--] = i+1;
            }
        }
        
        return answer;
    }
    
    private void initFactorials() {
        factorials[0] = factorials[1] = 1;
        for(int i=2; i<21; ++i) {
            factorials[i] = factorials[i-1] * i;
        }
    }
}
