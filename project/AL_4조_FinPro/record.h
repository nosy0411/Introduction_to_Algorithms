#ifndef __RECORD_H__
#define __RECORD_H__

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define max(X, Y) ((X) > (Y) ? (X) : (Y))

// 랜덤 함수
#define randomize() srand(time(NULL))
#define random(n) (rand() % (n))
// a-z 개수
#define SAMPLE 26

// 예약자 이름 문자열 최대 길이
#define MAXLENGTH 10

//초기 테이블 500개 생성
#define NUM 500

typedef int Key;

//테이블 RB트리 노드 정의
typedef struct _node {
    // RED-true, BLACK-false
    bool color;
    // 예약번호
    Key key;
    // 출발지
    char src;
    // 도착지
    char dest;
    // 예약자 이름
    char name[MAXLENGTH + 1];
    // 최단경로
    char path[SAMPLE];
    // 최단거리
    float dist;
    // 최소시간
    float time;

    struct _node* left;
    struct _node* right;
    struct _node* parent;
} node;

// RB트리 생성
node* CreateNode(Key key, char src, char dest, char* name);

// RB트리 최소값
node* TREE_MIN(node* n);

// RB트리 검색
node* RB_SEARCH(node* root, Key key);

// RB트리 좌회전
void* rotateLeft(node** root, node** x);

// RB트리 우회전
void* rotateRight(node** root, node** x);

// RB 삽입 및 트리 균형, 색깔 맞추기
void RB_INSERT_FIXUP(node** root, node** z);

// RB 삽입
node* RB_INSERT(node* root, Key key, char src, char dest, char* name);

// RB 트리 변형 교체
void RB_TRANSPLANT(node** root, node** u, node** v);

// RB트리 삭제 및 트리 균형, 색깔 맞추기
void RB_DELETE_FIXUP(node** root, node** x);

// RB트리 삭제
node* RB_DELETE(node* root, Key key);

// RB 트리 전체 삭제
void ClearTree(node* root);

// RB 트리 높이
int height(node* node);

// RB트리 노드 개수
int RBNodes(node* node);

// 500개 정보 가상으로 생성해서 RB테이블에 삽입
node* generate();

// 예약자 정보 출력
void PRINT_RBINFO(node* root);

// 예약 테이블 일부 출력
void PRINT_TABLE(node* root, int count);

// 최근 예약현황을 나타내는 메인 테이블 일부 출력 특정횟수 이상은 출력 안됨
// 개인정보이므로, 예약자 이름만 제거함. 이 함수는 메인테스트에서 실행됨.
void RESV_SECTABLE(node* root, int count);

#endif