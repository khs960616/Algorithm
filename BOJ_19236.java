import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;

/*
  https://www.acmicpc.net/problem/19236
  청소년 상어
  ---
  구현, 시뮬레이션
*/
public class BOJ_19236 {

    private static int[][] dirs = { {-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}};
    private static int answer = Integer.MIN_VALUE;

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int[][] grid = new int[4][4];
        List<Fish> origin = new ArrayList<>();

        for(int i=0; i<4; ++i) {
            int[] input = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            for(int j=0; j<8; j+=2) {
                Fish f = new Fish(i, j/2, input[j], input[j+1]-1);
                origin.add(f);
                grid[i][j/2] = f.number;
            }
        }

        Fish shark = origin.get(0);
        shark.isShark = true;
        origin.sort(Comparator.comparingInt(f -> f.number));
        br.close();

        simulation(grid, origin, shark.number, 15);
        System.out.println(answer);
    }

    private static void simulation(int[][] grid, List<Fish> fish, int cost, int remain) {
        if(remain == 0) {
            answer = Math.max(answer, cost);
            return;
        }

        int[][] copyGrid = new int[4][];
        for(int i=0; i<4; ++i) copyGrid[i] = grid[i].clone();
        List<Fish> copyFishList = new ArrayList<>();
        for(Fish f: fish) copyFishList.add(new Fish(f));

        Fish shark = null;
        for(Fish f: copyFishList) {
            if(f.isShark) {
                shark = f;
                continue;
            }
            if(f.isDie) continue;
            int movDir = f.getMoveDir(copyGrid, copyFishList);
            f.move(movDir, copyGrid, copyFishList);
        }

        int ny = shark.y + dirs[shark.dIdx][0], nx = shark.x + dirs[shark.dIdx][1];
        int originY = shark.y, originX = shark.x, originDir = shark.dIdx;

        while(isValid(ny, nx)) {
            int target = copyGrid[ny][nx];
            if(target != -1) {
                Fish f = copyFishList.get(target-1);
                f.isDie = true;
                copyGrid[ny][nx] = shark.number;
                copyGrid[shark.y][shark.x] = -1;
                shark.y = ny; shark.x = nx; shark.dIdx = f.dIdx;

                simulation(copyGrid, copyFishList, cost+f.number, remain - 1);

                copyGrid[ny][nx] = target;
                copyGrid[originY][originX] = shark.number;
                shark.y = originY; shark.x = originX; shark.dIdx = originDir;
                f.isDie = false;
            }
            ny += dirs[shark.dIdx][0];
            nx += dirs[shark.dIdx][1];
        }
        answer = Math.max(answer, cost);
    }

    private static boolean isValid(int y, int x) {
        return (y>=0 && y<4) && (x>=0 && x<4);
    }

    static class Fish {
        int y, x, number, dIdx;
        boolean isShark, isDie;

        Fish(int y, int x, int number, int dIdx) {
            this.y = y;
            this.x = x;
            this.number = number;
            this.dIdx = dIdx;
        }

        Fish(Fish f) {
            this.y = f.y;
            this.x = f.x;
            this.number = f.number;
            this.dIdx = f.dIdx;
            this.isShark = f.isShark;
            this.isDie = f.isDie;
        }

        public int getMoveDir(int[][] grid, List<Fish> fish) {
            for(int i=this.dIdx; i<this.dIdx+8; ++i) {
                int ny = this.y + dirs[i%8][0];
                int nx = this.x + dirs[i%8][1];

                if(!isValid(ny, nx)) continue;
                if(grid[ny][nx] != -1 && fish.get(grid[ny][nx]-1).isShark) continue;
                return i%8;
            }
            return -1;
        }

        public void move(int moveDir, int[][] grid, List<Fish> fish) {
            if(moveDir == -1) return;

            int ny = this.y + dirs[moveDir][0];
            int nx = this.x + dirs[moveDir][1];
            if(grid[ny][nx] != -1) {
                Fish swapTarget = fish.get(grid[ny][nx]-1);
                swapTarget.y = this.y;
                swapTarget.x = this.x;
                grid[this.y][this.x] = swapTarget.number;
            } else {
                grid[this.y][this.x] = -1;
            }

            this.y = ny;
            this.x = nx;
            this.dIdx = moveDir;
            grid[this.y][this.x] = this.number;
        }
    }
}
