import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
/*
  https://www.acmicpc.net/problem/2239
  스도쿠
  ---
  시뮬레이션 
  1. 빈 칸을 모두 저장해놓는다.
  2. 빈 칸에 대해서 들어갈 수 있는 모든 숫자를 조합하며, 맨 처음 정답이 되는 케이스를 출력한다. 
*/
public class Main {

    private static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    private static int[][] sudoku = new int[9][9];
    private static List<Space> emptySpace = new ArrayList<>();
    private static int spaceCnt = 0;
    private static boolean flag = false;

    public static void main(String[] args) throws Exception {
        for(int i=0; i<9; ++i) {
            String s = br.readLine();
            for(int j=0; j<9; ++j) {
                sudoku[i][j] = s.charAt(j)-'0';
                if(sudoku[i][j] == 0) {
                    emptySpace.add(new Space(i, j));  
                }
            }
        }
        spaceCnt = emptySpace.size();
        simulation(0);
    }

    private static void simulation(int idx) {
        if(flag) return;
        if(idx == spaceCnt) {
            flag = true;
            StringBuilder sb = new StringBuilder();
            for(int i=0; i<9; ++i) {
                for(int j=0; j<9; ++j) {
                    sb.append(sudoku[i][j]);
                }
                sb.append('\n');
            }
            System.out.println(sb.toString());
            return;
        }

        Space s = emptySpace.get(idx);
        boolean[] isUsed = checkPrevUsedNumber(s);
      
        // emptySpace에 원소를 insert할 때 배열의 왼쪽 위 원소부터 오른쪽 아래 원소까지 넣었으므로, 자리 수가 큰 수부터 시뮬레이션하게 된다.
        // 또한 해당 반복문에서 작은 숫자를 먼저 넣어보며 시뮬레이션 하므로 사전순으로 앞선, 작은 숫자부터 출력하게된다. 
        for(int i=1; i<10; ++i) {
            if(isUsed[i]) continue;
            sudoku[s.y][s.x] = i;
            simulation(idx+1);
            sudoku[s.y][s.x] = 0;
        }
    }

    private static boolean[] checkPrevUsedNumber(Space s) {
        boolean[] isUsed = new boolean[10];

        for(int i=1; i<9; ++i) {
            int ny = (s.y + i) % 9;
            int nx = (s.x +i) % 9;
            isUsed[sudoku[ny][s.x]] = true;
            isUsed[sudoku[s.y][nx]] = true;
        }

        int startY = (s.y / 3)*3, startX = (s.x / 3)*3;
        for(int i=startY; i<startY+3; ++i) {
            for (int j = startX; j < startX + 3; ++j) {
                isUsed[sudoku[i][j]] = true;
            }
        }

        return isUsed;
    }

    static class Space {
        int y, x;

        Space(int y, int x) {
            this.y = y;
            this.x = x;
        }
    }
}
