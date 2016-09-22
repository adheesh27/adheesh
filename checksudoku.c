#include <stdio.h>
 
void sudoku_checker(int N ,int a[]){
    int i,j,k;
    int count=0;
     
    /* This for loop calculates the sum of each rows */
    /* and checks whether it's equal to (1+2+3+4) 10 or not */
    for (i = 0; i < N*N; i = i+4) {
        int sumRow = 0;
        for (j = i; j < i+4; j++) {
            sumRow = sumRow + a[j];
        }
        if (sumRow != 10) {
                count++;
        }
    }
     
    /* This for loop calculates the sum of each columns */
    /* and checks whether it's equal to (1+2+3+4) 10 or not */
    for (i = 0; i < N; i++) {
        int sumCol = 0;
        for (j = i; j < N*N; j = j+4) {
            sumCol = sumCol + a[j];
        }
        if (sumCol != 10) {
                count++;
        }
    }
     
    printf("Mistakes: %d\n", count);
    if(count==0)
        printf("correct\n");
    else
        printf("Incorrect\n");
}
 
int main(void){
    int a[]={2,1,3,4,4,3,2,1,1,3,4,2,2,4,3,1}; //to check what the output is when input is correct
    int N = 4;
 
    for (int i = 0; i < N*N; i = i+4) {
        for (int j = i; j < i+4; j++) {
            printf("  %d  ", a[j]);
        }
        printf("\n");
    }
 
    sudoku_checker(N,a);
 
    return 0;
}
