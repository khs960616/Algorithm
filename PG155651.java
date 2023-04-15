/*
  https://school.programmers.co.kr/learn/courses/30/lessons/155651
  호텔 대실
  ---
  String parsing 구현, 누적합 
*/
class PG155651 {
    private int[] times = new int[25*60];
    
    public int solution(String[][] book_time) {
        int answer = 0;
        
        for(String[] info: book_time) {
            times[convertTime2Int(info[0])] += 1;
            times[convertTime2Int(info[1])+10] -= 1;
        }
        
        for(int i=1; i<25*60; ++i) {
            times[i] += times[i-1];
            answer = Math.max(answer, times[i]);
        }
        
        return answer;
    }
    
    private int convertTime2Int(String s) {
        String[] st = s.split(":");
        return Integer.parseInt(st[0])*60 + Integer.parseInt(st[1]);
    }
}
