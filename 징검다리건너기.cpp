#include <string>
#include <vector>
#include <algorithm>
#define MAX_ELEMENT 200000000

using namespace std;

int answer;

bool isValid(vector<int> stones, int k, int current_value){
    int v_size = stones.size();
    int cnt = 0;
    for(int i=0; i < v_size ;i++){
        if(stones[i]-(current_value-1)<=0){
            cnt++;
            if(cnt==k) return false;
        }
        else{
            cnt = 0;
        }
    }
    return true;
}

void calc_value(vector<int>stones, int k, int left, int right){
    if(left>right) return;
    int mid = (left+right)/2;
    bool flag = isValid(stones,k,mid);
    
    if(flag){
        if(answer < mid) answer = mid;
        calc_value(stones,k,mid+1,right);
    }else{
        calc_value(stones,k,left,mid-1);
    }
}

int solution(vector<int> stones, int k) {
    calc_value(stones,k,1,MAX_ELEMENT);
    return answer;
}
