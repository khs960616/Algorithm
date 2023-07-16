import java.util.*;
import java.io.*;

/*
  https://www.acmicpc.net/problem/2157
  여행
  DP
  ---
  1. 주어진 구간에서 남은 이동 횟수만큼 이동했을 때 얻을 수 있는 최댓값을 구해야한다.
  2. 1의 조건에서 다음의 세 가지 제약 조건을 만족하는 경우에만 답을 갱신해야한다.
     2-1) 마지막 종점이 N으로 끝나야한다. -> dp값을 갱신할 때 초기값을 매우 작은 음수로 설정하여 해결
     2-2) M번 이하로 움직일수 있다. -> 기저 조건으로 해결
     2-3) 번호가 낮은 도시로는 이동할 수 없다. -> 초기 input에서 필터링을 통해 해결 
*/
public class BOJ_2157 {

    // 출발점은 반드시 1, 도착점은 반드시 N
    // N : 도시의 갯수, M: 지날 수 있는 최대 도시의 수
    // K : 도시와 도시를 연결하는 항로 (유향 그래프)
    private static int N, M, K;
    private static int[][] dp;
    private static List<int[]>[] paths;

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());

        // dp[i][j] 현재노드가 i번 노드이고, j번 이동한 상태일 때, 앞으로 이동해서 얻을 수 있는 최대 value
        dp = new int[N+1][N+1];
        paths = new List[N+1];

        for(int i=0; i<N+1; ++i) {
            paths[i] = new ArrayList<>();
            for(int j=0; j<N+1; ++j) {
                dp[i][j] = -1;
            }
        }

        for(int i=0; i<K; ++i) {
            st = new StringTokenizer(br.readLine());
            int from = Integer.parseInt(st.nextToken());
            int to = Integer.parseInt(st.nextToken());
            int value = Integer.parseInt(st.nextToken());

            if(from < to) {
                paths[from].add(new int[]{to, value});
            }
        }

        System.out.println(getMax(1, 1));
    }

    // 1번에서 시작, N번 에서 끝나야함
    // M개 이하 도시만 거쳐야함
    private static int getMax(int cur, int moveCnt) {
        if(cur == N) return 0;
        if(moveCnt==M) return Integer.MIN_VALUE;
        if(dp[cur][moveCnt] != -1) return dp[cur][moveCnt];

        dp[cur][moveCnt] = Integer.MIN_VALUE;
        for(int[] path: paths[cur]) {
            dp[cur][moveCnt] = Math.max(dp[cur][moveCnt], path[1] + getMax(path[0], moveCnt+1));
        }

        return dp[cur][moveCnt];
    }
}
