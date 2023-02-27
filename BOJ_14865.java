import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Deque;
import java.util.List;
import java.util.Stack;
import java.util.StringTokenizer;

/*
  https://www.acmicpc.net/problem/14865
  곡선 자르기 
  구현, 자료구조
  --
  문제 조건 해석
  이 순서의 방향은 가장 왼쪽에 있는 수직 선분인 변을 볼 때 아래에서 위로 올라가는 방향이다 
  -> 입력이 가장 왼쪽 오른쪽 아래에 있는 좌표부터 주어진다는 의미가 아닌,
     입력으로 주어지는 좌표들이 반시계 방향으로 순서대로 진행되는 것을 보장한다는 의미
     
  1. 입력으로 들어오는 좌표들 중, 시작점의 y좌표는 항상 음수가 되도록 한다.
     (양수인 경우 x축 아래에 있는 봉우리와 구별하기가 어려워진다.)
     -> 입력을 deque에 저장해두면, 비교적 손쉽게 해당 기능을 구현할 수 있다.
     
  2. y좌표가 x축을 교차할 때마다 음수, 양수를 판별해서 봉우리 객체를 생성한다.
  
  3. 2번에서 만든 봉우리를 이용해, 봉우리 간의 포함 관계를 stack을 이용해서 시뮬레이션한다.
*/
public class BOJ_14865 {
	
	private static Deque<int[]> positions = new ArrayDeque<>();
	private static Stack<Integer> cross  = new Stack<>();
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int N = Integer.parseInt(br.readLine());
		
		for(int i = 0; i<N; ++i) {
			StringTokenizer st = new StringTokenizer(br.readLine());
			int[] pos = new int[2];
			pos[0] = Integer.parseInt(st.nextToken());
			pos[1] = Integer.parseInt(st.nextToken());
			positions.addLast(pos);
		}
		br.close();
		
		while(positions.peek()[1] > 0) {
			positions.addFirst(positions.pollLast());
		}
		positions.addLast(positions.getFirst().clone());
	
		
		List<Mountain> ml = new ArrayList<>();
		int prevY = positions.poll()[1];
		while(!positions.isEmpty()) {
			int[] current = positions.poll();
			boolean sameSign = (prevY>0 && current[1]>0) || (prevY<0 && current[1] <0);
			if(sameSign) continue;
			
			if(prevY < 0 && current[1] > 0) {
				if(cross.isEmpty()) cross.add(current[0]);
			} else if(prevY > 0 && current[1] < 0) {
				if(!cross.isEmpty()) {
					ml.add(new Mountain(cross.pop(), current[0]));
				}
			}
			prevY = current[1];
		}
		
		int mCnt = ml.size();
		int nonIncludeCnt = 0, includeCnt = 0;
		
		ml.sort((m1,m2)->m1.startX-m2.startX);
		Stack<Mountain> st = new Stack<>();
		for(int i=0; i<mCnt; ++i) {
			Mountain current = ml.get(i);
			
			int popCnt = 0;
			while(!st.isEmpty()) {
				Mountain top = st.peek();
				if(top.endX > current.endX) break;
				popCnt++;
				st.pop();
			}
			
			if(popCnt != 0) ++includeCnt;
			if(st.isEmpty()) ++nonIncludeCnt;
			st.add(current);
		}
		
		if(!st.isEmpty()) ++includeCnt;
		System.out.printf("%d %d", nonIncludeCnt, includeCnt);
	}
	
	static class Mountain {
		int startX, endX;
		Mountain(int x1, int x2) {
			this.startX = Math.min(x1, x2);
			this.endX = Math.max(x1, x2);
		}
	}
}
