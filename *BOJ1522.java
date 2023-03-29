import java.io.BufferedReader;
import java.io.InputStreamReader;

/*
https://www.acmicpc.net/problem/1522
다시 풀어볼것
문자열 교환
---
슬라이딩 윈도우 / 아이디어 

코드 자체는 간단하지만 풀이를 생각해는게 굉장히 어려운 문제 
*/
public class BOJ1522 {
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		char[] cs = br.readLine().toCharArray();
		
		int windowSize = 0;
		for(int i=0; i<cs.length; ++i) {
			if(cs[i] == 'a') ++windowSize;
		}
		
		int answer = Integer.MAX_VALUE;
		for(int i=0; i<cs.length; ++i) {
			int bCnt = 0;
			for(int j=i; j<i+windowSize; ++j) {
				if(cs[j%cs.length] == 'b') ++bCnt;
			}
			answer = Math.min(answer, bCnt);
		}
		
		System.out.println(answer);
	}
}
