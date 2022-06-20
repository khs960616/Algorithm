#include <bits/stdc++.h>
using namespace std;

vector<int> inOrder;
vector<int> postOrder;
map<int, int> valueToInOrderIdx;


/*
https://www.acmicpc.net/problem/2263
트리의 순회
--- 
다시 풀어볼것
*/
void printPreOrder(int inStart, int inEnd, int postStart, int postEnd) {
    if(inStart > inEnd || postStart > postEnd) return;

    int root = valueToInOrderIdx[postOrder[postEnd]];
    int leftSubTreeSize = root - inStart;
    cout << inOrder[root] << ' ';

    printPreOrder(inStart, root-1, postStart, postStart+leftSubTreeSize-1);
    printPreOrder(root+1, inEnd, postStart+leftSubTreeSize, postEnd-1);
}

int main() {
    int n;
    cin >> n;
    inOrder = vector<int>(n, 0);
    postOrder = vector<int>(n, 0);

    for(int i=0; i<n; ++i) {
        cin >> inOrder[i];
        valueToInOrderIdx[inOrder[i]] = i;
    }
    for(int i=0; i<n; ++i) cin >> postOrder[i];

    printPreOrder(0, n-1, 0, n-1);
    return 0;   
}


/*

1. Post Order로 출력되는 경우 항상 맨 마지막에 나오는 원소가 루트 노드이다.
2. In Order로 출력된 결과값은 Root값의 Index를 기준으로 좌측 서브트리, 우측 서브트리가 나뉜다.
(또한 InOrder로 출력되는 맨 첫번째 원소는 항상 가장 왼쪽에 위치한 leaf임)

ex) 
    4
  5   6  
1  2    7
    3
    
In Order 출력 :  1 5 2 3 4 6 7
Post Order 출력 : 1 3 2 5 7 6 4   

Post Order 출력에서 현재 트리의 Root를 구한다
 1 3 2 5 7 6 (4) 
> Root : 4

루트의 값을 출력한다.

In Order 출력에서 왼쪽 트리와 오른쪽 트리를 구한다. (왼쪽 서브트리의 사이즈를 구한다.)
(1,5,2,3)  4 (6, 7)   > 왼쪽 서브트리의 길이는 4이다. 이를 이용하면 

Post Order에서 현재 검사하고 있는 트리의 가장 왼쪽값 + 위에서 구한 사이즈를 하면 각 서브트리를 쪼갤 수 있다. (두 출력방식은 원소의 출력 순서가 다른 것일 뿐이지 실질적으로 트리의 구성은 완전히 같은 트리이므로)
(1,3,2,5) (7,6) 4 

이때 line 62 ~ 68번째 과정을 각 왼쪽서브트리, 오른쪽 서브트리에 대해서 leaf에 도달할 때까지 반복하면 Post Order 출력을 구할 수 있다.
*/
