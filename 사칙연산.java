/*
  https://school.programmers.co.kr/learn/courses/30/lessons/1843
  사칙연산
  dp, 점화식 
  ---
  dp[i][j][k] : 이전에 나왔던 기호가 (0 == +), (1 == -)일 때, j~k까지 연산의 결과의 최댓값

  case 1) 이전 기호가 + 이고, 현재 처리해야하는 기호가 -인 경우 
    수식의 형태는 다음과 같다 -> (a - b), 이 때 해당 수식이 최댓값이 되기 위해서는 주어진 op에서 적절하게 괄호를 씌워, a는 최댓값, b는 최솟값이 되도록 해야한다.

  case 2) 이전 기호가 + 이고, 현재 처리해야하는 기호가 +인 경우 
    수식의 형태는 다음과 같다 -> (a + b), 이 때 해당 수식이 최댓값이 되기 위해서는 주어진 op에서 적절하게 괄호를 씌워, a는 최댓값, b는 최댓값이 되도록 해야한다.

  case 3) 이전 기호가 - 이고, 현재 처리해야하는 기호가 -인 경우 
    수식의 형태는 다음과 같다 -> -(a - b)     (a-b)의 결과가 최솟값이 되도록 해야한다.  따라서 a는 최솟값, b는 최댓값이 되도록해야한다.

  case 3) 이전 기호가 - 이고, 현재 처리해야하는 기호가 +인 경우 
    수식의 형태는 다음과 같다 -> -(a+b)     (a+b)의 결과가 최솟값이 되도록 해야한다.  따라서 a는 최솟값, b는 최솟값이 되도록해야한다.

*/

class Solution {
    
    private final int[][][] dp = new int[2][256][256];
    private int len = 0;
    
    public int solution(String arr[]) {
        len = arr.length;
        for(int i=0; i<len; ++i) {
            for(int j=0; j<len; ++j) {
                dp[0][i][j] = Integer.MIN_VALUE;
                dp[1][i][j] = Integer.MAX_VALUE;
            }
        }
        
        return getMax(arr, 0, len-1, 0);
    }
    
    private int getMax(String arr[], int start, int end, int flag) {
        if(start == end) {
            return dp[flag][start][end] = Integer.parseInt(arr[start]);
        }
        
        if(dp[flag][start][end] != Integer.MIN_VALUE && dp[flag][start][end] != Integer.MAX_VALUE) {
            return dp[flag][start][end];
        }
        
        if(flag == 0) {
            // 이전 기호가 +인 경우 
            for(int i=start; i<end; i+=2) {
                String op = arr[i+1];
                if(op.equals("-")) {
                    dp[flag][start][end] = Math.max(dp[flag][start][end], getMax(arr, start, i, 0)-getMax(arr, i+2, end, 1));
                } else {
                    dp[flag][start][end] = Math.max(dp[flag][start][end], getMax(arr, start, i, 0)+getMax(arr, i+2, end, 0));
                }
            }
        } else {
            // 이전 기호가 -인 경우
            for(int i=start; i<end; i+=2) {
                String op = arr[i+1];
                if(op.equals("-")) {
                    dp[flag][start][end] = Math.min(dp[flag][start][end], getMax(arr, start, i, 1)-getMax(arr,i+2, end, 0));
                } else {
                    dp[flag][start][end] = Math.min(dp[flag][start][end], getMax(arr, start, i, 1)+getMax(arr,i+2, end, 1));
                }
            }
        }
    
        return dp[flag][start][end];
    }
    
}
