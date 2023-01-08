#include <bits/stdc++.h>

using namespace std;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/135807
  숫자 카드 나누기
  유클리드 호제법, 최대 공약수
  
  ---
  구하고자 하는 것 : 주어진 두 배열에 대해, 한 쪽 배열의 원소는 모두 나눌 수 있고, 한쪽 배열의 모든 수를 나눌 수 없는 수 중 가장 큰 값 
  - (만족하는 원소가 없다면 0을 return 해야한다.)
  
  sol)
    1. 두 배열에 대해서 최대 공약수를 구한다.
       (한 쪽 배열의 모든 숫자를 나눌 수 있기 위해서는, 공약수가 존재해야한다.)
    
    2. arrayA의 최대 공약수로 arrayB의 모든 원소를 나눌 수 없는지 확인한다.
    3. arrayB의 최대 공약수로 arrayA의 모든 원소를 나눌 수 없는지 확인한다.
    4. 
      -> 특정 배열의 모든 원소를 나눌 수 있는 값은, 해당 배열의 최대 공약수의 약수들의 집합이다.
      -> 최대 공약수로 나눌 수 있는 숫자는, 최대 공약수의 약수로도 나눌 수 있다.     
      위 두가지 특징으로 인해 2 또는 3에서 구해진 값이 있다면, 해당 값 중 큰 값이 정답이 된다.
*/
int get_gcd(vector<int> arr, int size) {
    if(size == 1) return arr[0];
    int ret = gcd(arr[0], arr[1]);
    for(int i=2; i<size; ++i) ret = gcd(ret, arr[i]);
    return ret;
}

bool is_answer(vector<int> arr, int divider) {
    for(int i: arr) if(i % divider == 0) return false;
    return true;
}

int solution(vector<int> arrayA, vector<int> arrayB) {
    int answer = 0;
    int a_gcd = get_gcd(arrayA, arrayA.size());
    int b_gcd = get_gcd(arrayB, arrayB.size());
    
    if(is_answer(arrayB, a_gcd)) answer = max(answer, a_gcd);
    if(is_answer(arrayA, b_gcd)) answer = max(answer, b_gcd);
    return answer;
}
