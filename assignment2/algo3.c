#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define max(X, Y) ((X) > (Y) ? (X) : (Y))

#define randomize() srand(time(NULL))
#define random(n) (rand()%(n))
#define SAMPLE 50
#define COUNT 5
#define NUM 20

int A[NUM]={0};

typedef int Key;
typedef struct _node {
    // RED-true, BLACK-false
    bool color;
    Key key;
    struct _node *left;
    struct _node *right;
    struct _node *parent;
} node;


node *CreateNode(Key key) {
    node *n = (node *)malloc(sizeof(node));
    n->left = NULL;
    n->right = NULL;
    n->parent = NULL;
    n->key = key;

    n->color = true;
    return n;
}

node *TREE_MIN(node* n){
    node *cur = n;
    while(cur->left!=NULL){
        cur=cur->left;
    }

    return cur;
}

// Search an item in RBTree
node* RB_SEARCH(node* root, Key key) {
    node* cur = root;
    while (cur != NULL) {
        if (cur->key == key){
            break;
        }

        else if (cur->key > key)
            cur = cur->left;
        else
            cur = cur->right;
    }

    return cur;
}

void *rotateLeft(node** root, node** x) {
    // printf("left rotation!!\n");
    node *y = (*x)->right;
    if(y==NULL){
        return;
    }

    (*x)->right = y->left;
    if((*x)->right!=NULL){
        (*x)->right->parent=(*x);
    }

    if(y->left!=NULL){
        y->left->parent=(*x);
    }
    y->parent=(*x)->parent;

    if((*x)->parent==NULL){
        *root=y;
    }
    else if((*x)==(*x)->parent->left){
        (*x)->parent->left=y;
    }
    else{
        (*x)->parent->right=y;
    }
    y->left = (*x);
    (*x)->parent = y;
}

void *rotateRight(node** root, node** x) {
    // printf("right rotation!!\n");
    node *y = (*x)->left;
    if(y==NULL){
        return;
    }

    (*x)->left = y->right;
    if((*x)->left!=NULL){
        (*x)->left->parent=(*x);
    }

    if(y->right!=NULL){
        y->right->parent=(*x);
    }
    y->parent=(*x)->parent;

    if((*x)->parent==NULL){
        *root=y;
    }
    else if((*x)==(*x)->parent->right){
        (*x)->parent->right=y;
    }
    else{
        (*x)->parent->left=y;
    }
    y->right = (*x);
    (*x)->parent = y;
}

void RB_INSERT_FIXUP(node** root, node** z){
    node *y=NULL;
    node *p=NULL, *gp=NULL;

    while(((*z)!=*root) && ((*z)->color!= false) && (*z)->parent->color==true){
        p=(*z)->parent;
        gp=(*z)->parent->parent;
        if(p==gp->left){

            y=gp->right;

            if(y!=NULL && y->color==true){
                p->color=false;
                y->color=false;
                gp->color=true;
                (*z)=gp;
            }

            else if((*z)==p->right){
                rotateLeft(root,&p);
                (*z)=p;
                p=(*z)->parent;
            }
            else{
                rotateRight(root,&gp);
                p->color=false;
                gp->color=true;
                (*z)=p;
            }
        }
        else{

            y=gp->left;
            if(y!=NULL && y->color==true){
                p->color=false;
                y->color=false;
                gp->color=true;
                (*z)=gp;
            }

            else if((*z)==(*z)->parent->left){
                rotateRight(root,&p);
                (*z)=p;
                p=(*z)->parent;
            }
            else{
                rotateLeft(root,&gp);
                p->color=false;
                gp->color=true;
                (*z)=p;
            }
        }
    }
    (*root)->color=false;
}

node* RB_INSERT(node* root, Key key){
    node *z=CreateNode(key);
    node *y=NULL;
    node *x=root;

    while(x!=NULL){
        y=x;
        if ((z->key)<(x->key)){
            x=x->left;
        }
        else{
            x=x->right;
        }
    }
    z->parent=y;
    if (y==NULL){
        root=z;
    }
    else if ((z->key)<(y->key)){
        y->left=z;
    }
    else{
        y->right=z;
    }
    
    RB_INSERT_FIXUP(&root,&z);

    return root;
}

