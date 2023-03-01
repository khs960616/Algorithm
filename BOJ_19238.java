import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;

/*
  https://www.acmicpc.net/problem/19238
  스타트택시
  구현, 시뮬레이션, bfs
  ---
  시도하다 실패한 방법들 
  
  >> (1) 택시의 출발점으로부터 도달가능한 모든 노드들을 방문하며 cost를 저장
     >> 이후 각 grid에 도달가능한 cost끼리 사칙연산하면 누적합처럼 cost가 나올거라고 잘못 생각함
       >> 택시가 승객을 태우러 이동하게 되면, 매번 출발점이 달라지게 되기 때문에 초기 위치로부터의 거리를 이용하면 당연히 정상적이지 못한 결과가 나옴
       
  >> (2) 시뮬레이션마다 가까운 승객을 구하기위해서, 승객과 택시의 위치를 bfs를 통해 거리를 구하며, 거리가 가장 짧은 승객을 선택함
     (bfs가 너무 자주 호출되기 때문에 시간초과 오류 발생)
     
  >> (3) 각 승객 정보를 저장하고, 격자판에도 승객 정보가 저장된 인덱스를 저장하고, 가장 가까운 승객을 구할 때 bfs 1번만 호출해서 가장 가까운 승객의 정보를 구함
         이 때 문제에서 제시된 우선순위에 맞게 dirs = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}}; 형태 bfs를 돌리면 항상 최적해가 나올거라 생각했는데, 반례가 존재했음 
         // https://www.acmicpc.net/board/view/58232
         
         
  ----
  3번 과정에서 찾자마자 바로 리턴하지않고, 동일 거리에 존재하는 모든 승객의 x좌표, y좌표를 비교해서 리턴하여 성공
  
  핵심 로직 -> 승객의 출발점 위치를 격자판에 표시하게 되면, 승객마다 bfs를 돌릴 필요 없이 1번의 bfs만으로 연산이 줄어든다.
*/
public class BOJ_19238 {

    private static int N, M, K;
    private static int[][] grids;
    private static final int[][] dirs = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
    private static int taxiY, taxiX;
    private static Passenger[] pList;

    public static void main(String[] args) throws Exception {
        input();
        for(int i=0; i<M; ++i) {
            Passenger p = getPassenger();
            if(p == null) {
                System.out.println(-1);
                return;
            }

            grids[p.startY][p.startX] = 0;
            taxiY = p.startY; taxiX = p.startX;
            
            K -= p.cost;
            int movCost = calcMinDist(taxiY, taxiX, p.endY, p.endX);
            if(K < movCost) {
                System.out.println(-1);
                return;
            } else {
                K += movCost;
                taxiY = p.endY;
                taxiX = p.endX;
            }
        }
        System.out.println(K);
    }

    private static Passenger getPassenger() {
        boolean[][] isVisited = new boolean[N][N];
        Queue<int[]> q = new LinkedList<>();
        q.add(new int[] { 0, taxiY, taxiX });
        isVisited[taxiY][taxiX] = true;

        Passenger ret = null;
        while(!q.isEmpty()) {
            int[] info = q.poll();

            if(ret != null && ret.cost < info[0]) continue;
            if(grids[info[1]][info[2]] > 1) {
                int passengerIdx = grids[info[1]][info[2]]-2;
                pList[passengerIdx].cost = info[0];

                boolean isChange = (ret == null) || (pList[passengerIdx].startY < ret.startY) ||
                        ((pList[passengerIdx].startY == ret.startY) && (pList[passengerIdx].startX < ret.startX));
                if(isChange) {
                    ret = pList[passengerIdx];
                }
            }

            insertQueue(isVisited, q, info);
        }
        return ret;
    }

    private static int calcMinDist(int startY, int startX, int endY, int endX) {
        boolean[][] isVisited = new boolean[N][N];
        Queue<int[]> q = new LinkedList<>();
        q.add(new int[] { 0, startY, startX });
        isVisited[startY][startX] = true;

        while(!q.isEmpty()) {
            int[] info = q.poll();
            if(info[1] == endY && info[2] == endX) {
                return info[0];
            }

            insertQueue(isVisited, q, info);
        }
        return 0x3f3f3f3f;
    }

    private static boolean isValid(int y, int x) {
        return (y>=0 && y<N) && (x>=0 && x<N);
    }

    private static void insertQueue(boolean[][] isVisited, Queue<int[]> q, int[] info) {
        for (int[] dir : dirs) {
            int ny = info[1] + dir[0];
            int nx = info[2] + dir[1];
            if (!isValid(ny, nx) || grids[ny][nx] == 1 || isVisited[ny][nx]) continue;
            isVisited[ny][nx] = true;
            q.add(new int[]{info[0] + 1, ny, nx});
        }
    }

    private static void input() throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());

        grids = new int[N][N];
        for(int i=0; i<N; ++i) {
            st = new StringTokenizer(br.readLine());
            for(int j=0; j<N; ++j) {
                grids[i][j] = Integer.parseInt(st.nextToken());
            }
        }

        st = new StringTokenizer(br.readLine());
        taxiY = Integer.parseInt(st.nextToken()) - 1;
        taxiX = Integer.parseInt(st.nextToken()) - 1;

        pList = new Passenger[M];
        for(int i=0; i<M; ++i) {
            st = new StringTokenizer(br.readLine());
            int startY = Integer.parseInt(st.nextToken()), startX = Integer.parseInt(st.nextToken());
            pList[i] = new Passenger(startY, startX, Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken()));
            grids[startY-1][startX-1] = i+2;
        }
        br.close();
    }

    static class Passenger {
        int startY, startX, endY, endX, cost;
        Passenger(int sy, int sx, int ey, int ex) {
            this.startY = sy-1;
            this.startX = sx-1;
            this.endY = ey-1;
            this.endX = ex-1;
        }
    }
}
