package algorithm;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;

/*
  https://www.acmicpc.net/problem/23290
  마법사 상어와 복제 
  구현, 시뮬레이션
  --- 
  
*/
public class BOJ_23290 {
	
	private static int sharkY, sharkX, maxCost;
	private static int M, S;
	private static int[][] dirs = {{0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}};
	private static int[] convertDirs = {2, 0, 6, 4};
	private static int[] selectedDir = new int[3];
	private static Grid[][] origin = new Grid[4][4];
	
	public static void main(String[] args) throws Exception {
		input();
		for(int i=0; i<S; ++i) {
			Grid[][] copy = getCopyGrid();
			moveFish();
			maxCost = -1;
			boolean[][] isVisited = new boolean[4][4];
			getSharkPath("", isVisited, 0, sharkY, sharkX);
			moveShark();
			decrease();
			addCopyValue(copy);
		}
		
		int sum = 0;
		for(int i=0; i<4; ++i) {
			for(int j=0; j<4; ++j) {
				sum += origin[i][j].getTotalFishCnt();
			}
		}
		System.out.println(sum);
	}
	
	private static void moveFish() {
		Grid[][] copy = new Grid[4][4];
		for(int i=0; i<4; ++i) {
			for(int j=0; j<4; ++j) copy[i][j] = new Grid(origin[i][j].remainCnt);
		}
		
		for(int i=0; i<4; ++i) {
			for(int j=0; j<4; ++j) {
				for(int k=0; k<8; ++k) {
					if(origin[i][j].fishsCnt[k] == 0) continue;
					copy[i][j].fishsCnt[k] += origin[i][j].fishsCnt[k];
					for(int range=0; range<8; ++range) {
						int ny = i + dirs[(8+k-range)%8][0];
						int nx = j + dirs[(8+k-range)%8][1];
						if(!isValid(ny, nx) || origin[ny][nx].remainCnt > 0) continue;
						if(sharkY == ny && sharkX == nx) continue;
						
						copy[i][j].fishsCnt[k] -= origin[i][j].fishsCnt[k];
						copy[ny][nx].fishsCnt[(8+k-range)%8] += origin[i][j].fishsCnt[k];
						break;
					}
				}
			}
		}
		
		origin = copy;
	}
	
	private static void moveShark() {
		for(int i=0; i<3; ++i) {
			sharkY += dirs[selectedDir[i]][0];
			sharkX += dirs[selectedDir[i]][1];
			
			int exceptCnt = origin[sharkY][sharkX].getTotalFishCnt();
			if(exceptCnt != 0) {
				origin[sharkY][sharkX].clearCurrentGrid();
				origin[sharkY][sharkX].remainCnt = 3;
			}
		}
	}
	
	private static void getSharkPath(String s, boolean[][] isVisited, int cost, int pathY, int pathX) {
		if(s.length() == 3) {
			if(maxCost < cost) {
				maxCost = cost;
				for(int i=0; i<3; ++i) {
					selectedDir[i] = convertDirs[s.charAt(i)-'0'];
				}
			}
			return;
		}
		
		for(int i=0; i<4; ++i) {
			int ny = pathY + dirs[convertDirs[i]][0];
			int nx = pathX + dirs[convertDirs[i]][1];
			if(!isValid(ny,nx)) continue;
			
			int nextCost = cost;
			boolean flag = false;
			if(!isVisited[ny][nx]) {
				nextCost += origin[ny][nx].getTotalFishCnt();
				isVisited[ny][nx] = flag = true;
			}
			getSharkPath(s+i, isVisited, nextCost, ny, nx);
			if(flag) isVisited[ny][nx] = false;
		}
	}
	
	private static boolean isValid(int y, int x) {
		return (y>=0 && y<4) && (x>=0 && x<4);
	}
	
	private static void decrease() {
		for(int i=0; i<4; ++i) {
			for(int j=0; j<4; ++j) {
				if(origin[i][j].remainCnt != 0) --origin[i][j].remainCnt;
			}
		}
	}
	
	private static void addCopyValue(Grid[][] copy) {
		for(int i=0; i<4; ++i) {
			for(int j=0; j<4; ++j) {
				for(int k=0; k<8; ++k) {
					origin[i][j].fishsCnt[k] += copy[i][j].fishsCnt[k];
				}
			}
		}
	}
	
	private static void input() throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		
		M = Integer.parseInt(st.nextToken());
		S = Integer.parseInt(st.nextToken());
		
		for(int i=0; i<4; ++i) {
			for(int j=0; j<4; ++j) {
				origin[i][j] = new Grid();
			}
		}
		
		for(int i=0; i<M; ++i) {
			st = new StringTokenizer(br.readLine());
			origin[Integer.parseInt(st.nextToken())-1][Integer.parseInt(st.nextToken())-1].fishsCnt[Integer.parseInt(st.nextToken())-1]++;
		}
		
		st = new StringTokenizer(br.readLine());
		sharkY = Integer.parseInt(st.nextToken())-1;
		sharkX = Integer.parseInt(st.nextToken())-1;
	}
	
	private static Grid[][] getCopyGrid() {
		Grid[][] ret = new Grid[4][4];
		for(int i=0; i<4; ++i) {
			for(int j=0; j<4; ++j) {
				ret[i][j] = new Grid(origin[i][j].fishsCnt);
			}
		}
		return ret;
	}
	
	static class Grid {
		int[] fishsCnt = new int[8];
		int remainCnt;
		
		Grid() {};
		Grid(int[] cnt) {
			for(int i=0; i<8; ++i) {
				this.fishsCnt[i] = cnt[i];
			}
			remainCnt = 0;
		}
		Grid(int remainCnt) {
			this.remainCnt = remainCnt;
		}
		
		int getTotalFishCnt() {
			return Arrays.stream(fishsCnt).sum();
		}
		
		void clearCurrentGrid() {
			Arrays.fill(this.fishsCnt, 0);
		}
	}
}
