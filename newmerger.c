#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include "myqsort.h"


int main(int argc, char* argv[]){

	FILE* file;
	int numWorkers = atoi(argv[2]);
	char* line = NULL;
	int len = 0;
	FILE* finalOutput;
	finalOutput = fopen(argv[4],"w");
	char read;
	int currChild = 0;
	int orderSort;
	if(strcmp(argv[5],"d") == 0){
		orderSort = 1;
	}
	else{
		orderSort = 0;
	}
	printf("orderSort %d in newmerger\n",orderSort);
	int* fpArray = (int*)calloc(numWorkers,sizeof(int));
	int j;
	int lines[numWorkers];
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
			lines[fps] = -1;
		}
		else{
			lines[fps] = atoi(line);
		}
	}
	while(1){
		if(orderSort == 0){
			int file;
			int lowestFile = 1000000000;
			int lowest = 1000000000;
			for(file=0;file<numWorkers;file++){
				printf("%d and %d comp\n",lines[file],lowest);
				if(lines[file] < lowest){
					if(lines[file] != -1){
						lowest = lines[file];
						lowestFile = file;
					}
				}
			}
			fprintf(finalOutput,"%d\n",lowest);
			read = getline(&line,&len, fpArray[lowestFile]);
			if (read == -1){
				lines[lowestFile] = -1;
			}
			else{
				lines[lowestFile] = atoi(line);
			}
			int p;
			int stop = 0;
			for(p=0;p<numWorkers;p++){
				if (lines[p] == -1){
				
					stop++;
				}
			}
			printf("Stop: %d\n",stop);
			if(stop == numWorkers){
				break;
			}
		}
		else{
			int file;
                        int lowestFile = -10000;
                        int lowest = -10000;
                        for(file=0;file<numWorkers;file++){
				printf("comparing %d and %d\n",lines[file],lowest);
                                if(lines[file] > lowest){
                                        if(lines[file] != -1){
                                                lowest = lines[file];
                                                lowestFile = file;
                                        }
                                }
                        }
                        fprintf(finalOutput,"%d\n",lowest);
                        read = getline(&line,&len, fpArray[lowestFile]);

			if (read == -1){
                                lines[lowestFile] = -1;
                        }
                        else{
                                lines[lowestFile] = atoi(line);
                        }
                        int p;
                        int stop = 0;
                        for(p=0;p<numWorkers;p++){
                                if (lines[p] == -1){

                                        stop++;
                                }
                        }
                        printf("Stop: %d\n",stop);
                        if(stop == numWorkers){
                                break;
                        }

		}

	}
}