void RB_TRANSPLANT(node** root, node** u, node** v){
    if((*u)->parent==NULL){
        *root=*v;
    }
    else if((*u)==(*u)->parent->left){
        (*u)->parent->left=*v;
    }
    else{
        (*u)->parent->right=*v;
    }
    if((*v)!=NULL){
        (*v)->parent=(*u)->parent;
    }
}

void RB_DELETE_FIXUP(node** root, node** x){
    node *w;
    while(((*x)!=(*root)) && (((*x)->color)==false)){
        if ((*x)==(*x)->parent->left){
            w=(*x)->parent->right;

            if(w->color==true){
                w->color=false;
                (*x)->parent->color=true;
                rotateLeft(root,&((*x)->parent));
                w=(*x)->parent->right;
            }

            if(w->left->color==false && w->right->color==false){
                w->color=true;
                (*x)=(*x)->parent;
            }
            
            else if (w->right->color==false && w->left->color==true){
                w->left->color=false;
                w->color=true;
                rotateRight(root,&w);
                w=(*x)->parent->right;
            }
            else {
                w->color=(*x)->parent->color;
                (*x)->parent->color=false;
                w->right->color=false;
                rotateLeft(root,&((*x)->parent));
                (*x)=*root;
            }
        }

        else{
            w=(*x)->parent->left;

            if(w->color==true){
                w->color=false;
                (*x)->parent->color=true;
                rotateRight(root,&((*x)->parent));
                w=(*x)->parent->left;
            }

            if(w->left->color==false && w->right->color==false){
                w->color=true;
                (*x)=(*x)->parent;
            }
            
            else if (w->left->color==false && w->right->color==true){
                w->right->color=false;
                w->color=true;
                rotateLeft(root,&w);
                w=(*x)->parent->left;
            }
            else {
                w->color=(*x)->parent->color;
                (*x)->parent->color=false;
                w->left->color=false;
                rotateRight(root,&((*x)->parent));
                (*x)=*root;
            }
        }
    }
    (*x)->color=false;
}

node* RB_DELETE(node* root, Key key){
    node *z=RB_SEARCH(root,key);
    node *x;
    node *y=z;
    bool yo;
    yo=y->color;
    
    if(z->left==NULL){
        x=z->right;
        RB_TRANSPLANT(&root,&z,&(z->right));
    }
    else if(z->right==NULL){
        x=z->left;
        RB_TRANSPLANT(&root,&z,&(z->left));
    }
    else{
        y=TREE_MIN(z->right);
        yo=y->color;
        x=y->right;

        if(y->parent==z){
            if(x!=NULL){
                x->parent=y;
            }
        }
        else{
            RB_TRANSPLANT(&root,&y,&(y->right));
            y->right=z->right;
            y->right->parent=y;
        }
        RB_TRANSPLANT(&root, &z, &y);
        y->left=z->left;
        y->left->parent=y;
        y->color=z->color;
    }
    if(yo==false){
        if(x!=NULL){
            RB_DELETE_FIXUP(&root,&x);
        }
    }
    if(z!=NULL){
        free(z);
    }
    return root;
}

//Display a tree.
void PRINT_RBT(node *root, int space) {
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    PRINT_RBT(root->right, space);

    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    if (root->color == true) {
        printf("%d[R]\n", root->key);
    } else {
        printf("%d[B]\n", root->key);
    }
    // Process left child
    PRINT_RBT(root->left, space);
}
void generate(){

    randomize();
	for(int i=0;i<NUM;i++){
		while(1){
			int check=0;
			A[i]=random(SAMPLE);
			for(int j=0;j<i;j++){
				if(A[j]==A[i]){
					check=1;
					break;
				}
			}
			if(check==1){
				continue;
			}
			else{
				break;
			}
		}

	}
}

// Insert an item to BST.
void TREE_INSERT(node* root, Key key) {
    node *y=NULL;
    node *x=root;
    node *z=CreateNode(key);
    node *temp=NULL;

    while(x!=NULL){
        x->parent=temp;
        y=x;

        if(x->key==key){
            return 0;
        }

        if((z->key)<x->key){
            temp=x;
            x=x->left;
        }
    
        else{
            temp=x;
            x=x->right;
        }
    }
    z->parent=y;
    if(y==NULL)
        root=z;
    else if ((z->key)<(y->key))
        y->left=z;
    else
        y->right=z;
}

