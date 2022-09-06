/*
https://school.programmers.co.kr/learn/courses/30/lessons/87390
n^2 배열 자르기 
---

제약 조건 
1. n은 2이상 10^7이하의 자연수 
2. 0<= left <= right <=n^2
3. right - left < 10^5
---

1. 문제 제약조건상 단순 시뮬레이션을 하는 경우 n^7 * n^7 배열의 경우 값을 init() 할때 너무 많은 시간복잡도를 요구한다.
2. right-left 즉, 실제 구해야하는 구간의 범위는 10^5으로 그렇게 크지 않다.
3. 초기 이차원 배열값, (i번째행 j번째열)의 값은 max(i+1, j+1)이다.
4. 따라서 n과 배열의 성질을 이용하여 left, right가 2차원 배열상에 어디에 위치하는지 구하면 된다. 
*/
import java.util.*;

class Solution {
    public int[] solution(int n, long left, long right) {
        List<Integer> answer = new ArrayList<>();
        for(long i = left; i<=right; ++i) {
            int row = (int) (i/n) + 1;
            int column = (int) (i%n) + 1;
            answer.add(Math.max(row, column));
        }
        return answer.stream().mapToInt(Integer::intValue).toArray();
    }
    
}
