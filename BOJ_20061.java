import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

/*
  https://www.acmicpc.net/problem/20061
  모노미노도미노2
  구현, 시뮬레이션, 비트마스킹 
  ---
  아이디어 1)  6*4 배열, 4*6배열로 생각하는 것이 아닌 초록색보드, 파란색 보드 6*4 형태의 배열로 생각하고, 들어오는 input을 변형하자.
      
     - 문제를 관찰해보면, 두 보드의 모양과 수행하는 operation은 모두 동일하다. 따라서 두 보드 모두 6*4 형태로 만들면 하나의 함수로 처리가 가능해진다.
     - 두 보드의 차이가 나는 부분은 결국 빨간색 보드에 놓는 위치의 해석과 2번, 3번 타일이 들어올 때 두 보드에 다른 타입의 타일을 넣는 것으로 볼 수 있다. 
       1. 초록색보드에서 2타입의 타일은 파란색 보드의 입장에서는 3타입의 타일이다.
       2. 초록색보드에서 3타입의 타일은 파란색 보드 입장에서는 2타입의 타일이다.
       3. 6*4 형태로 생각해보면, 타일을 놓는 위치 중 y좌표에만 영향을 받고 x좌표는 이전 타일들이 쌓이는 것에 종속적이다.
          파란색보드도 6*4 형태로 생각해보면 결국  3-x를 y좌표로 입력 받는 것으로 볼 수 있다.
 
  아이디어 2) 비트마스킹을 활용하자.
      6*4형태의 배열에서 각 행을 비트마스킹을 이용하여, 타일이 있는 경우 1, 타일이 없는 경우 0으로 설정하면 다음과 같은 이점이 있다.
      1) 행이 가득찬 경우를 보고자한다면 4개의 비트가 모두 켜져있는 15라는 숫자와 비교하면 되며, 비어있는 경우는 0과 비교하면 된다.
      2) 각 행을 한칸씩 아래로 내리는 연산을 할 때 위에 있는 숫자를 대입하면 되므로 비교적 간단해진다. 
*/
public class BOJ_20061 {

    private static int[] greenZone = new int[6];
    private static int[] blueZone = new int[6];
    private static int IS_FULL_LINE = (1<<4)-1;

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int N = Integer.parseInt(br.readLine());

        int answer = 0;
        for(int i=0; i<N; ++i) {
            StringTokenizer st = new StringTokenizer(br.readLine());

            int tileType = Integer.parseInt(st.nextToken());
            int x = Integer.parseInt(st.nextToken()), y = Integer.parseInt(st.nextToken());
            answer += insertGrid(greenZone, y, tileType);

            int[] info = convertOperationInfo(x, tileType);
            answer += insertGrid(blueZone, info[0], info[1]);

            eraseSpecialRow(greenZone);
            eraseSpecialRow(blueZone);
        }

        System.out.println(answer);
        System.out.println(getTileCnt());
    }

    private static int insertGrid(int[] grid, int y, int tileType) {
        int ret = 0;
        int depth = getDepth(grid, y);
        if(tileType == 2) {
            depth = Math.min(depth, getDepth(grid, y+1));
        }

        grid[depth] |= (1<<(3-y));
        if(tileType == 2) {
            grid[depth] |= (1<<(2-y));
        } else if(tileType == 3) {
            grid[depth-1] |= (1<<(3-y));
        }

        int cnt = 0;
        for(int i=5; i>=0; --i) {
            if(grid[i] == IS_FULL_LINE) {
                ret++; cnt++;
                grid[i] = 0;
            } else {
                grid[i+cnt] = grid[i];
            }
        }
        return ret;
    }

    private static void eraseSpecialRow(int[] grid) {
        int cnt = 0;
        for(int i=0; i<2; ++i) {
            if(grid[i] != 0) ++cnt;
        }

        if(cnt != 0) {
            for(int i=5; i>=cnt; --i) {
                grid[i] = grid[i-cnt];
                grid[i-cnt] = 0;
            }
        }
    }

    private static int getDepth(int[] grid, int y) {
        for(int i=0; i<6; ++i) {
            if((grid[i] & (1<<(3-y))) != 0) return i-1;
        }
        return 5;
    }

    private static int[] convertOperationInfo(int x, int tileType) {
        int nextY = 3-x;
        int convertTileType = 1;
        if(tileType == 2) {
            convertTileType = 3;
        } else if(tileType == 3){
            nextY-=1;
            convertTileType = 2;
        }
        return new int[] {nextY, convertTileType}; // blue 입장에서 보는 y좌표, 타일의 타입
    }

    private static int getTileCnt() {
        int ret = 0;
        for(int i=0; i<6; ++i) {
            for(int j=0; j<4; ++j) {
                if((greenZone[i] & (1<<j)) != 0) ret++;
                if((blueZone[i] & (1<<j)) != 0) ret++;
            }
        }
        return ret;
    }
}
