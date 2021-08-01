//문자열, 정렬
//숫자를 string으로 변환하여 벡터에 저장한다.
//저장된 벡터의 값들 중, 앞의 원소와 뒤의 원소를 더 한 숫자가 더 큰 순서로 정렬한다. 
//이후 모든 string을 이어붙이면 가장 큰수이다. 

#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool cmp(const string& a, const string& b){
    return a+b > b+a;
}

string solution(vector<int> numbers) {
    string answer = "";
    vector<string> num_strings;
    
    for(int number : numbers){
        num_strings.push_back(to_string(number));
    }
    sort(num_strings.begin(), num_strings.end(), cmp);
    if(num_strings[0] == "0") return "0";
    else{
        int sz = num_strings.size();
        for(int i=0; i< sz;i++){
            answer+=num_strings[i];
        }
    }
    return answer;
}
