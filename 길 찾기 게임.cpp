#include <bits/stdc++.h>
using namespace std;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/42892
  [2019 KAKAO BLIND RECRUITMENT]
  길 찾기 게임
  ---
  트리, 시뮬레이션
  
  1. 노드의 y좌표, x좌표가 담긴 정보에 각 노드의 번호도 추가한다.
  
  2. 각 노드를  (1) y좌표가 큰 순서, (2) x좌표가 작은 순서 대로 정렬한다.
     -> 문제 조건에 의해 x좌표는 모두 다르며, y좌표가 클수록 루트에 가까운 노드이다.
     
  3. 정렬된 배열에 존재하는 노드정보중 맨 처음 노드는 y좌표가 가장 큰 노드이며 이는 트리의 루트 노드이다.
     -> 이후 각 배열은 depth에 따라 x좌표가 작은 순서대로 정렬되어있으므로 트리의 루트부터 시작해서 해당 노드가 들어갈 위치를 찾아서 넣어주면 된다.
     
  4. pre_order, post_order는 간단하게 재귀로 구현 
  
  문제 제약조건으로 트리의 depth는 최대 1,000 이라고 제한하였다. 따라서 크기비교는 
  각 노드별로 최대 1000번만 일어나므로 
  
  10,000 * 1000 = 10^7의 복잡도를 요구함.
  ---
  트리 생성 자체를 재귀로 구현하는 방식으로 접근하면
  x 좌표가 작은 순서대로 정렬한 후, y좌표가 가장 큰 노드를 넣는 방식도 존재한다.
  
  Node* make_tree(vector<vector<int> > node_infos, int left, int right) {
    if(left > right) return NULL;
    Node* node = node_infos[left] ~ node_info[right] 중 가장 큰 y값을 가지는 노드를 선택해서 현재 노드에 저장 
    node->left = make_tree(node_infos, left, (현재 정보 저장한 index)-1)
    node->right = make_tree(node_infos, (현재 정보 저장한 index)+1, (right));
    
    return node;
  }
  
  이렇게 하는 경우, 총 넣어야되는 노드 n개에 대해, 매번 최대 y값을 찾아야하므로 n^2의 복잡도를 가지게 된다. 
  10^8 -> 따라서 이 경우 상수배가 커지면 시간초과가 날 수 있다.
  
*/
struct Node {
    int y;
    int x;
    int id;
    Node* left;
    Node* right;
    
    Node(){}
    Node(vector<int> node_info) {
        this->x = node_info[0];
        this->y = node_info[1];
        this->id = node_info[2];
        this->left = this->right = NULL;
    }
};

int node_cnt = 0;

void add_node_id(vector<vector<int>>& node_infos) {
    for(int i=0; i<node_cnt; ++i) node_infos[i].push_back(i+1);
}

void get_pre_order_path(vector<int>& pre_order, Node* node) {
    if(node == NULL) return;
    
    pre_order.push_back(node->id);
    get_pre_order_path(pre_order, node->left);
    get_pre_order_path(pre_order, node->right);
}

void get_post_order_path(vector<int>& post_order, Node* node) {
    if(node == NULL) return;

    get_post_order_path(post_order, node->left);
    get_post_order_path(post_order, node->right);
    post_order.push_back(node->id);
}

vector<vector<int> > get_answer(Node* tree) {
    vector<vector<int>> answer(2);
    get_pre_order_path(answer[0], tree);
    get_post_order_path(answer[1], tree);
    return answer;
}

bool cmp(vector<int> v1, vector<int> v2) {
    if(v1[1] == v2[1]) return v1[0] < v2[0];
    return v1[1] > v2[1];
}

void insert_node(Node* parent, Node* node) {
    while(1) {
        if(node->x < parent->x) {
            if(parent->left == NULL) {
                parent->left = node;
                return;
            }
            parent = parent->left;
        } else {
            if(parent->right == NULL) {
                parent->right = node;
                return;
            }
            parent = parent->right;
        }
    }
}
vector<vector<int>> solution(vector<vector<int>> node_infos) {
    node_cnt = node_infos.size();
    add_node_id(node_infos);
    sort(node_infos.begin(), node_infos.end(), cmp);
    
    Node root(node_infos[0]);
    for(int i=1; i<node_cnt; ++i) {
        Node* new_node = new Node(node_infos[i]);
        insert_node(&root, new_node);
    }
    
    vector<vector<int> > answer(2);
    get_pre_order_path(answer[0], &root);
    get_post_order_path(answer[1], &root);
    return answer;
}
