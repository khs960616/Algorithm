#include <bits/stdc++.h>
#define MOVE_UP 'U'
#define MOVE_DOWN 'D'
#define DELETE 'C'
#define CANCEL_PREV_DELETE 'Z'

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/81303
  2021 카카오 채용연계형 인턴십
  표 편집
  해설 : https://tech.kakao.com/2021/07/08/2021-%EC%B9%B4%EC%B9%B4%EC%98%A4-%EC%9D%B8%ED%84%B4%EC%8B%AD-for-tech-developers-%EC%BD%94%EB%94%A9-%ED%85%8C%EC%8A%A4%ED%8A%B8-%ED%95%B4%EC%84%A4/
  ---
  자료구조 (리스트, 스택)
  
  초기 실패했을 때 코드 구상한 방법  -> 이전 카카오 풀었던 문제처럼 누적합을 이용해서 시간복잡도를 줄이고자했음. 
  
  n = 4, k=2인 형태에서 현재 행을 지우면
  ex) [0, 0, 0, 0, 0] (초기 배열의 크기는 n+1이며 모든 원소값은 0으로 초기화)
      [0, 0, -1, 1, 0]  형태로 누적합을 구하고, 
      삭제한 노드의 번호를 stack에 저장해두고 왼쪽 배열을 이용해서 stack에 저장되어있는 노드의 번호를 위 배열을 이용해서 실제 어떤 노드가 삭제 되었는지 값을 보정하려했음 
  실패원인 : 해당 문제에서는 윈도우의 사이즈가 계속 변화하며, 실행순서에 따라 값이 변화하므로 복잡도도 줄일 수 없고, 원하고자하는 답도 구할수 없었음.
  
  >> 스택을 사용하는 것은 생각해냈는데 왜 링크드 리스트를 써서, 노드를 삭제할 생각은 하지못함. 
  -> 삭제한 노드에 대해 삭제를 취소할 때 어떻게 되돌릴까에 대한 것 때문이였는데, 
     문제 제약조건에서 (표의 모든 행을 제거하여, 행이 하나도 남지 않는 경우는 입력으로 주어지지 않습니다.)가 있으므로,
     노드를 삭제하는 경우, 해당 노드의 좌우 연결정보는 삭제하지 않은채 리스트에서만 빼주면 된다. 
     이후, 삭제를 취소하는 경우 해당 노드의 연결정보를 이용해서 다시 연결 리스트에 이어주면 복잡도 (1)로 처리가 가능함.
  
  >> 복잡도를 줄이기 위해서 어떤 자료구조로 데이터를 어떻게 설계할지에 대해서 먼저 고민해볼 필요가 있겠음.. 
*/
using namespace std;

struct Node {
    int id;
    Node* up;
    Node* down;
};

int node_cnt = 0;
Node* node_list;
Node node_pool[1000001];
stack<Node*> cache_deleted_node;

Node* init_node(int i) {
    node_pool[i].id = i;
    node_pool[i].up = node_pool[i].down = NULL;
    
    if(i-1 >= 0) node_pool[i].up = &node_pool[i-1];
    if(i+1 < node_cnt) node_pool[i].down = &node_pool[i+1];
    return &node_pool[i];
}

void init_node_pool() {
    for(int i=0; i<node_cnt; ++i) init_node(i);
}


Node* move_up(Node* current, int x) {
    Node* ret = current;
    while(x--) ret = ret->up;
    return ret;
}

Node* move_down(Node* current, int x) {
    Node* ret = current;
    while(x--) ret = ret->down;
    return ret;
}

Node* delete_current_node(Node* node) {
    cache_deleted_node.push(node);
    
    Node* prev_node = node->up;
    Node* next_node = node->down;
    if(prev_node == NULL) {
        node_list = node->down;
    } else {
        prev_node->down = node->down;
    }
    
    if(next_node != NULL) next_node->up = node->up;
    return (next_node != NULL) ? next_node : prev_node;
}

void cancel_delete() {
    Node* node = cache_deleted_node.top();
    cache_deleted_node.pop();
    
    Node* prev_node = node->up;
    Node* next_node = node->down;
    
    if(prev_node == NULL) {
         node_list = node;
    } else{
        prev_node->down = node;
    }
    
    if(next_node != NULL) next_node->up = node;
}

string get_node_state_to_string() {
    string answer(node_cnt, 'X');
    while(node_list!=NULL) {
        answer[node_list->id] = 'O';
        node_list = node_list->down;
    }
    return answer;
}

void excute_cmds(Node* current_node, vector<string> cmds) {
    for(string cmd: cmds) {
        char op_code = cmd[0];
        int x = (cmd.length() > 1) ? stoi(cmd.substr(2)) : 0;
        
        switch(op_code) {
            case MOVE_UP:
                current_node = move_up(current_node, x);
                break;
            case MOVE_DOWN:
                current_node = move_down(current_node, x);
                break;
            case DELETE:
                current_node = delete_current_node(current_node);
                break;
            case CANCEL_PREV_DELETE:
                cancel_delete();
                break;
        }
    }
}

string solution(int n, int k, vector<string> cmds) {
    node_cnt = n;
    init_node_pool();
    
    node_list = &node_pool[0];
    Node* current_node = &node_pool[k];
    
    excute_cmds(current_node, cmds);
    return get_node_state_to_string();
}
