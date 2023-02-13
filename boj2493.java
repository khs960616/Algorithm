import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.Stack;

/*
  https://www.acmicpc.net/problem/2493
  탑
  ---
  스택, 구현 
  
  1. stack에 탑을 순차적으로 넣는다.
  2. 자기 자신보다 높은 탑에 둘러쌓이는 경우, 더 이상 다른 어떤 탑으로도 레이저를 받지 못하기 때문에 stack에서 버린다. 
*/
public class Main {
	
	static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	static StringBuilder sb = new StringBuilder();
	
	public static void main(String[] args) throws Exception {
		int n = Integer.parseInt(br.readLine());
		int[] arr = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
		br.close();
		sb.append(0+" ");
		
		Stack<Pair> st = new Stack<>();
		st.add(new Pair(0, arr[0]));
		
		for(int i=1; i<arr.length; ++i) {
			int ret = -1;	
			while(!st.isEmpty()) {
				Pair p = st.peek();
				if(p.value >= arr[i]) {
					ret = p.idx;
					break;
				}
				st.pop();
			}
			
			ret = (ret == -1) ? 0 : ret+1;
			sb.append(ret + " ");
			st.add(new Pair(i, arr[i]));
		}
		System.out.println(sb.toString());
	}
	
	static class Pair {
		int idx;
		int value;
		
		public Pair(int idx, int value) {
			this.idx = idx;
			this.value = value;
		}
	}
}
