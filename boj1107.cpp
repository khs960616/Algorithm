#include <bits/stdc++.h>

using namespace std;

/*
https://www.acmicpc.net/problem/1107
리모컨
------------
브루트 포스
*/

#include <bits/stdc++.h>

using namespace std;

vector<bool> isBroken(10 , false);

bool isMakable(string s) {
    for(char c: s) {
        if(isBroken[c-'0']) return false;
    }
    return true;
}

int main() {
    int target;
    int n, answer;      
    cin >> target >> n;
    answer = abs(target-100); 

    for(int i=0; i<n; ++i) {
        int broken = 0;
        cin >> broken;
        isBroken[broken] = true;
    }
    /*
      ex) 499,999
          2
          0,9 
          >>    511,111 등 50만 이상의 숫자도 고려해야한다. 이떄 입력가능한 수의 범위가 0~9사이이므로 1000000까지만 고려해주면 모든 case가 커버 가능함 
    */
    for(int i=0; i<=1000000; ++i) {
        string num = to_string(i);
        if(isMakable(num)) {
            int cost = abs(target-i) + num.size();
            answer = min(answer, cost);
        }
    }
    cout << answer;

    return 0;   
}


/*
  오답 1 
  반례)
  9
  0 2 3 4 5 6 7 8 9
  9

  N의 상한선이 500,000 6자리 string이므로, 다음과 같이 재귀로 짜면 10^6 정도로 계산이 가능할 것이라 생각했음 
  (+, - 로 갈 수 있는 경우, 버튼을 눌러서 가는 경우를 계산)
  이 때, target.size() == current.size()과 같은 종료 조건으로 인해 누를 수 있는 오류가 나게됨 .
*/
// vector<bool> isBroken(10 , false);

// void calcMin(int& answer, const string target, string current) {
//     if(target.size() == current.size()) {
//         int value = stoi(current);
//         int diff = abs(stoi(target)-value);
//         if(value == 0) diff+=1;
//         while(value!=0) {
//             diff+=1;
//             value /= 10;
//         }
//         answer = min(answer, diff);
//         return;
//     }

//     for(int i=0; i<10; ++i) {
//         if(isBroken[i]) continue;
//         char c = i+48;
//         calcMin(answer, target, current+c);
//     }
// }

// int main() {
//     string target;
//     int n, answer;      
//     cin >> target >> n;
//     answer = abs(stoi(target)-stoi("100")); 

//     for(int i=0; i<n; ++i) {
//         int broken = 0;
//         cin >> broken;
//         isBroken[broken] = true;
//     }
//     calcMin(answer, target, "");
//     cout << answer;

//     return 0;   
// }
