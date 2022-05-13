/*
https://leetcode.com/problems/unique-paths/
Unique Paths
DP
---
m*n 의 격자판에 로봇이 존재한다. 초기 로봇의 위치는 (0, 0) 이다.(top left coner)
로봇은 bottom-right corner(m-1, n-1)로 이동하고자한다.
로봇은 한번에 한칸 내려가거나 오른쪽으로 1칸 이동밖에 하지 못한다.
bottom-right corner 까지 가는 unique한 패스의 갯수를 구하라 
*/

class Solution {
public:
    int uniquePaths(int m, int n) {
        if(1==m || 1==n) return 1;
        
        vector<vector<int>> grid(m, vector<int>(n, 0));
        //초기값 init 
        for(int i=1; i<n; ++i) grid[0][i] = 1;
        for(int i=1; i<m; ++i) grid[i][0] = 1;
        
        for(int i=1; i<m; ++i) {
            for(int j=1; j<n; ++j) {
                grid[i][j] = grid[i][j-1] + grid[i-1][j];
            }
        }
        return grid[m-1][n-1];
    }
};
