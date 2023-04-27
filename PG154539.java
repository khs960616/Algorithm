import java.util.*;
/*
  https://school.programmers.co.kr/learn/courses/30/lessons/154539
  뒤에 있는 큰수 
  자료구조(스택)
  ---
  정수로 이루어진 배열 numbers가 있습니다. 배열 의 각 원소들에 대해 자신보다 뒤에 있는 숫자 중에서 자신보다 크면서 가장 가까이 있는 수를 뒷 큰수라고 합니다.
  정수 배열 numbers가 매개변수로 주어질 때, 모든 원소에 대한 뒷 큰수들을 차례로 담은 배열을 return 하도록 solution 함수를 완성해주세요. 
  단, 뒷 큰수가 존재하지 않는 원소는 -1을 담습니다.
  
  numbers[]를 순회하며 다음의 작업을 반복한다.
  1) 스택이 비어있는지 확인한다. 
     1-1) 스택이 비어있지않다면, 스택에 존재하는 원소들과 현재 numbers의 크기를 비교하며,
          더 작은 원소들의 뒷 큰수를 현재 숫자로 갱신한다.
          
  2) 현재 원소를 스택에 넣는다. 
  3) numbers 배열을 모두 순회할 때까지 1~2의 과정을 반복한다.
  
  모두 순회한 이후 스택에 남아있는 원소들은 뒷 큰 수가 존재하지 않는 숫자 들이다. (스택의 남은 숫자들은 단조 감소)
  따라서 해당 원소들의 인덱스에는 -1을 담아야한다. (이 경우 별도로 다시 스택을 순회하기보다 초기 원소값을 -1로 초기화 하는편이 깔끔함) 
  
*/
class PG154539 {
    public int[] solution(int[] numbers) {
        int len = numbers.length;
        int[] answer = new int[len];
        Arrays.fill(answer, -1);
        
        Stack<int[]> st = new Stack<>();
        for(int i=0; i<len; ++i) {
            while(!st.isEmpty()) {
                int[] top = st.peek();
                if(top[0] >= numbers[i]) break;
                
                answer[top[1]] = numbers[i];
                st.pop();
            }
            st.add(new int[] {numbers[i], i});
        }
        
        return answer;
    }
}
