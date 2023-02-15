import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;

/*
  https://www.acmicpc.net/problem/2563
  색종이
  단순 구현 
  ---
  파괴되지 않은 건물 문제가 떠올라 누적합 알고리즘을 사용했으나, 
  해당 문제처럼 query 개수가 상당히 작고, 그에 비해 range가 넓은 경우 단순 시뮬레이션을 하는것이 더 빠르다. 
  
  실제 input으로 들어오는 색종이는 100개 이므로, 
  매 색종이마다 10*10 크기의 grid값을 1씩 증가시키면 총 10^4에 처리 가능하며, 
  값이 0-> 양수로 변경될때만 count해주면 오히려 더 빠르다. 
*/
public class Boj2563 {

	private static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	private static int[][] arr = new int[102][102];
	
	public static void main(String[] args) throws Exception {
		int n = Integer.parseInt(br.readLine());
		for(int i=0; i<n; ++i) {
			int[] coordinates = read();
			arr[coordinates[0]][coordinates[1]] += 1;
			arr[coordinates[0]+10][coordinates[1]] -= 1;
			arr[coordinates[0]][coordinates[1]+10] -= 1;
			arr[coordinates[0]+10][coordinates[1]+10] += 1;
		}
		
		for(int i=0; i<102; ++i) {
			for(int j=1; j<102; ++j) {
				arr[j][i] += arr[j-1][i];
			}
		}
		
		for(int i=0; i<102; ++i) {
			for(int j=1; j<102; ++j) {
				arr[i][j] += arr[i][j-1];
			}
		}
		
		int answer = 0;
		for(int i=0;i<102; ++i) {
			for(int j=0; j<102; ++j) {
				if(arr[i][j]>0) ++answer;
			}
		}
		System.out.println(answer);
	}
	
	private static int[] read() throws IOException {
		return Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
	}
}
