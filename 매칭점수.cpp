#include <bits/stdc++.h>
using namespace std;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/42893
  매칭점수 [2019 KAKAO BLIND RECRUITMENT]
  문자열 파싱, 복잡한 구현 
  ---
  
  정규 표현식 또는 문자열 패턴으로 구하고자하는 패턴을 html에서 뽑아야한다. 
  
  1. 검색하는 단어를 찾는 방법
     - 만일 정규표현식으로 표현하고자 한다면, \b(?i)검색한단어\b 로 표현할 수 있다.
       
     - string find를 이용하는 경우, 단어를 찾았을때, 단어의 앞뒤에 알파벳이 존재한다면 갯수를 세지 않는다. 
     
  2. 페이지의 url를 찾는 방법
     - <meta property=\"og:url\" content=\"https:// 문자열을 이용해, 페이지 전체를 탐색하며 직접 파싱하는 방법
     - <meta property=\"og:url\" content=\"(\\S*)\"의 정규표현식을 이용하는 방법이 존재한다.
       테스트 케이스에 url뒤에 공백을 포함하는 case가 있다고 한다. 따라서 .* 대신 S*를 사용한다.
       
  3. 외부 링크를 찾는 방법 
     - 정규표현식을 사용하는 방법 <a href=\"https://(\\S*)\" 
     - 문자열을 이용해, 페이지 전체를 탐색하며 직접 파싱하는 방법
     
 ----
 문제를 풀면서 사실 정규표현식에 대해 익숙하지 않아, 문자열을 일일히 직접 파싱하는 방법을 이용하였으나 정규표현식을 icase flag를 키고 활용했다면 좀 더 간결하게 나왔을 것이다.
 
 ?i   ->match the remainder of the pattern with the following effective flags: gmi
      i modifier: insensitive. Case insensitive match (ignores case of [a-zA-Z])
*/
int word_len = 0;
string META_URL_FORMAT = "<meta property=\"og:url\" content=\"https://";
string EXTERNAL_LINK_FORMAT = "<a href=\"https://";

void make_upper_case(string& word, vector<string>& pages) {
    transform(word.begin(), word.end(),word.begin(), ::toupper);
    for(string& page: pages) {
        transform(page.begin(), page.end(),page.begin(), ::toupper);
    }
    transform(META_URL_FORMAT.begin(), META_URL_FORMAT.end(),META_URL_FORMAT.begin(), ::toupper);
    transform(EXTERNAL_LINK_FORMAT.begin(), EXTERNAL_LINK_FORMAT.end(),EXTERNAL_LINK_FORMAT.begin(), ::toupper);
}

bool is_valid_word(string page, int idx) {
    int page_size = page.length();
    bool ret = true;
    if(idx-1 >= 0) 
        ret &= (!isalpha(page[idx-1]));
    if(idx+word_len < page_size) 
        ret &= (!isalpha(page[idx+word_len]));
    return ret;
}

int get_base_score(string word, string page) {
    int ret = 0;
    int idx = page.find(word);
    while(idx != string::npos) {
        if(is_valid_word(page, idx)) ret++;
        idx = page.find(word, idx+word_len);
    }
    return ret;
}

vector<string> get_external_link(string page) {
    vector<string> ret;
    int idx = page.find(EXTERNAL_LINK_FORMAT);
    while(idx != string::npos) {
        idx += EXTERNAL_LINK_FORMAT.size();
        int e_idx = page.find("\">", idx);
        string link = page.substr(idx, e_idx-idx);
        ret.push_back(link);
        idx = page.find(EXTERNAL_LINK_FORMAT, e_idx+1);
    }
    return ret;
}

string get_page_origin_url(string page) {
    int s_idx = page.find(META_URL_FORMAT);
    int e_idx = 0;
    string ret = "";
    if(s_idx != string::npos) {
        s_idx += META_URL_FORMAT.size();
        int e_idx = page.find("\"/", s_idx);
        ret = page.substr(s_idx, e_idx-s_idx);

        s_idx = page.find(META_URL_FORMAT, e_idx+1);
    }
    
    return ret;
}

struct Page {
    double total_score;
    string url;
    int page_idx;
    int base_score;
    vector<string> external_links;
    
    Page() {}
    Page(string url, int idx, int score, vector<string> v) {
        this->url = url;
        this->page_idx = idx;
        this->base_score = score;
        this->total_score = 0;
        this->external_links = v;
    }
};

map<string, Page*> page_map; 

vector<Page> convert_html_to_object(vector<string>& pages, string& word) {
    vector<Page> ret;
    int len = pages.size();
    for(int i=0; i<len; ++i) {
        string url = get_page_origin_url(pages[i]);
        int base_score = get_base_score(word, pages[i]);
        vector<string> links = get_external_link(pages[i]);
        
        ret.push_back(Page(url, i, base_score, links));
    }
    return ret;
}

bool cmp(Page p1, Page p2) {
    if(p1.total_score == p2.total_score) return p1.page_idx < p2.page_idx;
    return p1.total_score > p2.total_score;
}

int solution(string word, vector<string> pages) {
    make_upper_case(word, pages);
    word_len = word.length();
    int answer = 0;
    
    vector<Page> page_list = convert_html_to_object(pages, word);
    for(Page& p: page_list) page_map[p.url] = &p;
    
    for(Page& p: page_list) {
        p.total_score += p.base_score;
        if(p.external_links.size() == 0) continue;
        
        double link_score = p.base_score;
        link_score /= p.external_links.size();
        for(string link: p.external_links) {
            if(page_map.find(link) == page_map.end()) continue;
            page_map[link]->total_score += link_score;
        }
    }
    
    sort(page_list.begin(), page_list.end(), cmp);
    return page_list[0].page_idx;
}
