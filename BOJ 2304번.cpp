//https://www.acmicpc.net/problem/2304
//백준 2304번 창고다각형 문제
/*
1. 가장 높은 기둥을 찾는다.
2. 가장 높은 기둥을 기준으로 왼쪽 기둥들, 오른쪽 기둥들을 나눈다.
3. 2번에서 구한 기둥들을 높이순으로 정렬한다. 
4. 현재 가장 긴 높이를 가진 기둥과 이전에 가장 높은 기둥을 기준으로 넓이를 연산한다. 만일, 현재 가장 긴 높이를 가진 기둥이 이전의 기둥보다 앞선 순서라면 연산하지 않는다. (물이 고이면 안되기 때문에)

구현, 정렬
https://codecollector.tistory.com/775 다른 분 풀이법
*/

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

bool cmp_positions(pair<int, int> a, pair<int, int> b){
    return a.first < b.first;
}

bool cmp_height(pair<int, int> a, pair<int, int> b){
    return a.second > b.second;
}

void calc_area(int &area, vector<pair<int,int>> target,
               int max, int max_idx, int type){

    if(!target.size()) return;
    int final_idx = type==0 ? target[0].first : target[target.size()-1].first;
    int prev_idx = max_idx, prev_height = max;
    sort(target.begin(), target.end(), cmp_height);

    for(pair<int, int> pillar : target){
        if(type==0 && prev_idx < pillar.first) continue;
        if(type==1 && prev_idx > pillar.first) continue;
        int width =  abs(prev_idx - final_idx);
        int height = prev_height - pillar.second;
        area -= (width * height);
        if(pillar.first == final_idx) break;
        prev_idx = pillar.first;
        prev_height = pillar.second;
    }
    return;
}

int main() {
    int n, l, h;
    int max=0, max_idx=0;
    int base_area = 0;
    vector<pair<int, int>> pillars;
    vector<pair<int, int>> left;
    vector<pair<int, int>> right;
    cin >> n;

    for(int i=n; i>0; i--){
        cin >> l >> h;
        pillars.push_back(make_pair(l, h));
        if(h > max){
            max = h;
            max_idx = l;
        }
    }
    sort(pillars.begin(), pillars.end(), cmp_positions);  
    base_area = (pillars[n-1].first - pillars[0].first + 1) * max;

    for(pair<int, int> pillar : pillars){
        if(pillar.first < max_idx) left.push_back(pillar);
        else if(pillar.first > max_idx) right.push_back(make_pair(pillar.first+1, pillar.second));
    }

    calc_area(base_area, left, max, max_idx, 0);
    calc_area(base_area, right, max, max_idx+1, 1);

    cout << base_area;
    return 0;
}
