import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;

/*
  https://www.acmicpc.net/problem/1700
  멀티탭 스케쥴링
  그리디, Belady 페이징 교체 
*/
public class BOJ_1700 {

    public static void main(String[] args) throws Exception {

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        int N = Integer.parseInt(st.nextToken());
        int K = Integer.parseInt(st.nextToken());

        int[] jobSequences = new int[K];
        Queue[] jobQueue = new Queue[K+1];
        for(int i=1; i<K+1; ++i) jobQueue[i] = new LinkedList<Integer>();

        st = new StringTokenizer(br.readLine());
        for(int i=0; i<K; ++i) {
            jobSequences[i] = Integer.parseInt(st.nextToken());
            jobQueue[jobSequences[i]].add(i);
        }

        Map<Integer, Integer> caches = new HashMap<>();

        int answer = 0;
        for(int i=0; i<K; ++i) {
            if(caches.size() >= N && caches.get(jobSequences[i]) == null) {
                ++answer;
                Set<Integer> keySet = caches.keySet();

                int lastPeek = -1, jobNumber = -1;
                for(int key: keySet) {
                    int nextJob = caches.get(key);
                    if(nextJob > lastPeek) {
                        lastPeek = nextJob;
                        jobNumber = key;
                    }
                }
                caches.remove(jobNumber);
            }

            jobQueue[jobSequences[i]].poll();
            int next = jobQueue[jobSequences[i]].isEmpty() ? Integer.MAX_VALUE : (int) jobQueue[jobSequences[i]].peek();
            caches.put(jobSequences[i], next);
        }
        System.out.println(answer);
    }
}
