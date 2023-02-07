import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.Collections;
import java.util.LinkedList;
import java.util.List;

public class Boj17837 {
	
	private static int n,k;
	private static final Tile[][] board = new Tile[12][12]; 
	private static final Node[] nodes = new Node[10];
	private static final int[][] dirs = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
	
	public static void main(String[] args) throws IOException {
		init();
		
		for(int turn=1; turn<1001; turn++) {
			for(int i=0; i<k; ++i) {
				int ny = nodes[i].y + dirs[nodes[i].dir][0];
				int nx = nodes[i].x + dirs[nodes[i].dir][1];
				
				//만약 현재 체스말이 움직이고자하는 위치가 보드의 바깥이거나, 파란색 칸 이라면 체스말의 이동방향을 바꾼다.
				if(!isValid(ny, nx) || board[ny][nx].type == 2) nodes[i].convertDir();
				
				//만약 현재 체스말이 움직일 수 없다면 (이동하고자하는 곳이 파란 칸이거나, 보드의 바깥인 경우) 다음 체스말을 확인한다.
				if(!canMove(nodes[i])) continue;
				
				// 방향 변경 이후, 이동 가능한 칸의 좌표를 계산한다.
				ny = nodes[i].y + dirs[nodes[i].dir][0];
				nx = nodes[i].x + dirs[nodes[i].dir][1];
				
				// 현재 체스말이 서있는 체스판의 위치와, 다음 이동할 체스판의 위치를 가져온다.
				Tile currnentTile = board[nodes[i].y][nodes[i].x];
				Tile nextTile = board[ny][nx];
				
				// 현재 체스판의 위치에서, 현재 체스말이 어디에 위치하는지 찾는다.
				// 리스트에서 해당 체스말보다 인덱스가 빠른 체스말들은 해당 체스말 위에 있는 체스말이다.
				int pos = currnentTile.pieces.indexOf(nodes[i]);		
				
				// 현재 체스말을 기준으로, 자기 자신의 위에 있는 모든 체스말이 함께 이동해야하므로 이를 추출한다.
				List<Node> subList = new LinkedList<>();
				for(int j=0; j<=pos; ++j) {
					Node node = currnentTile.pieces.get(j);
					node.y = ny; node.x = nx;
					subList.add(node);
				}
				
				currnentTile.pieces.removeAll(subList);
				if(nextTile.type == 1) Collections.reverse(subList);
				nextTile.pieces.addAll(0, subList);
				
				if(nextTile.pieces.size() >= 4) {
					System.out.println(turn);
					return;
				}
			}
		}
		
		System.out.println(-1);
	}	
	
	private static boolean isValid(int y, int x) {
		return (y>=0 && y<n) && (x>=0 && x<n);
	}
	
	private static boolean canMove(Node node) {
		int ny = node.y+dirs[node.dir][0];
		int nx = node.x+dirs[node.dir][1];
		return isValid(ny, nx) && (board[ny][nx].type != 2);
	}
	
	private static void init() throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int[] tmp = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
		n = tmp[0]; k = tmp[1];
		for(int i=0; i<n; ++i) {
			int[] row = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
			for(int j=0; j<row.length; ++j) {
				board[i][j] = new Tile(row[j]);
			}
		}
		
		for(int i=0; i<k; ++i) {
			int[] row = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
			nodes[i] = new Node(row[0], row[1], row[2]);
			board[row[0]-1][row[1]-1].pieces.add(nodes[i]);
		}
		br.close();
	}
	
	static class Tile {
		int type;
		List<Node> pieces;
		
		public Tile() {}
		public Tile(int t) {
			this.type = t;
			this.pieces = new LinkedList<>();
		}
	}
	
	static class Node {
		int y, x;
		int dir;
		
		public Node() {}
		public Node(int y, int x, int dir) {
			this.y = y-1;
			this.x = x-1;
			this.dir = dir-1;
		}
		
		public void convertDir() {
			int add = (this.dir % 2 == 0) ? 1 : -1;
			this.dir += add;
		}
	}
}
