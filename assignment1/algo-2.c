#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define randomize() srand(time(NULL))
#define random(n) (rand()%(n))
#define SIZE 100
#define SAMPLE 1000

int count=0;

void Merge(int* list, int left, int mid, int right) {
    int sorted[SIZE];
    int first = left, second = mid + 1, i = left;

    // Merge two lists by comparing elements in sequence.
    while (first <= mid && second <= right) {
        if (list[first] >= list[second]){
            sorted[i++] = list[first++];
		}
        else{
            sorted[i++] = list[second++];
			count++;
		}
    }

    // For remaining items, add them in sequence.
    if (first > mid) {
        for (int j = second; j <= right; j++)
            sorted[i++] = list[j];
    } else {
        for (int j = first; j <= mid; j++)
            sorted[i++] = list[j];
    }

    // Copy the sorted list to the list.
    for (int j = left; j <= right; j++)
        list[j] = sorted[j];
}

void MergeSort(int* list, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;     // Equal partitioning
        MergeSort(list, left, mid);       // Sorting sublists
        MergeSort(list, mid + 1, right);  // Sorting sublists
        Merge(list, left, mid, right);    // Merging two sublists
		//for (int i = 0; i < SIZE; i++)
        //        printf("%d ", list[i]);
        //printf("\n");
    }
}

void sorted_fill(int* list){
	for(int i=0;i<SIZE;i++){
		list[i]=SIZE-i;		
	}
}

int main(){
	
	int A1[SIZE];
	int A2[SIZE];
	int A3[SIZE];

	randomize();
	for(int i=0;i<SIZE;i++){
		while(1){
			int check=0;
			A1[i]=random(SAMPLE);
			for(int j=0;j<i;j++){
				if(A1[j]==A1[i]){
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
	sorted_fill(A2);

	for(int i=0;i<SIZE;i++){
		A3[i]=A2[SIZE-1-i];
	}
	
	printf("Before sort A1: ");
	for(int i=0;i<SIZE;i++){
		printf("%d ",A1[i]);
	}
	printf("\n\n");	
	printf("After sort A1: ");
	MergeSort(A1,0,SIZE-1);
	int A1count=count;
	count=0;

	for(int i=0;i<SIZE;i++){
		printf("%d ",A1[i]);
	}
	printf("\n\n");
	printf("Before sort A2: ");
	for(int i=0;i<SIZE;i++){
		printf("%d ",A2[i]);
	}
	printf("\n\n");	
	printf("After sort A2: ");
	MergeSort(A2,0,SIZE-1);
	int A2count=count;
	count=0;

	for (int i=0;i<SIZE;i++){
		printf("%d ",A2[i]);
	}
	printf("\n\n");
	printf("Before sort A3: ");
	for(int i=0;i<SIZE;i++){
		printf("%d ",A3[i]);
	}
	printf("\n\n");
	printf("After sort A3: ");
	MergeSort(A3,0,SIZE-1);
	int A3count=count;
	count=0;

	for(int i=0;i<SIZE;i++){
		printf("%d ", A3[i]);
	}
	printf("\n\n\n");

	printf("A1 comparison count : %d\n",A1count);
	printf("A2 comparison count : %d\n",A2count);
	printf("A3 comparison count : %d\n",A3count);
}

