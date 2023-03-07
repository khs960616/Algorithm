import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

/*
https://www.acmicpc.net/problem/1030
프렉탈평면
분할정복, 백트래킹
---
분할정복을 사용하는 것은
다른 프렉탈과 비슷하지만, 입력으로 주어지는 크기가 크기 때문에
프렉탈 전체를 메모리에 저장하려하면 메모리 초과,
또한 백트래킹 기저 조건을 제대로 추가해주지 않으면 시간초과를 겪게된다. 
*/
public class Main_1030 {
	
	private static int s, N, K, R1, R2, C1, C2; 
	private static int[][] grid;
	private static int MAX_SIZE = 0;
	
	public static void main(String[] args) throws Exception {
		 input();
		 makeFractal(0, 0, MAX_SIZE, 0);
		 StringBuilder sb = new StringBuilder();
		 
		 for(int i=0; i<=R2-R1; ++i) {
			 for(int j=0; j<=C2-C1; ++j) {
				 sb.append(grid[i][j]);
			 }
			 sb.append('\n');
		 }
		 System.out.println(sb.toString());
	}
	
	private static void input() throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		s = Integer.parseInt(st.nextToken());
		N = Integer.parseInt(st.nextToken());
		K = Integer.parseInt(st.nextToken());
		R1 = Integer.parseInt(st.nextToken());
		R2 = Integer.parseInt(st.nextToken());
		C1 = Integer.parseInt(st.nextToken());
		C2 = Integer.parseInt(st.nextToken());
		br.close();
		
		MAX_SIZE = (int)Math.pow(N, s);
		grid = new int[R2-R1+1][C2-C1+1];
	}
	

	
	private static void makeFractal(int startY, int startX, int size, int prevType) {
		if(startY > R2 || startX > C2) return;  // 기저로 추가하지 않으면 시간 초과 
		if(startY+size < R1 || startX+size < C1) return;  // 기저로 추가하지 않으면 시간 초과 
		if(prevType == 1) {
			int sy = Math.max(0, startY - R1), ey = Math.min(startY - R1 + size, R2-R1+1);
			int sx = Math.max(0, startX - C1), ex = Math.min(startX - C1 + size, C2-C1+1);
			
			for(int i=sy; i<ey; ++i) {
				for(int j=sx; j<ex; ++j) {
					grid[i][j] = prevType;
				}
			}
			return;
		}
		if(size == 1) return;
		
		int prevBlockSize = size/N;
		int range = (N-K)/2 * prevBlockSize;
		
		for(int i=startY; i<startY+size; i+=prevBlockSize) {
			for(int j=startX; j<startX+size; j+=prevBlockSize) {
				int type = (((i>=startY+range) && (i<startY+size-range)) && ((j>=startX+range) && (j<startX+size-range))) ? 1 : 0;
				makeFractal(i, j, prevBlockSize, type);
			}
		}
	}
}
