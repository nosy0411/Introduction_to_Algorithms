#ifndef _PATH_H
#define _PATH_H

#include "Graph.h"

typedef enum { false,
               true } bool;

// 도시 좌표를 갖는 구조체
typedef struct _city_point {
    int x;
    int y;
} city_point;

// 경로 정보를 갖는 구조체(출발지, 도착지, 거리)
typedef struct _path_info {
    int src;
    int dest;
    double dist;
} path_info;

// 경로 생성
void CreatePath(Graph *g, city_point cp[], path_info pi[], int city_num, int path_num);

// 경로 출력
void PrintPath(path_info pi[], int path_num);

/* 최단 경로를 구하는 함수
PathCity 배열에 거쳐가는 도시 id가 저장되고
PathCityNum에 거쳐가는 도시의 개수가 저장됨 */
double ShortestPath(Graph *g, int src, int dest, path_info pi[], int PathCity[], int *PathCityNum);

/* DFS를 기반으로 가능한 모든 경로를 찾고 최종적으로 최단 경로를 찾는 함수
path_arr의 flight_num 번째 열 배열에 최단 경로 도시 배열이 저장되고
path_dist의 flight_num 번째 원소에 최단 경로 거리가 저장됨 */
void ShortestPathUtil(Graph *g, int cur, int dest, bool *visited,
                      int **path_arr, int *flight_num, int *path_idx, path_info pi[], double path_dist[]);

#endif