import java.util.*;

/*
    https://school.programmers.co.kr/learn/courses/30/lessons/12905
    가장 큰 정사각형 찾기
    ----
    1로만 이루어진 가장 큰 정사각형을 구해야한다.
    정사각형의 크기 : 1 ~ 1000
    
    전체 브루트포스 돌리는 경우, 
    1000*1000 짜리 배열에 1~1000까지 정사각형 유무를 확인
    10^9 정도.. 
*/

class Solution {
    boolean flag = false; // board의 첫번째 행, 또는 열에 1이 존재하는지 여부
    
    public int solution(int [][]board) {
        int row = board.length;
        int col = board[0].length;
        int[][] dp = init(board, row, col);
        
        int answer = flag ? 1 : 0;
        for(int i=1; i<row; ++i) {
            for(int j=1; j<col; ++j) {
                if(board[i][j] == 1) {
                    dp[i][j] = Math.min(dp[i-1][j-1], Math.min(dp[i][j-1], dp[i-1][j])) + 1;
                    answer = Math.max(answer, dp[i][j]);
                }
            }
        }
        return answer*answer;
    }
    
    private int[][] init(int[][] board, int row, int col) {
        int[][] ret = new int[row][col];
        for(int i=0;i<col; ++i) {
            if(board[0][i] != 1) continue;
            
            ret[0][i] = board[0][i];
            flag = true;
        }
        
        for(int i=0;i<row; ++i) {
            if(board[i][0] != 1) continue;
            ret[i][0] = board[i][0];
            flag = true;
        }
        return ret;
    }
}


/*
맨 처음 생각한 나이브한 코드, 
현재 사각형에서 나올수 있는 가장 큰 정사각형 사이즈부터, 크기가 1인 사이즈까지,
사이즈를 줄여가며 sliding window를 적용함. -> 10^9까지 걸리므로 효율성 테스트 통과불가

class Solution
{
    public int solution(int [][]board)
    {
        int answer = 0;
        int row = board.length;
        int col = board[0].length;
        int min = Math.min(row, col);
        
        for(int i=min; i>0; --i) {
            if(check(board, i, row, col)) {
                answer = i*i;
                break;
            }
        }
        
        return answer;
    }
    
    private boolean check(int[][] board, int windowSize, int row, int col) {
        for(int i=0; i<row-windowSize+1; ++i) {
            for(int j=0; j<col-windowSize+1; ++j) {
                boolean flag = true;
     
                for(int k=i; k<i+windowSize; ++k) {
                    if(!flag) break;
        
                    for(int l=j; l<j+windowSize; ++l) {
                        if(board[k][l] != 1) {
                            flag = false;
                            break;
                        }
                    }
                }
                if(flag) return true;
            }
        }
        
        return false;
    }
}*/
