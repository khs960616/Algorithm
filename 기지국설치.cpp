#include <bits/stdc++.h>
using namespace std;

int N = 0, W = 0;

/*  
  https://school.programmers.co.kr/learn/courses/30/lessons/12979
  기지국설치
  ---
  시뮬레이션
*/
int get_empty_space(int current_station, int next_station) {
    int current_end_point = (current_station + W) > N ? N : current_station + W;
    int next_start_point = (next_station - W) > 1 ? next_station - W : 1;
    return (next_start_point - current_end_point) - 1;    
}

int solution(int n, vector<int> stations, int w) {
    int answer = 0;
    int station_cnt = stations.size();
    int station_area_size = 2*w + 1;
    N = n;
    W = w;
    
    for(int i=0; i<station_cnt-1; ++i) {
        int empty_space = get_empty_space(stations[i], stations[i+1]);
        if(empty_space > 0) {
            int add_station_cnt = ceil((float)empty_space / station_area_size);
            answer+=add_station_cnt;
        }
    }
    
    int first_station_start_point = (stations[0]-w) > 1 ? stations[0]-w : 1;
    int last_station_end_point = (stations[station_cnt-1]+w) > n ? n : stations[station_cnt-1]+w;
    
    if(first_station_start_point > 1) {
        answer += ceil((float)(first_station_start_point-1)/station_area_size);
    }
    
    if(last_station_end_point < n) {
        answer += ceil((float)(n-last_station_end_point)/station_area_size);
    }
    return answer;
}



/*
다른 사람 풀이, 로직은 동일하나 훨씬 깔끔한듯 

#include <bits/stdc++.h>
using namespace std;

int solution(int n, vector<int> stations, int w)
{
    int ret = 0; 
    int prev = 0;
    for(int station : stations){
        int a = (station - w - 1) - prev;
        int b = (int)ceil((double)a / (double)(w * 2 + 1));
        ret += max(0, b);
        prev = station + w; 
    }
    ret += (int)ceil((double)(n - prev)/ (double)(w * 2 + 1)); 
    return ret;  
}
*/
