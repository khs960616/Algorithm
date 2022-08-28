import java.util.*;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/118666
  구현
*/
class Solution {
    // 요구하는 크기가 8정도로 매우 작아서 단순 해쉬맵 선택 (배열로 그냥 캐릭터값 인덱스로 치환하려다 의미가 뭔가 불명확하다 생각되서) 
    private Map<Character, Integer> mp = new HashMap<>();
  
    // switch - case, if-else 등의 불필요한 코드를 줄이기 위해 지표 정보를 배열로 저장하였다.
    // 실제 불변하는 값이므로 List.of , Collections::unmodifiableList 등으로 저장하는 게 의미적으로는 더 좋았을 듯 
    private static final char[] metrics = {'R', 'T', 'C', 'F', 'J', 'M', 'A', 'N'}; 
    
    public String solution(String[] survey, int[] choices) {
        StringBuilder sb = new StringBuilder(); // 불필요한 객체 생성을 방지하기 위해 사용
        
        for(int i=0; i<choices.length; ++i) {
            int addValue = Math.abs(choices[i]-4);
            if(addValue == 0) continue;
            
            char scoreChar = (choices[i] < 4) ? 
                survey[i].charAt(0) : survey[i].charAt(1);
            
            int currentSum = mp.getOrDefault(scoreChar, 0);
            mp.put(scoreChar, currentSum+addValue);
        }
        
        for(int i=0; i<metrics.length; i+=2) {
            int metric1 = mp.getOrDefault(metrics[i], 0);
            int metric2 = mp.getOrDefault(metrics[i+1], 0);
            char addValue = (metric1>=metric2) ? metrics[i] : metrics[i+1];
            
            sb.append(addValue);
        }
        
        return sb.toString();
    }
}
