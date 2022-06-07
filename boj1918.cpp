#include <bits/stdc++.h>

using namespace std;

/*
https://www.acmicpc.net/problem/1918
후위 표기식
-------
스택을 활용한 재귀 구현 

1. *와 / 연산은   + - 보다 항상 먼저 실행되야한다.
2. 괄호에 따라 연산의 우선순위가 변경된다. (식에서 가장 많이 중첩된 brackets 내부에 있는 operation이 우선순위가 가장 높다.
*/
int calcOperationPriority(char currentOperation, int internalWeight){
    if(currentOperation == '*' || currentOperation == '/') {
        return 2 + internalWeight;  
    } else {
        return 1 + internalWeight;        //priority값이 높을 수록 해당 op의 우선순위가 높다.
    }
}

void consumeStackElement(stack<pair<char, int>>& operationStack, int cost) {
    while (!operationStack.empty()) {
        if(operationStack.top().second < cost) break;
        cout << operationStack.top().first;
        operationStack.pop();
    }
}

void consumeStackElement(stack<pair<char, int>>& operationStack) {
    while (!operationStack.empty()) {
        cout << operationStack.top().first;
        operationStack.pop();
    }
}


int main() {
    string s;
    cin >> s;

    stack<pair<char, int>> operationStack;
    int internalWeight = 0;
    for(char c : s) {
        if(c == '(' || c == ')') {
            int cost = (c == '(') ? 5 : -5;
            internalWeight+=cost;
            continue;
        } 

        if(isalpha(c)) {
            cout << c;
            continue;
        }
        
        int currentOpPriority = calcOperationPriority(c, internalWeight);
        if(operationStack.empty()){
            operationStack.push({c, currentOpPriority});
            continue;
        }

        pair<char, int> prevOperation = operationStack.top();
        if(prevOperation.second == currentOpPriority) {
            cout << prevOperation.first;
            operationStack.pop();
        } else if(prevOperation.second > currentOpPriority) {
            consumeStackElement(operationStack, currentOpPriority);
        }
        operationStack.push({c, currentOpPriority});
    }
    consumeStackElement(operationStack);
    return 0;   
}
