//프로그래머스 H-INDEX
//구현

#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int solution(vector<int> citations) {
    int n = citations.size();
    sort(citations.begin(), citations.end());
    int answer = 0;
    
    for(int i=1; i< citations[n-1];i++){
        for(int j=0; j<n;j++){
            if(i<=citations[j] && i<=n-j) answer = i;
        }
    }
    return answer;
}


/*다른 사람 풀이 
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> citations) {
    sort(citations.begin(), citations.end(), greater<int>());

    for (int i = 0; i < citations.size(); ++i) {
        if (citations[i] < i + 1) {
            return i;
        }
    }

    return citations.size();
}*/
