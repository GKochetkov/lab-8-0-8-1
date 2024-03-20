#include <stdio.h>
#include <malloc.h>
#include "cg_stack.h"

#define MAX_VRTX_CNT 5000
#define V1 *edge
#define V2 *(edge+1)
#define LEN *(edge+2)

//function to get input;
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

//getting parent vertex
short Subset(int vrtx, short* parent) {
    if (parent[vrtx] == -1)
        return vrtx;
    return Subset(parent[vrtx], parent);
}

//union two subsets into one
void Union(int vrtx1, int vrtx2, short* parent) {
    parent[Subset(vrtx1, parent)] = Subset(vrtx2, parent);
}

int Kruskal(STACK *graph, STACK *res, int vrtxCnt, int edgeCnt) {
    short root;
    short *parent;

    parent = (short*)malloc(vrtxCnt*sizeof(short));
    for (int i = 0; i < vrtxCnt; i++)
        *(parent+i) = -1;

    for (int i = 1; i <= edgeCnt; i++) {
        STACK *cur = graph -> next;
        int v1 = (cur -> vrtx1) - 1;
        int v2 = (cur -> vrtx2) - 1;
        graph -> next = cur -> next;
        cur -> next = NULL;

        //checking for loop in tree
        if (Subset(v1, parent) != Subset(v2, parent)) {
            Union(v1, v2, parent);
            Add(res, cur);
        } else
            free(cur);

    }

    //checking for completeness of the tree
    root = Subset(0, parent);
    for (int i = 1; i < vrtxCnt; i++)
        if (Subset(i, parent) != root) {
            free(parent);
            return 0;
        }

    free(parent);
    return 1;
}

int main()
{
    int n, m, edgeCnt = 0, res;
    int *edge;
    STACK *first, *resF;
    char lastChr;

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

    if (n == 0) {
        printf("no spanning tree");
        return 0;
    }

    first = Create(0, 0, 0);
    resF = Create(0, 0, 0);
    edge = (int*)malloc(3*sizeof(int));

    //getting edges
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

        Insert(first, Create(V1, V2, LEN));
        edgeCnt++;
    }

    free(edge);

    if (edgeCnt != m) {
        printf("bad number of lines");
        Clear(first);
        return 0;
    }

    res = Crascal(first, resF, n, m);

    if (n == 1)
        res = 1;

    //output
    if (res) {
        while (resF -> next != NULL) {
            STACK *cur = resF -> next;
            resF -> next = cur -> next;
            printf("%d %d\n", cur -> vrtx1, cur -> vrtx2);
            free(cur);
        }
    } else
        printf("no spanning tree");

    return 0;
}
