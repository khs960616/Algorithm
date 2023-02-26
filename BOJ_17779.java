import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

/*
    https://www.acmicpc.net/problem/17779
    게리맨더링2
    구현, 시뮬레이션 
    --
    1. 모든 좌표를 기준점으로 삼고 게리맨더링 지역으로 쪼갠다.
       ->  주어진 기준점에 대해 다음의 조건에 만족하는 모든 d1, d2에 대해 시뮬레이션 한다. 
           (d1, d2 ≥ 1, 1 ≤ x < x+d1+d2 ≤ N, 1 ≤ y-d1 < y < y+d2 ≤ N)
    
    2. 5번 영역의 경우 시작점을 기준으로 d1값 만큼 왼쪽 시작 범위가 1씩 감소하다, 증가하고, 오른쪽 시작 범위는 d2값 만큼 증가하다 감소하는 특성이 있다.  
       이를 이용해 5번 영역을 구하면서 방문 여부를 표시한다.
       
    3. 5번 영역을 구하며 방문 여부를 표시해두면, 1,2,3,4번 영역은 단순히 주어진 구간에서 방문하지 않은 노드들의 합을 구하므로 단순화가 가능해진다. 
*/
public class BOJ_17779 {

    private static int[][] populations;
    private static int N;

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        N = Integer.parseInt(br.readLine());
        populations = new int[N+1][N+1];
        for(int i=1; i<=N; ++i) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            for(int j=1; j<=N; ++j) {
                populations[i][j] = Integer.parseInt(st.nextToken());
            }
        }

        int answer = Integer.MAX_VALUE;
        for(int i=1; i<=N; ++i) {
            for(int j=1; j<=N; ++j) {
                answer = Math.min(answer, getAreaPopulationDiff(i, j));
            }
        }
        System.out.println(answer);
    }

    private static int getAreaPopulationDiff(int x, int y) {
        int ret = Integer.MAX_VALUE;
        for(int d1=1; d1<=y-1; ++d1) {
            for(int d2=1; d2<=N-y; ++d2) {
                if(N-x < d1+d2) continue;
                ret = Math.min(ret, simulation(x, y, d1, d2));
            }
        }
        return ret;
    }

    private static int simulation(int x, int y, int d1, int d2) {
        boolean[][] isVisited = new boolean[N+1][N+1];

        int area = 0;
        int left = y, right = y;
        int leftBase=  d1, rightBase= d2;
        for(int i=x; i<=x+d1+d2; ++i) {
            for(int j=left; j<=right; ++j) {
                isVisited[i][j] = true;
                area += populations[i][j];
            }

            if(leftBase > 0) {
                left--;
                leftBase--;
            } else {
                left++;
            }
            if(rightBase > 0) {
                right++;
                rightBase--;
            } else {
                right--;
            }
        }

        int[][] dx = {{1, x+d1-1}, {1, x+d2}, {x+d1, N}, {x+d2+1, N}};
        int[][] dy = {{1, y}, {y+1, N}, {1, y-1-d1+d2}, {y-d1+d2, N}};
        int minArea = area, maxArea = area;
        for(int i=0; i<4; ++i) {
            area = getAreaSum(isVisited, dx[i][0], dy[i][0], dx[i][1], dy[i][1]);
            minArea = Math.min(minArea, area);
            maxArea = Math.max(maxArea, area);
        }
        return maxArea - minArea;
    }

    private static int getAreaSum(boolean[][] isVisited, int startX, int startY, int endX, int endY) {
        int ret = 0;
        for(int i=startX; i<=endX; ++i) {
            for(int j=startY; j<=endY; ++j) {
                if(isVisited[i][j]) continue;
                isVisited[i][j] = true;
                ret += populations[i][j];
            }
        }
        return ret;
    }
}
