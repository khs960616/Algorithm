import java.util.*;
import java.util.stream.*;

/* 
  https://school.programmers.co.kr/learn/courses/30/lessons/12938
  최고의 집합
*/
class Solution {
    private int[] answer = {-1};
    
    public int[] solution(int n, int s) {
        int quo = s/n;
        if(quo != 0) {
            answer = new int[n];
            Arrays.fill(answer, quo);
            
            int remainder = s % n;
            for(int i=n-1; i>=0; --i, --remainder) {
                if(remainder == 0) break;
                answer[i]+=1;
            }
        }
        
        return answer;
    }
}
