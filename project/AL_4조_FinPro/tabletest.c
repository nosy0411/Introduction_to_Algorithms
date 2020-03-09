#include <stdio.h>
#include <stdlib.h>
#include "table.h"

//테스트용, 랜덤한 날짜로부터 n일까지(최대 31일)의 Time Table 출력
int printTimeTables(int table[DATE][PATHS], Graph *g, int n) {
    srand(time(NULL));
    int date = rand() % DATE;

    //For test 2 only, negative n is not an expected input value for this function.
    if (n == -1) {
        date = 30;
        n = 31;
    }

    printf("Selected date to test : %d\n", date + 1);
    n = n + date + 1;
    if (n > DATE - 1)
        n = DATE;
    for (int i = date; i < n; i++) {
        printf("----Time Table for day %d----\n", i + 1);
        for (int s = 0; s < CITIES; s++) {
            GNode *cur = g->heads[s]->next;
            while (cur != NULL) {
                int dest = cur->id;
                int time = table[i][cur->path_idx];
                printf("Path from %c to %c departures ", 'a' + s, 'a' + dest);
                printf("at %02d:%02d\n", time / 60, time % 60);
                cur = cur->next;
            }
        }
    }
    return date;
}
//테스트용 map 제작
void drawTestMap1(Graph *g, path_info pi[]) {
    CreateGraph(g, CITIES);

    AddEdge(g, 2, 0, 0);
    AddEdge(g, 0, 1, 1);
    AddEdge(g, 0, 3, 2);
    AddEdge(g, 1, 2, 3);
    AddEdge(g, 0, 4, 4);

    pi[0].dist = 2500;
    pi[1].dist = 1500;
    pi[2].dist = 1000;
    pi[3].dist = 2000;
    pi[4].dist = 1000;
}
void drawTestMap2(Graph *g, path_info pi[]) {
    CreateGraph(g, CITIES);

    //src->dest, idx
    AddEdge(g, 0, 1, 0);   //a->b
    AddEdge(g, 0, 3, 1);   //a->d
    AddEdge(g, 0, 8, 2);   //a->i
    AddEdge(g, 1, 2, 3);   //b->c
    AddEdge(g, 1, 5, 4);   //b->f
    AddEdge(g, 2, 4, 5);   //c->e
    AddEdge(g, 3, 6, 6);   //d->g
    AddEdge(g, 5, 4, 7);   //f->e
    AddEdge(g, 6, 0, 8);   //g->a
    AddEdge(g, 7, 2, 9);   //h->c
    AddEdge(g, 8, 7, 10);  //i->h
    AddEdge(g, 9, 7, 11);  //j->h

    pi[0].dist = 1000;
    pi[1].dist = 1500;
    pi[2].dist = 2500;
    pi[3].dist = 1500;
    pi[4].dist = 3750;
    pi[5].dist = 750;
    pi[6].dist = 1000;
    pi[7].dist = 2500;
    pi[8].dist = 1000;
    pi[9].dist = 1750;
    pi[10].dist = 1000;
    pi[11].dist = 2000;
}
void printInfos(int *path, int len, int infos[]) {
    printf("Path \"");
    for (int i = 0; i < len; i++) {
        printf("%c", *(path + i) + 'a');
    }
    printf("\" infos:\n");
    if (infos[2] == -1) {
        printf("Dep. date - %d, time - %02d:%02d\n", infos[0] + 1, infos[1] / 60, infos[1] % 60);
        printf("The path is unvalid because date overs the limit during flight.\n");
        return;
    }
    printf("Dep. date - %d, time - %02d:%02d\n", infos[0] + 1, infos[1] / 60, infos[1] % 60);
    printf("Arr. date - %d, time - %02d:%02d\n", infos[2] + 1, infos[3] / 60, infos[3] % 60);
    if (infos[4] == 0)
        printf("Seat : Economy Class, price : %d만원.\n", infos[5]);
    else if (infos[4] == 1)
        printf("Seat : Business Class, price : %d만원.\n", infos[5]);
    else
        printf("Seat : First Class, price : %d만원.\n", infos[5]);
}

