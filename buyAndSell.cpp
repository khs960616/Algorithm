/*
https://leetcode.com/problems/best-time-to-buy-and-sell-stock/

prices vector : i번째날의 주식의 가격이 주어진 벡터

prices 벡터는 1 이상, 10^5 개 이하로 주어진다.
각 주식의 가격은 0이상, 10^4 이하

어떻게 해야 시간복잡도가 n이 나올까?

1. 만약 현재 들어온 값이 기존의 min보다 작다면, min값과 max값을 해당 값으로 갱신한다. (더 이상 기존 min값으로 계산하는 의미가 없으므로 )
2. 현재 들어온 값이 기존의 max값보다 크다면 max값을 갱신한다.
3. min max값의 차이가 현재 answer의 값보다 크다면 answer에 대입한다.

*/

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int answer = 0;
        int pSize = prices.size();
        int localMin = prices[0];
        int localMax = prices[0];
        
        for(int i=1; i<pSize; i++) {
            if (localMin > prices[i]) {
                localMin = localMax = prices[i];
            } else if (localMax < prices[i]) {
                localMax = prices[i];
            }
            
            int diff = localMax - localMin;
            if (diff > answer) {
                answer = diff;
            }
        }
        
        return answer;
    }
};

/* 
int maxProfit(vector<int>& prices) {

    int currentMin = INT_MAX;
    int result = 0;

    for (int i = 0; i < prices.size(); i++) {
        result = max(result, prices[i] - currentMin);
        currentMin = min(currentMin, prices[i]);
    }

    return result;

}
*/
