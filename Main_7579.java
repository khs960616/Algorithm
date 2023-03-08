import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.StringTokenizer;

/*
https://www.acmicpc.net/problem/7579
앱
dp
---

일반적으로 냅색 문제는 
메모이제이션하는 배열을 다음의 형태로 정의한다 -> dp[i][j] : 아이템이 i개 있고, 가방의 무게 제한이 j일 때 얻을 수 있는 최대 이득

해당 문제에서는 아이템의 갯수는 작지만, j의 최댓값이 10,000,000으로 매우 크기 때문에 동일한 형태로 dp를 구성하면 메모리 초과가 발생한다.

따라서 조금 변형해서 
dp[i][j] : 앱이 i개 있고 코스트가 j까지 도달할 때, 확보할 수 있는 최대 메모리의 수로 구성하고,
dp[N-1][0] ~ dp[N-1][모든 코스트의 합] 까지 순차적으로 수행하며, 최초로 메모리가 M보다 크거나 같아지는 j값을 출력하면 된다.


*/
public class Main_7579 {
	
	private static List<App> apps = new ArrayList<>();
	private static int[][] dp;
	private static int N, M;
	private static int totalCost;
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		st = new StringTokenizer(br.readLine());
		for(int i=0; i<N; ++i) apps.add(new App(Integer.parseInt(st.nextToken())));
	
		st = new StringTokenizer(br.readLine());
		for(int i=0; i<N; ++i) {
			apps.get(i).restartCost = Integer.parseInt(st.nextToken());
			totalCost += apps.get(i).restartCost;
		}
		br.close();
		
		dp = new int[N][totalCost+1];
		for(int i=1; i<N; ++i) Arrays.fill(dp[i], Integer.MIN_VALUE);
		dp[0][apps.get(0).restartCost] = apps.get(0).allocatedAmount;
		
		for(int i=0; i<=totalCost; ++i) {
			if(getMaxMemory(N-1, i) >= M) {
				System.out.println(i);
				return;
			}
		}
	}
	
	private static int getMaxMemory(int idx, int cost) {	
		if(dp[idx][cost] != Integer.MIN_VALUE) return dp[idx][cost];
		
		dp[idx][cost] = 0;
		dp[idx][cost] = Math.max(dp[idx][cost], getMaxMemory(idx-1, cost));
		
		if(cost >= apps.get(idx).restartCost) {
			dp[idx][cost] = Math.max(dp[idx][cost], getMaxMemory(idx-1, cost-apps.get(idx).restartCost)+apps.get(idx).allocatedAmount);
		}
		return dp[idx][cost];
	}

	static class App {
		int allocatedAmount;
		int restartCost;
		
		App(int allocatedAmount) {
			this.allocatedAmount = allocatedAmount;
		}
	}
}
