#include <stdio.h>
#include <stdlib.h>

void printVec(int *vec, int n){
	int i;
	for(i = 0; i < n; i++)
		printf("%d ", vec[i]);
	printf("\n");
}
void removeIndex(int *index, int *n, int pos){
	int i;
	
	for(i = pos; i < (*n)-1; i++){
		index[i] = index[i+1];
	}
	(*n)--;
	index = (int*) realloc(index, sizeof(int) * (*n));

	printVec(index, *n);
}

int main(int argc, char *argv[]){
	int *vec, i,d;
	int n = 10;
	vec = (int *)malloc(sizeof(int)*n);

	while(n-- >0){
		scanf("%d",&vec[i]);
	}

	n = 10;
	printVec(vec, n);

	for(i = 0; i < 3; i++)
		removeIndex(vec, &n,i);

	return 0;

}