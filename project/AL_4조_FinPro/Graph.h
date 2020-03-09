#ifndef _GRAPH_H
#define _GRAPH_H

/* 경로 연결 관계를 나타내는 그래프
id : 도시 id
path_idx : 하나의 head에 연결된 node들에 대하여(head->next, head->next->next, ...)
head에서 node까지 가는 경로의 인덱스(path_info 배열에서 몇 번째 경로인지 나타냄) */
typedef struct _GNode {
    int id;
    int path_idx;
    struct _GNode* next;
} GNode;

typedef struct _Graph {
    int num;
    GNode** heads;
} Graph;

// Create a graph.
void CreateGraph(Graph* pgraph, int num);

// Destroy a graph.
void DestroyGraph(Graph* pgraph);

// Add an undirected edge from src to dest.
int AddEdge(Graph* pgraph, int src, int dest, int path_idx);

// Print a graph for each vertex.
void PrintGraph(Graph* pgraph);

#endif