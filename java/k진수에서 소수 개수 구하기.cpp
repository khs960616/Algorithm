import java.util.*;

/*
https://school.programmers.co.kr/learn/courses/30/lessons/92335
2022 KAKAO BLIND RECRUITMENT
k진수에서 소수 개수 구하기

---
문자열, 소수판별 

백만 이하의 삼진수로 표현 가능한 최대의 수 
1212122222222   -> 십진수 (997271) 

따라서 만약 에라토스테네스의 체를 쓰기 위하면 최악의 경우 1,2121,2222,2222 개 만큼의 숫자에 대한 소수 판별여부를 저장해두어야한다.
따라서 에라토스테네스의 체를 쓰는 것보다 각 숫자에 대한 소수 판별을 하는 것이 빠를 것임. (백만 이하의 숫자에 대해서만 하면 되므로)
*/
class Solution {
    public int solution(int n, int k) {
        int answer = 0;
        String s = convertK(n, k);  // 십진수 n을 k진수 표현법으로 변경한다.
        
        int len = s.length();
        StringBuilder tmp = new StringBuilder();
        for(int i=0; i<len; ++i) {
            if(s.charAt(i) != '0') {      
                tmp.append(s.charAt(i));    
                continue;
            }
            
            if(isPrime(tmp.toString())) ++answer; // 0을 기준으로 토큰을 분리한다. 
            tmp.setLength(0);
        }
        
        if(isPrime(tmp.toString())) ++answer;
        return answer;
    }
    
    private boolean isPrime(String s) {
        if(s.length() == 0) return false; // 00 이런식으로 되는 경우 빈 스트링이 들어올 수 있으므로 별도 예외처리하였다. 그냥 main 메서드쪽에 두는 게 더 나았을꺼 같기도 함. 
        Long num = Long.parseLong(s);
        
        for(long i=2; i*i<= num; ++i) {
            if(num % i == 0) return false;
        }
        
        return num > 1;   // 0 또는 1의 경우 소수로 판별되면 안되므로 다음의 조건으로 return 한다.
    }
    
    private String convertK(int n, int k) {
        StringBuilder sb = new StringBuilder(); // 매번 새로운 String 생성 방지를 위함 
        while(n!=0) {
            sb.append(n%k);
            n/=k;
        }
        return sb.reverse().toString(); //insert(0, n%k)하려다, 이러면 넣을때마다 버퍼에 있는 값을 한칸씩 미뤄야되니까, 그냥 뒤로 이어붙힌 후 reverse 함수 사용 
    }
}
