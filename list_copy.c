/*A linked list is given such that each node contains an additional random pointer which could point to any node in the list or NULL.

Return a deep copy of the list.

Example

Given list

   1 -> 2 -> 3
with random pointers going from

  1 -> 3
  2 -> 1
  3 -> 1
You should return a deep copy of the list. The returned answer should not contain the same node as the original list, but a copy of them. The pointers in the returned list should not link to any node in the original input list.*/

/**
 * Definition for singly-linked random list.
 * struct RandomListNode {
 *     int label;
 *     struct RandomListNode *next;
 *     struct RandomListNode *random;
 * };
 * 
 * typedef struct RandomListNode randomlistnode;
 * 
 */
/**
 * @input A : Head pointer of random linked list 
 * 
 * @Output head pointer of copied random list.
 */
randomlistnode* copyRandomList(randomlistnode* A) {
    randomlistnode *res = NULL;
    randomlistnode *temp1, *temp2;
    
    if (A == NULL) return A;
    temp1 = A;
    while (temp1 != NULL) {
        res = listnode_new(temp1->label);
        res->next = temp1->next;
        temp1->next = res;
        temp1 = res->next;
    }
    
    temp1 = A;
    while (temp1 != NULL) {
        temp2 = temp1->next;
        if (temp1->random != NULL)
            temp2->random = temp1->random->next;
        temp1 = temp2->next;
    }
    
    
    temp1 = A;
    res = A->next;
    while (temp1 != NULL) {
        temp2 = temp1->next;
        temp1->next = temp2->next;
        if (temp1->next != NULL) {
            temp2->next = temp1->next->next;
        }
        
        temp1 = temp1->next;
    }
    
    return res;
}
