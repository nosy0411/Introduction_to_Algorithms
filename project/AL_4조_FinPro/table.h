#ifndef _TABLE_H
#define _TABLE_H

#include "Graph.h"
#include "Path.h"
#define DATE 31
#define CITIES 26
#define PATHS 100
#define VELOCITY 500
#define ECO_PRICE 1   //분당 1천원
#define BUS_PRICE 3   //분당 3천원
#define FIR_PRICE 10  //분당 1만원

void buildTimeTable(int timetable[DATE][PATHS]);
void printTimeTable(int timetable[DATE][PATHS], Graph *g, int date);
//시간은 분 단위로 올림, infos[6] = { dep_date, dep_time, arr_date, arr_time, seat_lv, price }
void computeFlightInfos(int timetable[DATE][PATHS], int *path, int p_len,
                        int infos[], Graph *g, path_info pi[]);
#endif