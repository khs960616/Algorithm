import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

/*

  https://www.acmicpc.net/problem/17404
  * RGB거리2
  DP
  ---
  1. 문제에서 주어진 배열이 원형 링크드 형태이므로 처음부터 모든 것을 dp로 구성하려고하면 문제의 복잡도가 너무 오름 
  2. 원형큐가 아닐때의 점화식은 dp[i][j] = min(dp[i-1][j가 아닌 모든 원소]) + 현재 cost 임
  
  -> 2번의 점화식을 그대로 활용하기 위해 문제를 다음과 같이 단순화 시킴
  
  1. 처음 시작하는 원소를 고정 시킨 후 2번의 과정을 거쳐 최소값을 구한다.
  2. 1번의 결과로 구해진 최소값에서, 처음 시작하는 원소와 마지막 원소의 색이 같은 경우는 정답을 갱신할 때 제외시킨다. 
  
  ---
  점화식써서 푸는 dp문제인 것은 캐치했고,
  이전에 풀어본 문제에서 조건이 하나 추가된 문제 였으나, 결국 풀지 못하고 다른 풀이를 참고함.
  
  > DP문제에서 문제를 풀 때,
  특정한 조건을 고정시키면 단순화 시킬 수 있는지도 고려해보는 것을 생각해야 할듯함.
  
*/
public class BOJ_17404 {

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int N = Integer.parseInt(br.readLine());

        int[][] cost = new int[N][3];
        for(int i=0; i<N; ++i) {
            StringTokenizer st = new StringTokenizer(br.readLine());

            cost[i][0] = Integer.parseInt(st.nextToken());
            cost[i][1] = Integer.parseInt(st.nextToken());
            cost[i][2] = Integer.parseInt(st.nextToken());
        }

        int answer = Integer.MAX_VALUE;

        for(int i=0; i<3; ++i) {
            int[][] dp = new int[N][3];
            dp[0][0] = dp[0][1] = dp[0][2] = 2_000_000;
            dp[0][i] = cost[0][i];

            for(int j=1; j<N; ++j) {
                dp[j][0] = Math.min(dp[j-1][1], dp[j-1][2]) + cost[j][0];
                dp[j][1] = Math.min(dp[j-1][0], dp[j-1][2]) + cost[j][1];
                dp[j][2] = Math.min(dp[j-1][0], dp[j-1][1]) + cost[j][2];
            }

            for(int j=0; j<3; ++j) {
                if(i==j) continue;
                answer = Math.min(answer, dp[N-1][j]);
            }
        }

        System.out.println(answer);
    }
}
