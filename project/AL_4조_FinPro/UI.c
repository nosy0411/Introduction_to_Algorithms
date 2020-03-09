#ifndef __UI_C__
#define __UI_C__

#include "UI.h"

//관리자 모드에서 테이블 확인
int table_stop;

//500개의 예약자, 예약번호 출발지 도착지를 생성하고 그 출발지와 도착지에 따른 최단경로와 최단거리, 최소시간을 레드블랙트리에 삽입한다.
//리턴으로 트리 루트값을 넘겨준다.
node *resv_init(Graph *path_graph, path_info pi[]) {
    // 500개 예약자, 예약번호, 출발지, 도착지 생성
    node *root = NULL;
    root = generate();
    int date;
    int i, j;
    int PathCity[CNUM];  // 최단 경로에서 거쳐가는 도시 id의 배열
    int PathCityNum;     // 최단 경로에서 거쳐가는 도시의 개수
    char pathname[CNUM + 1];
    double ShortestDistance;  // 최단 경로의 비행 거리

    // 500개에 대해 최단경로, 최단거리, 최소시간 대입.
    for (i = 1; i <= 500; i++) {
        node *loc = RB_SEARCH(root, i);
        int src = loc->src - 'a';
        int dest = loc->dest - 'a';
        ShortestDistance = ShortestPath(path_graph, src, dest, pi, PathCity, &PathCityNum);
        j = 0;
        while (j < PathCityNum) {
            loc->path[j] = PathCity[j] + 'a';
            j++;
        }
        loc->path[j] = '\0';
        loc->dist = ShortestDistance;
        loc->time = ShortestDistance / 500;
    }
    return root;
}

//초기 화면 출력. 앞으로 디자인 레이아웃이 이렇게 될 것이라는 안내.
void drawscreen(node *root) {
    char source = ' ';
    char destination = ' ';
    printf("\n출발지와 도착지를 입력하시면 최적경로를 찾아 드립니다.\n\n");
    printf("\n예약을 시작하면 아래와 같은 화면이 출력됩니다.\n\n");
    printf("\n키를 입력하시면 다음 창으로 넘어갑니다.\n\n\n");
    //위 사각형

    printf("*************");
    printf("                   ");
    printf("*************\n");
    //중간1사각형

    printf("*           *");
    printf("                   ");
    printf("*           *\n");
    //중간2사각형

    printf("*  출발 : %c *      ========>    ", source);
    printf("*  도착 : %c *\n", destination);
    //중간3사각형

    printf("*           *");
    printf("                   ");
    printf("*           *\n");
    //아래사각형

    printf("*************");
    printf("                   ");
    printf("*************\n");

    printf("\n\n\n\n\n <최근예약현황>\n\n");

    RESV_SECTABLE(root, 10);

    printf("\n\n\n이름 : ");
    printf("     출발지 : ");
    printf("     도착지 : \n\n");
    printf("출발날짜 :               출발시간 : \n\n");
    printf("도착날짜 :               도착시간 : \n\n");
    printf("비행경로 : \n\n");
    printf("좌석 등급 :          총 요금: ");
    printf("예상 비행 시간 : \n\n");
    printf("아무 키나 눌러서 다음 창으로 이동해 주십시오.");
}

//메뉴 0번 예약 확인
void zero(node *root) {
    int error = 0;
    int reserv_num;
    char reserv_name[MAXLENGTH + 1];

    while (error == 0) {
        printf("\n\n예약번호를 입력하세요(0 입력 = 종료) : ");
        scanf("%d", &reserv_num);

        if (reserv_num == 0) {
            break;
        }

        printf("\n예약자를 확인하기 위하여 예약자 이름을 입력해 주세요 : ");
        scanf("%s", reserv_name);

        //예약번호 조회
        node *loc = RB_SEARCH(root, reserv_num);
        //예약번호와 예약자 이름 일치 검사.
        if (strcmp(loc->name, reserv_name)) {
            printf("예약번호와 예약자가 일치하지 않습니다.\n");
            printf("예약번호와 예약자 이름을 다시 입력해 주세요.\n");
        } else {
            //일치 하면, record.c에 있는 예약자 이름, 예약번호, 출발지, 도착지와
            //그 경로에 따른 최단경로와 최단거리 최소시간을 출력해줌.
            PRINT_RBINFO(loc);
            printf("최단 경로 : %s\n", loc->path);
            printf("최단 거리 : %.2f\n", loc->dist);
            printf("최소 시간 : %02d:%02d\n", (int)loc->time, (int)(((loc->time) - ((int)loc->time)) * 60));
            error = 1;
        }
    }
}

