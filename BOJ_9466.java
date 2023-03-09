import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

/*
  https://www.acmicpc.net/problem/9466
  텀 프로젝트
  dfs를 이용한 사이클 구하기 
  ---
  dfs를 이용해서 각 정점들을 순차적으로 방문한다.
  이 때 콜스택을 활용해서 각 정점이 두 가지 상태를 가지도록한다.
  1. "방문한 노드인가?"
  2. "해당 노드로 dfs를 호출한 함수가 종료되었는가?"
  
  dfs를 재귀적으로 호출하며 콜스택이 깊어지다가, 1번 조건은 만족하지만 2번 조건을 만족하지 못하는 경우, 현재 노드 -> 다음 노드로 가는 것이 사이클을 만듬을 알 수 있다.
  이 경우 dfs 호출의 시작점의 위치와 상관없이 각 정점별로 depth를 표시해주면, 사이클의 크기를 구할 수 있다. 
  ---
  고민중인 다른 방법 
  > 유니온파인드

  유니온파인드를 사용하면 사이클은 구할 수 있는데, 
  1
  5
  3  3  1  2  1
  이런 예제처럼, 실제 사이클을 이루는 노드에 다른 노드들이 붙어있는 경우, 실제 사이클을 이루는 노드들의 개수만 어떻게 추출해낼 수 있을지 고민중인데,
  현재까지 생각으로는 input이 사이클을 이루는 순서대로 들어온다는 제약조건을 걸지 않는 이상 불가능할 것 같음.
*/
public class BOJ_9466 {
    private static int[] edges;
    private static int[] depths;
    private static boolean[] isFinished;

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int T = Integer.parseInt(br.readLine());
        for(int tc=0; tc<T; ++tc) {
            int N = Integer.parseInt(br.readLine());
            edges = new int[N];

            int answer = N;
            StringTokenizer st = new StringTokenizer(br.readLine());
            for(int i=0; i<N; ++i) edges[i] = Integer.parseInt(st.nextToken())-1;

            depths = new int[N];
            isFinished = new boolean[N];

            for(int i=0; i<N; ++i) {
                if(depths[i] != 0) continue;
                answer -= dfs(i, 1);
            }
            System.out.println(answer);
        }

        br.close();
    }

    private static int dfs(int node, int cost) {
    	int ret = 0;
    	depths[node] = cost;
    	
    	if(depths[edges[node]] == 0) ret = dfs(edges[node], cost+1);
    	else if(!isFinished[edges[node]])ret = depths[node] - depths[edges[node]] + 1;
   
    	isFinished[node] = true;
    	return ret;
    }
}
