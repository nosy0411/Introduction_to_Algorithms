#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>

// Create a graph.
void CreateGraph(Graph *pgraph, int num) {
    pgraph->num = num;
    pgraph->heads = (GNode **)malloc(sizeof(GNode *) * num);
    for (int i = 0; i < num; i++) {
        // Make a dummy node.
        pgraph->heads[i] = (GNode *)malloc(sizeof(GNode));
        pgraph->heads[i]->next = NULL;
    }
}

// Destroy a graph.
void DestroyGraph(Graph *pgraph) {
    GNode *cur, *temp;
    for (int i = 0; i < pgraph->num; i++) {
        cur = pgraph->heads[i];
        while (cur != NULL) {
            temp = cur;
            cur = cur->next;
            free(temp);
        }
    }

    free(pgraph->heads);
}

// Add an edge from src to dest.
int AddEdge(Graph *pgraph, int src, int dest, int path_idx) {
    GNode *cur = pgraph->heads[dest];

    while ((cur->next != NULL) && (cur->next->id != src))
        cur = cur->next;

    if (cur->next != NULL)
        return 0;

    // Create a node for dest in src.
    cur = pgraph->heads[src];
    while ((cur->next != NULL) && (cur->next->id != dest))
        cur = cur->next;

    if (cur->next != NULL)
        return 0;

    GNode *newNode1;
    newNode1 = (GNode *)malloc(sizeof(GNode));
    newNode1->id = dest;
    newNode1->path_idx = path_idx;
    newNode1->next = NULL;

    cur->next = newNode1;

    return 1;
}

// Print a graph for each vertex.
void PrintGraph(Graph *pgraph) {
    GNode *cur;
    for (int i = 0; i < pgraph->num; i++) {
        printf("%c: ", i + 'a');
        cur = pgraph->heads[i]->next;
        while (cur != NULL) {
            printf("%c  ", cur->id + 'a');
            cur = cur->next;
        }
        printf("\n");
    }
}