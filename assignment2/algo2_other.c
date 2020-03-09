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

typedef int Key;

typedef struct _BSTNode {
    Key key;
    struct _BSTNode* left_child;
    struct _BSTNode* right_child;
} BSTNode;

// Create a new node.
BSTNode* CreateNode(Key key) {
    BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
    node->key = key;
    node->left_child = NULL;
    node->right_child = NULL;

    return node;
}
// Destroy a node.
void DestroyNode(BSTNode* node) {
    free(node);
}

// Connect the root to a left child node.
void CreateLeftSubtree(BSTNode* root, Key key) {
    if (root->left_child != NULL)
        exit(1);
    else {
        BSTNode* node = CreateNode(key);
        root->left_child = node;
    }
}
// Connect the root to a right child node.
void CreateRightSubtree(BSTNode* root, Key key) {
    if (root->right_child != NULL)
        exit(1);
    else {
        BSTNode* node = CreateNode(key);
        root->right_child = node;
    }
}
// Search an item in BST.
BSTNode* TREE_Search(BSTNode* root, Key key) {
    BSTNode* cur = root;

    while (cur != NULL) {
        if (cur->key == key)
            break;
        else if (cur->key > key)
            cur = cur->left_child;
        else
            cur = cur->right_child;
    }

    return cur;
}

