#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <limits.h>

#define min(X, Y) ((X) < (Y) ? (X) : (Y))
#define randomize() srand(time(NULL))
#define random(n) (rand()%(n))
#define SAMPLE 50
#define INTERVAL 5
#define NUM 20

int A[NUM]={0};
int node_exist=1;

typedef enum { false,
               true } bool;

typedef int Key;

typedef struct _BSTNode {
    Key key;
    struct _BSTNode* left;
    struct _BSTNode* right;
    struct _BSTNode* parent;
} BSTNode;

// Create a new node.
BSTNode* CreateNode(Key key) {
    BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;

    return node;
}
// Destroy a node.
void DestroyNode(BSTNode* node) {
    free(node);
}
// Verify if the tree is a binary search tree.
// Initialize the minimum and maximum as INT_MIN and INT_MAX
bool Verify(BSTNode* root, int min, int max) {
    if (root != NULL) {
        // Return false if this node violates the min/max constraints.
        if (root->key < min || root->key > max)
            return false;
        else
            // Check the subtrees recursively tightening the min/max constraints.
            return Verify(root->left, min, root->key) && Verify(root->right, root->key, max);
    } else
        return true;  // an empty tree is BST.
}
// Search and display an item in BST.
BSTNode* TREE_SEARCH(BSTNode* root, Key key) {
    BSTNode* cur = root;
    while (cur != NULL) {
        printf("%d ",cur->key);
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
// Search an item in BST.
BSTNode* TREE_FILTER(BSTNode* root, Key key) {
    BSTNode* cur = root;
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
// Check an item
BSTNode* TREE_CHECK(BSTNode* root, Key key) {
    BSTNode* cur = root;
    BSTNode* temp=NULL;
    int check=0;
    while (cur != NULL) {
        if (cur->key == key){
            check=1;
            break;
        }
        else if (cur->key > key){
            temp=cur;
            cur = cur->left;
        }
        else{
            temp=cur;
            cur = cur->right;
        }
    }
    if(check==1)
        return cur;
    else{
        node_exist=0;
        return temp;
    }
}

// Insert an item to BST.
void TREE_INSERT(BSTNode* root, Key key) {
    BSTNode *check = TREE_FILTER(root,key);
    if(check==NULL){
        BSTNode *y=NULL;
        BSTNode *x=root;
        BSTNode *z=CreateNode(key);
        BSTNode *temp=NULL;

        while(x!=NULL){
            x->parent=temp;
            y=x;

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
}
BSTNode *TREE_MIN(BSTNode* node){
    BSTNode *cur = node;
    while(cur->left!=NULL){
        cur=cur->left;
    }

    return cur;
}

BSTNode *TREE_MAX(BSTNode* node){
    BSTNode *cur = node;
    while(cur->right!=NULL){
        cur=cur->right;
    }

    return cur;
}

void TRANSPLANT(BSTNode* root, BSTNode* u, BSTNode* v){
    if(u->parent==NULL){
        root=v;
    }
    else if(u==u->parent->left){
        u->parent->left=v;
    }
    else{
        u->parent->right=v;
    }
    if(v!=NULL){
        v->parent=u->parent;
    }
}

// Remove an item from BST.
void TREE_DELETE(BSTNode* root, BSTNode* z ) {

    if(z->left==NULL){
        TRANSPLANT(root, z,z->right);
    }
    else if (z->right==NULL){
        TRANSPLANT(root, z,z->left);
    }
    else {
        BSTNode *y = TREE_MIN(z->right);
        if(y->parent!=z){
            TRANSPLANT(root,y,y->right);
            y->right=z->right;
            y->right->parent=y;
        }
        TRANSPLANT(root,z,y);
        y->left=z->left;
        y->left->parent=y;
    }
    free(z);
}

//Display a tree.
void PRINT_BST(BSTNode* root, int dist) {
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    dist += INTERVAL;

    // Process right child first
    PRINT_BST(root->right, dist);

    // Print current node after space
    // count
    printf("\n");
    for (int i = INTERVAL; i < dist; i++)
        printf(" ");
    printf("%d\n", root->key);

    // Process left child
    PRINT_BST(root->left, dist);
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

BSTNode *TREE_SUCCESSOR(BSTNode *node, BSTNode *root){
    BSTNode *x=node;
    if (x->right!=NULL){
        return TREE_MIN(x->right);
    }
    if(x==TREE_MAX(root)){
        return x;
    }
    BSTNode *y=x->parent;

    while(y!=NULL && x==y->right){
        x=y;
        y=y->parent;
    }
    return y;
}

BSTNode *TREE_PREDECESSOR(BSTNode *node, BSTNode *root){
    BSTNode *x=node;
    if (x->left!=NULL){
        return TREE_MAX(x->left);
    }
    if(x==TREE_MIN(root)){
        return x;
    }
    BSTNode *y=x->parent;
    while(y!=NULL && x==y->left){
        x=y;
        y=y->parent;
    }
    return y;
}

BSTNode* TREE_NEAREST_NEIGHBOR(BSTNode* root, int key){
    BSTNode* y=NULL;
    BSTNode* ys=NULL;
    BSTNode* yp=NULL;
    y=TREE_CHECK(root,key);
    ys=TREE_SUCCESSOR(y,root);
    yp=TREE_PREDECESSOR(y,root);
    int miny, minys, minyp;
    miny=abs((y->key)-key);
    minys=abs((ys->key)-key);
    minyp=abs((yp->key)-key);

    if(min(miny,minys)==miny){
        if(min(miny,minyp)==miny)
            return y;
        else
            return yp;
    }
    else{
        if(min(minys,minyp)==minys)
            return ys;
        else
            return yp;
    }

}

// Clear a tree.
void ClearTree(BSTNode* root) {
    if (root != NULL) {
        ClearTree(root->left);
        ClearTree(root->right);
        free(root);
    }
}

int main(){

    int i;

    generate();
    BSTNode *T = CreateNode(A[0]);
    for(i=0;i<NUM;i++){
        printf("%d ",A[i]);
    }
    printf("\n===============================================\n");
    for(i=1;i<NUM;i++){
        TREE_INSERT(T,A[i]);
    }
    PRINT_BST(T,0);
    printf("===============================================\n\n");
    BSTNode *node = TREE_SEARCH(T,10);
    printf("\n");
    if (node==NULL){
        printf("Search 10 but not exist\n\n");
    }
    else{
        printf("Successfully searched 10\n\n");
    }
    node = TREE_SEARCH(T,9);
    printf("\n");
    if (node==NULL){
        printf("Search 9 but not exist\n\n");
    }
    else{
        printf("Successfully searched 9\n\n");
    }
    node = TREE_SEARCH(T,15);
    printf("\n");
    if (node==NULL){
        printf("Search 15 but not exist\n\n");
    }
    else{
        printf("Successfully searched 15\n\n");
    }
    printf("===============================================\n");
    printf("Nearest neighbor of 5 is %d\n",TREE_NEAREST_NEIGHBOR(T,5)->key);
    printf("Nearest neighbor of 9 is %d\n",TREE_NEAREST_NEIGHBOR(T,9)->key);
    printf("Nearest neighbor of 17 is %d\n",TREE_NEAREST_NEIGHBOR(T,17)->key);
    printf("===============================================\n");


    node = TREE_CHECK(T,6);
    if(node_exist==1){
        printf("Try to insert 6 but there is already node 6 in tree\n");
    }
    else{
        TREE_INSERT(T,6);
        if(Verify(T,TREE_MIN(T)->key,TREE_MAX(T)->key)==true){
            PRINT_BST(T,0);
            printf("\n===============================================\n");
            printf("Inserted 6\n");
        }
        else{
            printf("This is not Binary Search Tree\n");
        }
    }
    printf("===============================================\n");
    node_exist=1;
    node = TREE_CHECK(T,29);
    if(node_exist==1){
        printf("Try to insert 29 but there is already node 29 in tree\n");
    }
    else{
        TREE_INSERT(T,29);
        if(Verify(T,TREE_MIN(T)->key,TREE_MAX(T)->key)==true){
            PRINT_BST(T,0);
            printf("\n===============================================\n");
            printf("Inserted 29\n");
        }
        else{
            printf("This is not Binary Search Tree\n");
        }
    }

    printf("===============================================\n");
    node_exist=1;
    node = TREE_CHECK(T,17);
    if(node_exist==1){
        printf("Try to insert 17 but there is already node 17 in tree\n");
    }
    else{
        TREE_INSERT(T,17);
        if(Verify(T,TREE_MIN(T)->key,TREE_MAX(T)->key)==true){
            PRINT_BST(T,0);
            printf("\n===============================================\n");
            printf("Inserted 17\n");
        }
        else{
            printf("This is not Binary Search Tree\n");
        }
    }
    printf("===============================================\n");
    node_exist=1;
    node = TREE_CHECK(T,21);
    if(node_exist==1){
        printf("Try to insert 21 but there is already node 21 in tree\n");
    }
    else{
        TREE_INSERT(T,21);
        if(Verify(T,TREE_MIN(T)->key,TREE_MAX(T)->key)==true){
            PRINT_BST(T,0);
            printf("\n===============================================\n");
            printf("Inserted 21\n");
        }
        else{
            printf("This is not Binary Search Tree\n");
        }
    }
    node_exist=1;
    printf("===============================================\n\n\n\n");

    node = TREE_CHECK(T,6);
    if (node_exist==1){
        TREE_DELETE(T,node);
        if(Verify(T,TREE_MIN(T)->key,TREE_MAX(T)->key)==true){
            PRINT_BST(T,0);
            printf("\n===============================================\n");
            printf("Deleted 6\n");
        }
        else{
            printf("This is not Binary Search Tree\n");
        }
        printf("===============================================\n");
    }
    else{
        printf("Try to delete 6 but node 6 does not exist in tree\n");
    }
    printf("===============================================\n");

    node = TREE_CHECK(T,17);
    if (node_exist==1){
        TREE_DELETE(T,node);
        if(Verify(T,TREE_MIN(T)->key,TREE_MAX(T)->key)==true){
            PRINT_BST(T,0);
            printf("\n===============================================\n");
            printf("Deleted 17\n");
        }
        else{
            printf("This is not Binary Search Tree\n");
        }
        printf("===============================================\n");
    }
    else{
        printf("Try to delete 17 but node 17 does not exist in tree\n");
    }

    node = TREE_CHECK(T,21);
    if (node_exist==1){
        TREE_DELETE(T,node);
        if(Verify(T,TREE_MIN(T)->key,TREE_MAX(T)->key)==true){
            PRINT_BST(T,0);
            printf("\n===============================================\n");
            printf("Deleted 21\n");
        }
        else{
            printf("This is not Binary Search Tree\n");
        }
        printf("===============================================\n");
    }
    else{
        printf("Try to delete 21 but node 21 does not exist in tree\n");
    }

    node = TREE_CHECK(T,7);
    if (node_exist==1){
        TREE_DELETE(T,node);
        if(Verify(T,TREE_MIN(T)->key,TREE_MAX(T)->key)==true){
            PRINT_BST(T,0);
            printf("\n===============================================\n");
            printf("Deleted 7\n");
        }
        else{
            printf("This is not Binary Search Tree\n");
        }
        printf("===============================================\n");
    }
    else{
        printf("Try to delete 7 but node 7 does not exist in tree\n");
    }
    ClearTree(T);
}