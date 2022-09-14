import java.util.*;
import java.util.stream.*;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/67258
  2020 카카오 인턴십
  보석 쇼핑
  ---
  two pointer
*/
class Solution {
    public int[] solution(String[] gems) {
        int[] answer = {0, 0};
        
        Map<String, Integer> gemsCnt = new HashMap<>();
        int gemType = (int) Arrays.stream(gems).distinct().count();
        int currentTypeCnt = 0;
        int l=0, r=0, dist = Integer.MAX_VALUE;
        
        while(r<gems.length) {
            int prevRCnt = gemsCnt.getOrDefault(gems[r], 0);
            if(prevRCnt == 0) currentTypeCnt+=1;
            gemsCnt.put(gems[r], prevRCnt+1);
            
            if(currentTypeCnt == gemType) {
                while(l<r) {
                    int prevLCnt = gemsCnt.get(gems[l]);
                    if(prevLCnt == 1) break;
                    gemsCnt.put(gems[l++], prevLCnt-1);
                }
                
                if(r-l < dist) {
                    dist = r-l;
                    answer[0] = l+1; 
                    answer[1] = r+1;
                }
                
                gemsCnt.put(gems[l++], 0);
                currentTypeCnt-=1;
            }
            r++;
        }
        return answer;
    }
}
