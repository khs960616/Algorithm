import java.util.*;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/12923
  숫자 블록
  ---
  약수 찾기, 문제 오류 존재
*/

class Solution {
    private final int MAX = 10000000;
    
    public int[] solution(long begin, long end) {
        List<Integer> answer = new ArrayList<>();
        
        for(long i=begin; i<=end; ++i) {
            answer.add(getMaxDivisor(i));
        }
        
        return answer.stream().mapToInt(Integer::intValue).toArray();
    }
    
    private int getMaxDivisor(long num) {
        if(num == 1) return 0;
        
        int ret = 1;
        for(long i=2; i*i <= num; ++i) {
            if(num % i != 0) continue;
            ret = Math.max(ret, (int) i); // num이 최대 10^9이므로, i값은 max 값을 초과할 수 없다.
            
            int quotient = (int) (num/i); // 문제 조건상 두 가지 약수 중 큰 값으로 갱신해야 더 올바른 답이다. 
            if(quotient <= MAX) ret = Math.max(ret, quotient);
        }
        return ret;
    }
} 




/*
  통과한 코드 
import java.util.*;

class Solution {
    private final int MAX = 10000000;

    public int[] solution(long begin, long end) {
        List<Integer> answer = new ArrayList<>();

        for(long i=begin; i<=end; ++i) {
            answer.add(getMaxDivisor(i));
        }

        return answer.stream().mapToInt(Integer::intValue).toArray();
    }

    private int getMaxDivisor(long num) {
        if(num == 1) return 0;

        int ret = 1;
        for(long i=2; i*i <= num; ++i) {
            if(num % i != 0) continue;
            int quotient = (int) (num/i);
            int div = (int) i;
            int result = Math.max(quotient, div);

            if(result > MAX) continue;

            ret = Math.max(ret, result);    
            // 문제 조건상으로는 사실, 두 약수값중 max값보다 작은것이 하나라도 있다면 해당 값의 블록으로 깔리는게 맞는데 테스트케이스가 이상함 
        }
        return ret;
    }
} 

*/
