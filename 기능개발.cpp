#include <string>
#include <vector>
#include <queue>
#define ROUND(a,b) ((a+b-1)/b)
using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    int size = progresses.size();
    int cnt = 0;
    vector<int> answer;
    queue<int> job;
    
    for(int i=0;i<size;i++){
        job.push(i);
    }
    
    while(!job.empty()){
        int index = job.front();
        int iter = ROUND(100-progresses[index],speeds[index]);
        for(int i = index; i < size; i++){
            progresses[i] += (iter * speeds[i]);
        }
        
        while(progresses[index]>=100){
            job.pop();
            cnt++;
            if(job.empty()) break;
            index = job.front();
        }             
        
        answer.push_back(cnt);
        cnt = 0;
    }
    
    return answer;
}



/* 다른 코드
#include <string>
#include <vector>
#include <iostream>
using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;

    int day;
    int max_day = 0;
    for (int i = 0; i < progresses.size(); ++i)
    {
        day = (99 - progresses[i]) / speeds[i] + 1;

        if (answer.empty() || max_day < day)
            answer.push_back(1);
        else
            ++answer.back();

        if (max_day < day)
            max_day = day;
    }

    return answer;
}
*/
