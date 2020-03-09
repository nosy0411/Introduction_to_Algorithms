#include <stdio.h>
#include "Path.h"

#define CNUM 26
#define PNUM 100

int main() {
    city_point my_city_point[CNUM];
    path_info my_path_info[PNUM];
    Graph path_graph;

    CreatePath(&path_graph, my_city_point, my_path_info, CNUM, PNUM);  // 경로 생성
    PrintPath(my_path_info, PNUM);                                     // 경로 출력

    int PathCity[CNUM];       // 최단 경로에서 거쳐가는 도시 id의 배열
    int PathCityNum;          // 최단 경로에서 거쳐가는 도시의 개수
    double ShortestDistance;  // 최단 경로의 비행 거리

    /* Example: city 0(a)에서 city 25(z)로 가는 최단 경로 */
    ShortestDistance = ShortestPath(&path_graph, 0, 25, my_path_info, PathCity, &PathCityNum);

    /* city 0(a)에서 city 25(z)로 가는 최단 경로 출력 */
    printf("\n");
    for (int i = 0; i < PathCityNum; i++) {
        printf("%c ", PathCity[i] + 'a');
    }
    printf("\ndistance: %.3lf(km)\n", ShortestDistance);

    DestroyGraph(&path_graph);
    return 0;
}