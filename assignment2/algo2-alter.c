#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define randomize() srand(time(NULL))
#define random(n) (rand()%(n))
#define SAMPLE 50
#define INTERVAL 5
#define NUM 20

int A[NUM]={0};
int insert_check=0;

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

    return node;
}
// Destroy a node.
void DestroyNode(BSTNode* node) {
    free(node);
}

// Connect the root to a left child node.
void CreateLeftSubtree(BSTNode* root, Key key) {
    if (root->left != NULL)
        exit(1);
    else {
        BSTNode* node = CreateNode(key);
        root->left = node;
    }
}
// Connect the root to a right child node.
void CreateRightSubtree(BSTNode* root, Key key) {
    if (root->right != NULL)
        exit(1);
    else {
        BSTNode* node = CreateNode(key);
        root->right = node;
    }
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
// Search an item in BST.
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

// Insert an item to BST.
void TREE_INSERT(BSTNode* root, Key key) {
    BSTNode* cur = root;
    while (cur != NULL) {
        if (cur->key == key){
            insert_check=1;    
            break;
        }
        else if (cur->key > key) {
            if (cur->left == NULL) {
                CreateLeftSubtree(cur, key);
                break;
            } else
                cur = cur->left;
        } else {
            if (cur->right == NULL) {
                CreateRightSubtree(cur, key);
                break;
            } else
                cur = cur->right;
        }
    }
}
// Remove an item from BST.
void TREE_DELETE(BSTNode* root, Key key) {
    BSTNode *cur = root, *parent = NULL;

    // FInd the current node and its parent node.
    while (cur != NULL && cur->key != key) {
        parent = cur;
        if (cur->key > key)
            cur = cur->left;
        else
            cur = cur->right;
    }

    if (cur == NULL) exit(1);
    if (cur->left == NULL && cur->right == NULL) {
        if (parent != NULL) {
            // Remove the current node depending on its position.
            if (parent->left == cur) {
                parent->left = NULL;
            } else {
                parent->right = NULL;
            }
        } else
            cur = NULL;  // The current node is the root.
    } else if (cur->left == NULL || cur->right == NULL) {
        BSTNode* child;
        if (cur->left != NULL)
            child = cur->left;
        else
            child = cur->right;

        if (parent != NULL) {
            if (parent->left == cur)
                parent->left = child;
            else
                parent->right = child;
        }
    } else {
        BSTNode *succ_parent = cur, *succ = cur->right;
        // Find the successor (left-most node of the current node.)
        while (succ->left != NULL) {
            succ_parent = succ;
            succ = succ->left;
        }

        // If the successor has a child node,
        // connect the child node to its parent node.
        if (succ_parent->right == succ)
            succ_parent->right = succ->right;
        else
            succ_parent->left = succ->right;

        // Copy the key of the successor to the current node.
        cur->key = succ->key;
        // Remove the successor.
        cur = succ;
    }

    DestroyNode(cur);
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

int TREE_MIN(BSTNode* root){
    BSTNode *cur = root;
    while(cur->left!=NULL){
        cur=cur->left;
    }

    return cur->key;
}

int TREE_MAX(BSTNode* root){
    BSTNode *cur = root;
    while(cur->right!=NULL){
        cur=cur->right;
    }

    return cur->key;
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
    TREE_INSERT(T,6);
    if(insert_check==1){
        printf("Try to insert 6 but there is already node 6 in tree\n");
    }
    else{
        if(Verify(T,TREE_MIN(T),TREE_MAX(T))==true){
            PRINT_BST(T,0);
            printf("Inserted 6\n");
        }
        else{
            printf("This is not Binary Search Tree\n");
        }
    }
    insert_check=0;
    printf("===============================================\n");
    TREE_INSERT(T,29);
    if(insert_check==1){
        printf("Try to insert 29 but there is already node 29 in tree\n");
    }
    else{
        if(Verify(T,TREE_MIN(T),TREE_MAX(T))==true){
            PRINT_BST(T,0);
            printf("Inserted 29\n");
        }
        else{
            printf("This is not Binary Search Tree\n");
        }
    }
    insert_check=0;
    printf("===============================================\n");
    TREE_INSERT(T,17);
    if(insert_check==1){
        printf("Try to insert 17 but there is already node 17 in tree\n");
    }
    else{
        if(Verify(T,TREE_MIN(T),TREE_MAX(T))==true){
            PRINT_BST(T,0);
            printf("Inserted 17\n");
        }
        else{
            printf("This is not Binary Search Tree\n");
        }
    }
    insert_check=0;
    printf("===============================================\n");
    TREE_INSERT(T,21);
    if(insert_check==1){
        printf("Try to insert 21 but there is already node 21 in tree\n");
    }
    else{
        if(Verify(T,TREE_MIN(T),TREE_MAX(T))==true){
            PRINT_BST(T,0);
            printf("Inserted 21\n");
        }
        else{
            printf("This is not Binary Search Tree\n");
        }
    }
    insert_check=0;
    printf("===============================================\n\n\n\n");


    TREE_DELETE(T,6);
    if(Verify(T,TREE_MIN(T),TREE_MAX(T))==true){
        PRINT_BST(T,0);
        printf("\nDeleted 6\n");
    }
    else{
        printf("This is not Binary Search Tree\n");
    }
    printf("===============================================\n");
    TREE_DELETE(T,29);
    if(Verify(T,TREE_MIN(T),TREE_MAX(T))==true){
        PRINT_BST(T,0);
        printf("\nDeleted 29\n");
    }
    else{
        printf("This is not Binary Search Tree\n");
    }
    printf("===============================================\n");
    TREE_DELETE(T,17);
    if(Verify(T,TREE_MIN(T),TREE_MAX(T))==true){
        PRINT_BST(T,0);
        printf("\nDeleted 17\n");
    }
    else{
        printf("This is not Binary Search Tree\n");
    }
    printf("===============================================\n");
    TREE_DELETE(T,21);
    if(Verify(T,TREE_MIN(T),TREE_MAX(T))==true){
        PRINT_BST(T,0);
        printf("\nDeleted 21\n");
    }
    else{
        printf("This is not Binary Search Tree\n");
    }
    printf("===============================================\n\n\n\n");
}