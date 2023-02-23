import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

/*
  https://www.acmicpc.net/problem/17143
  낚시왕
  ---
  구현, 시뮬레이션 
  
  1. 상어의 이동방향이 좌우라면, 2(columnSize-1)만큼,   상하라면 2(rowSize-1)만큼 이동하고 나면 본래 자기 자신의 위치로 돌아온다.
     (이 부분에서 위치만 그대로고 방향은 반대방향을 바라보는줄 알고 잘못짜서 오류가 발생했었음)
     이런식으로 이동 횟수를 최소화한 뒤, 남은 횟수만큼 이동하면 된다.
     
  2. 낚시꾼이 상어를 잡는 것은 각 column별로 상어의 row값 기준 min heap을 만들어서 해결하였다.
  
  3. 상어가 합쳐지는 것은 (x축, y축) 좌표를 기준으로 정렬하되, 동일한 좌표인 경우 z값 내림차순으로 정렬한다.
     이렇게 한번 정렬하고 순차적으로 탐색하게되면 nlogn 스케일로 모든 경우를 탐색할 수 있다. (처음에 이부분 n^2 으로 짜서 시간초과났었음)
*/
public class boj17143 {

    private static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    private static int rowSize, columnSize, m, inplaceR, inplaceC;
    private static PriorityQueue<Shark> grid[];
    private static List<Shark> sharks = new ArrayList<>();

    public static void main(String[] args) throws Exception {
        int[] tmp = read();
        rowSize = tmp[0]; columnSize = tmp[1]; m = tmp[2];
        grid = new PriorityQueue[columnSize+1];
        for(int i=1; i<=columnSize; ++i) {
            grid[i] = new PriorityQueue<>(Comparator.comparingInt(e -> e.r));
        }

        inplaceR = (rowSize-1) << 1; inplaceC = (columnSize-1) << 1;
        for(int i=0; i<m; ++i) {
            Shark s = new Shark(read());
            sharks.add(s);
            grid[s.c].add(s);
        }

        int pos = 0, answer = 0;
        while(pos<columnSize) {
            ++pos;
            if(!grid[pos].isEmpty()) {
                Shark catchedShark = grid[pos].poll();
                answer += catchedShark.z;
                sharks.remove(catchedShark);
            }

            for(int i=1; i<=columnSize; ++i) grid[i].clear();
            sharks.forEach(Shark::move);
            merge();
        }

        System.out.println(answer);
    }

    private static void merge() {
        int size = sharks.size();
        if(size == 0) return;

        List<Shark> ret = new ArrayList<>();
        Collections.sort(sharks, (e1, e2)-> {
            if(e1.r == e2.r  && e1.c == e2.c) return e2.z - e1.z;
            if(e1.r == e2.r) return e1.c - e2.c;
            return e1.r - e2.r;
        });

        Shark prevShark = sharks.get(0);
        ret.add(prevShark);
        grid[prevShark.c].add(prevShark);

        for(int i=1; i<size; ++i) {
            Shark currentShark = sharks.get(i);
            if(prevShark.r == currentShark.r && prevShark.c == currentShark.c) continue;

            ret.add(currentShark);
            grid[currentShark.c].add(currentShark);
            prevShark = currentShark;
        }
        sharks = ret;
    }

    private static int[] read() throws IOException {
        return Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
    }

    static class Shark {
        int r, c, s, d, z;

        Shark(int[] io) {
            this.r = io[0];
            this.c = io[1];
            this.s = io[2];
            this.d = io[3];
            this.z = io[4];

            int baseInfo = (d<3) ? inplaceR : inplaceC;
            this.s %= baseInfo;
        }

        void convertDir() {
            int add = (this.d % 2 == 0) ? -1 : 1;
            this.d += add;
        }

        void move() {
            int moveAmount = this.s;
            while(true) {
                int addValue = 0;
                switch(this.d) {
                    case 1:
                        addValue = Math.min(moveAmount, this.r-1);
                        this.r -= addValue;
                        break;
                    case 2:
                        addValue = Math.min(moveAmount, rowSize-this.r);
                        this.r += addValue;
                        break;
                    case 3:
                        addValue = Math.min(moveAmount, columnSize-this.c);
                        this.c += addValue;
                        break;
                    default:
                        addValue = Math.min(moveAmount, this.c-1);
                        this.c -= addValue;
                        break;
                }

                moveAmount -= addValue;
                if(moveAmount == 0) break;
                convertDir();
            }
        }
    }
}
