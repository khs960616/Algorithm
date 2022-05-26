#include <bits/stdc++.h>

using namespace std;

/*
https://www.acmicpc.net/problem/5430
문자열 파싱, 구현
*/
void parseString(string s, deque<int>& v) {
    s = s.substr(1, s.size()-2);
    stringstream ss(s);
    string token;
    int idx = 0;
    while (getline(ss, token, ',')){
        v[idx++] = stoi(token);
    }
}

string makeString(deque<int> v, bool isFront) {
    int vSize = v.size();
    string ret = "[";

    if(isFront) {
        for(int i=0; i<vSize; ++i) {
            ret += to_string(v[i]);
            if(i!=vSize-1) ret += ",";
        }
    } else {
        for(int i=vSize-1; i>=0; --i) {
            ret += to_string(v[i]);
            if(i!=0) ret += ",";
        }
    }
    ret += "]\n";
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t--) {
        string op;
        cin >> op;

        int n;
        string s;
        cin >> n >> s;
        deque<int> v(n, 0);
        parseString(s, v);

        bool errorFlag = false;
        bool isFront = true;
        
        for(char c: op) {
            if(c == 'R') {
                isFront = !isFront;
            } else {
                if(v.size() == 0) {
                    errorFlag = true;
                    break;
                }
                
                if(isFront) v.pop_front();
                else v.pop_back();
            }
        }

        if(errorFlag) cout  << "error\n";
        else cout << makeString(v, isFront);
    }
    
    return 0;   
}



/*  시간 초과된 코드 
#include <bits/stdc++.h>

using namespace std;

void parseString(string s, vector<int>& v) {
    s = s.substr(1, s.size()-2);
    stringstream ss(s);
    string token;
    int idx = 0;
    while (getline(ss, token, ',')){
        v[idx++] = stoi(token);
    }
}

string makeString(vector<int> v, bool isFront) {
    int vSize = v.size();
    string ret = "[";

    if(isFront) {
        for(int i=0; i<vSize; ++i) {
            ret += to_string(v[i]);
            if(i!=vSize-1) ret += ",";
        }
    } else {
        for(int i=vSize-1; i>=0; --i) {
            ret += to_string(v[i]);
            if(i!=0) ret += ",";
        }
    }
    ret += "]\n";
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t--) {
        string op;
        cin >> op;

        int n;
        string s;
        cin >> n >> s;
        vector<int> v(n, 0);
        parseString(s, v);

        bool errorFlag = false;
        bool isFront = true;
        
        for(char c: op) {
            if(c == 'R') {
                isFront = !isFront;
            } else {
                if(v.size() == 0) {
                    errorFlag = true;
                    break;
                }
                
                if(isFront) v.erase(v.begin());
                else v.pop_back();
            }
        }

        if(errorFlag) cout  << "error\n";
        else cout << makeString(v, isFront);
    }
    
    return 0;   
}

*/
