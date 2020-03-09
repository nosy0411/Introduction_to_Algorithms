#include "Path.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PATH_NUM 100

void CreatePath(Graph *g, city_point cp[], path_info pi[], int city_num, int path_num) {
    srand(time(NULL));

    CreateGraph(g, city_num);

    // 도시 좌표 랜덤 생성
    for (int i = 0; i < city_num; i++) {
        cp[i].x = rand() % 6001;
        cp[i].y = rand() % 6001;
    }

    // 서로 다른 임의의 두 도시 id를 생성하여 출발지와 도착지로 설정
    for (int i = 0; i < path_num;) {
        int city1 = rand() % city_num, city2;

        do {
            city2 = rand() % city_num;
        } while (city1 == city2);

        // 해당 하는 경로가 이미 존재한다면 넘어감
        if (!AddEdge(g, city1, city2, i)) continue;

        // 경로 정보 pi에 주어진 경로의 출발지, 도착지, 거리 저장
        int x_dif = cp[city1].x - cp[city2].x;
        int y_dif = cp[city1].y - cp[city2].y;
        pi[i].dist = sqrt(x_dif * x_dif + y_dif * y_dif);
        pi[i].src = city1;
        pi[i].dest = city2;

        i++;
    }

    //PrintGraph(g);
}

void PrintPath(path_info pi[], int path_num) {
    for (int i = 0; i < path_num; i++) {
        printf("Path %d : city %c -> city %c, distance is %lf(km)\n",
               i, pi[i].src + 'a', pi[i].dest + 'a', pi[i].dist);
    }
}

double ShortestPath(Graph *g, int src, int dest, path_info pi[], int PathCity[], int *PathCityNum) {
    double ShortestDistance = 0;  // 최단 경로의 비행 거리 (return 값)
    int cityNum = g->num;

    // DFS를 위한 visited 배열
    bool *visited = (bool *)malloc(sizeof(bool) * cityNum);
    memset(visited, false, sizeof(bool) * cityNum);

    // 경로를 구할 때마다 그 경로의 비행 거리를 저장할 배열
    double *path_dist = (double *)malloc(sizeof(double) * MAX_PATH_NUM);
    memset(path_dist, 0, sizeof(double) * MAX_PATH_NUM);

    // 경로를 구할 때마다 그 경로에서 거쳐가는 도시 id 배열을 저장할 배열
    int **path_arr = (int **)malloc(sizeof(int *) * MAX_PATH_NUM);
    for (int i = 0; i < MAX_PATH_NUM; i++) {
        path_arr[i] = (int *)malloc(sizeof(int) * cityNum);
    }

    /* flight_num : 배열 개수
	path_idx : 각 경로에서 현재 도시가 몇 번째인지 인덱싱 */
    int flight_num = 0, path_idx = 0;

    ShortestPathUtil(g, src, dest, visited, path_arr, &flight_num, &path_idx, pi, path_dist);

    // 출발지에서 도착지로 가는 경로가 없음
    if (flight_num == 0)
        *PathCityNum = 0;

    /* 경로가 존재한다면 path_dist의 마지막 성분에 최단 경로의 비행 거리가 있고
	path_arr의 마지막 열 배열에 최단 경로에서 거쳐가는 도시 id의 배열이 있음 */
    else {
        ShortestDistance = path_dist[flight_num - 1];

        for (int i = 0;; i++) {
            PathCity[i] = path_arr[flight_num - 1][i];
            if (PathCity[i] == dest) {
                *PathCityNum = i + 1;
                break;
            }
        }
    }

    // 동적 할당 해제
    free(visited);
    free(path_dist);

    for (int i = 0; i < MAX_PATH_NUM; i++) {
        free(path_arr[i]);
    }
    free(path_arr);

    return ShortestDistance;
}

void ShortestPathUtil(Graph *g, int cur, int dest, bool *visited,
                      int **path_arr, int *flight_num, int *path_idx, path_info pi[], double path_dist[]) {
    visited[cur] = true;
    path_arr[*flight_num][*path_idx] = cur;
    (*path_idx)++;

    int cur_dist = path_dist[*flight_num];  // 현재 경로의 비행거리
    int next_dist;

    /* 경로를 하나씩 찾을 때마다 flight_num 을 증가하여
	path_arr의 다음 열에 경로를 저장함
	최종적으로 최단 경로 배열은 path_arr[flight_num - 1]에 저장됨 */

    // 현재 도시가 도착지인 경우
    if (cur == dest) {
        (*flight_num)++;
        for (int i = 0; i < *path_idx; i++) {
            path_arr[*flight_num][i] = path_arr[(*flight_num) - 1][i];
        }
    }

    // 현재 도시가 도착지가 아닌 경우
    else {
        GNode *curNode = g->heads[cur]->next;
        int isnextdest = 0;

        // 현재 도시에서 갈 수 있는 도시에 도착지가 있는 지 확인
        while (curNode != NULL) {
            // 도착지가 있는 경우
            if (curNode->id == dest) {
                next_dist = cur_dist + pi[curNode->path_idx].dist;
                isnextdest = 1;

                /* 현재 경로가 첫 번째 경로거나
				도착지가 있고 비행 거리가 현재 최단 경로의 비행 거리보다
				작은 경우 탐색함 */
                if ((*flight_num == 0) || (next_dist < path_dist[(*flight_num) - 1])) {
                    path_dist[*flight_num] = next_dist;
                    ShortestPathUtil(g, curNode->id, dest, visited, path_arr, flight_num, path_idx,
                                     pi, path_dist);
                }

                break;
            }
            curNode = curNode->next;
        }

        // 도착지가 없는 경우
        if (isnextdest == 0) {
            curNode = g->heads[cur]->next;

            // 이미 방문한 도시는 다시 방문하지 않음 (no cycle)
            while (curNode != NULL) {
                if (!visited[curNode->id]) {
                    next_dist = cur_dist + pi[curNode->path_idx].dist;

                    /* 거리가 현재 최단 경로 거리보다 커지면
					넘어가고 다음 갈 수 있는 도시를 확인 */
                    if ((*flight_num) && (next_dist > path_dist[(*flight_num) - 1])) {
                        curNode = curNode->next;
                        continue;
                    }

                    // 거리가 현재 최단 경로 거리보다 작다면 탐색
                    else {
                        path_dist[*flight_num] = next_dist;

                        ShortestPathUtil(g, curNode->id, dest, visited, path_arr, flight_num,
                                         path_idx, pi, path_dist);
                    }
                }
                curNode = curNode->next;
            }
        }
    }

    // path_dist 배열에 현재 경로 거리 저장
    path_dist[(*flight_num)] = cur_dist;

    // DFS 기반 탐색이므로 갈 수 있는 도시를 모두 탐색했다면 이전 도시로 돌아간다
    (*path_idx)--;
    visited[cur] = false;
}