#include<bits/stdc++.h>
using namespace std;

/*
  1. 접미사 배열을 만든 후, 각 접미사 배열을 사전 순으로 정렬시킨다.
  2. 중복을 제거하기 위해 정렬된 접미사 배열중, 인접한 접미사 배열끼리의 최대 접두사 길이를 적어둔다.
  3. 각 접미사 배열에서 나올 수 있는 부분 문자열은 (접미사의 길이 - 최대 접두사의 길이) 이다. 
  4. k값에 도달할 때까지 cnt값을 증가시킨다.
  
  cnt값이 k에 도달한 경우 현재 접미사.substr(0, k-cnt+v[i].second)가 답이 된다.
  
  v[i].second를 더하는 이유는, 최대 접두사의 길이가 0이 아니면, 해당 길이 만큼 사전순에서 앞선 접미사에서 문자열 cnt값이 더해져있기 때문이다.
  
  ---
  
  ex)
  string s = "food";
  
  s에서 파생될 수 있는 접미사 배열
  [d, od, ood, food] 이를 사전순으로 정렬하면 [d, food, od, ood]가 된다.
  
  이때 인접한 두개의 단어끼리의 최대 접두사 길이를 구한다.
  d는 맨 처음 원소이므로 x
  food는 d와 공유하는 접두사가 없으므로 0
  od 는 food와 공유하는 접두사가 없으므로 0
  ood는 od와 접두사 o를 공유하므로 1 
  
  이제 각 접미사에서 파생되는 부분 문자열을 확인해보면
  d  -> d
  food -> f, fo, foo, food
  od -> o, od
  ood -> o, oo, ood      (o는 중복되는 부분 문자열이므로 제외되어야한다.) 
*/

string s;

bool cmp(pair<int, int> a, pair<int, int> b) {
	return s.substr(a.first) < s.substr(b.first);
}

int main(int argc, char** argv) {
	int test_case;
	int T;
	cin>>T;

	for(test_case = 1; test_case <= T; ++test_case) {
		int k;
        cin >> k >> s;
        int len = s.length();
        vector<pair<int, int> > v;
        for(int i=0; i<len; ++i) v.push_back({i, 0});
        sort(v.begin(), v.end(), cmp);
        
        for(int i=0; i<len-1; ++i) {
        	string s1 = s.substr(v[i].first);
            string s2 = s.substr(v[i+1].first);
            int m = min(s1.length(), s2.length());
            int cnt = 0;
            for(int i=0; i<m; ++i) {
            	if(s1[i] != s2[i]) break;
                ++cnt;
            }
            v[i+1].second+=cnt;
        }
        
        int cnt = 0;
        string answer = "none";
        for(int i=0; i<len; ++i) {
        	string current = s.substr(v[i].first);
            int sub_cnt = current.length() - v[i].second;
            if(cnt+sub_cnt < k) {
            	cnt+=sub_cnt;
                continue;
            }
            answer = current.substr(0, k-cnt+v[i].second);
            break;
        }
        cout << '#' << test_case << ' ' << answer << '\n';
	}
	return 0;
}
