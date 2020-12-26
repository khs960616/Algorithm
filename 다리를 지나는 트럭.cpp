#include <string>
#include <vector>
#include <queue>

using namespace std;

struct vector_info{
    int time;
    int weight;
};

int solution(int bridge_length, int weight, vector<int> truck_weights) {
    int answer = 0;
    int size = truck_weights.size();
    int pre_weight = 0, current_index=0;
    queue<vector_info> on_bridge;
    
    for(int time = 0 ; current_index < size ; time++){
    
        if((time-on_bridge.front().time) == bridge_length){
            pre_weight -= on_bridge.front().weight;
            on_bridge.pop();
        }
        
        int current_weight = (pre_weight + truck_weights[current_index]);
        
        if(weight >= current_weight){
            pre_weight = current_weight;
            struct vector_info temp;
            temp.time = time;
            temp.weight = truck_weights[current_index++];
            on_bridge.push(temp);
        }
    }
    
    while(!(on_bridge.size()==1)){
        on_bridge.pop();
    }
    
    answer = on_bridge.front().time + bridge_length + 1;
    return answer;
}
