import java.util.*;

/*
https://school.programmers.co.kr/learn/courses/30/lessons/169199
리코쳇 로봇
---
bfs
*/

class Solution {

    private int row = 0, column = 0;
    private int[][] dirs = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
    private String[] boards;

    public int solution(String[] board) {
        row = board.length;
        column = board[0].length();
        boards = board;

        int startRobotRow = 0, startRobotColumn = 0;
        int[][] isVisit = new int[row][column];
        for(int i=0; i<row; ++i) {
            for(int j=0; j<column; ++j) {
                isVisit[i][j] = Integer.MAX_VALUE;
                if(board[i].charAt(j) == 'R') {
                    isVisit[i][j] = 0;
                    startRobotRow = i;
                    startRobotColumn = j;
                }
            }
        }

        Queue<int[]> q = new LinkedList<>();
        q.add(new int[]{startRobotRow, startRobotColumn, 0});

        while(!q.isEmpty()) {
            int[] info = q.poll();
            if(boards[info[0]].charAt(info[1]) == 'G') {
                return info[2];
            }

            for(int[] dir: dirs) {
                int nRow = info[0], nColumn = info[1];
                while(isValid(nRow+dir[0], nColumn+dir[1]) && boards[nRow+dir[0]].charAt(nColumn+dir[1]) != 'D') {
                    nRow += dir[0];
                    nColumn += dir[1];
                }

                if(isVisit[nRow][nColumn] <= info[2]+1) continue;
                isVisit[nRow][nColumn] = info[2] + 1;
                q.add(new int[]{nRow, nColumn, info[2] + 1});
            }
        }
        return -1;
    }

    private boolean isValid(int y, int x) {
        return (y>=0 && y<row) && (x>=0 && x<column);
    }
}
