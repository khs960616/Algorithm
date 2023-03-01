import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;

/*
  https://www.acmicpc.net/status?user_id=hongk&problem_id=20055&from_mine=1
  컨베이어 벨트 위의 로봇
  --
  구현, 시뮬레이션 
*/
public class BOJ_20055_컨베이어벨트 {

    private static int zeroCnt;
    private static int N, K;
    private static List<Belt> belts = new ArrayList<>();
    private static Queue<Robot> robots = new LinkedList<>();

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        N = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());

        st = new StringTokenizer(br.readLine());
        for(int i=0; i<(N<<1); ++i) {
            belts.add(new Belt(Integer.parseInt(st.nextToken())));
        }

        int turn = 0;
        while(zeroCnt < K) {
            turn++;
            beltsRotate();

            int rSize = robots.size();
            for(int i=0; i<rSize; ++i) {
                Robot r = robots.poll();
                if(r.moveIfAbsent()) robots.add(r);
            }

            if(belts.get(0).durability == 0) continue;

            Robot r = new Robot(0);
            belts.get(0).robot = r;
            robots.add(r);
            if(--belts.get(0).durability == 0) ++zeroCnt;
        }

        System.out.println(turn);
    }

    private static void beltsRotate() {
        Collections.rotate(belts, 1);
        belts.forEach(Belt::move);
    }

    static class Robot {
        int position;

        boolean moveIfAbsent() {
            Belt current = belts.get(this.position);
            Belt nextBelts = belts.get((this.position+1)%(N<<1));
            if(nextBelts.robot != null || nextBelts.durability == 0) return true;

            this.position = (this.position+1) % (N<<1);
            current.robot = null;
            if(--nextBelts.durability == 0) zeroCnt++;

            if(this.position != N-1) nextBelts.robot = this;
            return (this.position != N-1);
        }

        Robot(int position) {
            this.position = position;
        }
    }

    static class Belt {
        int durability;
        Robot robot;

        Belt(int durability) {
            this.durability = durability;
        }

        void move() {
            if(this.robot != null) {
                robot.position = (robot.position+1) % (N<<1);
                if(robot.position == N-1) {
                    robots.remove(robot);
                    this.robot = null;
                }
            }
        }
    }
}
