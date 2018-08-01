#ifndef MYQSORT_H
#define MYQSORT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

// Quick Sort Algorithm for sorters to use 

void quickSort(int* array, int l, int h){
	int split;
	if (l<h){
		split = middle(array,l,h);

		quickSort(array,l,split-1);
		quickSort(array,split+1,h);
	}
}

int middle(int* array, int l, int h){

	int piv = array[h];

	int i = l - 1;
	int j;

	for(j=l;j<=h-1;j++){
		if(array[j] <= piv){
			i++;
			int s = array[i];
			array[i] = array[j];
			array[j] = s;
		}
	}
	int swap = array[i+1];
	array[i+1] = array[h];
	array[h] = swap;
	return i+1;
}


#endif 
