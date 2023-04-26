import java.util.*;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/181188?language=java
  요격 시스템
  그리디 
  --
  강의장 배정 문제와 동일한 문제
  
*/
class PG181188 {
    public int solution(int[][] targets) {
        int answer = 1;
        Arrays.sort(targets, (e1, e2)->{
            if(e1[1] == e2[1]) return e1[0] - e2[0];
            return e1[1]-e2[1];
        });
        
        int len = targets.length;
        int prev = targets[0][1];
        for(int i=1; i<len; ++i) {
            if(prev > targets[i][0]) continue;
            prev = targets[i][1];
            ++answer;
        }
        return answer;
    }
}
