import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;

/*
  https://www.acmicpc.net/problem/16946
  벽 부수고 이동하기 4 
  bfs, 자료구조
  --------------
  1. 연결된 0끼리 그룹을 동일한 그룹번호를 부여한다. (이 때 각 그룹별 사이즈를 hashmap을 이용해 기록)
  2. 벽을 순회하며 이동 가능한 주변 그룹의 사이즈를 더한다. 
*/
public class BOJ16946 {
	
	private static int inc = 2;
	private static int N, M;
	private static int[][] grid;
	private static int[][] answer;
	private static int[][] dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
	
	private static Map<Integer, Integer> groupInfo = new HashMap<>();
	private static List<int[]> blocks = new ArrayList<>();
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		grid = new int[N][M];
		answer = new int[N][M];
		
		for(int i=0; i<N; ++i) {
			char[] cs = br.readLine().toCharArray();
			for(int j=0; j<M; ++j) {
				grid[i][j] = (cs[j]-'0');
				if(grid[i][j] == 1) {
					blocks.add(new int[] {i, j});
				}
			}
		}
		
		for(int i=0; i<N; ++i) {
			for(int j=0; j<M; ++j) {
				if(grid[i][j] != 0) continue;
				bfs(i, j);
				inc++;
			}
		}
		
		for(int[] block: blocks) {
			int size = 1;
			Set<Integer> groupSet = new HashSet<>();
			
			for(int[] dir: dirs) {
				int ny = block[0] + dir[0];
				int nx = block[1] + dir[1];
				
				if(isValid(ny, nx) && grid[ny][nx] != 1 && !groupSet.contains(grid[ny][nx])) {
					groupSet.add(grid[ny][nx]);
					size+=groupInfo.get(grid[ny][nx]);
				}
			}
			answer[block[0]][block[1]] = (size % 10);
		}
		
		StringBuilder sb = new StringBuilder();
		for(int i=0; i<N; ++i) {
			for(int j=0; j<M; ++j) {
				sb.append(answer[i][j]);
			}
			sb.append('\n');
		}
		
		System.out.println(sb.toString());
	}
	
	private static boolean isValid(int y, int x) {
		return (y>=0  && y<N) && (x>=0 && x<M);
	}
	
	private static void bfs(int startY, int startX) {
		Queue<int[]> q = new LinkedList<>();
		q.add(new int[] {startY, startX});
		grid[startY][startX] = inc;
		
		int size = 0;
		while(!q.isEmpty()) {
			int[] info = q.poll();
			size++;
			
			for(int[] dir: dirs) {
				int ny = info[0] + dir[0];
				int nx = info[1] + dir[1];
				
				if(!isValid(ny, nx) || grid[ny][nx] != 0) continue;
				q.add(new int[] {ny, nx});
				grid[ny][nx] = inc;
			}
		}
		groupInfo.put(inc, size);
	}
}
