#ifndef __UI_H__
#define __UI_H__

#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "Path.h"
#include "record.h"
#include "table.h"

#define SECRET "algorithm"
#define CNUM 26
#define PNUM 100

//키 입력 함수
int kbhit(void);
//초기 화면 출력
void drawscreen(node *root);

//500개 정보 초기화
node *resv_init(Graph *path_graph, path_info pi[]);
//메뉴 0번
void zero(node *root);
//메뉴 1번
node *first(Graph *path_graph, path_info pi[], node *root, int resv_fin);
//메뉴 2번
node *second(node *root);

//메뉴 3번
void third(path_info pi[]);
//메뉴 4번
void fourth(node *root);

//관리자 메뉴 1번
node *first_manage(node *root);

//관리자 메뉴 2번
void second_manage(node *root);

//관리자 조회 테이블
void ALL_SECTABLE(node *root, int count);
#endif