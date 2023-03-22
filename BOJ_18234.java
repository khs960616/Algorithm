import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

/*
https://www.acmicpc.net/problem/18234
당근 훔쳐먹기 
그리디
---
1)  주어진 조건 1 ≤ wi ≤ pi ≤ 100 에서,
    항상 영양제로 증가되는 양이 더 크며,  초기 당근의 값은 영양제로 인해 누적되는 양보다 클 수 없음을 알 수 있다.
    따라서 그리디 조건이 성립한다.
    
2) N보다 T가 큰 경우 (T-N) 만큼 당근을 먹지 않고 기다린다. (모든 당근은 누적했다가 먹는 것이, 새로 심는것보다 항상 더 큰 이득이므로)

3) N일동안  pi값이 작은 당근부터 순차적으로 먹는다. 

1시간
*/
public class BOJ_18234 {
	
	private static int N, T;
	private static int bias;
	private static PriorityQueue<long[]> pq = new PriorityQueue<>((e1,e2)->(int)(e1[1]-e2[1]));
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		T = Integer.parseInt(st.nextToken());
		
		bias = T-N-1;
		
		for(int i=0; i<N; ++i) {
			st = new StringTokenizer(br.readLine());
			pq.add(new long[] {Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken())});
		}
		
		long answer = 0;
		while(!pq.isEmpty()) {
			long[] carrot = pq.poll();
			bias++;
			answer = answer + carrot[0] + carrot[1]*bias;
		}
		System.out.println(answer);
	}
}
