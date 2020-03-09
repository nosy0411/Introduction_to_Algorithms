#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define randomize() srand(time(NULL))
#define random(n) (rand()%(n))
#define SIZE 100
#define SAMPLE 20

typedef enum { false, true } bool;
typedef int Data;

typedef struct _Node {
    Data item;
    struct _Node* next;
} Node;

typedef struct {
    Node* head;
    int len;
} LinkedList;

// Make a list empty.
void InitList(LinkedList* plist) {
    // Create a dummy node;
    plist->head = (Node*)malloc(sizeof(Node));
    plist->head->next = NULL;
    plist->len = 0;
}

// Check whether the list is empty.
bool IsEmpty(LinkedList* plist) {
    return plist->len == 0;
}

// Insert an item at the k-th position.
void InsertMiddle(LinkedList* plist, int pos, Data item) {
    Node *cur, *newNode;
    if (pos < 0 || pos > plist->len)
        exit(1);

    // Create a new node.
    newNode = (Node*)malloc(sizeof(Node));
    newNode->item = item;
    newNode->next = NULL;

    // Move the cur pointer to the (k-1)-th position.
    cur = plist->head;
    for (int i = 0; i < pos; i++)
        cur = cur->next;

    // Insert the new node to the k-th position.
    newNode->next = cur->next;
    cur->next = newNode;
    plist->len++;
}

// Insert an item at the last position.
void insert_last(LinkedList* plist, Data item) {
    InsertMiddle(plist, plist->len, item);
}


// Remove an item at the k-th position.
void delete_value(LinkedList* plist, int value) {
    Node *cur, *temp, *prev;

	if(IsEmpty(plist)) exit(1);
	
	cur = plist->head;
	prev = plist->head;
	cur = cur->next;
	prev->next=cur;

	while(cur!=NULL){
		int check=0;
		while(cur!=NULL){
			if (cur->item==value){
					check=1;
					break;
			}
			prev=cur;
			cur=cur->next;
			prev->next=cur;
		}
		if(check==1){
			temp = cur;
			cur=cur->next;
			prev->next=cur;
			plist->len--;
			free(temp);
		}
	}
}

// Print each item in a list in sequence.
void PrintList(LinkedList* plist) {
	int check=0;
	int count=0;
    for (Node* cur = plist->head->next; cur != NULL; cur = cur->next){
		
		if(count<(plist->len)/2.0){
			printf("%d ", cur->item);
			count++;
		}
		else{
			if(check==1){
				printf("%d ",cur->item);
			}
			else{
				printf("\n%d ",cur->item);
				check=1;
			}
		}
	}
}

int main(){
	LinkedList list;
	int A[SIZE];

	InitList(&list);
	randomize();
	for(int i=0;i<SIZE;i++){
		A[i]=random(SAMPLE);
		insert_last(&list, A[i]);
	}
	int flag;
	printf("Select delete(0) or Print(1) and if you want to stop, press -1\n");
	scanf("%d",&flag);
	
	while(flag!=-1){
		if(flag==0){
			int value=A[random(SIZE)];
			printf("Randomly selected value :%d\n",value);
			delete_value(&list,value);
			printf("value=%d is erased\n",value);
		}
		else if(flag==1){	
			printf("Print Linked List : ");
			PrintList(&list);
		}
		else{
			printf("please press correct number\n");
		}
		printf("\n\n");
		printf("Select delete(0) or Print(1) and if you want to stop, press -1\n");
		scanf("%d",&flag);
	}
}
