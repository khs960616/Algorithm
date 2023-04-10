/*
https://school.programmers.co.kr/learn/courses/30/lessons/150365
미로 탈출 명령어
그리디, DFS
---

1. 사전순으로 우선되는 순서 먼저 dfs를 탐색한다.
2. 기저를 정의한다.
   -> 이동 가능한 모든 횟수를 소모하고 도착지에 도달하는 경우 
   
3. prunning 조건을 정의한다.
  3-1) 도착지까지의 거리가 현재 이동 가능한 횟수보다 멀리 있는 경우
  3-2) 현재 이동 가능한 거리 - 도착지까지의 거리) 가 홀수인 경우 
       (도착지까지의 거리는 짝수만큼 남았으나, 이동가능한 횟수는 홀수이거나,  그 역이므로 해당 케이스에서는 도착지에 도달할 수 없다.)

4. 그리디한 prunning 조건을 추가한다.
   -> d, l, r, u 사전순으로 우선되는 알파벳 순으로 탐색하며, 정답을 찾은 경우, 더 이상 다른 함수 호출을 하지 않고 return 한다.
      (더 진행해서 답이 나와도 사전순으로 뒤에 나올 것이므로) 

--
4번에서 답을 찾자마자 return 시켜야하는 것을 생각하는 것이 어려운 문제였다. 

*/

class PG_150365 {
    
    private int N, M, K;
    private int R, C;
    private char[] dChar = { 'd', 'l', 'r', 'u' };
    private int[][] dirs = { {1, 0}, {0, -1}, {0, 1}, {-1, 0} };
    private String answer = null;
    
    public String solution(int n, int m, int x, int y, int r, int c, int k) {
        N = n; M = m; K = k;
        R = r; C = c;
        dfs(x, y, 0, "");
        return (answer != null) ? answer : "impossible";
    }
    
    private boolean dfs(int y, int x, int cnt, String tmp) {
    	if(K-cnt == 0 && y==R && x == C) {
    		answer = tmp;
    		return true;
    	}
    	
    	int dist = getManhattanDist(y, x);
    	int remain = K-cnt;
    	if(dist > remain || (remain - dist) % 2 != 0) return false;
    	
    	for(int i=0; i<4; ++i) {
    		int ny = y + dirs[i][0];
    		int nx = x + dirs[i][1];
    		
    		if(!isValid(ny, nx)) continue;
    		if(dfs(ny, nx, cnt+1, tmp+dChar[i])) return true;
    	}
    	
    	return false;
    }
    
    private boolean isValid(int y, int x) {
        return (y>0 && y<=N) && (x>0 && x<=M);
    }
    
    private int getManhattanDist(int sy, int sx) {
        return Math.abs(sy-R) + Math.abs(sx-C);
    }
}
