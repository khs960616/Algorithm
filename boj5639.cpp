#include <bits/stdc++.h>
using namespace std;

/*
https://www.acmicpc.net/problem/5639
이진 검색 트리

---
pre order의 맨 처음 출력되는 노드는 무조건 root이다. (sub tree의 경우에도 같다.
이진 검색 트리는 root값을 기준으로, root보다 작은값이라면 왼쪽 서브트리, root보다 큰값이라면 오른쪽 서브 트리로 나뉜다.
위 두성질을 이용해 트리를 루트를 기준으로 쪼개며 재귀 함수를 호출하면 post order 출력순서를 구할 수 있다.
*/

int tree[10001];

void postOrder(int left, int right) {
    if(left > right) return;
    if(left == right) {
        cout << tree[left] << '\n';
        return;
    }

    int root = tree[left];
    int nextLeft = right;

    for(int i=left+1; i<=right; ++i) {
        if(root < tree[i]) {
            nextLeft = i-1;
            break;
        }
    }

    postOrder(left+1, nextLeft);
    postOrder(nextLeft+1, right);
    cout << root << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int num = 0, idx = 0;

    while(cin >> num) {
        tree[idx++] = num;
    }

    postOrder(0, idx-1);
    return 0;
}
