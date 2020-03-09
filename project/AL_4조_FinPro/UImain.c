#include "UI.h"
//예약 테이블에서 몇개까지 출력할껀지 변수
extern int table_stop;

int main() {
    //그래프 초기화
    city_point my_city_point[CNUM];
    path_info my_path_info[PNUM];
    Graph path_graph;

    // 26개의 도시중 그래프 경로 100개 랜덤 생성
    CreatePath(&path_graph, my_city_point, my_path_info, CNUM, PNUM);

    //500개의 예약자 정보를 생성합니다. 경로, 최단시간 모두 삽입
    node *root;
    root = resv_init(&path_graph, my_path_info);

    //초기 500개 생성 이후 추가되는 예약번호를 설정하기 위한 변수
    int fin_num = 500;
    //초기 화면 출력
    drawscreen(root);
    table_stop = 0;
    int flag;

    //아무 키나 눌러지면 화면 지워지고 예약과정 시작
    int s = getch();
    if (s) {
        system("cls");
    }
menu:
    printf("<<메뉴를 선택해 주세요!>>\n\n");
    printf("0 : 예약 확인\n\n1 : 예약 진행 \n\n2 : 예약 취소\n\n3 : 도시 간 비행편 확인\n\n4 : 관리자 모드\n\n");
    printf("진행을 원하시는 번호를 눌러주세요. 그 이외의 숫자 키가 입력되면 프로그램이 종료됩니다.\n");
    printf("선택 : ");
    scanf("%d", &flag);
    while (getchar() != '\n')
        ;

    //메뉴 0번
    if (flag == 0) {
        system("cls");
        zero(root);
        printf("\n\n아무 키나 누르면 홈으로 돌아갑니다.");
        s = getch();
        if (s) {
            system("cls");
        }
        goto menu;
    }

    //메뉴 1번
    else if (flag == 1) {
        system("cls");
        root = first(&path_graph, my_path_info, root, fin_num);
        //예약 테이블 출력 후 초기화
        table_stop = 0;
        //예약 후 예약 번호 증가.
        fin_num += 1;
        printf("\n\n아무 키나 누르면 홈으로 돌아갑니다.");
        s = getch();
        if (s) {
            system("cls");
        }
        goto menu;
    }

    // 메뉴 2번
    else if (flag == 2) {
        system("cls");
        root = second(root);
        printf("\n\n아무 키나 누르면 홈으로 돌아갑니다.");
        s = getch();
        if (s) {
            system("cls");
        }
        goto menu;
    }

    // 메뉴 3번
    else if (flag == 3) {
        system("cls");
        third(my_path_info);
        printf("\n\n아무 키나 누르면 홈으로 돌아갑니다.");
        s = getch();
        if (s) {
            system("cls");
        }
        goto menu;
    }

    // 메뉴 4번
    else if (flag == 4) {
        char secret[MAXLENGTH + 1];
        printf("\n\n 관리자만 이용가능합니다. 비밀번호를 입력하세요 : ");
        scanf("%s", secret);
        while (getchar() != '\n')
            ;

        // 비밀 번호를 입력받고 비밀번호와 일치하면 관리자 모드 실행. 비밀번호는 UI.h에 선언 되어 있음.
        if (!strcmp(SECRET, secret)) {
            system("cls");
            fourth(root);
        } else {
            printf("\n\n**비밀번호가 일치하지 않습니다.**\n\n");
        }
        printf("\n\n아무 키나 누르면 홈으로 돌아갑니다.");
        s = getch();
        if (s) {
            system("cls");
        }
        goto menu;
    }

    // 이외의 키는 시스템 종료
    else {
        printf("\n\n시스템을 종료합니다.");

        //만들어진 테이블과 그래프 모두 해제하고 종료.
        ClearTree(root);
        DestroyGraph(&path_graph);
        exit(1);
    }
}