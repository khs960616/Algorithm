//2020 카카오 인턴쉽
//수식 최대화 
//문자열 처리, 브루트포스

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool isOp(char c){
    if(c=='+' || c =='-' || c == '*') return true;
    else return false;
}

long long calc(vector<long long> numbers, vector<char>op, vector<char> &opv){
    int opv_size = opv.size();
    long long calc;
    for(int i=0; i<opv_size; i++){
        for(int j=0; j< op.size(); j++){
            if(opv[i] == op[j]){
                if(op[j] == '+'){
                    calc = numbers[j]+numbers[j+1];
                } else if(op[j] == '*'){
                    calc = numbers[j]*numbers[j+1];
                } else if(op[j] == '-'){
                    calc = numbers[j]-numbers[j+1];
                }
                numbers[j] = calc;
                numbers.erase(numbers.begin()+(j+1));
                op.erase(op.begin()+j);
                j--;
            }
        }
    }
    return abs(calc);
}

long long solution(string expression) {
    long long answer = 0;
    int esz = expression.size();
    string num = "";
    vector<long long> numbers;
    vector<char> op;
    vector<char> opv;
    
    for(int i=0; i<esz; i++){
        if(isOp(expression[i])){
            numbers.push_back(stoll(num));
            num = "";
            op.push_back(expression[i]);
            if(find(opv.begin(), opv.end(), expression[i]) == opv.end()){
                opv.push_back(expression[i]);
            }
        } else{
            num+=expression[i];
        }
    }
    int op_size = op.size();
    int opv_size = opv.size();
    numbers.push_back(stoll(num));
    sort(opv.begin(),opv.end());
    
    do{
        long long c = calc(numbers, op, opv);
        if(answer < c) answer = c;
    }while(next_permutation(opv.begin(),opv.end()));
    return answer;
}
