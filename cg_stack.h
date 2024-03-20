#ifndef CG_STACK_H_INCLUDED
#define CG_STACK_H_INCLUDED

#include <malloc.h>

#define STACK struct stack

STACK {
    int vrtx1;
    int vrtx2;
    int len;
    STACK *next;
};

STACK* Create(int v1, int v2, int len) {
    STACK *res;

    res = (STACK*)malloc(sizeof(STACK));
    res -> vrtx1 = v1;
    res -> vrtx2 = v2;
    res -> len = len;
    res -> next = NULL;

    return res;
}

//inserting edge into stack
void Insert(STACK *pre, STACK *elem) {
    if (pre -> next == NULL) {
        pre -> next = elem;
        return;
    }

    if ((pre -> next -> len) > (elem -> len)) {
        elem -> next = pre -> next;
        pre -> next = elem;
        return;
    }
    else
        Insert(pre -> next, elem);
}

//adding edge into result stack
void Add(STACK *first, STACK *elem) {
    if (first -> next == NULL)
        first -> next = elem;
    else
        Add(first -> next, elem);
}

void Clear(STACK *first) {
    if (first -> next != NULL)
      Clear(first -> next);
    free(first);
}

#endif // CG_STACK_H_INCLUDED