int main() {
    //time table 생성
    int table[DATE][PATHS] = {0};
    buildTimeTable(table);

    //Test 1.
    printf("Test Case 1\n\n");
    Graph *map1 = (Graph *)malloc(sizeof(Graph));
    path_info pi1[5];
    //map 적당히 작성
    drawTestMap1(map1, pi1);
    //path 적당히 작성
    int path1[2] = {0, 1};     //Shortest path a->b
    int path2[2] = {0, 3};     //Shortest path a->d
    int path3[3] = {2, 0, 4};  //Shortest path c->e

    //함수 작동 테스트
    int date = printTimeTables(table, map1, 2);
    int val_arr1[6] = {0}, val_arr2[6] = {0}, val_arr3[6] = {0};
    val_arr1[0] = date;
    val_arr2[0] = date;
    val_arr3[0] = date;

    val_arr1[4] = 1;
    val_arr2[4] = 0;
    val_arr3[4] = 2;

    computeFlightInfos(table, path1, 2, val_arr1, map1, pi1);
    computeFlightInfos(table, path2, 2, val_arr2, map1, pi1);
    computeFlightInfos(table, path3, 3, val_arr3, map1, pi1);

    printInfos(path1, 2, val_arr1);
    printInfos(path2, 2, val_arr2);
    printInfos(path3, 3, val_arr3);
    printf("\n");

    //Test 2. (31일 예외 case 적용)
    printf("Test Case 2\n\n");
    printTimeTables(table, map1, -1);
    date = 30;
    val_arr1[0] = date;
    val_arr2[0] = date;
    val_arr3[0] = date;

    val_arr1[4] = 0;
    val_arr2[4] = 1;
    val_arr3[4] = 2;

    computeFlightInfos(table, path1, 2, val_arr1, map1, pi1);
    computeFlightInfos(table, path2, 2, val_arr2, map1, pi1);
    computeFlightInfos(table, path3, 3, val_arr3, map1, pi1);

    printInfos(path1, 2, val_arr1);
    printInfos(path2, 2, val_arr2);
    printInfos(path3, 3, val_arr3);

    DestroyGraph(map1);
    printf("\n");

    //Test 3.
    printf("Test Case 3\n\n");
    //새로운 time table 생성
    buildTimeTable(table);

    Graph *map2 = (Graph *)malloc(sizeof(Graph));
    path_info pi2[12];
    //map 적당히 작성
    drawTestMap2(map2, pi2);
    //path 적당히 작성
    int path4[2] = {9, 7};           //Shortest path j->h
    int path5[3] = {0, 3, 6};        //Shortest path a->g
    int path6[3] = {1, 2, 4};        //Shortest path b->e
    int path7[4] = {8, 7, 2, 4};     //Shortest path i->e
    int path8[5] = {6, 0, 1, 2, 4};  //Shortest path g->e

    //함수 작동 테스트
    date = printTimeTables(table, map2, 4);
    int val_arr4[6] = {0}, val_arr5[6] = {0};

    val_arr1[0] = date;
    val_arr2[0] = date;
    val_arr3[0] = date;
    val_arr4[0] = date;
    val_arr5[0] = date;

    val_arr1[4] = 2;
    val_arr2[4] = 1;
    val_arr3[4] = 1;
    val_arr4[4] = 0;
    val_arr5[4] = 1;

    computeFlightInfos(table, path4, 2, val_arr1, map2, pi2);
    computeFlightInfos(table, path5, 3, val_arr2, map2, pi2);
    computeFlightInfos(table, path6, 3, val_arr3, map2, pi2);
    computeFlightInfos(table, path7, 4, val_arr4, map2, pi2);
    computeFlightInfos(table, path8, 5, val_arr5, map2, pi2);

    printInfos(path4, 2, val_arr1);
    printInfos(path5, 3, val_arr2);
    printInfos(path6, 3, val_arr3);
    printInfos(path7, 4, val_arr4);
    printInfos(path8, 5, val_arr5);

    DestroyGraph(map2);
    printf("\n");
    return 0;
}