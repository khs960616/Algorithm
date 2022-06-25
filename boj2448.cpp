#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/2448
별찍기
분할정복

1. n은 가장 큰 삼각형의 높이이다.
2. 각 삼각형은 높이가 3인 삼각형으로 이루어져있다.
3. 초기 가장큰 삼각형의 맨위 꼭지점은 n번째 인덱스에 위치한다.
4. 각 삼각형들은 자기 자신의 높이/2 인 3개의 삼각형으로 분할이 가능하다. 
*/
void drawStars(vector<vector<char>>& stars, int y, int x, int height) {
    if(height == 3) {
        stars[y][x] = '*';
        stars[y+1][x-1] = stars[y+1][x+1] = '*';
        stars[y+2][x-2] = stars[y+2][x-1] = stars[y+2][x] = stars[y+2][x+1] = stars[y+2][x+2] = '*';
        return;
    }

    drawStars(stars, y, x, height/2);
    drawStars(stars, y+height/2, x-height/2, height/2);
    drawStars(stars, y+height/2, x+height/2, height/2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;
    vector<vector<char>> stars(n, vector<char>(2*n, ' '));
    drawStars(stars, 0, n-1, n);

    for(int i=0; i<n; ++i) {
        for(int j=0; j<2*n; ++j) {
            cout << stars[i][j];
        }
        cout << '\n';
    }
    return 0;
}
