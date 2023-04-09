import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

/*
  https://www.acmicpc.net/problem/21944
  문제 추천 시스템 Version2 
  구현, 시뮬레이션, 자료구조 
  ---
  1. 번호, 난이도, 그룹을 멤버변수로 가지는 Class를 정의한다.
  
  2. 문제들을 저장할 자료 구조를 설계한다.
     2-1) 
      problems 배열
      -> 문제는 최대 100,000개 만큼 있으므로 크기 10만 짜리 배열을 선언한다. 해당 배열은 문제의 번호를 인덱스로 
         문제 객체에 접근하도록 도와주며, add, solve 함수를 최적화한다.
      
      2-2)
      우선순위큐 배열 4개를 선언한다.
      1) 문제의 난이도를 인덱스로 하는 우선순위큐 배열 2개 (문제의 번호 오름차순, 내림차순으로 정렬한다.
      2) 문제의 그룹을 인덱스로 하는 우선순위큐 배열 2개 (문제의 난이도, 문제의 번호) 순서쌍으로 오름차순, 내림차순 정렬
      
  3. 문제 조건에 맞게 시뮬레이션한다.
     solved 함수에서 특정 문제를 리스트에서 제거할때는 
     원래대로라면 총 5개의 래퍼런스를 끊어야한다. (배열, 우선순위큐 4개)
     그러나 우선순위큐는 항상 트리의 가장 맨 위의 원소에만 접근 가능하므로 lazy propagtion을 적용하여 문제를 해결한다. 
     
     problems배열에서 우선순위큐들이 래퍼런싱하고 있는 객체에 접근하여 해당 객체는 삭제된 객체임을 표시한다.
     이후 problems 배열에서 해당 객체에 대한 참조를 끊는다. 
     
     우선순위 큐에서 문제 조건에 맞게 원소들을 조회할때, 객체가 삭제된 객체라면 해당 객체는 연산에 반영하지 않고 버린다.
     -> 이렇게 하면 삭제 연산을 단순화할 수 있으며, 실제 우선순위큐에서 필요없는 객체가 참조될때만 제거할 수 있다. 
*/
public class Main {

    private static final int MAX_NUM = 100_001;
    private static int N, M;
    private static Problem[] problems = new Problem[MAX_NUM];

    private static PriorityQueue[][] groups, difficulties;

    static {
        groups = new PriorityQueue[101][2];
        difficulties = new PriorityQueue[101][2];

        for(int i=1; i<=100; ++i) {
            groups[i][0] = new PriorityQueue<Problem>((p1, p2)->{
                if(p1.difficulty == p2.difficulty) {
                    return p2.no - p1.no;
                }
                return p2.difficulty - p1.difficulty;
            });
            groups[i][1] = new PriorityQueue<Problem>((p1, p2)->{
                if(p1.difficulty == p2.difficulty) {
                    return p1.no - p2.no;
                }
                return p1.difficulty - p2.difficulty;
            });

            difficulties[i][0] = new PriorityQueue<Problem>((p1, p2)->p2.no - p1.no);
            difficulties[i][1] = new PriorityQueue<Problem>(Comparator.comparingInt(p -> p.no));
        }
    }

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;
        N = Integer.parseInt(br.readLine());
        for(int i=0; i<N; ++i) {
            st = new StringTokenizer(br.readLine());
            add(Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken()));
        }

        StringBuilder sb = new StringBuilder();
        M = Integer.parseInt(br.readLine());
        for(int i=0; i<M; ++i) {
            st = new StringTokenizer(br.readLine());
            String op = st.nextToken();
            int ret = 0;
            switch(op) {
                case "add":
                    add(Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken()));
                    break;
                case "solved":
                    solved(Integer.parseInt(st.nextToken()));
                    break;
                case "recommend":
                    ret = recommend(Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken()));
                    sb.append(ret).append('\n');
                    break;
                case "recommend2":
                    ret = recommend2(Integer.parseInt(st.nextToken()));
                    sb.append(ret).append('\n');
                    break;
                case "recommend3":
                    ret = recommend3(Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken()));
                    sb.append(ret).append('\n');
                    break;
            }
        }

        System.out.println(sb.toString());
    }

    private static void add(int p, int l, int g) {
        problems[p] = new Problem(p, l, g);
        for(int i=0; i<2; ++i) {
            groups[g][i].add(problems[p]);
            difficulties[l][i].add(problems[p]);
        }
    }

    private static void solved(int p) {
        problems[p].isDeleted = true;
        problems[p] = null;
    }

    private static int recommend(int g, int x) {
        int chkIdx = (x==1) ? 0 : 1;
        while(!groups[g][chkIdx].isEmpty()) {
            Problem p = (Problem) groups[g][chkIdx].peek();
            if(!p.isDeleted) return p.no;
            groups[g][chkIdx].poll();
        }
        return -1;
    }

    private static int recommend2(int x) {
        int addValue = x==1 ? -1 : 1;
        int startIdx = x==1 ? 100 : 1;
        int endIdx = x==1 ? 0 : 101;
        int chkIdx = x==1 ? 0 : 1;

        for(int i=startIdx; i!=endIdx; i+=addValue) {
            if(difficulties[i][chkIdx].isEmpty()) continue;
            else {
                while(!difficulties[i][chkIdx].isEmpty()) {
                    Problem p = (Problem) difficulties[i][chkIdx].peek();
                    if(!p.isDeleted) return p.no;
                    difficulties[i][chkIdx].poll();
                }
            }
        }
        return -1;
    }

    private static int recommend3(int x, int l) {
        if(x==1) {
            for(int i=l; i<=100; ++i) {
                if(difficulties[i][1].isEmpty()) continue;
                while(!difficulties[i][1].isEmpty()) {
                    Problem p = (Problem) difficulties[i][1].peek();
                    if(p.isDeleted) difficulties[i][1].poll();
                    else return p.no;
                }
            }
        } else {
            for(int i=l-1; i>0; --i) {
                if(difficulties[i][0].isEmpty()) continue;
                while(!difficulties[i][0].isEmpty()) {
                    Problem p = (Problem) difficulties[i][0].peek();
                    if(p.isDeleted) difficulties[i][0].poll();
                    else return p.no;
                }
            }
        }
        return -1;
    }

    private static class Problem {
        int no;         // P
        int difficulty; // L
        int group;      // G
        boolean isDeleted;

        Problem(int p, int l, int g) {
            this.no = p;
            this.difficulty = l;
            this.group = g;
            isDeleted = false;
        }
    }
}
