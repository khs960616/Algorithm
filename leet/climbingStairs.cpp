/*
    한번의 1, 2번의 step만이 가능하다.
    계단의 정상까지는 n번의 step이 필요하다.
    정상까지 갈 수 있는 경우의 수는 몇 가지인가?
    n은 1 이상 45 이하이다.
    
    n = 1 일 때 -> 1    1가지 경우의 수 
    n = 2 일 때 -> (1,1), 2   2가지 경우의 수 
    n = 3 일 때 -> (1,1,1), (1,2), (2, 1) 3가지 경우의 수
    ...
    
    n번째 경우의 수는 ? (n-1번째 경우의수) + (n-2번째 경우의 수)
    why ? n-1번째 경우의 수에서 1만큼 의 step을 더 오르고
    n-2 번째 경우의 수에서 2만큼의 step을 더오르는 경우만 따지면 된다. 
    (n-2번째에서 1, 1 두번의 오른 거는 이미 n-1번째 경우의 수에 의해 포함되었으므로)
*/

class Solution {
public:
    int climbStairs(int n) {
        vector<int> v;
        v.push_back(0);
        v.push_back(1);
        v.push_back(2);
            
        for (int i=3; i<=n; i++) {
            v.push_back(v[i-2] + v[i-1]);
        }
        
        return v[n];
    }
};