//메뉴 1번 예약 진행
node *first(Graph *path_graph, path_info pi[], node *root, int resv_fin) {
    char name[MAXLENGTH + 1];
    char source, destination;
    int date;

    int PathCity[CNUM];       // 최단 경로에서 거쳐가는 도시 id의 배열
    int PathCityNum;          // 최단 경로에서 거쳐가는 도시의 개수
    double ShortestDistance;  // 최단 경로의 비행 거리

    printf("\n예약을 진행합니다.");
    printf("\n예약자의 이름을 입력해 주세요(10자 이내) : ");
    scanf("%s", name);
    while (getchar() != '\n')
        ;

    printf("\n출발지를 입력해 주세요(a~z) : ");
    scanf("%c", &source);
    while (getchar() != '\n')
        ;

    printf("\n도착지를 입력해 주세요(a~z) : ");
    scanf("%c", &destination);
    while (getchar() != '\n')
        ;

    printf("\n\n안내사항 : 비행 타임 테이블은 매일 바뀌기 때문에 상황에 따라 출발시간은 달라집니다.\n");
    printf("따라서, 같은 출발지, 도착지, 출발날짜라도 최단경로는 같으나 도착시간이 달라질 수 있습니다.\n");
    printf("안내사항을 인지하시고 출발날짜(일 : 1 ~ 31)을 입력해 주세요. : ");
    scanf("%d", &date);
    while (getchar() != '\n')
        ;

    printf("\n\n");
    int class_num;
    while (1) {
        printf("0번 : Economy Class는 분당 1000원\n");
        printf("1번 : Business Class는 분당 3000원\n");
        printf("2번 : First Class는 분당 10000원\n");
        printf("\n\n타고 싶은 비행기 등급을 선택해 주세요 : ");
        scanf("%d", &class_num);
        while (getchar() != '\n')
            ;
        if (class_num == 0 || class_num == 1 || class_num == 2) {
            break;
        } else {
            printf("등급을 다시 입력해 주세요\n\n");
        }
    }
    int src = source - 'a';
    int dest = destination - 'a';
    // src에서 dest로 가는 최단 경로
    ShortestDistance = ShortestPath(path_graph, src, dest, pi, PathCity, &PathCityNum);

    // 최단경로에 따른 비행시간
    float total_time = ShortestDistance / 500;
    // 비행시간의 시
    int time_hour = (int)total_time;
    // 비행시간의 분
    int time_minute = (total_time - time_hour) * 60;
    // 최단경로 출력 확인.
    // printf("\n");
    // for (int i = 0; i < PathCityNum; i++) {
    //     printf("%c ", PathCity[i] + 'a');
    // }
    // 최단거리 출력 확인.
    // printf("\ndistance: %lf(km)\n", ShortestDistance);

    //time table 생성
    int table[DATE][PATHS] = {0};
    // 출발 날짜, 출발 시간, 도착날짜, 도착시간, 좌석등급, 총 요금  저장 배열
    int timearr[6] = {0};
    // 비행 등급 배열
    char class[3][20] = {"Economy Class", "Business Class", "First Class"};
    // 출발 날짜
    timearr[0] = date;
    // 비행 등급
    timearr[4] = class_num;
    buildTimeTable(table);

    // 날짜 및 시간 계산.
    computeFlightInfos(table, PathCity, PathCityNum, timearr, path_graph, pi);

    // 예약 테이블 삽입
    root = RB_INSERT(root, resv_fin + 1, source, destination, name);
    node *loc = RB_SEARCH(root, resv_fin + 1);
    int j = 0;
    while (j < PathCityNum) {
        loc->path[j] = PathCity[j] + 'a';
        j++;
    }
    loc->path[j] = '\0';
    loc->dist = ShortestDistance;
    loc->time = ShortestDistance / 500;

    // 출력
    printf("*************");
    printf("                   ");
    printf("*************\n");
    //중간1사각형

    printf("*           *");
    printf("                   ");
    printf("*           *\n");
    //중간2사각형

    printf("*  출발 : %c *      ========>    ", source);
    printf("*  도착 : %c *\n", destination);
    //중간3사각형

    printf("*           *");
    printf("                   ");
    printf("*           *\n");
    //아래사각형

    printf("*************");
    printf("                   ");
    printf("*************\n");

    printf("\n\n\n\n\n <최근예약현황>\n\n");

    RESV_SECTABLE(root, 10);
    printf("\n\n   *** 예약 번호 : %d ***  ", resv_fin + 1);
    printf("\n\n\n이름 : %s", name);
    printf("     출발지 : %c", source);
    printf("     도착지 : %c\n\n", destination);

    //도착날짜가 -1을 리턴받으면 시간표가 없기 때문에 계산 및 출력 에서 제외.
    if (timearr[2] == -1) {
        printf("출발날짜 : %d\n\n", timearr[0]);
        printf("시간표가 업데이트 되지 않아 출발 시간, 도착 날짜, 도착 시간을 계산할 수 없습니다.\n\n");
    } else {
        printf("출발날짜 : %d         출발시간 : %02d:%02d\n\n", timearr[0], timearr[1] / 60, timearr[1] % 60);
        printf("도착날짜 : %d         도착시간 : %02d:%02d\n\n", timearr[2], timearr[3] / 60, timearr[3] % 60);
    }
    printf("비행경로 : ");
    for (int i = 0; i < PathCityNum; i++) {
        printf("%c ", PathCity[i] + 'a');
        if (i != (PathCityNum - 1)) {
            printf("--> ");
        }
    }
    printf("\n\n좌석 등급 : %-20s 총 요금 : %d(만)", class[timearr[4]], timearr[5]);
    printf("\n\n예상 비행시간 : %02d:%02d\n", time_hour, time_minute);
    printf("(경유함에 따른 대기시간은 포함되지 않았습니다.)\n\n");

    printf("마지막으로 예약번호를 꼭 확인하시기 바랍니다. 예약 정보를 검색할 때 이용됩니다.\n\n");

    return root;
}

