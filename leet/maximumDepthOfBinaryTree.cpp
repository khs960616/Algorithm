/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 
 https://leetcode.com/problems/maximum-depth-of-binary-tree/
 이진트리의 maximum depth를 구하라. 트리의 노드의 개수는 최대 10000개 이다.
 ---
 
 노드와 depth를 인자로 받는 재귀함수를 작성한다.
 만일, 인자로 받은 노드의 왼쪽, 오른쪽노드가 null이 아니라면, depth를 증가시키고 null이 아닌 자식노드를 재귀로 호출한다.
 만일 자식노드가 모두 null ptr인 노드인 경우 max값과 현재의 depth를 비교해서 더 크다면 값을 갱신한다.
 
 */
class Solution {
public:
    int maxDepth(TreeNode* root) {
        int answer = 0;
        if(root != NULL) calcMaxDepth(root, answer, 0);
        return answer;
    }
    
private:
    void calcMaxDepth(TreeNode* node, int& max, int depth) {
        bool hasLeftChild = (node->left != NULL);
        bool hasRightChild = (node->right != NULL);
        ++depth;
        
        if(!(hasLeftChild || hasRightChild)) {
            if(max<depth) max = depth;
            return;
        }
        
        if(hasLeftChild) calcMaxDepth(node->left, max, depth);
        if(hasRightChild) calcMaxDepth(node->right, max, depth);
    }
};
