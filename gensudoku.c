#include<stdio.h>


void genSudokuBoard(int grid[ ], int display[ ]){
int i,c, j, rowNum, colNum, blockNum;

for(c=0; c<N*N; c++) {
   blockNum = colNum = 1;
   //rowNum = c / N;
     //colNum = c % N;
     //blockNum = (rowNum / 3) * 3 + (colNum / 3);
     for (j=0; j<N; j++)
     printf("%d", grid[((blockNum/3)*N*3) + (colNum/3)*3 + (j/3)*N + j%3]);
   }


printf("\n");
for(i=0; i<N*N; i++) {  /* displaying all N*N numbers in the 'grid' array */

  if(i%N==0 && i!=0) { /* printing a newline for every multiple of N */
     printf("\n");
  }
  printf("%d ", grid[i]);
}
printf("\n");

return 0;
}


