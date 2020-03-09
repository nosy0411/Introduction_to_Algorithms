#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define randomize() srand(time(NULL))
#define random(n) (rand()%(n))
#define t1 4
#define t2 8
#define SAMPLE 1000

int count_addition=0;
int count_multiply=0;
int count_subtraction=0;

void standard_algorithm(int** A,int** B, int** C, int dim){
	int i,j,k;	
	int n=dim;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			count_addition-=1;
			for(k=0;k<n;k++){
				C[i][j]+=A[i][k]*B[k][j];
				count_addition+=1;
				count_multiply+=1;
			}
		}
	}
}

void display(int** X,int dim){
	int i,j;
	int n=dim;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			printf("%d ",X[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void add(int **A, int **B, int **C, int dim){
	int i,j;
	int n=dim;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			C[i][j]=A[i][j]+B[i][j];
		}
	}
}
void sub(int **A, int **B, int **C, int dim){
	int i,j;
	int n=dim;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			C[i][j]=A[i][j]-B[i][j];
		}
	}
}


void recursion_algorithm(int** A,int** B, int** C, int haf,int dim){
	int n=dim;
	int k=haf;
	int i,j;

	int **p1=(int**)malloc(sizeof(int*)*k);
	int **p2=(int**)malloc(sizeof(int*)*k);
	int **p3=(int**)malloc(sizeof(int*)*k);
	int **p4=(int**)malloc(sizeof(int*)*k);
	int **p5=(int**)malloc(sizeof(int*)*k);
	int **p6=(int**)malloc(sizeof(int*)*k);
	int **p7=(int**)malloc(sizeof(int*)*k);
	int **p8=(int**)malloc(sizeof(int*)*k);
	

	int **A11=(int**)malloc(sizeof(int*)*k);
	int **A12=(int**)malloc(sizeof(int*)*k);
	int **A21=(int**)malloc(sizeof(int*)*k);
	int **A22=(int**)malloc(sizeof(int*)*k);
	int **B11=(int**)malloc(sizeof(int*)*k);
	int **B12=(int**)malloc(sizeof(int*)*k);
	int **B21=(int**)malloc(sizeof(int*)*k);
	int **B22=(int**)malloc(sizeof(int*)*k);
	int **C11=(int**)malloc(sizeof(int*)*k);
	int **C12=(int**)malloc(sizeof(int*)*k);
	int **C21=(int**)malloc(sizeof(int*)*k);
	int **C22=(int**)malloc(sizeof(int*)*k);

	for(i=0;i<k;i++){
		*(p1+i)=(int*)malloc(sizeof(int)*k);
		*(p2+i)=(int*)malloc(sizeof(int)*k);
		*(p3+i)=(int*)malloc(sizeof(int)*k);
		*(p4+i)=(int*)malloc(sizeof(int)*k);
		*(p5+i)=(int*)malloc(sizeof(int)*k);
		*(p6+i)=(int*)malloc(sizeof(int)*k);
		*(p7+i)=(int*)malloc(sizeof(int)*k);
		*(p8+i)=(int*)malloc(sizeof(int)*k);
		*(A11+i)=(int*)malloc(sizeof(int)*k);
		*(A12+i)=(int*)malloc(sizeof(int)*k);
		*(A21+i)=(int*)malloc(sizeof(int)*k);
		*(A22+i)=(int*)malloc(sizeof(int)*k);
		*(B11+i)=(int*)malloc(sizeof(int)*k);
		*(B12+i)=(int*)malloc(sizeof(int)*k);
		*(B21+i)=(int*)malloc(sizeof(int)*k);
		*(B22+i)=(int*)malloc(sizeof(int)*k);
		*(C11+i)=(int*)malloc(sizeof(int)*k);
		*(C12+i)=(int*)malloc(sizeof(int)*k);
		*(C21+i)=(int*)malloc(sizeof(int)*k);
		*(C22+i)=(int*)malloc(sizeof(int)*k);
	}
	if(k==1){
		C[0][0]=A[0][0]*B[0][0]+A[0][1]*B[1][0];
		C[0][1]=A[0][0]*B[0][1]+A[0][1]*B[1][1];
		C[1][0]=A[1][0]*B[0][0]+A[1][1]*B[1][0];
		C[1][1]=A[1][0]*B[0][1]+A[1][1]*B[1][1];
		count_addition+=4;
		count_multiply+=8;
		return;
	}

	for(i=0;i<k;i++){
		for(j=0;j<k;j++){
			A11[i][j]=A[i][j];
			A12[i][j]=A[i][j+k];
			A21[i][j]=A[i+k][j];
			A22[i][j]=A[i+k][j+k];
			B11[i][j]=B[i][j];
			B12[i][j]=B[i][j+k];
			B21[i][j]=B[i+k][j];
			B22[i][j]=B[i+k][j+k];
		}
	}
	recursion_algorithm(A11,B11,p1,k/2,n);
	recursion_algorithm(A12,B21,p2,k/2,n);
	recursion_algorithm(A11,B12,p3,k/2,n);
	recursion_algorithm(A12,B22,p4,k/2,n);
	recursion_algorithm(A21,B11,p5,k/2,n);
	recursion_algorithm(A22,B21,p6,k/2,n);
	recursion_algorithm(A21,B12,p7,k/2,n);
	recursion_algorithm(A22,B22,p8,k/2,n);
	
	add(p1,p2,C11,k);
	add(p3,p4,C12,k);
	add(p5,p6,C21,k);
	add(p7,p8,C22,k);
	count_addition+=4;

	display(A11,k);
	display(A12,k);
	display(A21,k);
	display(A22,k);

	display(B11,k);
	display(B12,k);
	display(B21,k);
	display(B22,k);
	
	display(C11,k);
	display(C12,k);
	display(C21,k);
	display(C22,k);

	for(i=0;i<k;i++){
		for(j=0;j<k;j++){
			C[i][j]=C11[i][j];
			C[i][j+k]=C12[i][j];
			C[i+k][j]=C21[i][j];
			C[i+k][j+k]=C22[i][j];
		}
	}

	for(i=0;i<k;i++){
		free(*(p1+i));
		free(*(p2+i));
		free(*(p3+i));
		free(*(p4+i));
		free(*(p5+i));
		free(*(p6+i));
		free(*(p7+i));
		free(*(p8+i));
		free(*(A11+i));
		free(*(A12+i));
		free(*(A21+i));
		free(*(A22+i));
		free(*(B11+i));
		free(*(B12+i));
		free(*(B21+i));
		free(*(B22+i));
		free(*(C11+i));
		free(*(C12+i));
		free(*(C21+i));
		free(*(C22+i));
	}
	free(p1);
	free(p2);
	free(p3);
	free(p4);
	free(p5);
	free(p6);
	free(p7);
	free(p8);
	free(A11);
	free(A12);
	free(A21);
	free(A22);
	free(B11);
	free(B12);
	free(B21);
	free(B22);
	free(C11);
	free(C12);
	free(C21);
	free(C22);
}

