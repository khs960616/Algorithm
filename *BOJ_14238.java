import java.util.Scanner;

/*
  https://www.acmicpc.net/problem/14238
  출근기록
  ---
  백트래킹으로 풀었는데 시간 나오는거보니 정해가 아닌듯함 -> 다른 코드 로직 보고 수정 
  47분 소요 
*/
public class BOJ_14238 {
	
	private static int N;
	private static boolean flag = false;
	private static int[] freq = new int[3];
	private static char[] selected;
	
	public static void main(String[] args) throws Exception {
		Scanner sc = new Scanner(System.in);
		char[] alpha = sc.next().toCharArray();
		sc.close();
		
		for(char c: alpha) freq[c-'A'] += 1;
		N = alpha.length;
		
		selected = new char[N];
		simulation(0);
		if(!flag) System.out.println(-1);
	}

	private static void simulation(int idx) {
		if(idx == N) {
			flag = true;
			System.out.println(new String(selected));
			return;
		}
		
		boolean validB = (freq[1]-1) <= (freq[0]+freq[2]);
		boolean validC = (freq[2]-1)*2 <= (freq[0]+freq[1]);
		
		if((freq[1] > 1 && !validB) || (freq[2] > 1 && !validC)) return;
		
		for(int i=0; i<3; ++i) {
			if(flag) return;
			if(freq[i] == 0) continue;
			char alpha = (char)('A'+i);
			
			if(alpha=='B' && (idx>0  && selected[idx-1] == alpha)) continue;
			if(alpha =='C' && ((idx>0 && selected[idx-1] == alpha) || (idx>1 && selected[idx-2] == alpha))) continue;
			
			selected[idx] = alpha;
			freq[i]--;
			simulation(idx+1);
			freq[i]++;
		}
	}
}
