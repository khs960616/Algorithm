#include <bits/stdc++.h>
using namespace std;

/*
https://programmers.co.kr/learn/courses/30/lessons/17683
2018 KAKAO BLIND RECRUITMENT
[3차] 방금그곡
문자열 파싱, 문자열 변환
-----
C#,D#,F#,G#,A# 5개의 음은 1분당 1개씩 재생되는 음임에도 불구하고 길이가 2이다. 따라서 문자열의 길이를 이용해 재생시간등을 관리하기 어렵게 만듬.
또한 부분 문자열로 비교할때, substr을 이용하고자할 때,
m = ABC, 악보정보 : ABC# 인 경우, ABC는 ABC#의 substr이지만,  C!=C# 두개는 다른 음이므로 문제 요구사항과 맞지 않다.

A~G까지 7개의 범위내의 알파뱃만 사용되고 있으므로 뒤에 #이 붙은 음표의 경우, 앞의 문자에 7을 더해 다른 알파벳으로 변환 후 #을 제거한후 비교하면 위에서 제시한 문제점들이 해결됨.

*/

void convertCrossHatch(string& s) {
    int stringSize = s.size();    
    for(int i=stringSize-1; i>0; --i) {
        if(s[i] == '#') {
            s[i-1]+=('G'-'A'+1);
            s.erase(i, 1);
            --i;
        }
    }
}

vector<string> parseMusicInfo(string info) {
    vector<string> tokens;
    string token;
    stringstream ss(info);
    while(getline(ss, token, ',')) {
        tokens.push_back(token);
    }
    return tokens;
}

int getMinutes(string start, string end) {
    int startTime = stoi(start.substr(0, 2))*60 + stoi(start.substr(3, 2));
    int endTime = stoi(end.substr(0, 2))*60 + stoi(end.substr(3, 2));
    return endTime-startTime;
}

string listenString(string musicInfo, int listenTime) {
    int musicTime = musicInfo.size();
    if(musicTime == listenTime) return musicInfo;
    
    string result = "";
    if(musicTime > listenTime) {
        result = musicInfo.substr(0, listenTime);
    } else {
        result = musicInfo;
        int i = listenTime-musicTime;
        
        while(i>0) {
            result += musicInfo.substr(0, i);
            i-=musicTime;
        }
    }
    
    return result;
}

string solution(string m, vector<string> musicinfos) {
    int maxTime = -1;
    string answer = "(None)";
    map<int, vector<string>> mp;
    convertCrossHatch(m);
    
    for(string music: musicinfos) {
        vector<string> tokens = parseMusicInfo(music);
        int radioTime = getMinutes(tokens[0], tokens[1]);
        convertCrossHatch(tokens[3]);
        
        string s = listenString(tokens[3], radioTime);
        if(s.find(m) == std::string::npos) continue;
        if(maxTime<radioTime) maxTime = radioTime;

        mp[radioTime].push_back(tokens[2]);
    }

    for(string s: mp[maxTime]) {
        answer = s;
        break;
    }
    
    return answer;
}
