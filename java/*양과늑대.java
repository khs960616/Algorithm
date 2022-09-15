/*
https://school.programmers.co.kr/learn/courses/30/lessons/92343
카카오블라인드 2022
---
dfs, 브루트포스 
*/

class Solution {
    private int[] leftChild = new int[18];
    private int[] rightChild = new int[18];
    private int[] value = new int[18];
    private int answer = 0;
    private int n = 0;
    private boolean[] isVisit = new boolean[1<<17]; //비트마스킹, LSB부터 0번째 노드가 현재 부분 집합에 포함되는 지 여부를 나타낸다.
        
    public int solution(int[] info, int[][] edges) {
        this.n = info.length;
        for(int i=0; i<n; ++i) {
            value[i] = info[i];
        }
        
        for(int i=0; i<edges.length; ++i) {
            if(leftChild[edges[i][0]] == 0) {
                leftChild[edges[i][0]] = edges[i][1];
                continue;
            } 
            rightChild[edges[i][0]] = edges[i][1];
        }
        solve(1);
        return answer;
    }
    
    private void solve(int state) {
        if(isVisit[state]) return;
        isVisit[state] = true;
        
        int currentVisitNodeCnt = 0;
        int wolf = 0;
        for(int i=0; i<n; ++i) {
            if((state & (1<<i)) != 0) {
                wolf += value[i];
                currentVisitNodeCnt++;
            }
        }
        
        if(2*wolf >= currentVisitNodeCnt) return;
        answer = Math.max(answer, currentVisitNodeCnt-wolf);
        
        for(int i=0; i<n; ++i) {
            if((state & (1<<i)) == 0) continue;
            
            if(leftChild[i] != 0) solve(state|(1<<leftChild[i]));
            if(rightChild[i] != 0) solve(state|(1<<rightChild[i]));
        }
    }
}
