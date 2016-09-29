#include <stdio.h>

void sudoku_checker(int N ,int a[]){
    int i,j,k;
    int count=0;
     
    /* This for loop calculates the sum of each rows */
    /* and checks whether it's equal to 45 or not */
    for (i = 0; i < N*N; i = i+9) {
        int sumRow = 0;
        for (j = i; j < i+9; j++) {
            sumRow = sumRow + a[j];
        }
        if (sumRow != 45) {
                count++;
        }
    }
     
    /* This for loop calculates the sum of each columns */
    /* and checks whether it's equal to 45 or not */
    for (i = 0; i < N; i++) {
        int sumCol = 0;
        for (j = i; j < N*N; j = j+9) {
            sumCol = sumCol + a[j];
        }
        if (sumCol != 45) {
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
  int a[81]={7,3,2,8,1,5,9,4,6,5,4,9,7,6,3,8,2,1,8,6,1,4,2,9,3,5,7,4,5,6,3,8,1,7,9,2,2,7,8,5,9,6,1,3,4,9,1,3,2,4,7,5,6,8,3,8,4,9,7,2,6,1,5,6,9,7,1,5,4,2,8,3,1,2,5,6,3,8,4,7,9};//to check the function
    int N = 9;
 int i,j;
/*for user input*/
 /*for (i = 0; i < N*N; i = i+9) {
       for (j = i; j < i+9; j++) {
           scanf(" %d ", &a[j]);
        }
    }
*/


    for (i = 0; i < N*N; i = i+9) {
        for (j = i; j < i+9; j++) {
            printf("  %d  ", a[j]);
        }
        printf("\n");
    }
 
    sudoku_checker(N,a);
 
    return 0;
}
