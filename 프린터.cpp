#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct doc_info{
    int priorities;
    int idx;
};

int solution(vector<int> priorities, int location) {
    int answer = 0;
    int size = priorities.size();
    queue<doc_info> docs;
    
    for(int i=0;i<size;i++){
        struct doc_info temp = {priorities[i], i};
        docs.push(temp);
    }
    
    sort(priorities.begin(), priorities.end());
    
    while(1){
        if(docs.front().priorities == priorities.back()){
            answer++;
            if(docs.front().idx == location) break;
            else{
                docs.pop();
                priorities.pop_back();
            }
        }
        else{
            docs.push(docs.front());
            docs.pop();
        }
    }
    return answer;
}

/* 백준 1966번 동일 문제 
#include <iostream>
#include <queue>
#include <algorithm>
#include <utility>

using namespace std;

struct cmp {
	bool operator()(int &u, int &v) {
		return u < v;
	}
};

int main() {	
	std::ios::sync_with_stdio(false); cin.tie(0);

	int n = 0;
	cin >> n;

	while (n--) {
		int docNum = 0, target=0, preTop=0, result=0;
		priority_queue<int,vector<int>,cmp > wt;
		queue< pair<int, int> > doc;
		cin >> docNum >> target;

		for (int i = 0; i < docNum; i++) {
			int temp = 0;
			cin >> temp;
			doc.push({i,temp});
			wt.push(temp);
		}

		preTop = wt.top();
		wt.pop();

		while (!doc.empty()) {
			int curIdx = doc.front().first;
			int curWeight = doc.front().second;
			doc.pop();
			
			if (curWeight == preTop) {
				if (!wt.empty()) {
					preTop = wt.top();
					wt.pop();
				}
				result += 1;
                
				if (curIdx == target) {
					cout << result << '\n';
					break;
				}
			}
			else {
				doc.push({ curIdx,curWeight });
			}
		}
	}
	return 0;
}


*/
