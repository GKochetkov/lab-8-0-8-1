#ifndef PG_STACK_H_INCLUDED
#define PG_STACK_H_INCLUDED

#define EDGE struct edge
#define STACK struct stack

#include <malloc.h>


//struct for adjacency list
EDGE {
    int v1;
    int v2;
    int len;
    EDGE *next;
};

EDGE* Create(int v1, int v2, int len) {
    EDGE *res;

    res = (EDGE*)malloc(sizeof(EDGE));
    res -> v1 = v1;
    res -> v2 = v2;
    res -> len = len;
    res -> next = NULL;

    return res;
}

//adding edge into adjacency list
void Add(EDGE *first, EDGE *elem) {
    if (first -> next == NULL)
        first -> next = elem;
    else
        Add(first -> next, elem);
}

void Clear(EDGE *first) {
    if (first -> next != NULL)
        Clear(first -> next);
    free(first);
}



STACK {
    EDGE *edge;
    STACK *next;
};

STACK* CreateS(EDGE *edge) {
    STACK *res;

    res = (STACK*)malloc(sizeof(STACK));
    res -> edge = edge;
    res -> next = NULL;

    return res;
}

void Insert(STACK *pre, STACK *elem) {
    if (pre -> next == NULL) {
        pre -> next = elem;
        return;
    }

    if ((pre -> next -> edge -> len) > (elem -> edge -> len)) {
        elem -> next = pre -> next;
        pre -> next = elem;
        return;
    }
    else
        Insert(pre -> next, elem);
}

//insert all vertex's edges into stack
void VrtInStck(EDGE *adjList, EDGE *stk) {
    Insert(stk, CreateS(adjList));
    if (adjList -> next != NULL)
        VrtInStck(adjList -> next, stk);
}

//add edge into result
void AddS(STACK *first, STACK *elem) {
    if (first -> next == NULL)
        first -> next = elem;
    else
        AddS(first -> next, elem);
}

#endif // PG_STACK_H_INCLUDED
