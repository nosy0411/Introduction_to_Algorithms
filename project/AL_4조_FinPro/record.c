#ifndef __RECORD_C__
#define __RECORD_C__

#include "record.h"

// 예약 테이블 몇개까지 출력할건지
int table_stop = 0;

// RB트리 생성
node *CreateNode(Key key, char src, char dest, char *name) {
    node *n = (node *)malloc(sizeof(node));
    n->left = NULL;
    n->right = NULL;
    n->parent = NULL;
    // 예약번호, 출발지, 도착지, 예약자 이름 대입
    n->key = key;
    n->src = src;
    n->dest = dest;
    strcpy(n->name, name);

    n->color = true;
    return n;
}

// RB트리 최소값
node *TREE_MIN(node *n) {
    node *cur = n;
    while (cur->left != NULL) {
        cur = cur->left;
    }

    return cur;
}

// RB트리 검색
node *RB_SEARCH(node *root, Key key) {
    node *cur = root;
    while (cur != NULL) {
        if (cur->key == key) {
            break;
        } else if (cur->key > key)
            cur = cur->left;
        else
            cur = cur->right;
    }

    return cur;
}

// RB트리 좌회전
void *rotateLeft(node **root, node **x) {
    node *y = (*x)->right;

    (*x)->right = y->left;
    if ((*x)->right != NULL) {
        (*x)->right->parent = (*x);
    }

    if (y->left != NULL) {
        y->left->parent = (*x);
    }
    y->parent = (*x)->parent;

    if ((*x)->parent == NULL) {
        *root = y;
    } else if ((*x) == (*x)->parent->left) {
        (*x)->parent->left = y;
    } else {
        (*x)->parent->right = y;
    }
    y->left = (*x);
    (*x)->parent = y;
}

// RB트리 우회전
void *rotateRight(node **root, node **x) {
    node *y = (*x)->left;

    (*x)->left = y->right;
    if ((*x)->left != NULL) {
        (*x)->left->parent = (*x);
    }

    if (y->right != NULL) {
        y->right->parent = (*x);
    }
    y->parent = (*x)->parent;

    if ((*x)->parent == NULL) {
        *root = y;
    } else if ((*x) == (*x)->parent->right) {
        (*x)->parent->right = y;
    } else {
        (*x)->parent->left = y;
    }
    y->right = (*x);
    (*x)->parent = y;
}

// RB 삽입 및 트리 균형, 색깔 맞추기
void RB_INSERT_FIXUP(node **root, node **z) {
    node *y = NULL;
    node *p = NULL, *gp = NULL;

    while (((*z) != *root) && ((*z)->color != false) && (*z)->parent->color == true) {
        p = (*z)->parent;
        gp = (*z)->parent->parent;
        if (p == gp->left) {
            y = gp->right;

            if (y != NULL && y->color == true) {
                p->color = false;
                y->color = false;
                gp->color = true;
                (*z) = gp;
            }

            else if ((*z) == p->right) {
                rotateLeft(root, &p);
                (*z) = p;
                p = (*z)->parent;
            } else {
                rotateRight(root, &gp);
                p->color = false;
                gp->color = true;
                (*z) = p;
            }
        } else {
            y = gp->left;
            if (y != NULL && y->color == true) {
                p->color = false;
                y->color = false;
                gp->color = true;
                (*z) = gp;
            }

            else if ((*z) == (*z)->parent->left) {
                rotateRight(root, &p);
                (*z) = p;
                p = (*z)->parent;
            } else {
                rotateLeft(root, &gp);
                p->color = false;
                gp->color = true;
                (*z) = p;
            }
        }
    }
    (*root)->color = false;
}

