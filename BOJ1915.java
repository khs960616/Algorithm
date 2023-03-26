import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

/*
  https://www.acmicpc.net/problem/1915
  가장 큰 정사각형 
  ---
  누적합 형태로 시간복잡도를 줄이려고 시도한 풀이.
  코드 자체는 통과하였으나, 효율적이지 못함
  
  dp를 사용해서 
  if(arr[i][j] == 1) dp[i][j] = Math.min(dp[i-1][j-1], Math.min(dp[i-1][j], dp[i][j-1])) + 1
  형태로 자기 자신의 왼쪽, 위쪽, 왼쪽 위 대각선 방향만을 체크하며, 값을 갱신하는게 훨씬 빠르고 좋은 풀이.
*/
public class BOJ1915 {

    private static int N, M;
    private static int[][] arr;
    private static int[][] calcSum;

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());

        arr = new int[N][M];
        for(int i=0; i<N; ++i) {
            String s = br.readLine();
            for(int j=0; j<M; ++j) {
                arr[i][j] = (s.charAt(j) - '0');
            }
        }

        calcSum = new int[N+1][M+1];
        for(int i=1; i<=M; ++i) {
            calcSum[1][i] = (calcSum[1][i-1] + arr[0][i-1]);
        }

        for(int i=1; i<=N; ++i) {
            calcSum[i][1] = (calcSum[i-1][1] + arr[i-1][0]);
        }

        for(int i=2; i<=N; ++i) {
            for(int j=2; j<=M; ++j) {
                calcSum[i][j] = (calcSum[i-1][j]+calcSum[i][j-1]+arr[i-1][j-1]-calcSum[i-1][j-1]);
            }
        }

        int answer = 0;
        for(int i=0; i<N; ++i) {
            for(int j=0; j<M; ++j) {
                if(arr[i][j] == 0) continue;
                answer = Math.max(answer, getMaxSize(i, j, 1));
            }
        }
        System.out.println(answer);
    }

    private static boolean isValid(int y, int x) {
        return (y>=0 && y<=N) && (x>=0 && x<=M);
    }

    private static int getMaxSize(int startY, int startX, int size) {
        int ret = (int) Math.pow(size, 2);

        int targetY = startY+size;
        int targetX = startX+size;
        if(!isValid(targetY, targetX)) return (size-1)*(size-1);

        int currentAreaSum = calcSum[targetY][targetX] - calcSum[targetY][startX] - calcSum[startY][targetX] + calcSum[startY][startX];
        if(currentAreaSum != size*size) return (size-1)*(size-1);

        ret = Math.max(ret, getMaxSize(startY, startX, size+1));
        return ret;
    }
}
