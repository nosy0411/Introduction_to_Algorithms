#ifndef _TABLE_C
#define _TABLE_C

#include "table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//시간 출력에 관련된 사항. 거리 float, 출력은 올림으로
//time = min + hour * 60으로 계산, 5분 단위로 출력. 24:00 -> 1440.
//각 경로의 출발 시간에 대한 time table random하게 만들기
//2nd order array
void buildTimeTable(int timetable[DATE][PATHS]) {
    srand(time(NULL));
    for (int d = 0; d < DATE; d++) {
        for (int p = 0; p < PATHS; p++) {
            timetable[d][p] = (rand() % 288) * 5;
        }
    }
}
void printTimeTable(int timetable[DATE][PATHS], Graph *g, int date) {
    printf("----Time Table for day %d----\n", date + 1);
    for (int s = 0; s < CITIES; s++) {
        GNode *cur = g->heads[s]->next;
        while (cur != NULL) {
            int dest = cur->id;
            int time = timetable[date][cur->path_idx];
            printf("Path from %c to %c departures ", 'a' + s, 'a' + dest);
            printf("at %02d:%02d\n", time / 60, time % 60);
            cur = cur->next;
        }
    }
}
//경로를 입력받아 최종 도착 시각과 날짜를 출력하는 함수
//시간은 분 단위로 올림, infos[6] = { dep_date, dep_time, arr_date, arr_time, seat_lv, price }
//seat_lv : 0 - economy class, 1 - business class, 2 - first class
void computeFlightInfos(int timetable[DATE][PATHS], int *path, int p_len, int infos[], Graph *g, path_info pi[]) {
    int dep_time = -1;
    int arr_time = 0;
    int arr_date = infos[0];
    infos[5] = 0;
    int s, d;
    for (int i = 0; i < p_len - 1; i++) {
        s = *(path + i);
        d = *(path + i + 1);
        GNode *cur = g->heads[s]->next;
        //각 path마다의 출발 시간을 임시 저장해둘 변수
        int flight_time = 0;
        //s->d edge의 dep.time들 중 현재 시각보다 늦은 시간들 중 가장 빠른 시간을 찾는다
        while (cur != NULL) {
            if (cur->id == d) {
                int idx = cur->path_idx;
                //도착 시간 = 출발 시간 + 비행 시간, 비행 시간은 분단위로 올림
                int t = timetable[arr_date][idx];
                flight_time = (int)(pi[idx].dist * 60);
                if (flight_time % VELOCITY)
                    flight_time = flight_time / VELOCITY + 1;
                else
                    flight_time = flight_time / VELOCITY;

                //현재 시간 이후에 출발하는 비행기가 오늘 없는 경우, 다음 날짜에서 찾는다.
                if (arr_time > t)
                    t = timetable[++arr_date][idx];
                arr_time = t + flight_time;
                infos[5] += flight_time;
                //첫 번째 비행의 출발 시간이 전체 비행의 출발 시간이 된다.
                if (i == 0)
                    dep_time = t;

                //도착시 날짜가 변경될 경우 현재 날짜를 바꾸어준다.
                if (arr_time >= 1440) {
                    arr_time -= 1440;
                    arr_date++;
                }
                //도착시 비행이 남아있는데 32일차가 된 경우, boundary checking을 위해
                //arr_date와 arr_time이 없다고 출력한다. (둘 다 -1값 할당)
                // if ((i != p_len - 1) && arr_date == DATE)
                if ((p_len != 2) && (i != p_len - 1) && arr_date >= DATE) {
                    infos[1] = dep_time;
                    infos[2] = -1;
                    infos[3] = -1;
                    return;
                }
                break;
            }
            cur = cur->next;
        }
    }

    //outputs : infos[6] = { dep_date, dep_time, arr_date, arr_time, seat_lv, price }
    infos[1] = dep_time;
    infos[2] = arr_date;
    infos[3] = arr_time;
    if (infos[4] == 0)
        infos[5] == infos[5] * ECO_PRICE / 10;
    else if (infos[4] == 1)
        infos[5] == infos[5] * BUS_PRICE / 10;
    else if (infos[4] == 2)
        infos[5] == infos[5] * FIR_PRICE / 10;
    else
        printf("Error: seat level undefined, please choose 0, 1, or 2.\n");
}

#endif