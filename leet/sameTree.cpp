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
 
 https://leetcode.com/problems/same-tree/
 
 두 트리 p와 q가 주어질 때, 각 트리가 완전히 같은 트리인지를 구한다.
 
 
 */
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        bool isSame = true;
        isEqual(p, q, isSame);
        return isSame;
    }

private:
    void isEqual(TreeNode* p, TreeNode* q, bool& isSame) {
        bool isPNull = (p==NULL);
        bool isQNull = (q==NULL);
        if(!isSame || (isPNull && isQNull)) return;
        
        bool isDifferentValue = !(isPNull || isQNull) && (p->val != q->val);
        bool isIncomparable = (isPNull && !isQNull) || (!isPNull && isQNull);
        if(isDifferentValue || isIncomparable) {
            isSame = false;
            return;
        }
        
        isEqual(p->left, q->left, isSame);
        isEqual(p->right, q->right, isSame);
    }
};



/*
다른 사람 풀이법 

class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if(p == NULL &&  q== NULL) return true;
        if(p == NULL ||  q== NULL) return false;
        if(p->val != q->val) return false;
        return isSameTree(p->right, q->right) && isSameTree(p->left, q->left) ;
    }
};
훨씬 간결하고 읽기도 더 편한듯함. 
*/
