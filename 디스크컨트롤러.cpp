#include <bits/stdc++.h>

using namespace std;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/42627
  디스크 컨트롤러
  시뮬레이션, 우선순위큐
  ---
  제한조건) 하드디스크가 작업을 수행하고 있지 않을 때에는 먼저 요청이 들어온 작업부터 처리합니다. 
  
  0. 모든 작업을 요청순서대로 정렬한다.
  1. 현재 시간을 설정한다. (최초 request time이 가장 작은 시간)
  2. 현재 시간과 request time이 같거나 작은 프로세스들을 모두 우선순위큐에 넣는다. ( {프로세스 실행시간, 프로세스 들어온 순서} 순서로 우선순위가 높다.} )
  3. 만일 현재 시간 이후에 들어온 프로세스가 들어온다면 다음의 과정을 따른다.
     1) 현재 실행시킬 수 있는 프로세스가 존재하지 않는 경우 -> 현재 시간을 현재 넣으려는 프로세스의 시간으로 변경하고, 프로세스를 우선순위큐에 insert하고 2번의 과정으로 돌아간다.
     2) 현재 실행시킬 수 있는 프로세스가 존재하는 경우 -> 우선순위큐에 존재하는 작업을 하나 수행한 후, 해당 작업의 시간만큼 현재 시간을 늘려준다. 이후 2번의 과정으로 돌아간다.
     
  4. 모든 프로세스가 우선순위큐에 insert되었다면, 우선순위에 따라 모든 프로세스를 수행시킨다.
   
  대기시간은 : (현재 시간 - 프로세스가 들어온 시간) +  프로세스가 수행되는데 필요한 시간이다. 
*/

// insert된 순서에 따라 프로세스들을 정렬하는 함수, v1, v2는 각각 프로세스들의 정보이며 0번 인덱스에는 프로세스가 들어온 순서, 1번 인덱스에는 프로세스를 수행하는 cost가 들어있다.
bool cmp(vector<int> v1, vector<int> v2) {
    return v1[0] < v2[0];
}

//현재 실행가능한 프로세스 저장중인 heap
priority_queue<pair<int, int> > pq;

int consume_jobs(int& current_time) { 
    int cost = -pq.top().first;
    int job_insert_time = -pq.top().second;
    pq.pop();
    
    int ret = (current_time - job_insert_time) + cost;
    current_time += cost;
    return ret;
}

int solution(vector<vector<int>> jobs) {
    sort(jobs.begin(), jobs.end(), cmp);
    
    int answer = 0;
    int j_size = jobs.size();
    int current_time = jobs[0][0];
    
    for(int i=0; i<j_size; ++i) {
        // 현재 시간 이전에 들어온 프로세스들은 insert한다.
        if(jobs[i][0] <= current_time) {
            pq.emplace(-jobs[i][1], -jobs[i][0]);
            continue;
        }
        
        // 만약 현재 시간 이후에 들어온 프로세스이며, 현재 실행가능한 프로세스가 없는 경우 
        if(pq.empty()) {
            current_time = jobs[i][0];
            pq.emplace(-jobs[i][1], -jobs[i][0]);
        } else {
            // 현재 실행가능한 프로세스가 존재하는 경우 우선 1가지 job을 소모시킨다.
            answer += consume_jobs(current_time);
            --i;
        }
    }
    
    //남은 모든 job을 수행시킨다.
    while(!pq.empty()) answer += consume_jobs(current_time);
    return answer/j_size;
}
