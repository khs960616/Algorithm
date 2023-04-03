import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

/*
  https://www.acmicpc.net/problem/16496
  큰 수 만들기
  그리디
  ---
  우선 순위 큐를 사용하여, 숫자들을 조합했을 때 가장 크게 나오는 순으로 정렬한 뒤, 각 값을 이어 붙혀서 답을 출력한다. 
  완성된 String의 맨 앞이 0이라면 별도 예외처리 
*/
public class BOJ_16496 {

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int N = Integer.parseInt(br.readLine());
        PriorityQueue<String> pq = new PriorityQueue<>((s1,s2)-> (s2+s1).compareTo(s1+s2));

        StringTokenizer st = new StringTokenizer(br.readLine());
        for(int i=0; i<N; ++i) pq.add(st.nextToken());

        StringBuilder sb = new StringBuilder();
        while(!pq.isEmpty()) sb.append(pq.poll());

        String answer = sb.toString();
        if(answer.charAt(0) == '0') answer = "0";
        System.out.println(answer);
    }
}
