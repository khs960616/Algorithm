import java.util.*;
import java.util.stream.Collectors;

/*
https://school.programmers.co.kr/learn/courses/30/lessons/118667
2022 KAKAO TECH INTERNSHIP
두 큐 합 같게 만들기
--
two pointer approch
*/

class Solution {
    private List<Integer> wholeElements = new ArrayList<>(); 
    
    public int solution(int[] queue1, int[] queue2) {
        int answer = -1;
        //two pointer approach를 위해 두 queue를 하나로 합친다.
        addElements(queue1, queue2);
        
        // 목표 값 설정 
        long sum1 = Arrays.stream(queue1).sum();
        long sum2 = Arrays.stream(queue2).sum();
        long target = sum1+sum2;
        if(target % 2 != 0) return -1;  //정확하게 2로 나누지 못하는 경우 별도 예외처리 한다.
        target /= 2;
        
        int l = 0, r = queue1.length-1, cnt = 0;
        int size = wholeElements.size();
        
        while(l<=r && r < size-1) {
            if(sum1 == target) {
                answer = cnt;
                break;
            }
            
            if(sum1 < target) sum1 += wholeElements.get(++r);
            else sum1 -= wholeElements.get(l++);
            ++cnt;
        }
        return answer;
    }
    
    private void addElements(int[] queue1, int[] queue2) {
        wholeElements.addAll(Arrays.stream(queue1)
                             .boxed()
                             .collect(Collectors.toList()));
        wholeElements.addAll(Arrays.stream(queue2)
                             .boxed()
                             .collect(Collectors.toList()));
    }
}
