import java.util.*;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/178870?language=java
  연속된 부분 수열의 합
  투포인터 
*/
class Solution {
    public int[] solution(int[] sequence, int k) {
        int seqSize = sequence.length;
        int left = 0, right = 0;
        int lRange = 0, rRange = 0, cnt = 1000001;
        int sum = 0;
        
        while(left<seqSize && left <= right) {
            
            if(right < seqSize && sum < k) {
                sum += sequence[right++];
            } else {
                sum -= sequence[left++];
            }
            
            if(sum == k) {
                if(cnt == right-left) continue;
                cnt = right-left;
                lRange = left;
                rRange = right-1;
            }
        }
        
        return new int[] { lRange, rRange };
    }
}
