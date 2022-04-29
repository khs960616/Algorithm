/*
https://programmers.co.kr/learn/courses/30/lessons/17676
2018 KAKAO BLIND RECRUITMENT

문자열 파싱, 구현 
차후 다시 풀어볼 것

1.lines는 Request의 종료시간이 오름차순으로 정렬되어있다.
2.따라서 만일, i번째 Request의 시작 시간이 i-1번째 종료시간 + 1초를 한 시간보다 작다면, i-1번째 endTime, endTime+1 구간에 i번째 Request에 대한 처리가 진행중일것이다.
3.(endTime-processTime+1)  --> 문제조건에서 시작시간, 종료시간 모두 개구간이므로 범위를 구할때 1ms를 더해주어야한다.

*/

#include <bits/stdc++.h>
#define HOUR_TO_MINUTE 60
#define MINUTE_TO_SECOND 60
#define SECOND_TO_MILISECOND 1000

using namespace std;

int convertTimeToInt(string s) {
    int hour = stoi(s.substr(0, 2));
    int minute = stoi(s.substr(3, 2));
    int second = stoi(s.substr(6, 2));
    int miliSecond = stoi(s.substr(9));
    
    return((((hour * HOUR_TO_MINUTE) + minute) * MINUTE_TO_SECOND) + second) * SECOND_TO_MILISECOND + miliSecond;
}

int convertProcessTime(string s) {
    s.pop_back();
    
    double d = stod(s);
    int processTime = d*1000;
    return processTime;
}

int solution(vector<string> lines) {
    int answer = 0;
    vector<int> startedTimeList;
    vector<int> endTimeList;
    
    for (string line: lines) {
        stringstream stream(line);
        string s, t, year, time;
        stream >> year >> time >> t;
        
        int endTime = convertTimeToInt(time);
        int processTime = convertProcessTime(t);
        startedTimeList.push_back(endTime-processTime+1);
        endTimeList.push_back(endTime);
    }
    
    int lSize = lines.size();
    for (int i=0; i<lSize; ++i) {
        int range = endTimeList[i] + SECOND_TO_MILISECOND;
        
        int cnt = 0;
        for(int j=i; j<lSize; ++j) {
            if (startedTimeList[j] < range) ++cnt;
        }
        
        answer = max(answer, cnt);
    }
    return answer;
}