// Insert an item to BST.
void TREE_INSERT(BSTNode* root, Key key) {
    BSTNode* cur = root;
    while (cur != NULL) {
        if (cur->key == key)
            exit(1);
        else if (cur->key > key) {
            if (cur->left_child == NULL) {
                CreateLeftSubtree(cur, key);
                break;
            } else
                cur = cur->left_child;
        } else {
            if (cur->right_child == NULL) {
                CreateRightSubtree(cur, key);
                break;
            } else
                cur = cur->right_child;
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
            cur = cur->left_child;
        else
            cur = cur->right_child;
    }

    if (cur == NULL) exit(1);
    if (cur->left_child == NULL && cur->right_child == NULL) {
        if (parent != NULL) {
            // Remove the current node depending on its position.
            if (parent->left_child == cur) {
                parent->left_child = NULL;
            } else {
                parent->right_child = NULL;
            }
        } else
            cur = NULL;  // The current node is the root.
    } else if (cur->left_child == NULL || cur->right_child == NULL) {
        BSTNode* child;
        if (cur->left_child != NULL)
            child = cur->left_child;
        else
            child = cur->right_child;

        if (parent != NULL) {
            if (parent->left_child == cur)
                parent->left_child = child;
            else
                parent->right_child = child;
        }
    } else {
        BSTNode *succ_parent = cur, *succ = cur->right_child;
        // Find the successor (left-most node of the current node.)
        while (succ->left_child != NULL) {
            succ_parent = succ;
            succ = succ->left_child;
        }

        // If the successor has a child node,
        // connect the child node to its parent node.
        if (succ_parent->right_child == succ)
            succ_parent->right_child = succ->right_child;
        else
            succ_parent->left_child = succ->right_child;

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
    PRINT_BST(root->right_child, dist);

    // Print current node after space
    // count
    printf("\n");
    for (int i = INTERVAL; i < dist; i++)
        printf(" ");
    printf("%d\n", root->key);

    // Process left child
    PRINT_BST(root->left_child, dist);
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

//for asciinode display

#define MIN(X, Y) ((X) < (Y) ? (X) : (Y))
#define MAX(X, Y) ((X) > (Y) ? (X) : (Y))
#define MAX_HEIGHT 1000
int lprofile[MAX_HEIGHT];
int rprofile[MAX_HEIGHT];
#define INFINITY (1 << 20)
//adjust gap between left and right nodes
#define gap 3

//used for printing next node in the same level,
//this is the x coordinate of the next char printed
int print_next;

typedef struct _asciinode {
    struct _asciinode* left;
    struct _asciinode* right;
    //length of the edge from this node to its children
    int edge_length;
    int height;
    int lablen;

    //-1=I am left, 0=I am root, 1=right
    int parent_dir;

    //max supported unit32 in dec, 10 digits max
    char label[11];
} asciinode;

asciinode* build_ascii_tree_recursive(BSTNode* root);

//Copy the tree into the ascii node structre
asciinode* build_ascii_tree(BSTNode* root);

//Free all the nodes of the given tree
void free_ascii_tree(asciinode* node);

//The following function fills in the lprofile array for the given tree.
//It assumes that the center of the label of the root of this tree
//is located at a position (x,y).  It assumes that the edge_length
//fields have been computed for this tree.
void compute_lprofile(asciinode* node, int x, int y);
void compute_rprofile(asciinode* node, int x, int y);

//This function fills in the edge_length and
//height fields of the specified tree
void compute_edge_lengths(asciinode* node);

//This function prints the given level of the given tree, assuming
//that the node has the given x cordinate.
void print_level(asciinode* node, int x, int level);

//prints ascii tree for given Tree structure
void print_ascii_tree(BSTNode* root);

asciinode* build_ascii_tree_recursive(BSTNode* root) {
    asciinode* node;

    if (root == NULL) return NULL;

    node = malloc(sizeof(asciinode));
    node->left = build_ascii_tree_recursive(root->left_child);
    node->right = build_ascii_tree_recursive(root->right_child);

    if (node->left != NULL) {
        node->left->parent_dir = -1;
    }

    if (node->right != NULL) {
        node->right->parent_dir = 1;
    }

    sprintf(node->label, "%d", root->key);
    node->lablen = strlen(node->label);

    return node;
}

//Copy the tree into the ascii node structre
asciinode* build_ascii_tree(BSTNode* root) {
    asciinode* node;
    if (root == NULL) return NULL;
    node = build_ascii_tree_recursive(root);
    node->parent_dir = 0;
    return node;
}

//Free all the nodes of the given tree
void free_ascii_tree(asciinode* node) {
    if (node == NULL) return;
    free_ascii_tree(node->left);
    free_ascii_tree(node->right);
    free(node);
}

//The following function fills in the lprofile array for the given tree.
//It assumes that the center of the label of the root of this tree
//is located at a position (x,y).  It assumes that the edge_length
//fields have been computed for this tree.
void compute_lprofile(asciinode* node, int x, int y) {
    int i, isleft;
    if (node == NULL) return;
    isleft = (node->parent_dir == -1);
    lprofile[y] = MIN(lprofile[y], x - ((node->lablen - isleft) / 2));
    if (node->left != NULL) {
        for (i = 1; i <= node->edge_length && y + i < MAX_HEIGHT; i++) {
            lprofile[y + i] = MIN(lprofile[y + i], x - i);
        }
    }
    compute_lprofile(node->left, x - node->edge_length - 1, y + node->edge_length + 1);
    compute_lprofile(node->right, x + node->edge_length + 1, y + node->edge_length + 1);
}

void compute_rprofile(asciinode* node, int x, int y) {
    int i, notleft;
    if (node == NULL) return;
    notleft = (node->parent_dir != -1);
    rprofile[y] = MAX(rprofile[y], x + ((node->lablen - notleft) / 2));
    if (node->right != NULL) {
        for (i = 1; i <= node->edge_length && y + i < MAX_HEIGHT; i++) {
            rprofile[y + i] = MAX(rprofile[y + i], x + i);
        }
    }
    compute_rprofile(node->left, x - node->edge_length - 1, y + node->edge_length + 1);
    compute_rprofile(node->right, x + node->edge_length + 1, y + node->edge_length + 1);
}

//This function fills in the edge_length and
//height fields of the specified tree
void compute_edge_lengths(asciinode* node) {
    int h, hmin, i, delta;
    if (node == NULL) return;
    compute_edge_lengths(node->left);
    compute_edge_lengths(node->right);

    /* first fill in the edge_length of node */
    if (node->right == NULL && node->left == NULL) {
        node->edge_length = 0;
    } else {
        if (node->left != NULL) {
            for (i = 0; i < node->left->height && i < MAX_HEIGHT; i++) {
                rprofile[i] = -INFINITY;
            }
            compute_rprofile(node->left, 0, 0);
            hmin = node->left->height;
        } else {
            hmin = 0;
        }
        if (node->right != NULL) {
            for (i = 0; i < node->right->height && i < MAX_HEIGHT; i++) {
                lprofile[i] = INFINITY;
            }
            compute_lprofile(node->right, 0, 0);
            hmin = MIN(node->right->height, hmin);
        } else {
            hmin = 0;
        }
        delta = 4;
        for (i = 0; i < hmin; i++) {
            delta = MAX(delta, gap + 1 + rprofile[i] - lprofile[i]);
        }

        //If the node has two children of height 1, then we allow the
        //two leaves to be within 1, instead of 2
        if (((node->left != NULL && node->left->height == 1) ||
             (node->right != NULL && node->right->height == 1)) &&
            delta > 4) {
            delta--;
        }

        node->edge_length = ((delta + 1) / 2) - 1;
    }

    //now fill in the height of node
    h = 1;
    if (node->left != NULL) {
        h = MAX(node->left->height + node->edge_length + 1, h);
    }
    if (node->right != NULL) {
        h = MAX(node->right->height + node->edge_length + 1, h);
    }
    node->height = h;
}

//This function prints the given level of the given tree, assuming
//that the node has the given x cordinate.
void print_level(asciinode* node, int x, int level) {
    int i, isleft;
    if (node == NULL) return;
    isleft = (node->parent_dir == -1);
    if (level == 0) {
        for (i = 0; i < (x - print_next - ((node->lablen - isleft) / 2)); i++) {
            printf(" ");
        }
        print_next += i;
        printf("%s", node->label);
        print_next += node->lablen;
    } else if (node->edge_length >= level) {
        if (node->left != NULL) {
            for (i = 0; i < (x - print_next - (level)); i++) {
                printf(" ");
            }
            print_next += i;
            printf("/");
            print_next++;
        }
        if (node->right != NULL) {
            for (i = 0; i < (x - print_next + (level)); i++) {
                printf(" ");
            }
            print_next += i;
            printf("\\");
            print_next++;
        }
    } else {
        print_level(node->left,
                    x - node->edge_length - 1,
                    level - node->edge_length - 1);
        print_level(node->right,
                    x + node->edge_length + 1,
                    level - node->edge_length - 1);
    }
}

//prints ascii tree for given Tree structure
void print_ascii_tree(BSTNode* root) {
    asciinode* proot;
    int xmin, i;
    if (root == NULL) return;
    proot = build_ascii_tree(root);
    compute_edge_lengths(proot);
    for (i = 0; i < proot->height && i < MAX_HEIGHT; i++) {
        lprofile[i] = INFINITY;
    }
    compute_lprofile(proot, 0, 0);
    xmin = 0;
    for (i = 0; i < proot->height && i < MAX_HEIGHT; i++) {
        xmin = MIN(xmin, lprofile[i]);
    }
    for (i = 0; i < proot->height; i++) {
        print_next = 0;
        print_level(proot, -xmin, i);
        printf("\n");
    }
    if (proot->height >= MAX_HEIGHT) {
        printf("(This tree is taller than %d, and may be drawn incorrectly.)\n", MAX_HEIGHT);
    }
    free_ascii_tree(proot);
}

int main(){

    int i;

    generate();
    BSTNode *T = CreateNode(A[0]);
    // for(i=0;i<NUM;i++){
    //     printf("%d ",A[i]);
    // }
    for(i=1;i<NUM;i++){
        TREE_INSERT(T,A[i]);
    }
    print_ascii_tree(T);
}