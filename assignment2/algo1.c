#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define max(X, Y) ((X) > (Y) ? (X) : (Y))
#define randomize() srand(time(NULL))
#define random(n) (rand()%(n)+97)
#define SAMPLE 26
#define DM 37
#define SL 30

int hashtable_l[DM];
int hashtable_q[DM];
int hashtable_d[DM];
int keyarray[SL];


int hash(int key){
    return key % DM;
}

int hash2(int key){
    return (1+(key%(DM-1)));
}

int linear_probing(int key) {
    int i, bucket, count=0;
    for (i=0;i<DM;i++){

        bucket=hash(hash(key)+i);
        count++;
        if(hashtable_l[bucket]==0){
            hashtable_l[bucket]=key;
            break;
        }
    }
    return count;
}

int quadratic_probing(int key) {
    int i, bucket, count=0;
    for (i=0;i<DM;i++){

        bucket=hash(hash(key)+1*i+3*i*i);
        count++;
        if(hashtable_q[bucket]==0){
            hashtable_q[bucket]=key;
            break;
        }
    }
    return count;
}

int double_hashing(int key) {
    int i, bucket, count=0;
    for (i=0;i<DM;i++){

        bucket=hash(hash(key)+i*hash2(key));
        count++;
        if(hashtable_d[bucket]==0){
            hashtable_d[bucket]=key;
            break;
        }
    }
    return count;
}

void display(int A[DM]){
    
    int i;
    for(i=0;i<DM;i++){
        if(A[i]==0){
            printf("%d\t:%c\n",i,' ');
        }
        else{
            printf("%d\t:%d\n",i,A[i]);
        }
    }
}

int clustering(int A[DM]){
    
    int i,count=0,saved=0;
    for(i=0;i<DM;i++){
        if(A[i]!=0){
            count++;
            if (i==DM-1){
                saved=max(saved,count);
                count=0;
            }
        }
        else{
            saved=max(saved,count);
            count=0;
        }
    }
    return saved;
}

void generate(){
    int i,check,count=0;

    randomize();
    while(count<SL){

        int sum_key=0;
        int flag=0;

        for(i=0;i<3;i++){
            check = random(SAMPLE);
            sum_key +=check;
        }
        for(i=0;i<count+1;i++){
            if(sum_key==keyarray[i]){
                count--;
                flag=1;
                break;
            }
        }
        
        if (flag==0){
            keyarray[count]=sum_key;
        }
        count++;
    }
}

int main(){

    int i;

    memset(hashtable_l, 0, sizeof(hashtable_l));
    memset(hashtable_q, 0, sizeof(hashtable_q));
    memset(hashtable_d, 0, sizeof(hashtable_d));
    memset(keyarray, 0, sizeof(keyarray));

    generate();

    float probe_l=0, probe_q=0, probe_d=0;

    for(i=0;i<SL;i++){
        probe_l+=linear_probing(keyarray[i]);
        probe_q+=quadratic_probing(keyarray[i]);
        probe_d+=double_hashing(keyarray[i]);
    }

    printf("This is linear probing hash table\n\n");
    display(hashtable_l);
    printf("=================================\n\n");
    printf("This is quadratic probing hash table\n\n");
    display(hashtable_q);
    printf("=================================\n\n");
    printf("This is double_hashing hash table\n\n");
    display(hashtable_d);
    printf("=================================\n\n");

    printf("The average number of probes for linear probing = %0.3f\n",probe_l/SL);
    printf("The average number of probes for quadratic probing = %0.3f\n",probe_q/SL);
    printf("The average number of probes for double hashing = %0.3f\n",probe_d/SL);
    printf("\n");
    printf("The largest cluster of linear probing = %d\n",clustering(hashtable_l));
    printf("The largest cluster of quadratic probing = %d\n",clustering(hashtable_q));
    printf("The largest cluster of double hashing = %d\n",clustering(hashtable_d));
}
