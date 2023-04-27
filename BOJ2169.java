import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

/*
  https://www.acmicpc.net/problem/2169
  로봇 조종하기 
  dp, dfs
  ---
  1. dp배열 정의
     dp[i][j] : (0,0)에서 시작해서 (i, j)좌표에 도달했을 때의 최댓값
     단, 각 블록에 들어갈때의 방향이 다른 경우, 최댓값이 갱신될 수 있으므로 방향정보까지 포함한 3차원 배열을 선언한다.
     
  2. 기저
     (0, 0)이 출발점으로 0,0에 도달하였거나, 
     이미 값이 구해진 경우 더 이상 재귀함수를 호출하지 않고 종료한다. 
*/
public class BOJ2169 {

    private static int INF = -400_000_000;
    private static int N, M;
    private static int[][] map;
    private static int[][] dirs = { {0, -1}, {-1, 0} , {0, 1} };
    private static int[][][] dp;
    private static boolean[][] isVisit;

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());

        map = new int[N][M];
        dp = new int[N][M][3];
        isVisit = new boolean[N][M];

        for(int i=0; i<N; ++i) {
            st = new StringTokenizer(br.readLine());
            for(int j=0; j<M; ++j) {
                map[i][j] = Integer.parseInt(st.nextToken());
                dp[i][j][0] = dp[i][j][1] = dp[i][j][2] = INF;
            }
        }

        System.out.println(getMaxValue(N-1, M-1, 0));
    }

    private static boolean isValid(int y, int x) {
        return (y>=0 && y<N) && (x>=0 && x<M);
    }

    private static int getMaxValue(int y, int x, int dIdx) {
        if(y==0 && x==0) return map[0][0];
        if(dp[y][x][dIdx] != INF) return dp[y][x][dIdx];

        int maxPrevValue = INF;

        isVisit[y][x] = true;
        for(int i=0; i<3; ++i) {
            int ny = y+dirs[i][0];
            int nx = x+dirs[i][1];

            if(!isValid(ny,nx) || isVisit[ny][nx]) continue;
            maxPrevValue = Math.max(maxPrevValue, getMaxValue(ny, nx, i));
        }

        isVisit[y][x] = false;
        return dp[y][x][dIdx] = (maxPrevValue+map[y][x]);
    }
}
