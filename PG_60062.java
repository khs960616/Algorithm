import java.util.*;

/*
https://school.programmers.co.kr/learn/courses/30/lessons/60062
[2020 KAKAO BLIND RECRUITMENT] 외벽 점검
브루트 포스, 순열

1. 학생들이 1명 선택되는 경우 ~ 학생 전체가 선택되는 경우에 대하여 모든 순열을 구한다.
    (8! + 7! + 6 ! .... 1)

2. 원형으로 이어진 맵에 대하여, (1)에서 구한 순열을 모든 출발점에 대해 대입하며 모든 취약지점을 순회할 수 있는지 검사한다. 

---
풀이 코드 자체는 어렵지 않으나,

원형 큐를 어떻게 일차원 벡터로 단순화할 지, 학생들을 어떻게 선택할지 순열을 선택하는 것 등
문제 풀이에 필요한 요소들을 찾는 것이 어려웠다. (카카오 블로그 보고 접근 방법보고품) 
*/

class Solution {
    
    private int[] selected = new int[8];
    private int[] dists;
	  private List[] rotateWeaks;
    
    public int solution(int n, int[] weak, int[] dist) {
        makeRotateWeaks(n, weak);
        this.dists = dist;
        
        int answer = Integer.MAX_VALUE;
        for(int i=1; i<=dists.length; ++i) {
            answer = Math.min(answer, permutation(0, 0, i));
        }
    
        return (answer == Integer.MAX_VALUE) ? -1 : answer;
    }
    
    private int simulation(int size) {
        int weakCnt = rotateWeaks.length;
    
        for(int i=0; i<weakCnt; ++i) {
            int fIdx = 0;
            int currentPos = (int) rotateWeaks[i].get(0) + dists[selected[fIdx++]];
            
            for(int j=1; j<weakCnt; ++j) {
                if(fIdx == size) break;
                if(currentPos >= (int) rotateWeaks[i].get(j)) continue;
                else {
                    currentPos = (int) rotateWeaks[i].get(j) + dists[selected[fIdx++]];
                }
            }
            if(currentPos >= (int) rotateWeaks[i].get(weakCnt-1)) return size;
        }
        return Integer.MAX_VALUE;
    }
    
    private int permutation(int idx, int state, int size) {
        if(idx == size) return simulation(size); 
        
        int ret = Integer.MAX_VALUE;
        for(int i=0; i<dists.length; ++i) {
            if((state & (1<<i)) != 0) continue;
            selected[idx] = i;
            ret = Math.min(ret, permutation(idx+1, state|(1<<i), size));
        }
        return ret;
    }
    
    private void makeRotateWeaks(int N, int[] weaks) {
        rotateWeaks = new ArrayList[weaks.length];
        
        Deque<Integer> dq = new ArrayDeque<>();
        for(int weak: weaks) dq.add(weak);
        
        for(int i=0; i<weaks.length; ++i) {
            rotateWeaks[i] = new ArrayList(dq);
            dq.add(dq.pollFirst()+N);
        }
    }
}
