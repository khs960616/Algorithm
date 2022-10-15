#include <bits/stdc++.h>
#define MAX_SECOND 360001
using namespace std;
/*
    https://school.programmers.co.kr/learn/courses/30/lessons/72414
    2021 KAKAO BLIND RECRUITMENT
    광고 삽입
    --- 
    DP, 누적합
  
    ---
    처음 시도한 풀이 
    0. 로그를 시작시간을 기준으로 정렬한다.
    
    1. 로그를 순회하며, 
      각 로그의 시작점 ~ 로그의 시작점 + 광고의 재생시간을 기준으로 검사한다.
      - 해당 구간내에 시작점이 존재하는 모든 로그 정보를 담아둔다.
      - 해당 구간내에 로그끼리 중복되는 구간과, 해당 구간에 속하는 로그의 갯수를 저장한다.
      
    2. 각 구간별 중복되는 구간의 길이 * 로그의 갯수의 합으로 누적 재생시간을 계산한다.
    3. 누적 재생시간이 가장 긴 경우 해당 구간의 시작점을 답으로 갱신한다. 
    
    >> 00:00:00부터, 각 사용자의 시작 시간을 광고의 시작 시간으로 하여 광고를 배치
       해당 광고 시간과 겹치는 로그를 구한다.
       광고 시간과 로그의 시간에서 겹치는 만큼 더해서 누적 재생시간을 계산하여 값을 갱신해나간다. 
    
    위 방법대로 하는 경우 logs 배열의 길이의 제곱만큼의 복잡도를 요구하게 된다. 따라서 300,000 ^ 2 까지 되므로 시간 초과로 인해 문제를 해결할 수 없게 된다.
    ---
    사용 풀이
    https://tech.kakao.com/2021/01/25/2021-kakao-recruitment-round-1/#%EB%AC%B8%EC%A0%9C-5-%EA%B4%91%EA%B3%A0-%EC%82%BD%EC%9E%85
     
    1. 각 로그의 시작 시간과 종료시간을 초로 변환한 후, 배열에 저장한다.
       이 때 시작 시간인 경우 +1, 종료 시간인 경우 -1을 한다.  
       
       ex) 1분 시작 5분 종료,   2분 시작 5분 종료,   5분 시작 7분 종료
           [0, 1, 1, 0, 0, -1, 0, -1, 0, 0, 0....]   
           (누적합의 개념 - 1분에서 시작해서 5분에 종료된 영상은 각각 1분, 2분, 3분, 4분 에 재생 횟수를 1회씩 늘려야하므로 5에 -1을 해주고 누적합을 계산하면 복잡도를 줄일 수 있다.)
       
    2. 위에서 계산한 배열을 이용해 누적합을 구한다.
       이렇게되면, 각 초별 사용자의 누적된 재생횟수가 나오게 된다.   (이 부분을 생각해내는게 문제를 푸는 키포인트인것 같다.. 이렇게 되면 문제가 단순한 누적합 문제로 바뀌게됨)
       ex) [0, 1, 1, 0, 0, -1, 0, -1, 0, 0, 0....] 
        >  [0, 1, 2, 2, 2, 1, 1, 0, 0, 0, 0....]   
        
    3. 2에서 구한 배열을 누적합을 이용하면 dp[i]는  0부터 시작해서 i초까지의 누적 재생 횟수가 나오게 된다. 
    
    4. 3에서 계산한 값을 이용하면    dp[광고종료시간-1] - dp[광고시작시간-1] 을 하는 경우, 해당 구간의 누적 재생 횟수를 구할 수 있게된다.
       광고 재생시간 범위내에 누적 재생 횟수가 가장 많다는 것은, 해당 구간내에 누적 재생 시간이 가장 길다는 것을 의미한다.
    ---
   
    시간을 초로 변환하는 것 까지는 떠올렸으나, 복잡도를 어떻게 줄여야할지 방법을 찾지 못했다.
    문제에서 누적합 개념을 사용해야한다는 것 자체를 떠올리지 못했다.
    차후 다시 풀어보자.
*/

long long dp[MAX_SECOND];
int video_seconds;
int advertise_seconds;

int convert_string_time_to_integer_second(string time) {
    int hour = stoi(time.substr(0, 2));
    int minute = stoi(time.substr(3, 2));
    int second = stoi(time.substr(6));
    return second+(minute + hour*60)*60;
}

pair<int, int> convert_user_play_time(string s) {
    int start = convert_string_time_to_integer_second(s.substr(0, 8));
    int end = convert_string_time_to_integer_second(s.substr(9));
    return {start, end};
}

void calc_prefix_sum() {
    for(int i=1; i<MAX_SECOND; ++i) dp[i] += dp[i-1];
}

int get_max_value_start_time() {
    long long time = dp[advertise_seconds-1];
    int second = 0;
    
    for (int i=1;i<=video_seconds-advertise_seconds; ++i) {
        long long current_range_play_times = dp[i+advertise_seconds-1] - dp[i-1];
        if(time < current_range_play_times) {
            time = current_range_play_times;
            second = i;
        }
    }
    return second;
}

string get_formmating_string_number(int i) {
    string s = to_string(i);
    if(s.length() == 1) s = "0" + s;
    return s;
}

string convert_integer_second_to_string_time(int time) {
    int hour = (time / 3600);
    int minute = (time-3600*hour) / 60;
    int second = time % 60;

    string ret = get_formmating_string_number(hour) + ":" + get_formmating_string_number(minute);
    return ret + ":" + get_formmating_string_number(second);
}

string solution(string play_time, string adv_time, vector<string> logs) {
    video_seconds = convert_string_time_to_integer_second(play_time);
    advertise_seconds = convert_string_time_to_integer_second(adv_time);
    
    for(string log: logs) {
        pair<int, int> converted_log = convert_user_play_time(log);
        int start_time = converted_log.first;
        int end_time = converted_log.second;
        dp[start_time]+=1;
        dp[end_time]-=1;
    }
    
    calc_prefix_sum();
    calc_prefix_sum();
    int answer_second = get_max_value_start_time();
    return convert_integer_second_to_string_time(answer_second);
}
