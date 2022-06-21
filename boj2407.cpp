#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/2407
조합
-----
이항 계수의 성질, 큰수를 다루기 위한 string 변환
*/

vector<vector<string>> combinationResult;

string addString(string s1, string s2) {
    string ret = "";
    int sum = 0;

    while (!s1.empty() || !s2.empty() || sum) {
        if(!s1.empty()) {
            sum += (s1.back() - '0');
            s1.pop_back();
        }

        if(!s2.empty()) {
            sum += (s2.back() - '0');
            s2.pop_back();
        }

        char c = (sum % 10) + '0';
        ret.insert(ret.begin(), c);
        sum /= 10;
    }

    return ret;
}

string getCombination(int n, int k) {
    string& ret = combinationResult[n][k]; 
    if(n == k || k == 0) ret = "1";
    if(ret != "") return ret;

    ret = addString(getCombination(n-1, k-1), getCombination(n-1, k));
    return ret;
}

int main() {
    int n, m;
    cin >> n >> m;
    combinationResult = vector<vector<string>>(n+1, vector<string>(m+1, ""));
    cout << getCombination(n, m);
    return 0;   
}
