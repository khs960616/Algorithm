#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> solution(vector<int> prices) {
    int max = prices.size();
    vector<int> answer(max, 0);
    vector<int> time;
    time.push_back(0);

    for(int i=1 ; i < max ; i++){        
        while(!time.empty()){ 
            int pre = time.back(); 
            if(prices[i] < prices[pre]){   
                answer[pre] = i-pre;    
                time.pop_back(); 
            } else {
                break;
            }
        }
        time.push_back(i); 
    }

    while(!time.empty()){
        int pre = time.back();
        time.pop_back();
        answer[pre] = max - pre - 1;
    }

    return answer;
}
