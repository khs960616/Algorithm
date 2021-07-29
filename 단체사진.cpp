//알고리즘 : 브루트포스. 순열

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iostream>
using namespace std;

void init(vector<char>& line){
    line.push_back('A');
    line.push_back('C');
    line.push_back('F');
    line.push_back('J');
    line.push_back('M');
    line.push_back('N');
    line.push_back('R');
    line.push_back('T');
}

int calc_distance(vector<char> &photo_line, char fr1, char fr2){
    int fr1_idx, fr2_idx;
    int result = 0;
    for(int i=0; i<8; i++){
        if(photo_line[i] == fr1) fr1_idx = i;
        if(photo_line[i] == fr2) fr2_idx = i;
    }
    result = abs(fr1_idx-fr2_idx);
    return result-1;
}

bool isTrue(vector<string>& data, vector<char> &photo_line, int n){
    char fr1, fr2, cmp_op;
    int distance_condition = 0;
    
    for(int i=0; i<n; i++){ 
        fr1 = data[i][0];
        fr2 = data[i][2];
        cmp_op = data[i][3];
        distance_condition = (data[i][4] - '0');  
        int distance = calc_distance(photo_line, fr1, fr2); //실제 두 점사이의 거리 
        
        if(cmp_op == '>'){
            if(distance_condition >= distance){ //실제 두점 사이의 거리보다 주어진 조건이 더 크다면 조건에 만족하지 않는다. 
                return false;
            }  
        }else if(cmp_op == '<'){
            if(distance_condition <= distance){ //실제 두점 사이의 거리보다 주어진 조건이 더 작다면 조건에 만족하지 않는다.
                return false;
            }
        }else if(cmp_op == '='){
            if(distance_condition != distance){
                return false;
            }
        }
    }
    return true;
}

int solution(int n, vector<string> data) {
    vector<char> photo_line;
    int answer = 0;
    init(photo_line);
    
    do{
        if(isTrue(data, photo_line, n)){
            answer++;
        }
    }while(next_permutation(photo_line.begin(), photo_line.end()));

    return answer;
}
