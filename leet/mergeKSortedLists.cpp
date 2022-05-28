  /**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

/*
https://leetcode.com/problems/merge-k-sorted-lists/
Merge k Sorted Lists

주어진 K개의 Lists는 각각 오름차순으로 정렬되어있다. 
이 때, 주어진 Lists들을 하나의 오름차순으로 정렬된 List가 되도록 하여 반환해야한다.
-----

머지 소트 구현과 비슷하다.
각 리스트들이 오름차순으로 정렬되어있지 않다면 각각을 partition 하는 과정도 구현해야하나
문제 조건에 의해 각각의 리스트가 이미 오름차순으로 정렬되어있다.
따라서 merge 하는 과정을 구현하면 된다.

*/

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode* ret = NULL;
        int k = lists.size();
        
        for(int i=0; i<k; ++i) {
            if(lists[i] == NULL) continue;
            ret = merge(ret, lists[i]);
        }
        return ret;
    }
    
    //별도의 노드를 추가하지 않고 기존의 노드들을 끊어서 사용하도록 구현함 
    ListNode* merge(ListNode* ret, ListNode* target) {
        if(ret == NULL) return target;
        
        ListNode* l = ret;    // 현재 ret의 어느 원소까지 탐색했는지를 나타내는 포인터 
        ListNode* r = target; // 현재 target의 어느 원소까지 탐색했는지를 나타내는 포인터 
        ListNode* result = NULL;  
        
        if(l->val <= r->val) {
            result = ret;
            l = l->next;
            result->next = NULL;  // 현재 정렬중인 result에서는 기존 노드의 연결 상태를 알 필요가 없음
        } else {
            result = target;
            r = r->next;
            result->next = NULL;
        }
        
        ListNode* current = result;   //현재 연결상태를 바꿔줄 노드를 가르키는 포인터
      
        while(l != NULL || r != NULL) {
            //ret 또는 target은 각각 이미 오름차순 정렬되어있으므로, 한쪽 리스트를 끝까지 다 훑었다면 남은 리스트를 다 쏟아내고 끝내면 됨
            if(l == NULL && r != NULL) {
                while(r != NULL) {
                    current = current->next = r;
                    r = r->next;
                    current->next = NULL;
                }
                break;
            } else if (l != NULL && r == NULL) {
                while(l != NULL) {
                    current = current->next = l;
                    l = l->next;
                    current->next = NULL;
                }
                break;
            } else {
                if(l->val <= r->val) {
                    current = current->next = l;
                    l = l->next;
                    current->next = NULL;
                } else {
                    current = current->next = r;
                    r = r->next;
                    current->next = NULL;
                }
            }
        }
        return result;
    }
};