//메뉴 2번 예약 취소
node *second(node *root) {
    int check = 0;
    int reserv_num;
    char reserv_name[MAXLENGTH + 1];

    while (1) {
        printf("\n\n예약번호를 입력하세요(0 입력 = 종료) : ");
        scanf("%d", &reserv_num);

        if (reserv_num == 0) {
            break;
        }

        printf("\n예약자를 확인하기 위하여 예약자 이름을 입력해 주세요 : ");
        scanf("%s", reserv_name);

        //예약자 번호 조회
        node *loc = RB_SEARCH(root, reserv_num);

        //예약자 번호와 예약자가 일치하는지 확인
        if (strcmp(loc->name, reserv_name)) {
            printf("예약번호와 예약자가 일치하지 않습니다.\n");
            printf("예약번호와 예약자 이름을 다시 입력해 주세요.\n");
        } else {
            //일치하면 예약정보 지울 것인지 물어보고 예약정보 삭제 진행
            printf("정말로 예약을 지우시겠습니까??\n");
            printf("1을 입력하시면 예약이 취소됩니다.\n");
            scanf("%d", &check);

            if (check == 1) {
                root = RB_DELETE(root, reserv_num);
                printf("\n\n성공적으로 예약이 취소되었습니다.\n\n");
                break;
            } else {
                printf("\n\n 예약이 취소되지 않았습니다.\n\n");
            }
        }
    }
    return root;
}

//메뉴 3번 도시간 비행 경로 모두 출력
void third(path_info pi[]) {
    printf("\n\n <<비행 가능한 두 도시간 경로를 모두 출력합니다.>>\n\n");
    PrintPath(pi, PNUM);
}