void strassen(int** A, int** B, int** C,int haf, int dim){
	int n=dim;
	int k=haf;
	int i,j;
	int P1,P2,P3,P4,P5,P6,P7;
	if(k==1){
		P1=A[0][0]*(B[0][1]-B[1][1]);
		P2=(A[0][0]+A[0][1])*B[1][1];
		P3=(A[1][0]+A[1][1])*B[0][0];
		P4=A[1][1]*(B[1][0]-B[0][0]);
		P5=(A[0][0]+A[1][1])*(B[0][0]+B[1][1]);
		P6=(A[0][1]-A[1][1])*(B[1][0]+B[1][1]);
		P7=(A[0][0]-A[1][0])*(B[0][0]+B[0][1]);
		C[0][0]=P5+P4-P2+P6;
		C[0][1]=P1+P2;
		C[1][0]=P3+P4;
		C[1][1]=P5+P1-P3-P7;
		count_multiply+=7;
		count_subtraction+=7;
		count_addition+=11;
		return;
	}
	int **p1=(int**)malloc(sizeof(int*)*k);
	int **p2=(int**)malloc(sizeof(int*)*k);
	int **p3=(int**)malloc(sizeof(int*)*k);
	int **p4=(int**)malloc(sizeof(int*)*k);
	int **p5=(int**)malloc(sizeof(int*)*k);
	int **p6=(int**)malloc(sizeof(int*)*k);
	int **p7=(int**)malloc(sizeof(int*)*k);
	

	int **A11=(int**)malloc(sizeof(int*)*k);
	int **A12=(int**)malloc(sizeof(int*)*k);
	int **A21=(int**)malloc(sizeof(int*)*k);
	int **A22=(int**)malloc(sizeof(int*)*k);
	int **B11=(int**)malloc(sizeof(int*)*k);
	int **B12=(int**)malloc(sizeof(int*)*k);
	int **B21=(int**)malloc(sizeof(int*)*k);
	int **B22=(int**)malloc(sizeof(int*)*k);
	int **C11=(int**)malloc(sizeof(int*)*k);
	int **C12=(int**)malloc(sizeof(int*)*k);
	int **C21=(int**)malloc(sizeof(int*)*k);
	int **C22=(int**)malloc(sizeof(int*)*k);

	
	int **tmp1=(int**)malloc(sizeof(int*)*k);
	int **tmp2=(int**)malloc(sizeof(int*)*k);
	
	
	for(i=0;i<k;i++){
		*(p1+i)=(int*)malloc(sizeof(int)*k);
		*(p2+i)=(int*)malloc(sizeof(int)*k);
		*(p3+i)=(int*)malloc(sizeof(int)*k);
		*(p4+i)=(int*)malloc(sizeof(int)*k);
		*(p5+i)=(int*)malloc(sizeof(int)*k);
		*(p6+i)=(int*)malloc(sizeof(int)*k);
		*(p7+i)=(int*)malloc(sizeof(int)*k);
		*(A11+i)=(int*)malloc(sizeof(int)*k);
		*(A12+i)=(int*)malloc(sizeof(int)*k);
		*(A21+i)=(int*)malloc(sizeof(int)*k);
		*(A22+i)=(int*)malloc(sizeof(int)*k);
		*(B11+i)=(int*)malloc(sizeof(int)*k);
		*(B12+i)=(int*)malloc(sizeof(int)*k);
		*(B21+i)=(int*)malloc(sizeof(int)*k);
		*(B22+i)=(int*)malloc(sizeof(int)*k);
		*(C11+i)=(int*)malloc(sizeof(int)*k);
		*(C12+i)=(int*)malloc(sizeof(int)*k);
		*(C21+i)=(int*)malloc(sizeof(int)*k);
		*(C22+i)=(int*)malloc(sizeof(int)*k);
		*(tmp1+i)=(int*)malloc(sizeof(int)*k);
		*(tmp2+i)=(int*)malloc(sizeof(int)*k);
	}
	
	for(i=0;i<k;i++){
		for(j=0;j<k;j++){
			A11[i][j]=A[i][j];
			A12[i][j]=A[i][j+k];
			A21[i][j]=A[i+k][j];
			A22[i][j]=A[i+k][j+k];
			B11[i][j]=B[i][j];
			B12[i][j]=B[i][j+k];
			B21[i][j]=B[i+k][j];
			B22[i][j]=B[i+k][j+k];
		}
	}
	
	sub(B12,B22,tmp1,k);
	strassen(A11,tmp1,p1,k/2,n);	//p1
	add(A11,A12,tmp1,k);
	strassen(tmp1,B22,p2,k/2,n);	//p2
	add(A21,A22,tmp1,k);
	strassen(tmp1,B11,p3,k/2,n);	//p3
	sub(B21,B11,tmp1,k);
	strassen(A22,tmp1,p4,k/2,n);	//p4
	add(A11,A22,tmp1,k);
	add(B11,B22,tmp2,k);
	strassen(tmp1,tmp2,p5,k/2,n);	//p5
	sub(A12,A22,tmp1,k);
	add(B21,B22,tmp2,k);
	strassen(tmp1,tmp2,p6,k/2,n);	//p6
	sub(A11,A21,tmp1,k);
	add(B11,B12,tmp2,k);
	strassen(tmp1,tmp2,p7,k/2,n);	//p7

	add(p5,p4,tmp1,k);
	sub(tmp1,p2,tmp2,k);
	add(tmp2,p6,C11,k);	//C11
	add(p1,p2,C12,k);	//C12
	add(p3,p4,C21,k);	//C21
	add(p5,p1,tmp1,k);
	sub(tmp1,p3,tmp2,k);
	sub(tmp2,p7,C22,k);	//C22
	
	display(A11,k);
	display(A12,k);
	display(A21,k);
	display(A22,k);

	display(B11,k);
	display(B12,k);
	display(B21,k);
	display(B22,k);
	
	display(C11,k);
	display(C12,k);
	display(C21,k);
	display(C22,k);
	
	count_addition+=11;
	count_subtraction+=7;
	for(i=0;i<k;i++){
		for(j=0;j<k;j++){
			C[i][j]=C11[i][j];
			C[i][j+k]=C12[i][j];
			C[i+k][j]=C21[i][j];
			C[i+k][j+k]=C22[i][j];
		}
	}

	for(i=0;i<k;i++){
		free(*(p1+i));
		free(*(p2+i));
		free(*(p3+i));
		free(*(p4+i));
		free(*(p5+i));
		free(*(p6+i));
		free(*(p7+i));
		free(*(A11+i));
		free(*(A12+i));
		free(*(A21+i));
		free(*(A22+i));
		free(*(B11+i));
		free(*(B12+i));
		free(*(B21+i));
		free(*(B22+i));
		free(*(C11+i));
		free(*(C12+i));
		free(*(C21+i));
		free(*(C22+i));
		free(*(tmp1+i));
		free(*(tmp2+i));
	}
	
	free(p1);
	free(p2);
	free(p3);
	free(p4);
	free(p5);
	free(p6);
	free(p7);
	free(A11);
	free(A12);
	free(A21);
	free(A22);
	free(B11);
	free(B12);
	free(B21);
	free(B22);
	free(C11);
	free(C12);
	free(C21);
	free(C22);
	free(tmp1);
	free(tmp2);
}

