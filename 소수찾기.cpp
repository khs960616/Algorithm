//브루트포스
//에라토스테네스의 체, Set, Sort, 순열 

//next_permutation은 모든 순열을 구해주는 함수가 아니다. 사전 순으로 다음번 순열을 찾아준다. 따라서 정렬되있지않다면 모든 경우가 탐색되지 않을 수 있다.
//이점을 처음에 모르고 짰다가 오류가 발생했었다.
//중복되는 자료를 날리기 위해 Set을 사용하였다. 

#include <string>
#include <vector>
#include <algorithm>
#include <set>
#define MAX_NUM 10000000 
using namespace std;

void init_prime(vector<bool> &isPrime){
    isPrime[0] = isPrime[1]  = false;
    for(int i = 2; i <= MAX_NUM; i++){
        if(!isPrime[i]) continue;
        for(int j = i*i; j <= MAX_NUM; j+=i){
            isPrime[j] = false;
        }
    }
}

int solution(string numbers) {
    set<int> stg;
    int nsz = numbers.size();

    vector<bool> isPrime(MAX_NUM, true);
    init_prime(isPrime);
    sort(numbers.begin(), numbers.end());

    do{
        for(int i=0; i<nsz;i++){
            int n = stoi(numbers.substr(0,i+1));
            if(isPrime[n]) stg.insert(n);
        }
    }while(next_permutation(numbers.begin(), numbers.end()));

    return stg.size();
}
