#include <stdio.h>
#include <malloc.h>
#include "pg_stack.h"

#define MAX_VRTX_CNT 5000
#define V1 *edge
#define V2 *(edge+1)
#define LEN *(edge+2)


//getting input
char Input(int *edge) {
    char chr;
    int i = 0;

    chr = getchar();
    while (chr != EOF & chr != '\n') {
        if (chr == ' ')
            i++;
        else {
        *(edge+i) *= 10;
        *(edge+i) += chr-48;
        }

        chr = getchar();
    }

    return chr;
}

int Prima(EDGE **graph, STACK *res, int vrtxCnt) {
    short *frame;

    //array for checking attached vertices
    frame = (short*)malloc(vrtxCnt*sizeof(short));
    for (int i = 0; i < vrtxCnt; i++)
        *(frame+i) = 0;

    *frame = 1;
    STACK *stack = CreateS(0);
    VrtInStck((*graph) -> next, stack);

    while (stack -> next != NULL) {
        //taking edge from stack
        STACK *cur = stack -> next;
        stack -> next = cur -> next;
        int v1 = cur -> edge -> v1;
        int v2 = cur -> edge -> v2;

        //checking for loop in tree
        if(*(frame+v1-1) != *(frame+v2-1)) {
            VrtInStck((*(graph+v2-1)) -> next, stack);
            *(frame+v1-1) = 1;
            *(frame+v2-1) = 1;
            cur -> next = NULL;
            AddS(res, cur);
        } else
            free(cur);
    }

    free(stack);

    //checking for completeness of the tree
    for (int i = 0; i < vrtxCnt; i++)
        if (*(frame+i) == 0)
            return 0;

    return 1;
}

int main()
{
    int n, m, edgeCnt = 0, res;
    int *edge;
    EDGE **graph;
    char lastChr;
    STACK *sRes;

    //getting input
    scanf("%d", &n);
    if (n < 0 || n > MAX_VRTX_CNT) {
        printf("bad number of vertices");
        return 0;
    }

    scanf("%d", &m);
    if (m < 0 || m > n*(n+1)/2) {
        printf("bad number of edges");
        return 0;
    }

    if (n == 1)
        return 0;
    else if (m == 0) {
        printf("no spanning tree");
        return 0;
    }

    //creating empty adjacency list
    graph = (EDGE**)malloc(n*sizeof(EDGE*));
    for (int i = 0; i < n; i++)
        *(graph+i) = Create(0, 0, 0);

    //getting edges and making adjacency list
    edge = (int*)malloc(3*sizeof(int));

    lastChr = getchar();
    while (lastChr != EOF & edgeCnt != m) {
        V1 = 0, V2 = 0, LEN = 0;
        lastChr = Input(edge);

        if (V1 == 0 & V2 == 0 & LEN == 0) {
            printf("bad number of lines");
            return 0;
        }

        if (V1 < 1 || V1 > n || V2 < 1 || V2 > n) {
            printf("bad vertex");
            return 0;
        }

        if (LEN < 0) {
            printf("bad length");
            return 0;
        }

        Add(*(graph+V1-1), Create(V1, V2, LEN));
        Add(*(graph+V2-1), Create(V2, V1, LEN));
        edgeCnt++;
    }

    free(edge);

    if (edgeCnt != m) {
        printf("bad number of lines");
        for (int i = 0; i < n; i++)
            Clear(*(graph+i));
        free(graph);
        return 0;
    }

    sRes = CreateS(0);

    res = Prima(graph, sRes, n);

    //printing result
    if (res) {
        while (sRes -> next != NULL) {
            STACK *curS = sRes -> next;
            EDGE *curE = curS -> edge;
            sRes -> next = curS -> next;
            free(curS);

            if (curE -> v1 < curE -> v2)
                printf("%d %d\n", curE -> v1, curE -> v2);
            else
                printf("%d %d\n", curE -> v2, curE -> v1);

            free(curE);
        }
    } else
        printf("no spanning tree");

    if (n == 0)
        printf("no spanning tree");

    //clearing memory
    free(sRes);
    for (int i = 0; i < n; i++)
        Clear(*(graph+i));
    free(graph);

    return 0;
}
