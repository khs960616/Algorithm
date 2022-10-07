#include <bits/stdc++.h>
using namespace std;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/17678
  2018 KAKAO BLIND RECRUITMENT
  셔틀버스
  ---
  구현, 시뮬레이션, 문자열 처리 
  
  구하고자하는 것 : 콘이 셔틀을 타고 사무실로 갈 수 있는 도착 시각 중 제일 늦은 시각
  
  1. 마지막에 출발하는 버스의 시간을 구한다.
  2. 대기열에 대기중인 승객들을 오름차순으로 정렬한 후, 마지막 버스보다 늦게 도착한 승객들을 제거한다. 
  3. 출발 시간을 09:00으로 설정하여, t분 간격으로 n번 출발 시킨다. 이 때, 만일 탑승할 수 있는 승객이 존재한다면, 각 버스에 m명 까지만 태운다.
  
  4. (3)번의 과정이 끝나면 3가지 결과값을 얻을 수 있다.  [마지막 탑승한 버스의 출발시간, 마지막 탑승한 버스에 탄 승객의 수, 마지막으로 탑승한 승객의 번호]
     이를 이용해 경우의 수를 나눠서 생각해보자.
     
     
     case 1 : 마지막 탑승한 버스의 출발 시간이 (1)에서 구한 시간보다 작은 경우 
              - 이 경우 마지막 버스에 탑승하는 승객은 0명이므로 (1)번에서 구한 시간이 정답이 된다. 
              
     case 2 : 마지막 탑승한 버스의 출발 시간이 (1)에서 구한 시간과 같은 경우 
              - 이 경우 해당 버스에 승객이 가득차 있는지, 아닌지를 구분해야한다.
              case 2-1: 승객이 가득차지 않은 경우 : 각 버스에 탈수 있는 가장 늦은 시간은, 버스가 도착하는 시간과 같다. 따라서 (1)번에서 구한 시간이 정답이 된다.
              case 2-2: 승객이 가득찬 경우 : 이 경우 콘은 맨 마지막에 온 승객보다 1분만 일찍오면 버스에 탑승할 수 있다. 따라서 마지막으로 탑승한 승객의 시간에서 1분을 뺀 것이 답이 된다.
              
    ----------------
    문제 풀면서 생각해본것들 .. 
    
    문제에서 주어지는 데이터를 전처리하면 좀 더 쉽게 풀 수 있을까도 문제 풀 때 생각해볼만한듯..
    
    무작정 코드부터 짜지좀 말자.. 어떤 알고리즘이 필요할지, 문제 해결을 위해 필요한 기능 리스트는 무엇인지 먼저 정리하자.
    기능 단위로 쪼개고, 기능 내에서도 추상화 레벨을 생각해서 쪼개면, 좀 더 디버깅하기 쉽고, 코드도 잘 읽히는 기분.. 
*/
string make_number_format(string s) {
    int len = s.size();
    if(len == 1) s = "0" + s;
    return s;
}

string get_formatting_time(int hour, int minute) {
    string hour_string = to_string(hour);
    string hour_minute = to_string(minute);
    return make_number_format(hour_string) + ":" + make_number_format(hour_minute) ;
}

string get_last_bus_time(int n, int t) {
    int hour = 9 + (((n-1)*t) / 60);
    int minute = ((n-1)*t) % 60;
    
    return get_formatting_time(hour, minute);
}

void preprocessin_timetable(vector<string>& timetable, string last_bus_start_time) {
    sort(timetable.begin(), timetable.end());
    
    while(1) {
        if(timetable.empty() || (timetable[timetable.size()-1] <= last_bus_start_time)) return;
        timetable.pop_back();
    }
}

string add_bus_time(string time, int t) {
    int current_hour = stoi(time.substr(0, 2));
    int current_minute = stoi(time.substr(3));
    
    if(t > 0) {
        current_hour += ((current_minute+t) / 60);
        current_minute = (current_minute+t) % 60;
    } else {
        if(current_minute+t < 0) current_hour--;
        current_minute = (current_minute+t+60) % 60;
    }
    return get_formatting_time(current_hour, current_minute);
}

string solution(int n, int t, int m, vector<string> timetable) {
    string last_bus_start_time = get_last_bus_time(n, t);
    preprocessin_timetable(timetable, last_bus_start_time);
    
    string current_time = "09:00";
    int total_passenger_capacity = n*m;
    int passenger_idx = 0;
    int iter_size = min((int)timetable.size(), total_passenger_capacity);
    int passenger_cnt = 0;
        
    for(int i=0; i<n; ++i) {
        if(passenger_idx == iter_size) break;
        passenger_cnt = 0;
        for(;passenger_idx<iter_size;) {
            if(passenger_cnt == m || timetable[passenger_idx] > current_time) break;
            ++passenger_cnt;
            ++passenger_idx;
        }
        if(i!=n-1) current_time = add_bus_time(current_time, t);
    }
    
    string ret = last_bus_start_time;
    if(current_time == last_bus_start_time && passenger_cnt == m) {
        string last_passenger_time = timetable[passenger_idx-1];
        ret = add_bus_time(last_passenger_time, -1);
    }
    
    return ret;
}
