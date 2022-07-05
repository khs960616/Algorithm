#include <bits/stdc++.h>
#define PRE_FIX_QUANTITY 2
#define MAX_TARGET 1000000
using namespace std;

/*
  구간 구하기 문제 유형과 비슷한 DP
*/
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    double C = 30;
    double F = 2.0;
    double X = 100;
    double answer = X / PRE_FIX_QUANTITY;

    int maxWorker = (MAX_TARGET / F)+1;

    vector<double> prefixTime;
    prefixTime.push_back(0.0);
    for(int worker=1; worker<maxWorker; ++worker) {
        double time = (C / (PRE_FIX_QUANTITY + (worker-1) * F));
        prefixTime.push_back(prefixTime[worker-1] + time);
    }

    int ptSize = prefixTime.size();
    for(int worker=0; worker<ptSize; ++worker) {
        double currentTime = prefixTime[worker] + (X / (PRE_FIX_QUANTITY + worker * F));
        answer = min(answer, currentTime);
    }

    cout << answer;
    return 0;
}
