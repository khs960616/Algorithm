import java.util.*;

/*
https://school.programmers.co.kr/learn/courses/30/lessons/12980
점프와 순간 이동
---
모듈러, 수학 

1. n의 최대값이 10억이므로 단순 브루트 포스로 접근이 불가능하다. 
2. 점프의 횟수를 항상 최소한으로 만들어야된다. 

n = 6인 경우
-> n=3인 경우와 동일한 답을 가진다.
-> n=3인 경우 -> n=1인 경우보다 +1의 답을 가진다. 

따라서 해당 문제는 n을 2로 나누면서 발생하는 나머지 값을 모두 더하면 구하고자하는 최소값을 구할 수 있다.
*/
public class Solution {
    public int solution(int n) {
        int ans = 0;
        while(n!=0) {
            ans+=(n%2);
            n/=2;
        }
        return ans;
    }
}
