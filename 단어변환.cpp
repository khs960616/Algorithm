#include <bits/stdc++.h>
using namespace std;

int answer = 100;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/43163?language=cpp
  단어변환
  ---
  백트래킹
  
  1. 아직 사용하지 않은 word 중에 변환이 가능한 단어를 찾는다.
  2. 변환한 count를 세며, 만일 target까지 도달이 가능한 경우 answer값을 최소값이 되도록 갱신한다.
  
  총 50개의 단어가 존재함.
  총 경우의 수는 50! 임.   target이 배열에 존재하지 않는 경우는 별도 예외처리를 하는게 좋았을까 싶기도함.
*/
bool isConvertible(string s1, string s2) {
    int ret = 0;
    int sSize = s1.size();
    for(int i=0; i<sSize; ++i) {
        if(s1[i] != s2[i]) ret++;
    }
    
    return ret == 1 ? true : false;
}

void solve(string target, string current, int cnt,
          vector<bool> isVisit, vector<string> words) {
    if(answer <= cnt) return;
    
    if(target == current) {
        if(answer > cnt) answer = cnt;
        return;
    }
    
    int wordCnt = words.size();
    for(int i=0; i<wordCnt; ++i) {
        if(isVisit[i]) continue;
        if(!isConvertible(current, words[i])) continue;
        
        isVisit[i] = true;
        solve(target, words[i], cnt+1, isVisit, words);
        isVisit[i] = false;
    }
}

int solution(string begin, string target, vector<string> words) {
    vector<bool> isVisit(words.size(), false);
    solve(target, begin, 0, isVisit, words);
    return answer == 100 ? 0 : answer;
}


/*

다른 사람 풀이. BFS사용함 
근데 의문이 드는게 0번 인덱스부터 bfs를 탐색하는데, isVisit[i]를 true로 돌리면, 과연 모든 케이스가 고려가 되는지? 궁금함.

#include <string>
#include <vector>
#include <queue>

using namespace std;

int visited[50];

int possible(string a, string b)
{
    int i;
    int cnt = 0;

    for(i=0;i<a.length();i++)
    {
        if(a[i] != b[i]) cnt++;
    }

    if(cnt==1) return 1;
    else return 0;
}

int solution(string begin, string target, vector<string> words) {
    int answer = 0;
    queue<pair<string,int>> Q;
    int i;
    string temp;
    int num;

    Q.push(make_pair(begin,0));
    while(!Q.empty())
    {
        temp = Q.front().first;
        num = Q.front().second;
        Q.pop();

        if(temp.compare(target) == 0)
        {
            answer = num;
            break;
        }

        for(i=0;i<words.size();i++)
        {
            if(visited[i]) continue;
            if(possible(temp, words[i]))
            {
                visited[i] = 1;
                Q.push(make_pair(words[i],num+1));
            }
        }
    }

    return answer;
}

*/
