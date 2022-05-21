#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/2133
타일 채우기
-------------
차후 다시 풀어볼 것

3*4를 채우는 case는 3*4를 고유하게 채우는값 2개, 3*2에서 원소를 하나씩 뽑아서 만드는 케이스 9개 - > 총 11개의 케이스가 존재
3*6을 채우는 case는 3*6을 고유하게 채우는값 2개  f[4]*f[2],  f[2]*(f[4]중 3*2를 채우는 case에 종속적이지 않은 케이스
각 경우 이전의 블록에 영향을 받지않고 자기 자신의 블럭을 채우는 case는 모두 상수 2임

.... 
v[i] = (v[i-2] * v[2]) + (v[i-4] * (v[i-2]에서 사용하지 않았던 패턴을 사용해서 v[i-4]를 채우는 경우 = 2)) + ... 

*/
int main() {
    int n;
    cin >> n;
    if(n%2 != 0) {
        cout << 0;
        return 0;
    }

    vector<int> v(n+1, 0);
    v[0] = 1; v[2] = 3;
    for(int i=4; i<n+1; i+=2) {
        v[i] += v[i-2] * 3;
        for(int j=i-4 ;j>=0; j-=2) {
            v[i] += v[j] * 2;
        }
    }
    cout << v[n];
    return 0;
}
