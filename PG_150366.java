import java.util.*;

/*
https://school.programmers.co.kr/learn/courses/30/lessons/150366
표 병합
union find 구현
---
각각의 셀을 union find 하며 구한다.
unmerge의 경우, 셀의 경우가 크지 않으므로 전체를 순회하도록 구현,
이 때 곧바로 parents 배열을 갱신 해버리면 findParents(parents[i]) 함수가 정상적으로 동작하지 않으므로 
기존 배열을 복사해 값 갱신을 위한 임시 배열로 사용.
*/
class PG_150366 {
    
    String[] cells = new String[2501];
    int[] parents = new int[2501];
    
    public String[] solution(String[] commands) {
        List<String> answer = new ArrayList<>();
        initParent();
    
        for(String command: commands) {
            String[] tokens = command.split(" ");
            
            String operation = tokens[0];
            
            switch(operation) {
                case "UPDATE":
                    update(tokens);
                    break;
                case "MERGE":
                    merge(tokens);
                    break;
                case "UNMERGE":
                    unmerge(tokens);
                    break;
                case "PRINT":
                    int node = findParents(
                        convertDimension(Integer.parseInt(tokens[1])-1, Integer.parseInt(tokens[2])-1));
                    
                    answer.add(cells[node] == null ? "EMPTY" : cells[node]);
                    break;
            }
        }
        return answer.toArray(String[]::new);
    }
    
    private void update(String[] tokens) {
        if(tokens.length == 3) {
            for(int i=0; i<2501; ++i) {
                if(cells[i] == null) continue;
                if(cells[i].equals(tokens[1])) cells[i] = tokens[2];
            }    
            return;
        }
        
        int node = convertDimension(Integer.parseInt(tokens[1])-1, Integer.parseInt(tokens[2])-1);
        int target = findParents(node);
        cells[target] = tokens[3];
    }
    
    private void merge(String[] tokens) {
        int r1 = Integer.parseInt(tokens[1])-1, c1 = Integer.parseInt(tokens[2])-1;
        int r2 = Integer.parseInt(tokens[3])-1, c2 = Integer.parseInt(tokens[4])-1;
        unionNode(convertDimension(r1, c1), convertDimension(r2, c2));
    }
    
    private void unmerge(String[] tokens) {
        int r = Integer.parseInt(tokens[1])-1, c = Integer.parseInt(tokens[2])-1;
        int currentNode = convertDimension(r, c);
        int root = findParents(currentNode);
        
        int[] updateParents = parents.clone();
        String prevValue = cells[root];
        for(int i=0; i<2501; ++i) {
            if(findParents(parents[i]) != root) continue;
            updateParents[i] = i;
            cells[i] = null;
        }
        cells[currentNode] = prevValue;
        parents = updateParents;
    }
    
    private void initParent() {
        for(int i=0; i<2501; ++i) parents[i] = i;
    }
    
    private int findParents(int r) {
        if(parents[r] == r) return r;
        else return parents[r] = findParents(parents[r]);
    }
    
    private void unionNode(int node1, int node2) {
        int p1 = findParents(node1);
        int p2 = findParents(node2);
        
        if(p1 == p2) return;
        parents[p2] = p1;
        
        if(cells[p1] == null && cells[p2] != null) cells[p1] = cells[p2];
    }

    private int convertDimension(int r, int c) {
        return r*50+c;
    }
}
