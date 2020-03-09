#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define randomize() srand(time(NULL))
#define random(n) (rand()%(n))
#define SIZE 100
#define SAMPLE 10000
int count=0;

void InsertionSort(int* array, int n) {
    int i, j, key;
    for (i = 1; i < n; i++) {
        key = array[i];  // Choose the i-th element.
        for (j = i - 1; j >= 0; j--) {
            // If the j-th element is lower than key,
            // move to the next position.
            if (key > array[j]){
                array[j + 1] = array[j];
				count++;
			}
            else{
                break;
			}
        }
        // Otherwise, move the key to the (j+1)-th element.
        array[j + 1] = key;
    }
}

void sorted_fill(int* array){
	for(int i=0;i<SIZE;i++){
		array[i]=SIZE-1-i;		
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
	InsertionSort(A1,SIZE);
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
	InsertionSort(A2,SIZE);
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
	InsertionSort(A3, SIZE);
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

