import java.util.*;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/12927
  야근 지수
  ---
  1. 현재 남은 잔업량이 큰 순서대로 작업량을 줄여나가야 제곱해서 더했을때의 최종 결과값이 최솟값이 된다.
    >> 우선순위큐로 잔업을 선택
    
  2. 우선순위큐에 front에 존재하는 값을 1씩 줄여나간다. (만일 이때, 잔업량이 0이 되었다면, 해당 업무는 끝난 상태이므로 다시 큐에 넣지 않는다.) 
*/
class Solution {
    public long solution(int n, int[] works) {
        long answer = 0;
        PriorityQueue<Integer> pq = new PriorityQueue<>(Collections.reverseOrder());
        for(int i=0; i<works.length; ++i) {
            pq.add(works[i]);
        }
        
        while(!pq.isEmpty() && n-- > 0) {
            Integer num = pq.poll() - 1;
            if(num == 0) continue;
            pq.add(num);
        }
        
        while(!pq.isEmpty()) {
            Integer front = pq.poll();
            answer += (front*front);
        }
        return answer;
    }
}
