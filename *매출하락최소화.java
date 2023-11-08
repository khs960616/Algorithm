import java.util.*;
import java.io.*;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/72416
  2021 KAKAO BLIND RECRUITMENT
  매출 하락 최소화
  ---
  Tree DP

  1. input으로 주어진 links 배열을 트리 형태로 가공한다.
  2. 2차원 dp 배열을 선언한다.
     dp[i][0]: i번째 노드가 루트노드인 서브트리에서, i번째 노드가 워크샵에 참여하지 않는 경우의 부분 최적해
     dp[i][1] : i번째 노드가 루트노드인 서브트리에서, i번째 노드가 워크샵에 참여하는 경우 부분 최적해 

  3. 리프노드 정의 : 번호가 k번이라 하면, 이 때 dp[k][0] = 0 (자식 노드가 없으므로),  dp[k][1] = sales[k-1]; 이다.
  4. 자식노드들의 합 정의 : min(dp[자식노드번호][0], dp[자식노드들번호][1]) 의 총합 
  5. 점화식 정의 
     dp[i][1] = (i번쨰 노드의 자식노드들의 최적해의 합 + sales[i-1]);

     dp[i][0] = (i번쨰 노드들의 합 + @) 
    -> i번째 노드의 자식 노드를 k1, k2, ... kn이라하자. 

    1) dp[kn][0] > dp[kn][1] 가 포함되는 경우
       : kn번쨰 노드를 루트로 하는 서브트리는, 루트 노드를 포함하는 해가 부분 최적해이다. 
         이 때, i번째 노드 입장에서는 같은 그룹내에 존재하는 kn번째 노드가 포함되어있으므로, 더 이상 부분 최적해들 외의 노드를 추가할 필요가 없다. 따라서
         dp[i][0] = 자식 노드들의 합
    
    2) 포함되지 않는 경우
       : 이 경우, 자식노드들의 합에는, i번째 노드를 루트로하는 서브트리(그룹)의 어떠한 노드도 포함되지 않는 경우이다. 따라서 자식 노드들 중 최소한 하나는 선택해야한다. 
       
       이 때 자식 노드들의 정의를 생각해보면 min(dp[kn][0], dp[kn][1])의 총합이며, 모든 자식 노드들은 dp[kn][0] <= dp[kn][1] 이므로,
       자식노드들의 합 = dp[k1][0] + dp[k2][0] + .... + dp[kn][0] 이다.
       
       이때 자식 노드들 중, 부분 최적해가 아닌, 자식노드를 포함하도록 하는 경우 발생하는 손실은 dp[kn][1] - dp[kn][0] 이다.
       따라서 min(dp[kn][1]-dp[kn][0]) 값을 구하여,  자식 노드들의 합을 구하면,  i번째 그룹의 자식중 (k1~kn) 중 하나를 포함하는 해를 구할수 있다. 
*/

class Solution {

	private int[][] dp;
	private Node[] nodePool;

	public static void main(String[] args) {
		Solution s = new Solution();
		int answer = s.solution(
			new int[] {14, 17, 15, 18, 19, 14, 13, 16, 28, 17},
			new int[][] {{10, 8}, {1, 9}, {9, 7}, {5, 4}, {1, 5}, {5, 10}, {10, 6}, {1, 3}, {10, 2}});

		System.out.println(answer);
	}

	public int solution(int[] sales, int[][] links) {
		dp = new int[sales.length+1][2];
		nodePool = new Node[sales.length+1];

		for(int i=1; i<=sales.length; ++i) {
			nodePool[i] = new Node();
			nodePool[i].num = i;

			dp[i][0] = dp[i][1] = Integer.MAX_VALUE;
		}

		for(int[] link: links) {
			nodePool[link[0]].addChild(nodePool[link[1]]);
		}

		int answer = Math.min(getMinValue(sales, 1, 0), getMinValue(sales, 1, 1));
		return answer;
	}

	private int getMinValue(int[] sales, int i, int j) {
		if(dp[i][j] != Integer.MAX_VALUE) {
			return dp[i][j];
		}

		if(nodePool[i].child.size() == 0) {
			dp[i][1] = sales[i-1];
			dp[i][0] = 0;
			return dp[i][j];
		}

		boolean containChild = false;
		int sum = 0;
		int saveValue = Integer.MAX_VALUE;

		for(Node node: nodePool[i].child) {
			int ncrSum = getMinValue(sales, node.num, 0);
			int crSum = getMinValue(sales, node.num, 1);
			saveValue = Math.min(saveValue, crSum-ncrSum);
			if(ncrSum > crSum) {
				containChild = true;
			}
			sum += Math.min(ncrSum, crSum);
		}

		dp[i][j] = sum;
		if(j==1) {
			return dp[i][j]+=sales[i-1];
		}
		if(containChild) {
			return dp[i][j];
		}

		return dp[i][j]+=saveValue;
	}

	private class Node {
		private int num;
		private List<Node> child = new LinkedList<>();
		public void addChild(Node node) {
			child.add(node);
		}
	}
}
