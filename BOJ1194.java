import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

/*
  https://www.acmicpc.net/problem/1194
  달이 차오른다, 가자.
  --
  비트마스킹 + bfs
*/
class BOJ1194 {
	
	private static int N, M;
	private static int[][] dirs = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };
	private static String[] map;
	
	public static void main(String args[]) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		map = new String[N];
		
		int startY = 0, startX = 0;
		// 알파벳 'a', 'b', 'c', 'd', 'e', 'f'
		for(int i=0; i<N; ++i) {
			map[i] = br.readLine();
			for(int j=0; j<M; ++j) {
				if(map[i].charAt(j) == '0') {
					startY = i;
					startX = j;
				}
			}
		}
		
		// a,b,c,d,e,f
		boolean[][][] isVisited = new boolean[N][M][(1<<6)];
		Queue<int[]> q = new LinkedList<>();
		q.add(new int[] {startY, startX, 0, 0});  
		isVisited[startY][startX][0] = true;
		
		while(!q.isEmpty()) {
			int[] info = q.poll();
			
			if(map[info[0]].charAt(info[1]) == '1') {
				System.out.print(info[3]);
				return;
			}
			
			for(int[] dir: dirs) {
				int ny = info[0] + dir[0];
				int nx = info[1] + dir[1];
				
				if(!isValid(ny, nx)) continue;
				
				char c = map[ny].charAt(nx);
				if(c=='#') continue;
				int state = info[2];
				// 문 or 열쇠
				if(Character.isAlphabetic(c)) {
					if(Character.isUpperCase(c)) {
						if((state & (1<<(c-'A'))) == 0) continue;
					} else {
						state |= (1<<(c-'a'));
					}
				}
				
				if(isVisited[ny][nx][state]) continue;
				isVisited[ny][nx][state] = true;
				q.add(new int[] {ny, nx, state, info[3]+1});
			}
		}
		
		System.out.println("-1");
		return;
	}
	
	private static boolean isValid(int y, int x) {
		return (y>=0 && y<N) && (x>=0 && x<M);
	}
}
