#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include "myqsort.h"


int numWorkers;
int offset; 
FILE* fp;
int maxChild;
char buff[50];
int u = 0;
char buffer[100];

int compare(int* array, int* info,int numWorkers){
	//array of N pointers want to compare and return smallest
//	int* sortPointers = malloc(sizeof(array));
	int* sortPointers = (int*)calloc(sizeof(array),sizeof(int));
	memcpy(sortPointers, array, sizeof(array));
	quickSort(sortPointers,0,numWorkers-1);
	int t;
	int startPos = 0;
	for(t=0;t<numWorkers;t++){
		printf("sorted pointers[%d] : %d\n",t,sortPointers[t]);
		if(sortPointers[t] == -1){
			startPos++;
		}
	}
	int y;
	for(y=startPos;y<numWorkers;y++){
		if(info[y] == sortPointers[0]){
			return y;
		}
	}
}

int main(int argc, char* argv[]){
	printf("-MERGER MADE-\n");
	printf("Merger Pid: %d\n",getpid());
	numWorkers = atoi(argv[2]);
	offset = atoi(argv[1]);
	fp = fopen(argv[3],"r");
	maxChild = atoi(argv[2]);
	while(fgets(buffer,100,(FILE*)fp)){
                u++;    
        }      
	printf("u %d\n",u); 
//        int* info = (int*)calloc(u,sizeof(int));
	int info[6];
	FILE* f;
	int currChild = 0;
	int i = 0;
	while(currChild < maxChild){
		printf("currChild %d\n",currChild);
		char name[] = "outputFromSort";
		char currChildString[1];
		sprintf(currChildString,"%d",currChild);
		strcat(name,currChildString);
		strcat(name,".txt");
		f = fopen(name,"r");
		printf("opening %s max %d\n",name,maxChild);
		/*
		while( fgets(buff,sizeof(buff),f) ){
			//printf("Merger got: %s\n",buff);
			char dest[100];
			strcpy(dest,buff);
			info[i] = atoi(dest);
			printf("merger got: %d\n",info[i]);
			i++;
		}*/
		currChild++;
	}
	int m;
	for(m=0;m<(sizeof(info)/sizeof(info[0]));m++){
		printf("info[%d]: %d\n",m,info[m]);
	}
	printf("info 6: %d\n",info[6]);
	int n;
//	for(n=0;n<numWorkers;n++){
	int* mypointers = (int*)calloc(numWorkers,sizeof(int));
	for(n=0;n<numWorkers;n++){
		if(n==0){mypointers[n] = info[0];}
		else{
			mypointers[n] = info[n*offset];
		}
	}
	int h;
	for(h=0;h<numWorkers;h++){
		printf("pointer %d is %d\n",h,mypointers[h]);
	}
	int notDone = 0;
//	printf("PUT WHILE HERE\n");
	while(notDone<(sizeof(info)/sizeof(info[0]))){
		int position = compare(mypointers,info,numWorkers);
		if(position >numWorkers){position++;}	
		printf("pos is: %d\n",position);	
		printf("in order %d\n",info[position]);
		mypointers[position%numWorkers] = info[position + 1];
		if((position + 1) % offset == 0){
			mypointers[position-offset] = -1;
		}
		printf("pointer 0 is %d\n",mypointers[0]);
		printf("pointer 1 is %d\n",mypointers[1]);
		notDone = 1000000000;//notDone++; // = 0;
	}
	exit(0);
}



