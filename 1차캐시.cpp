//2018 KAKAO BLIND RECRUITMENT [1차 캐시]

#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

#define CACHE_HIT 1
#define CACHE_MISS 5
using namespace std;

int solution(int cacheSize, vector<string> cities) {
    if(cacheSize == 0) return cities.size()*CACHE_MISS;
    
    int answer = 0;
    int last_index = cacheSize-1;
    vector<string> cache;
    vector<string>::iterator it;
    
    //순차적으로 cache에 넣으며 가장 최근에 사용된 원소는 맨 뒤로 옮긴다.
    for(string city: cities){
        transform(city.begin(), city.end(), city.begin(), ::tolower);
        it = find(cache.begin(), cache.end(), city);
        if(it != cache.end()){
            //cache hit
            answer+=CACHE_HIT;
            cache.erase(it);
            cache.push_back(city);
        }else{
            //cache miss
            answer+=CACHE_MISS;
            if(!cache.empty() && cache.size() == cacheSize){
                cache.erase(cache.begin());
            }
            cache.push_back(city);
        }
    }
    return answer;
}