// 메뉴 4번 관리자 모드
void fourth(node *root) {
    int manage;
    int s;
st:
    printf("\n\n 관리자 화면입니다.");
    printf("  메뉴를 선택해 주세요!\n\n");
    printf("1 : 예약 및 취소 테스트 \n\n2 : 예약자 정보 전체 출력\n\n");
    printf("진행을 원하시는 번호를 눌러주세요. 그 이외의 숫자 키가 입력되면 관리자모드가 종료됩니다.\n");
    printf("선택 : ");
    scanf("%d", &manage);
    while (getchar() != '\n')
        ;
    //예약 취소 테스트
    if (manage == 1) {
        system("cls");
        // 예약 취소 테스트 함수 실행
        root = first_manage(root);
        table_stop = 0;
        printf("\n\n아무 키나 누르면 홈으로 돌아갑니다.");
        s = getch();
        if (s) {
            system("cls");
        }
        goto st;
    }
    // 예약자 정보 조회
    else if (manage == 2) {
        system("cls");
        // 예약자 정보 조회 함수 실행
        second_manage(root);
        printf("\n\n아무 키나 누르면 관리자 화면으로 돌아갑니다.");
        s = getch();
        if (s) {
            system("cls");
        }
        goto st;
    }
    // 그 이외에 관리자 모드 나가기
    else {
        printf("\n\n관리자 모드를 종료합니다.");
    }
}

//테스트 용도이므로 간단하게 이름은 빈칸으로 두고 예약번호만 삽입했다.
//그리고 시스템에 영향을 미치면 안되므로 삽입만 만큼 삭제를 시켰다.
//실제 정보로 예약 삽입, 삭제를 진행하려면, 예약 진행, 예약 취소 과정을 거치기 바란다.
//관리자 모드 메뉴 1번
node *first_manage(node *root) {
    int insert_and_delete;
    int i;
    char test_name[2] = {' ', '\0'};
    //테스트를 위한 가상의 번호는 5000부터 시작
    int virkey = 5000;
    //가상의 출발지 도착지는 모두 a-z로 통일
    char src = 'a';
    char dest = 'z';
    printf("테스트를 위해 몇 개의 정보를 삽입하시겠습니까? : ");
    scanf("%d", &insert_and_delete);

    //삽입 전 노드수 트리높이 출력 및 삽입 진행.
    printf("before insertion, nodes : %d 개, height : %d\n\n", RBNodes(root), height(root));
    for (i = 0; i < insert_and_delete; i++) {
        root = RB_INSERT(root, virkey, src, dest, test_name);
        if (i != insert_and_delete - 1) {
            virkey++;
        }
    }
    //삽입 후 노드수 트리높이 출력 및 삭제 전 노드 수 트리높이 출력, 삭제 진행.
    printf("after insertion, nodes : %d 개, height : %d\n\n", RBNodes(root), height(root));
    printf("before deletion, nodes : %d 개, height : %d\n\n", RBNodes(root), height(root));

    for (i = 0; i < insert_and_delete; i++) {
        root = RB_DELETE(root, virkey);
        if (i != insert_and_delete - 1) {
            virkey--;
        }
    }
    //삭제 후 노드수 트리높이
    printf("after deletion, nodes : %d 개, height : %d\n\n", RBNodes(root), height(root));
    return root;
}

// 관리자 모두 메뉴 2번
void second_manage(node *root) {
    int count;
    printf("\n\n최근 예약정보중 몇번째까지 예약정보를 볼지 입력해주세요 : ");
    scanf("%d", &count);
    //예약자 현황 출력 함수 실행
    ALL_SECTABLE(root, count);
    table_stop = 0;
}

// 예약자 현황 출력 입력 받은 갯수만큼 최근 예약 순대로 출력
void ALL_SECTABLE(node *root, int count) {
    if (root == NULL || table_stop == count) {
        return;
    }

    ALL_SECTABLE(root->right, count);
    if (table_stop == count) {
        return;
    }
    printf("예약번호 : %d\t 예약자 : %-11s\t 출발지 : %c\t 도착지 : %c \t 비행경로 : %-26s \t 비행시간 : %.2f\n", root->key, root->name, root->src, root->dest, root->path, root->time);
    table_stop += 1;

    ALL_SECTABLE(root->left, count);
}

#endif