// RB 삽입
node *RB_INSERT(node *root, Key key, char src, char dest, char *name) {
    node *z = CreateNode(key, src, dest, name);
    node *y = NULL;
    node *x = root;

    while (x != NULL) {
        y = x;
        if ((z->key) < (x->key)) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    z->parent = y;
    if (y == NULL) {
        root = z;
    } else if ((z->key) < (y->key)) {
        y->left = z;
    } else {
        y->right = z;
    }

    RB_INSERT_FIXUP(&root, &z);

    return root;
}

// RB 트리 변형 교체
void RB_TRANSPLANT(node **root, node **u, node **v) {
    if ((*u)->parent == NULL) {
        *root = *v;
    } else if ((*u) == (*u)->parent->left) {
        (*u)->parent->left = *v;
    } else {
        (*u)->parent->right = *v;
    }
    if ((*v) != NULL) {
        (*v)->parent = (*u)->parent;
    }
}

// RB트리 삭제 및 트리 균형, 색깔 맞추기
void RB_DELETE_FIXUP(node **root, node **x) {
    node *w;
    while (((*x) != (*root)) && (((*x)->color) == false)) {
        if ((*x) == (*x)->parent->left) {
            w = (*x)->parent->right;

            if (w->color == true) {
                w->color = false;
                (*x)->parent->color = true;
                rotateLeft(root, &((*x)->parent));
                w = (*x)->parent->right;
            }

            if (w->left->color == false && w->right->color == false) {
                w->color = true;
                (*x) = (*x)->parent;
            }

            else if (w->right->color == false && w->left->color == true) {
                w->left->color = false;
                w->color = true;
                rotateRight(root, &w);
                w = (*x)->parent->right;
            } else {
                w->color = (*x)->parent->color;
                (*x)->parent->color = false;
                w->right->color = false;
                rotateLeft(root, &((*x)->parent));
                (*x) = *root;
            }
        }

        else {
            w = (*x)->parent->left;

            if (w->color == true) {
                w->color = false;
                (*x)->parent->color = true;
                rotateRight(root, &((*x)->parent));
                w = (*x)->parent->left;
            }

            if (w->left->color == false && w->right->color == false) {
                w->color = true;
                (*x) = (*x)->parent;
            }

            else if (w->left->color == false && w->right->color == true) {
                w->right->color = false;
                w->color = true;
                rotateLeft(root, &w);
                w = (*x)->parent->left;
            } else {
                w->color = (*x)->parent->color;
                (*x)->parent->color = false;
                w->left->color = false;
                rotateRight(root, &((*x)->parent));
                (*x) = *root;
            }
        }
    }
    (*x)->color = false;
}

// RB트리 삭제
node *RB_DELETE(node *root, Key key) {
    node *z = RB_SEARCH(root, key);
    node *x;
    node *y = z;
    bool yo;
    yo = y->color;

    if (z->left == NULL) {
        x = z->right;
        RB_TRANSPLANT(&root, &z, &(z->right));
    } else if (z->right == NULL) {
        x = z->left;
        RB_TRANSPLANT(&root, &z, &(z->left));
    } else {
        y = TREE_MIN(z->right);
        yo = y->color;
        x = y->right;

        if (y->parent == z) {
            if (x != NULL) {
                x->parent = y;
            }
        } else {
            RB_TRANSPLANT(&root, &y, &(y->right));
            y->right = z->right;
            y->right->parent = y;
        }
        RB_TRANSPLANT(&root, &z, &y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if (yo == false) {
        if (x != NULL) {
            RB_DELETE_FIXUP(&root, &x);
        }
    }
    if (z != NULL) {
        free(z);
    }
    return root;
}

// RB트리 노드 개수
int RBNodes(node *node) {
    int r = 0, l = 0;
    if (node->right != NULL)
        r = RBNodes(node->right);
    if (node->left != NULL)
        l = RBNodes(node->left);

    return 1 + r + l;
}

// RB 트리 높이
int height(node *node) {
    int r = 0, l = 0;
    if (node->right != NULL)
        r = height(node->right);
    if (node->left != NULL)
        l = height(node->left);

    return 1 + max(r, l);
}

// RB 트리 전체 삭제
void ClearTree(node *root) {
    if (root != NULL) {
        ClearTree(root->left);
        ClearTree(root->right);
        free(root);
    }
}

// 500개 정보 가상으로 생성해서 RB테이블에 삽입
node *generate() {
    randomize();
    char src;
    char dest;
    int key = 0;
    int i, j;
    char passby[26];
    char virname[NUM][MAXLENGTH + 1];

    node *root = NULL;

    for (i = 0; i < NUM; i++) {
        //출발지, 도착지, 예약자 이름 랜덤 생성
        src = 'a' + random(SAMPLE);
        dest = 'a' + random(SAMPLE);
        // 예약번호 값은 순서대로 생성
        key += 1;
        // 1-10개의 랜덤길이를 가진 문자열 이면서 각 문자는 a-z중 랜덤으로 설정되고 중복이 없는 이름
        for (j = 0; j < random(MAXLENGTH) + 1; j++) {
            virname[i][j] = 'a' + random(SAMPLE);
        }
        virname[i][j] = '\0';
        root = RB_INSERT(root, key, src, dest, virname[i]);
    }

    return root;
}

// 예약자 정보 출력
void PRINT_RBINFO(node *root) {
    printf("\n\n< %s님의 예약 정보입니다.>\n", root->name);
    printf("예약번호 : %d\t", root->key);
    printf("출발지 : %c\t", root->src);
    printf("도착지 : %c\t\n", root->dest);
}

// 예약 테이블 일부 출력 특정횟수 이상은 출력 안됨
void PRINT_TABLE(node *root, int count) {
    if (root == NULL || table_stop == count) {
        return;
    }

    PRINT_TABLE(root->right, count);
    if (table_stop == count) {
        return;
    }
    printf("예약번호 : %d\t 예약자 : %-11s\t 출발지 : %c\t 도착지 : %c \t\n", root->key, root->name, root->src, root->dest);
    table_stop += 1;

    PRINT_TABLE(root->left, count);
}

// 최근 예약현황을 나타내는 메인 테이블 일부 출력 특정횟수 이상은 출력 안됨
// 개인정보이므로, 예약자 이름만 제거함. 이 함수는 UI테스트에서 실행됨.
void RESV_SECTABLE(node *root, int count) {
    if (root == NULL || table_stop == count) {
        return;
    }

    RESV_SECTABLE(root->right, count);
    if (table_stop == count) {
        return;
    }
    printf("예약번호 : %d\t 출발지 : %c\t 도착지 : %c \t\n", root->key, root->src, root->dest);
    table_stop += 1;

    RESV_SECTABLE(root->left, count);
}

#endif