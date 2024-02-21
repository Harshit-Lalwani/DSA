#include<stdio.h>
#include<stdlib.h>

typedef struct ListNode {
    int val;
    struct ListNode *next;
}ListNode;

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode s1;
        ListNode* s = &s1;
        ListNode* t = &s1;
        while (l1->next != NULL && l2->next!=NULL) {
            s->val = l1->val + l2->val;
            l1 = l1->next;
            l2 = l2->next;
            s->next = (ListNode*)malloc(sizeof(ListNode));
            s = s->next;
        }
        s->val = l1->val + l2->val;
            l1 = l1->next;
            l2 = l2->next;
            s->next = (ListNode*)malloc(sizeof(ListNode));
            s = s->next;
        return t;
    }
int main(){
    ListNode l1;
    l1.val = 1;
    l1.next = NULL;
    ListNode l2;
    l2.val = 2;
    l2.next = NULL;
    ListNode* l3 = addTwoNumbers(&l1, &l2);
    printf("%d\n", l3->val);
    return 0;
}

