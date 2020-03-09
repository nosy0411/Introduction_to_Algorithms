#include "record.h"
//예약 테이블에서 몇개까지 출력할껀지 변수
extern int table_stop;

int main() {
    int reserv_num;
    int error = 0;
    char reserv_name[MAXLENGTH + 1];
    int count;
    node* root = NULL;

    printf("500개의 예약자 정보를 생성합니다.\n");
    root = generate();

    printf("예약 테이블 중 일부를 출력합니다.\n");
    printf("최근 예약정보중 몇번째까지 예약정보를 볼지 입력해주세요 : ");
    scanf("%d", &count);
    PRINT_TABLE(root, count);
    // 테이블 몇번째까지 조회할건지 변수. extern 선언되어 record.c와 공유
    table_stop = 0;

    //예약번호와 예약이름을 입력받고 일치하는 정보가 있으면 예약자의 이름, 번호, 출발지, 도착지를 출력한다.
    //경유지와 최단경로, 최단시간은는 path와 departure time에 따라 달라지므로
    //나중에 데이터를 받을 수 있게 공간만 만들어두고 record 모듈 테스트에서는 출력하지 않는다. UI에서 출력한다.
    while (error == 0) {
        printf("\n\n예약번호를 입력하세요 : ");
        scanf("%d", &reserv_num);

        printf("\n예약자를 확인하기 위하여 예약자 이름을 입력해 주세요 : ");
        scanf("%s", reserv_name);

        node* loc = RB_SEARCH(root, reserv_num);

        if (strcmp(loc->name, reserv_name)) {
            printf("예약번호와 예약자가 일치하지 않습니다.\n");
            printf("예약번호와 예약자 이름을 다시 입력해 주세요.\n");
        } else {
            PRINT_RBINFO(loc);
            //경유지 출력 생략.
            //최단시간 출력 생략.
            error = 1;
        }
    }

    // 예약 테이블의 높이 출력.
    printf("\n테이블의 총 높이는 %d 입니다.\n", height(root));
    // 예약 테이블 노드 수 출력
    printf("\n예약자는 총 %d 명 입니다.\n", RBNodes(root));

    ClearTree(root);
    return 0;
}