void init(int** X,int dim){
	int i,j;
	int n=dim;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			X[i][j]=0;
		}
	}
}

int main(){
	
	int **A1 = (int**)malloc(sizeof(int *)*t1);
	int **B1 = (int**)malloc(sizeof(int *)*t1);
	int **C1 = (int**)malloc(sizeof(int *)*t1);
	int **A2 = (int**)malloc(sizeof(int *)*t2);
	int **B2 = (int**)malloc(sizeof(int *)*t2);
	int **C2 = (int**)malloc(sizeof(int *)*t2);
	int i,j;

	randomize();
	for(i=0;i<t1;i++){
		*(A1+i)=(int*)malloc(sizeof(int)*t1);
		*(B1+i)=(int*)malloc(sizeof(int)*t1);
		*(C1+i)=(int*)malloc(sizeof(int)*t1);
		for(j=0;j<t1;j++){
			A1[i][j]=random(SAMPLE);
			B1[i][j]=random(SAMPLE);
			C1[i][j]=0;
		}
	}

	for(i=0;i<t2;i++){
		*(A2+i)=(int*)malloc(sizeof(int)*t2);
		*(B2+i)=(int*)malloc(sizeof(int)*t2);
		*(C2+i)=(int*)malloc(sizeof(int)*t2);
		for(j=0;j<t2;j++){
			A2[i][j]=random(SAMPLE);
			B2[i][j]=random(SAMPLE);
			C2[i][j]=0;
		}
	}

	printf("Matrix A1 is :\n");
	display(A1,t1);
	printf("\n");

	printf("Matrix B1 is :\n");
	display(B1,t1);
	printf("\n");
	printf("\nBy using standard algorithm Matrix C1 is :\n");
	standard_algorithm(A1,B1,C1,t1);
	int count_standard_addition_C1=count_addition;
	int count_standard_multiply_C1=count_multiply;
	count_addition=0;
	count_multiply=0;
	display(C1,t1);
	printf("\n");

	printf("addition : %d, multiplication : %d\n",count_standard_addition_C1, count_standard_multiply_C1);

	printf("\nBy using recursion Matrix C1 is :\n");
	init(C1,t1);
	recursion_algorithm(A1,B1,C1,t1/2,t1);
	display(C1,t1);
	printf("\nPartial matrix completion\n");
	printf("\nRecursion Matrix C1 :\n");
	int count_recursion_addition_C1=count_addition;
	int count_recursion_multiply_C1=count_multiply;
	count_addition=0;
	count_multiply=0;
	display(C1,t1);
	printf("\n");

	printf("addition : %d, multiplication : %d\n",count_recursion_addition_C1, count_recursion_multiply_C1);
	printf("\n");
	printf("\nBy using strassen algorithm Matrix C1 is :\n");
	init(C1,t1);
	strassen(A1,B1,C1,t1/2,t1);
	display(C1,t1);
	printf("\nPartial matrix completion\n");
	printf("\nStrassen Matrix C1 :\n");

	int count_strassen_addition_C1=count_addition;
	int count_strassen_multiply_C1=count_multiply;
	int count_strassen_subtraction_C1=count_subtraction;
	count_addition=0;
	count_multiply=0;
	count_subtraction=0;
	display(C1,t1);
	printf("\n");

	printf("addition : %d, multiplication : %d, subtraction : %d\n",count_strassen_addition_C1, count_strassen_multiply_C1,count_strassen_subtraction_C1);

	printf("\n");
	printf("Matrix A2 is :\n");
	display(A2,t2);	
	printf("\n");

	printf("Matrix B2 is :\n");
	display(B2,t2);
	printf("\n");
	printf("\nBy using standard algorithm Matrix C2 is :\n");
	standard_algorithm(A2,B2,C2,t2);
	int count_standard_addition_C2=count_addition;
	int count_standard_multiply_C2=count_multiply;
	count_addition=0;
	count_multiply=0;
	display(C2,t2);
	printf("\n");

	printf("addition : %d, multiplication : %d\n",count_standard_addition_C2, count_standard_multiply_C2);

	printf("\nBy using recursion Matrix C2 is :\n");
	init(C2,t2);
	recursion_algorithm(A2,B2,C2,t2/2,t2);
	display(C2,t2);
	printf("\nPartial matrix completion\n");
	printf("\nRecursion Matrix C2 :\n");
	int count_recursion_addition_C2=count_addition;
	int count_recursion_multiply_C2=count_multiply;
	count_addition=0;
	count_multiply=0;
	display(C2,t2);
	printf("\n");

	printf("addition : %d, multiplication : %d\n",count_recursion_addition_C2, count_recursion_multiply_C2);
	
	printf("\nBy using strassen algorithm Matrix C2 is :\n");
	init(C2,t2);
	strassen(A2,B2,C2,t2/2,t2);
	display(C2,t2);
	printf("\nPartial matrix completion\n");
	printf("\nStrassen Matrix C2 :\n");

	int count_strassen_addition_C2=count_addition;
	int count_strassen_multiply_C2=count_multiply;
	int count_strassen_subtraction_C2=count_subtraction;
	count_addition=0;
	count_multiply=0;
	count_subtraction=0;
	display(C2,t2);
	printf("\n");

	printf("addition : %d, multiplication : %d, subtraction : %d\n",count_strassen_addition_C2, count_strassen_multiply_C2, count_strassen_subtraction_C2);
	for(i=0;i<t1;i++){
		free(*(A1+i));
		free(*(B1+i));
		free(*(C1+i));
	}
	for(i=0;i<t2;i++){
		free(*(A2+i));
		free(*(B2+i));
		free(*(C2+i));
	}

	free(A1);
	free(B1);
	free(C1);
	free(A2);
	free(B2);
	free(C2);
}
