import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;
import java.util.stream.Collectors;

/*
  https://www.acmicpc.net/problem/1114
  통나무 자르기 
  파라메트릭 서치
  ---
  구하고자 하는 것 : 통나무의 최대 길이의 최솟값 
  -> 길이가 L인 통나무를 최대 C번 잘랐을 때, 모든 나무 도막이 주어진 길이 minLength보다 작거나 같을 수 있는가? (결정 문제로 바꾸기)
  
*/
public class BOJ_1114 {

    private static int L, K, C;
    private static List<Integer> cuttingPoints = new ArrayList<>();

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        L = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());
        C = Integer.parseInt(st.nextToken());

        st = new StringTokenizer(br.readLine());
        for(int i=0; i<K; ++i) {
            cuttingPoints.add(Integer.parseInt(st.nextToken()));
        }
        cuttingPoints = cuttingPoints.stream().distinct().sorted().collect(Collectors.toList());

        int left = 1, right = L; // 탐색의 범위 결정 : 나무 도막의 길이는 최소 1,  최대 L

        int[] answer = new int[2];  // answer[0] : 나무도막의 길이,  answer[1] : 처음 자른 위치

        while(left <= right) {
            int mid = (left+right)/2;
            int result = getCutInfo(mid);

            if(result == 0) { // 모든 나무 도막의 길이가 현재의 mid값보다 작지 않다면, 탐색의 범위를 큰쪽으로 옮겨 mid값을 키워줘야한다.
                left = mid+1;
            } else {
                right = mid-1;
                answer[0] = mid;
                answer[1] = result;
            }
        }

        System.out.println(answer[0] + " " + answer[1]);
    }
    
    // 처음 자른 위치가 가장 작은 것을 우선으로 출력해야한다.
    // 항상 minLength보다 길기 전까지는 자르지 않으므로, 왼쪽부터 자르기 시작하는 경우 항상 최적값을 보장하지 않는다. -> 오른쪽 부터 자르기 시작해야한다. 
    private static int getCutInfo(int minLength) {
        int ret = 0;
        int last = L, cnt = 0;

        int len = cuttingPoints.size();
        for(int i=len-1; i>=0; --i) {
            int cur = cuttingPoints.get(i);
            // last-cur : 현재까지 cutting points를 기준으로 자른 누적된 나무도막의 길이
            if(last-cur > minLength) {
                if(i==len-1) return 0;
                int prev = cuttingPoints.get(i+1);
                if(prev - cur > minLength) return 0;  // prev - cur : 현재 나무도막의 길이가 minLength보다 크면, 모든 나무 도막이 minLength보다 작아질 수 없다.

                cnt++;
                last = ret = prev;
            }
            if(cnt >= C) break;
        }

        if(cnt < C) ret = cuttingPoints.get(0);

        return ret > minLength ? 0 : ret;
    }
}
