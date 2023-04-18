import java.util.*;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/152995
  인사 고과
  ---
  정렬
  
  1. 1 ≤ scores의 길이 ≤ 100,000 이므로 
     각 사원이, 적어도 하나의 점수는 다른 사원보다 큰 경우를 중첩 for문으로 구하는 경우 시간 초과가 발생한다.
     따라서 최소 nlogn 로 해결해야한다.
     
     이를 위해 각 사원들의 점수를 하나는 내림차순, 하나는 오름차순으로 정렬한다.
     -> 오름차순 기준으로 정렬한 값의 최댓값을 계속 갱신 해나간다.
     
        하나의 값은 내림차순으로 정렬되어있으므로 항상 단조 감소한다
        내림차순으로 정렬된 값의 경우, 만일 오름차순으로 정렬된 값이 이전의 max값 보다 크다는 의미는,
        해당 사원보다 두 점수 모두 높은 사원이 존재한다는 의미이다. 
        
     -> 이후 pq를 이용해 구하고자 하는 점수가 맨 처음 나오는 순간의 rank을 return 하면 된다. 
     
     
*/
class PG152995 {
    public int solution(int[][] scores) {

        int[] target = scores[0];
        int targetSum = scores[0][0] + scores[0][1];
        
        Arrays.sort(scores, (o1, o2) -> o1[0] == o2[0] ? o1[1] - o2[1] : o2[0] - o1[0]);

        PriorityQueue<Integer> pq = new PriorityQueue<>((e1, e2)->e2-e1);

        int k = scores[0][1];
        for(int[] score: scores) {
            if(k > score[1]) {
                if(score == target) return -1;
                continue;
            } else {
                k = score[1];
                pq.add(score[0]+score[1]);
            }
        }

        int rank = 0;
        while(!pq.isEmpty()) {
            ++rank;
            int info = pq.poll();
            if(info == targetSum) return rank;
        }

        return -1;
    }
}
