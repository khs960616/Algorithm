import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

/*
https://www.acmicpc.net/problem/19237
어른상어
구현, 시뮬레이션

*/
public class Main {
	
	private static Grid[][] grid;
	private static List<Shark> sharks = new ArrayList<>();
	private static int[][] dirs = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
	private static int N, M, K;
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		K = Integer.parseInt(st.nextToken());
	
		for(int i=0; i<M; ++i) sharks.add(new Shark(i));
	
		grid = new Grid[N][N];
		for(int i=0; i<N; ++i) {
			st = new StringTokenizer(br.readLine());
			for(int j=0; j<N; ++j) {
				grid[i][j] = new Grid();
				int value = Integer.parseInt(st.nextToken());
				if(value != 0) {
					grid[i][j].sharkNumber = value-1;
					grid[i][j].remainCnt = K;

					sharks.get(value-1).y = i;
					sharks.get(value-1).x = j;
				}
			}
		}
		
		st = new StringTokenizer(br.readLine());
		for(int i=0; i<M; ++i) sharks.get(i).dir = Integer.parseInt(st.nextToken())-1;
		for(int i=0; i<M; ++i) {
			Shark currentShark = sharks.get(i);
			for(int j=0; j<4; ++j) {
				st = new StringTokenizer(br.readLine());
				for(int k=0; k<4; ++k) {
					currentShark.moveInfo[j][k] = Integer.parseInt(st.nextToken())-1;
				}
			}
		}
		
		int answer = -1;
		for(int i=1; i<=1000; ++i) {
			sharks = getMoveResult();
			for(int j=0; j<N; ++j) Arrays.stream(grid[j]).forEach(Grid::decreaseRemainCnt);
			for(Shark s: sharks) {
				grid[s.y][s.x].sharkNumber = s.num;
				grid[s.y][s.x].remainCnt = K;
			}
			
			if(sharks.size() == 1) {
				answer = i;
				break;
			}
		}
		System.out.println(answer);
	}
	
	private static List<Shark> getMoveResult() {
		PriorityQueue<Shark>[][] pq = getEmptyPriorityQueue();
		for(Shark shark: sharks) {
			shark.move();
			pq[shark.y][shark.x].add(shark);
		}
		
		List<Shark> ret = new ArrayList<>();
		for(int i=0; i<N; ++i) {
			for(int j=0; j<N; ++j) {
				if(pq[i][j].isEmpty()) continue;
				ret.add(pq[i][j].poll());
			}
		}
		return ret;
	}
	
	private static PriorityQueue<Shark>[][] getEmptyPriorityQueue() {
		PriorityQueue<Shark>[][] ret = new PriorityQueue[N][N];
		for(int i=0; i<N; ++i) {
			for(int j=0; j<N; ++j) {
				ret[i][j] = new PriorityQueue<>((s1, s2)->s1.num - s2.num);
			}
		}
		return ret;
	}
	
	private static boolean isValid(int y, int x) {
		return (y>=0 && y<N) && (x>=0 && x<N);
	}
	
	static class Shark {
		int num, y, x, dir;
		int[][] moveInfo = new int[4][4];
		
		Shark(int num) {
			this.num = num;
		}
		
		public void move() {
			if(isMove(-1)) return;
			if(isMove(this.num)) return;
		}
		
		private boolean isMove(int baseNumber) {
			for(int dir: moveInfo[this.dir]) {
				int ny = this.y + dirs[dir][0];
				int nx = this.x + dirs[dir][1];
				
				if(!isValid(ny, nx)) continue;
				if(grid[ny][nx].sharkNumber == baseNumber) {
					this.y = ny;
					this.x = nx;
					this.dir = dir;
					return true;
				}
			}
			return false;
		}
	}
	
	static class Grid {
		int sharkNumber = -1;
		int remainCnt = 0;
		
		void decreaseRemainCnt() {
			if(sharkNumber == -1) return;
			if(--remainCnt == 0) sharkNumber = -1;
		}
	}
}