//calculate the height of a binary treefree(del1);
int height(node* node) {
    int r = 0, l = 0;
    if (node->right != NULL)
        r = height(node->right);
    if (node->left != NULL)
        l =height(node->left);

    return 1 + max(r, l);
}

void ClearTree(node* root) {
    if (root != NULL) {
        ClearTree(root->left);
        ClearTree(root->right);
        free(root);
    }
}

int main(){
    int i;

    generate();

    for(i=0;i<NUM;i++){
        printf("%d ",A[i]);
    }
    printf("\n");

    printf("\n===============================================\n");
    node *root = NULL;
    for(i=0;i<NUM;i++){
        root=RB_INSERT(root,A[i]);
    }
    PRINT_RBT(root,0);
    printf("RBT Constructed\n");
    printf("\n===============================================\n");
    node *check=RB_SEARCH(root,6);
    if(check==NULL){
        root=RB_INSERT(root,6);
        PRINT_RBT(root,0);
        printf("Inserted node 6 in red black tree\n");
        printf("\n===============================================\n");
    }
    else{
        printf("\n===============================================\n");
        printf("Already exist node 6 in red black tree\n");
        printf("===============================================\n");
    }
    check=RB_SEARCH(root,29);
    if(check==NULL){
        root=RB_INSERT(root,29);
        PRINT_RBT(root,0);
        printf("Inserted node 29 in red black tree\n");
        printf("\n===============================================\n");
    }
    else{
        printf("\n===============================================\n");
        printf("Already exist node 29 in red black tree\n");
        printf("===============================================\n");
    }
    check=RB_SEARCH(root,17);
    if(check==NULL){
        root=RB_INSERT(root,17);
        PRINT_RBT(root,0);
        printf("Inserted node 17 in red black tree\n");
        printf("\n===============================================\n");
    }
    else{
        printf("\n===============================================\n");
        printf("Already exist node 17 in red black tree\n");
        printf("===============================================\n");
    }
    check=RB_SEARCH(root,21);
    if(check==NULL){
        root=RB_INSERT(root,21);
        PRINT_RBT(root,0);
        printf("Inserted node 21 in red black tree\n");
        printf("\n===============================================\n");
    }
    else{
        printf("\n===============================================\n");
        printf("Already exist node 21 in red black tree\n");
        printf("===============================================\n");
    }
    printf("\n===============================================\n");

    check = RB_SEARCH(root,6);
    if (check==NULL){
        printf("Not exist node 6 in red black tree\n");
        printf("===============================================\n");
    }
    else{
        root =RB_DELETE(root,6);
        PRINT_RBT(root,0);
        printf("deleted node 6 in red black tree\n");
        printf("\n===============================================\n");
    }

    check = RB_SEARCH(root,17);
    if (check==NULL){
        printf("Not exist node 17 in red black tree\n");
        printf("===============================================\n");
    }
    else{
        root=RB_DELETE(root,17);
        PRINT_RBT(root,0);
        printf("deleted node 17 in red black tree\n");
        printf("\n===============================================\n");
    }

    check = RB_SEARCH(root,21);
    if (check==NULL){
        printf("Not exist node 21 in red black tree\n");
        printf("===============================================\n");
    }
    else{
        root =RB_DELETE(root,21);
        PRINT_RBT(root,0);
        printf("deleted node 21 in red black tree\n");
        printf("\n===============================================\n");
    }

    check = RB_SEARCH(root,7);
    if (check==NULL){
        printf("Not exist node 7 in red black tree\n");
        printf("===============================================\n");
    }
    else{
        root=RB_DELETE(root,7);
        PRINT_RBT(root,0);
        printf("deleted node 7 in red black tree\n");
        printf("\n===============================================\n");
    }
    ClearTree(root);

    node *BST = CreateNode(A[0]);
    for(i=1;i<NUM;i++){
        TREE_INSERT(BST,A[i]);
    }
    node *RBT = NULL;
    for(i=0;i<NUM;i++){
        RBT=RB_INSERT(RBT,A[i]);
    }
    printf("\n");
    printf("The height of BST is %d\n",height(BST));
    printf("The height of RBT is %d\n",height(RBT));

    ClearTree(BST);
    ClearTree(RBT);

    return 0;
}