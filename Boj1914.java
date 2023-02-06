import java.math.BigDecimal;
import java.util.Scanner;

public class Boj1914 {
	private static StringBuilder sb = new StringBuilder();
	
	public static void hanoi(int cnt, int from, int mid, int to) {
		if(cnt == 1) {
			sb.append(from);
			sb.append(' ');
			sb.append(to);
			sb.append('\n');
			return;
		}
		hanoi(cnt-1, from, to, mid);
		sb.append(from);
		sb.append(' ');
		sb.append(to);
		sb.append('\n');
		hanoi(cnt-1, mid, from, to);
	}
	
	public static void main(String args[]) throws Exception {
		Scanner sc = new Scanner(System.in);
		int T = sc.nextInt();
		
		BigDecimal answer = new BigDecimal("2");
		System.out.println(answer.pow(T).subtract(BigDecimal.ONE));
		if(T<=20) {
			hanoi(T, 1, 2, 3);
			System.out.println(sb.toString());
		}
		sc.close();
	}
}
