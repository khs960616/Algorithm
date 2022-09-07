/*  
    https://school.programmers.co.kr/learn/courses/30/lessons/68936
    쿼드압축후 개수세기
    ---
    문제 : 
    0과 1로 이루어진 배열 arr
    1. 압축하고자하는 영역을 S라 정의한다.
    2. 압축하고자하는 영역의 수가 모두 같은 값이면 S를 해당 수 하나로 압축한다.
    3. 그렇지 않다면 S를 정확히 4개의 정사각형 영역으로 쪼갠 후 2번을 시도한다.
    ---
    전형적인 분할 정복 문제의 형태
    배열 최대크기 1024 * 1024
    최대 10^6 가량의 재귀 함수 호출되므로 지장 없을 듯.
*/

class Solution {
    private int[] answer = new int[2];
    
    public int[] solution(int[][] arr) {
        compression(arr, arr.length, 0, 0);
        return answer;
    }
    
    private void compression(int[][] arr, int len, int y, int x) {
        int startElement = arr[y][x];
        for(int i=y; i<y+len; ++i) {
            for(int j=x; j<x+len; ++j) {
                if(arr[i][j] == startElement) continue;
                
                int nextSize = len/2;
                compression(arr, nextSize, y, x);
                compression(arr, nextSize, y, x+nextSize);
                compression(arr, nextSize, y+nextSize, x);
                compression(arr, nextSize, y+nextSize, x+nextSize);
                return;
            }   
        }
        ++answer[startElement];
    }
}
