#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp(string a, string b){
    return a.length() < b.length();
}

vector<int> solution(string s) {
    vector<int> answer;
    vector<string> subStrings;
    vector<int>::iterator iter;
    
    int size = s.size();
    string subString = "";
    
    for(int i = 1; i < size-1 ; i++){
        subString+=s.at(i);
        if(s.at(i)=='}'){
            subStrings.push_back(subString);
            subString = "";
            i++;
        }
    }
    
    sort(subStrings.begin(), subStrings.end(),cmp);

    for(int i = 0; i<subStrings.size();i++){
        subString = "";
        for(int j=1; j < (subStrings[i].length()-1); j++){
            if(subStrings[i].at(j)!=','){
                subString += subStrings[i].at(j);
            }
            if(subStrings[i].at(j)==',' || j==(subStrings[i].length()-2)){
                int num = stoi(subString);
                iter = find(answer.begin(), answer.end(), num);
                if(iter==answer.end()) answer.push_back(num);
                subString = "";
            }
        }
    }
    return answer;
}


/* 다른 분 풀이..
#include <bits/stdc++.h>
using namespace std;

vector<int> solution(string s) {
    int st[101010]={};
    vector<int> answer;
    string tmp;
    for(char i: s){
        if(i-'0' >=0 && i-'0' <=9){
            tmp += i;
        }
        else{
            if(tmp.length())
                st[stoi(tmp)]++, tmp.clear();
        }
    }
    vector<pair<int, int>> v;
    for(int i =0; i <101010; i++)
        if(st[i])
            v.push_back({st[i], i});
    sort(v.begin(), v.end());
    reverse(v.begin(),v.end());
    for(auto it: v) answer.push_back(it.second);
    return answer;
}

*/
