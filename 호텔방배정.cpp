#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

vector<long long> solution(long long k, vector<long long> room_number) {
    vector<long long> answer;
    vector<long long> temp;
    map<long long, int> isSelect;
    int s = room_number.size();
    
    for(int i=0;i<s;i++){
        long long current_value = room_number[i];
        
        if(isSelect.find(current_value)==isSelect.end()){
            isSelect[current_value] = current_value+1;
            answer.push_back(current_value);
        }
        else{
            while(1){
                long long find_value = isSelect[current_value];
                
                if(isSelect.find(find_value)==isSelect.end()){
                    isSelect[find_value] = find_value+1;
                    answer.push_back(find_value);
                    for(int i=0;i<temp.size();i++){
                        isSelect[temp[i]] = find_value+1;
                    }
                    temp.clear();
                    break;
                }
                temp.push_back(current_value);
                current_value = find_value;
            }
        }
    }
    return answer;
}
// 처음에 내가 푼 풀이 (효율성 테스트케이스 5,6,7 통과 x)

/*  재귀함수를 이용한 다른 사람의 풀이

#include <string>
#include <vector>
#include <map>
using namespace std;
 
map<long long, long long> m;
 
long long getNextEmptyRoom(long long num) {
    if (m[num] == 0) return num;
    return m[num] = getNextEmptyRoom(m[num]);
}
 
 
vector<long long> solution(long long k, vector<long long> room_number) {
    vector<long long> answer;
 
    for (long long num : room_number) {
        long long emptyRoom = getNextEmptyRoom(num);
        answer.push_back(emptyRoom);
        m[emptyRoom] = emptyRoom + 1;
    }
 
    return answer;
}


*/
