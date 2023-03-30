/*
  https://school.programmers.co.kr/learn/courses/30/lessons/150367
  카카오 2023 블라인드
  표현 가능한 이진트리
  ---
  자료구조(포화 이진트리의 성질), 분할정복 
*/
class PG_150367 {
  
    public int[] solution(long[] numbers) {
        int nSize = numbers.length;
        
        int[] answer = new int[nSize];
        
        for(int i=0; i<nSize; ++i) {
            String s = Long.toBinaryString(numbers[i]);
            s = addPadding(s);
    
            if(isValidTree(s, 0, s.length()-1, s.charAt(s.length()/2)-'0')) answer[i] = 1;
        }
        return answer;
    }
    
    private boolean isValidTree(String s, int start, int end, int prev) {
        int mid = (start - end)/2 + end;
        if(prev == 0 && s.charAt(mid) == '1') return false;
        if(start == end) return true;
        if(s.charAt(mid) == '0') prev = 0;
        return isValidTree(s, start, mid-1, prev) && isValidTree(s, mid+1, end, prev);
    }
    
    private int getTreeDepth(int len) {
        int depth = 0;
        while(len != 0) {
            len /= 2;
            depth++;
        }
        return depth;
    }
    
    private String addPadding(String s) {
        int treeDepth = getTreeDepth(s.length());
        int fullCnt = (int) Math.pow(2, treeDepth)-1;
        int needPadding = fullCnt - s.length();
        return "0".repeat(needPadding) + s;
    }
}
