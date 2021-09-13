//2018 KAKAO BLIND RECRUITMENT
//문자열, map

#include <string>
#include <ctype.h>
#include <map>
#include <algorithm>

using namespace std;

int solution(string str1, string str2) {
    map<string, int> a;
    int asize=  str1.size(); int bsize = str2.size();
    int intersection = 0; int unionCnt = 0;
    
    for(int i=0; i<asize-1; i++){
        string s = str1.substr(i, 2);
        if(isalpha(s[0]) && isalpha(s[1])){
            unionCnt++;
            transform(s.begin(), s.end(), s.begin(), ::toupper);
            if(a.find(s) == a.end()){
                a[s] = 1;
            } else{
                a[s]++;
            }
        }
    }
    
    for(int i=0; i<bsize-1; i++){
        string s = str2.substr(i, 2);
        if(isalpha(s[0]) && isalpha(s[1])){
            transform(s.begin(), s.end(), s.begin(), ::toupper);
            if(a.find(s) != a.end() && a[s]){
                intersection++;
                a[s]--;
            }else{
                unionCnt++;
            }
        }
    }
    if(unionCnt == 0) return 65536;
    return intersection*65536/unionCnt;;
}
