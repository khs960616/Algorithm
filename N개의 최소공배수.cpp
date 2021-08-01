//프로그래머스 N개의 최대 공배수
//유클리드 호제법

#include <string>
#include <vector>
using namespace std;

int gcd(int a, int b){
    if(b==0) return a;
    return gcd(b, a%b);
}

int lcm(int a, int b){
    int g = gcd(a,b);
    return a*b/g;
}

int solution(vector<int> arr) {
    int answer = 0;
    int s= arr.size();
    if(s==1) return arr[0];
    
    answer = lcm(arr[0], arr[1]);
    for(int i=2; i<s; i++){
        answer = lcm(answer, arr[i]);
    }
    return answer;
}
