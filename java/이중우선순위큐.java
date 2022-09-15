import java.util.*;
import java.util.stream.*;

/*
https://school.programmers.co.kr/learn/courses/30/lessons/42628
이중우선순위큐 
---
다른 풀이들을 보니 자바에서 priority queue는 자체적으로 중간 element값을 지울 수 있는 remove함수가 있어,
maxHeap, minHeap로 만들어서 D -1,  D 1에 따라 poll(), remove() 연산을 이용하는 코드들이 많았음. 
//https://stackoverflow.com/questions/12719066/priority-queue-remove-complexity-time 해당 부분 보면 
어쩌피 contains 연산 진행하면서 remove자체도 n의 시간복잡도를 가지긴함. 

https://codeung.tistory.com/315  << 다음과 같이 java.util에서 제공하는 자료구조 구현체를 사용하려면 treeMap을 사용하는게 가장 적절한듯함. 

*/
class Solution {
    private List<Integer> list = new ArrayList<>();
    private int[] answer = {0, 0};
    
    public int[] solution(String[] operations) {
        for(String operation: operations) {
            excuteOperation(operation);
        }
        
        if(!list.isEmpty()) {
            list.sort(Comparator.naturalOrder());
            answer[0] = list.get(list.size()-1);
            answer[1] = list.get(0);
        }
        return answer;
    }
    
    private void excuteOperation(String operation) {
        String[] opInfo = operation.split(" ");
        int n = Integer.parseInt(opInfo[1]);
        
        if(opInfo[0].equals("D")) {
            deleteElement(n);
            return;
        }
        
        list.add(n);
    }
    
    private void deleteElement(int num) {
        int listSize = list.size();
        if(listSize == 0) return;
        
        int deleteIndex = (num == -1) ? 0 : listSize-1;
        list.sort(Comparator.naturalOrder());
        list.remove(deleteIndex);
    }
}
