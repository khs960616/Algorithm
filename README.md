# Algorithm
Boj - algorithm

## How to Solve it
```
  1. 문제를 이해한다.
  2. 문제를 익숙한 용어를 재정의한다.
  3. 어떻게 해결할 것인지 계획을 세운다.
  4. 계획을 검증한다.
  5. 프로그램으로 구현한다.
  6. 어떻게 풀었는지 돌아보고, 개선할 방법이 있는지 찾아본다.
```
---
### STL 시퀸스 기반 컨테이너 vs 노드기반 컨테이너

Sequence containers implement data structures that can be accessed sequentially. 
데이터를 선형으로 저장, 삽입된 요소의 순서가 그대로 유지됨

STL 구현에서의 Sequence containers : array, vector, dequeue, forward_list, list
vector : 객체의 요소 추가, 삭제 시 자동으로 메모리를 재할당함, index를 활용한 임의접근이 가능함


Associative containers implement sorted data structures that can be quickly searched (O(log n) complexity). 
STL 구현에서의 Associative containers : Set, map, multiSet, multimap

Container adaptors
Container adaptors provide a different interface for sequential containers. 
종류 : stack, queue, priority_queue 


성능 퍼포먼스 관련 자료 : 
https://baptiste-wicht.com/posts/2012/12/cpp-benchmark-vector-list-deque.html
https://nonuruzun.medium.com/stl-container-performance-3ec5a8fbc3be

---
### 행렬 거듭 제곱을 이용한 선형 점화식 구하기

https://driip.me/00556a4c-0782-4c5b-a86a-8e27e5f4ac1b

---
### Meet in the middle
https://www.secmem.org/blog/2019/03/08/meet-in-the-middle/

---
### Rabin-Karp 알고리즘을 이용한 2차원 문자열 벡터의 패턴 매칭
https://www.geeksforgeeks.org/rabin-karp-algorithm-for-pattern-searching-in-matrix/

---
### 누적합 구하기
https://tech.kakao.com/2022/01/14/2022-kakao-recruitment-round-1/#%EB%AC%B8%EC%A0%9C-6-%ED%8C%8C%EA%B4%B4%EB%90%98%EC%A7%80-%EC%95%8A%EC%9D%80-%EA%B1%B4%EB%AC%BC

6번 문제.. 쩐다.

---
### 정규표현식 
https://velog.io/@koseungbin/%EC%A0%95%EA%B7%9C-%ED%91%9C%ED%98%84%EC%8B%9D

