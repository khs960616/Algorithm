#include <bits/stdc++.h>
using namespace std;

vector<vector<long long>> operator*(vector<vector<long long>> v1, vector<vector<long long>> v2) {
    long long vSize = v1.size();
    vector<vector<long long>> ret(vSize, vector<long long>(vSize, 0));

    for(int i=0; i<vSize; ++i) {
        for(int j=0; j<vSize; ++j) {
            for(int k=0; k<vSize; ++k) {
                ret[i][j] += (v1[i][k] * v2[k][j]);
            }
            ret[i][j] %= 1000;
        }
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    long long n, m;
    cin >> n >> m;
    vector<vector<long long>> v(n, vector<long long>(n, 0));
    vector<vector<long long>> answer(n, vector<long long>(n, 0));

    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            cin >> v[i][j];

            if(i==j) answer[i][j] = 1;
        }
    }

    while(m) {
        if(m%2 == 1) answer = answer * v;
        v = v * v;
        m /= 2;
    }

    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            cout << answer[i][j] << ' ';
        }
        cout << '\n';
    }
    return 0;
}
