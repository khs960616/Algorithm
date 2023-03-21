import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;

/*
  https://www.acmicpc.net/problem/22947
  실행시간
  위상정렬 + 조합
  --- 
  1. 첫 번쨰로 위상정렬을 실행하며 시작 노드와 마지막 실행 노드를 구한다.
  2. 조합을 이용해 (1)에서 구한 노드들을 제외한 노드에서 K개의 노드를 (단 K는 최대 3) 0으로 값을 바꾼다.
  3. (2)에서 변경한 cost로 1번의 위상정렬을 반복 수행하며 최소 cost를 구한다. 
*/
public class BOJ_22947 {

    static int N, M, K;
    static long answer = Long.MAX_VALUE;
    static int[] jobCost;
    static int[] inDegreeCnt;
    static int[] selectedIdx;
    static int startNode, endNode;
    static Map<Integer, List<Integer>> edgesInfo = new HashMap<>();

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());

        jobCost = new int[N];
        inDegreeCnt = new int[N];
        selectedIdx = new int[K];

        st = new StringTokenizer(br.readLine());
        for(int i=0; i<N; ++i) jobCost[i] = Integer.parseInt(st.nextToken());

        for(int i=0; i<M; ++i) {
            st = new StringTokenizer(br.readLine());
            int from = Integer.parseInt(st.nextToken())-1;
            int to = Integer.parseInt(st.nextToken())-1;
            inDegreeCnt[to] += 1;
            List<Integer> children = edgesInfo.getOrDefault(from, new ArrayList<>());
            children.add(to);
            edgesInfo.put(from, children);
        }

        for(int i=0; i<N; ++i) {
            if(inDegreeCnt[i] == 0) {
                startNode = i;
                break;
            }
        }
        getCost(inDegreeCnt.clone(), jobCost.clone());

        simulation(0, 0);
        System.out.println(answer);
    }

    private static void simulation(int idx, int cnt) {
        if(cnt == K) {
            int[] cost = jobCost.clone();
            for(int i=0; i<K; ++i) cost[selectedIdx[i]] = 0;
            answer = Math.min(answer, getCost(inDegreeCnt.clone(), cost));
            return;
        }

        for(int i=idx; i<N; ++i) {
            if(i==startNode || i==endNode) continue;
            selectedIdx[cnt] = i;
            simulation(i+1, cnt+1);
        }
    }

    private static long getCost(int[] inDegree, int[] cost) {
        long ret = 0;

        long[] maxDelayTime = new long[N];
        Queue<Integer> q = new LinkedList<>();
        q.add(startNode);

        while(!q.isEmpty()) {
            int node = q.poll();

            endNode = node;
            long nextDelayTime = maxDelayTime[endNode]+cost[endNode];

            ret = Math.max(ret, nextDelayTime);
            List<Integer> nodeList = edgesInfo.get(endNode);
            if(nodeList == null) continue;

            for(int c: nodeList) {
                maxDelayTime[c] = Math.max(maxDelayTime[c], nextDelayTime);
                if(--inDegree[c] == 0) q.add(c);
            }
        }
        return ret;
    }
}
