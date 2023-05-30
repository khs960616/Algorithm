import java.io.BufferedReader;
import java.io.InputStreamReader;

/*
https://www.acmicpc.net/problem/2877
4와 7
수열의 규칙성, 수학 
---

1) 4와 7로 이루어진 숫자와, 그 순서를 나열해본다. 

4 (1)     44 (3)  444(7)
                  447(8)
          47 (4)  474(9)
                  477(10)
7 (2)     74 (5)
          77 (6)

2) 위와 같이 수를 나열하면 다음의 규칙을 찾을 수 있다.
  1) k가 짝수이면, 해당 자리수는 7이고, 홀수이면 4이다.
  2) 자리수가 증가하는 경우, 해당 숫자의 순번은 다음와 같이 증가한다. 
     2-1) 뒷자리가 4인 경우  
           *2 + 1
     2-2) 뒷자리가 7인 경우 
           *2  + 2

따라서 2의 규칙에 맞게 계산을 하면 풀리는 간단한 수열 문제였다. 
*/
public class Main {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder sb = new StringBuilder();
        int k = Integer.parseInt(br.readLine());

        while (k != 0) {
            if (k % 2 == 0) {
                k -= 2;
                sb.append("7");
            } else {
                k -= 1;
                sb.append("4");
            }
            k /= 2;
        }

        System.out.println(sb.reverse().toString());
    }
}
