import java.util.*;

/*
https://school.programmers.co.kr/learn/courses/30/lessons/43162
네트워크
---
BFS
*/
class Solution {
    private boolean[] isVisit = {};
    private int computerCnt = 0;
    
    public int solution(int n, int[][] computers) {
        int answer = 0;
        computerCnt = n;
        isVisit = new boolean[n];
        
        for(int i=0; i<n; ++i) {
            if(isVisit[i]) continue;
            bfs(computers, i);
            answer++;
        }
        return answer;
    }
    
    public void bfs(int[][] computers, int networkRootNum) {
        Queue<Integer> q = new LinkedList<>();
        isVisit[networkRootNum] = true;
        q.add(networkRootNum);
        
        while(!q.isEmpty()) {
            int num = q.poll();
            for(int i=0; i<computerCnt; ++i) {
                if(computers[num][i] == 1 && !isVisit[i]) {
                    isVisit[i] = true;
                    q.add(i);
                }
            }
        }
    }
}
