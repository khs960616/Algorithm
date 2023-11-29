import java.util.*;

/*
https://school.programmers.co.kr/learn/courses/30/lessons/17685
2018 KAKAO BLIND RECRUITMENT [3차] 자동완성
---
트라이 

1. 문자를 트라이 형태로 저장하며, 해당 위치에 문자가 몇번 등장했는 지 빈도수를 카운트한다.
2. 완성된 트라이를 순회하며 문자열이 몇번의 탐색을 통해 추천이 가능한지 확인한다. (탐색 중인 녿의 카운트가 1인 경우, 해당 입력까지만 입력하면, 다른 알파벳과 겹치지 않으므로 return 한다.) 

주의사항 : insert할때 재귀로 넣으면 콜스택 터지는 것으로 보임 
*/
class Solution {
    
    public int solution(String[] words) {
        int answer = 0;
        Node tries = new Node();
        for(String word: words) {
            tries.insert(word);
        }
        
        for(String word: words) {
            answer += tries.getMinCount(word, 0);
        }
        return answer;
    }
    
    private class Node {
        Map<Character, Node> children = new HashMap<>();
        int count=0;

        public void insert(String src) {
            int len = src.length();
            
            Node prev = this;
            for(int i=0; i<len; ++i) {
                char key = src.charAt(i);
                Node node = prev.children.getOrDefault(key, new Node());
                node.count+=1;
                prev.children.put(key, node);
                prev = node;
            }
        }
        
		public int getMinCount(String src, int from) {
			if(src.length()-1 == from) {
				return 1;
			}

			char key = src.charAt(from);
			Node node = children.get(key);
            if(node.count == 1) {
				return 1;
			}
			return 1+node.getMinCount(src, from+1);
		}
    } 
}
