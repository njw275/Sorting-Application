#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include "myqsort.h"


int main(int argc, char* argv[]){
	printf("IM IN ALPHA MERGE\n");
	FILE* file;
	int numWorkers = atoi(argv[2]);
	char* line = NULL;
	int len = 0;
	FILE* finalOutput;
	finalOutput = fopen(argv[4],"w");
	char read;
	int currChild = 0;
	int* fpArray = (int*)calloc(numWorkers,sizeof(int));
	int j;
	char* lines[numWorkers];
	for(j=0;j<numWorkers;j++){
		char name[] = "outputFromSort";
        	char currChildString[1];
	        sprintf(currChildString,"%d",currChild);
	        strcat(name,currChildString);
	        strcat(name,".txt");
		printf("fpArray[%d] is %s\n",j,name);
        	fpArray[j] = fopen(name,"r");
		currChild++;
	}
	int fps;
	for(fps=0;fps<numWorkers;fps++){
		read = getline(&line,&len, fpArray[fps]);
		if (read == -1){
			lines[fps] = "--";
		}
		else{
			char* a = strdup(line);
			lines[fps] = a;
		}
	}
	while(1){
		int file;
		int lowestFile = 1000000000;
		char* lowest = "zzzzzzzzzzzzz";
		for(file=0;file<numWorkers;file++){
			printf("looking into file %d\n",file);
			printf("see what lines[%d] is : %s\n",file,lines[file]);
			printf("Comparing %s with %s\n",lines[file],lowest);
			if(strcmp(lines[file],lowest) < 0){
				if(strcmp(lines[file],"--") != 0){
					printf("I chose %s\n",lines[file]);
					char* dest;
					dest =strdup(lines[file]);
					lowest = dest;
					lowestFile = file;
				}
			}
		}
		printf("in order: %s\n",lowest);
		fprintf(finalOutput,"%s\n",lowest);
		printf("Moving in file: %d\n",lowestFile);
		read = getline(&line,&len, fpArray[lowestFile]);
		if (read == -1){
			lines[lowestFile] = "--";
		}
		else{
			lines[lowestFile] = line;
		}
		int p;
		int stop = 0;
		for(p=0;p<numWorkers;p++){
			if (strcmp(lines[p],"--") == 0){
				
				stop++;
			}
		}
		printf("Stop: %d\n",stop);
		if(stop == numWorkers){
			break;
		}
	}
}

