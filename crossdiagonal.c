#include <stdio.h>
#include <stdlib.h>
#define ROWS 3

int **diagonal(int A[ROWS][ROWS], int n11, int n12, int *len1)
{
	int **output;
	int i,j,k,l;
	int len;
	int len2 = 0;
	
	len = *len1 = 2*n11 - 1;
	
	output = (int**)malloc(sizeof(int*) * len);
	
	for (i = 0,j = 0; j < n12; j++) {
		l = 0;
		int row = 0;
		output[len2] = (int*)malloc(sizeof(int) * (j+2));
		output[len2][l++] = j+2;
		for (k = j; k >= 0; k--, row++) {
			output[len2][l++] = A[row][k];
		}
		len2++;
	}
	
	for (j = n12, i = 1; i < n11; i++) {
		int x = n12 - i;
		int col;
		int row;
		l = 0;
		output[len2] = (int*)malloc(sizeof(int) * (x+1));
		output[len2][l++] = x+1;
		col = n12 - 1;
		for (k = 0, row = i; k < x; k++, row++, col--) {
			output[len2][l++] = A[row][col];
		}
		len2++;
	}
	
	for (i = 0; i < len; i++) {
		for (j = 0; j < output[i][0]; j++) {
			printf("%d ", output[i][j]);
		}
		printf("\n");
	}
	
	return output;
}

int main() 
{
	int A[ROWS][ROWS] = {1,2,3,4,5,6,7,8,9};
	int len;
	
	diagonal(A, ROWS, ROWS, &len);
}
