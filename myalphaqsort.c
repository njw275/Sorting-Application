#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

// Quick Sort Algorithm for sorters to use 

void quickSort(char** array, int l, int h){
	int split;
	if (l<h){
		split = middle(array,l,h);

		quickSort(array,l,split-1);
		quickSort(array,split+1,h);
	}
}

int middle(char** array, int l, int h){

	char* piv = array[h];

	int i = l - 1;
	int j;
	printf("strcmp pre\n");
	for(j=l;j<=h-1;j++){
		char* toComp = array[j];
		if(strcmp(array[j],piv) < 0){
			i++;
			char* s = array[i];
			array[i] = array[j];
			array[j] = s;
		}
	}
	char* swap = array[i+1];
	array[i+1] = array[h];
	array[h] = swap;
	return i+1;
}


int main(int argc, char* argv[]){
	printf("Sorter here\n");
	char buff[100];	
        int range = atoi(argv[5]);
	FILE *fp = fopen(argv[1],"r");
	int myMinRange = atoi(argv[2]);
	int myMaxRange = atoi(argv[3]);
	int myOffset = myMinRange / range;
	printf("my off %d my min range %d range %d\n",myOffset, myMinRange, range);
	char name[] = "outputFromSort";
	char myOffsetString[1];
	sprintf(myOffsetString,"%d", myOffset);
	strcat(name,myOffsetString);
//	strcat(name,".txt");
	printf("name is: %s\n",name);
	int u = 0;
	int myArrayLength;
	printf("Alpha here\n");
        while(fgets(buff,100,(FILE*)fp)){
		if(u>=myMinRange && u<myMaxRange){
			myArrayLength++;
        	}
		u++;
	}
	int n = 10;
	char** myA = (char**)calloc(myArrayLength,sizeof(char*));
	int c = 0;
	int place = 0;
	int y;  
	rewind(fp);
	while(fgets(buff,100,(FILE*)fp)){
		printf("PLACE: %d\n",place);
		if(c>=myMinRange && c<myMaxRange){
			strtok(buff, " \n");
			char* a = strdup(buff);
			myA[place] = a;
			place++;
		}
		else{
			strtok(buff," \n");
		}
		c++;
	}
	//int y;
	for(y=0;y<myArrayLength;y++){
		printf("mya[%d]: %s\n",y,myA[y]);
	}
	quickSort(myA,0,myArrayLength-1);
	
	printf("Finished Sorting\n");
	int r;
	FILE* fps;
	strcat(name,".txt");
	printf("name is %s\n",name);
	fps = fopen(name,"w+");
	if (fps ==NULL){
		printf("Open error\n");
	}
	for(r=0;r<myArrayLength;r++){
		fprintf(fps,"%s",myA[r]);
		fprintf(fps,"\n");
		fflush(fps);
	}
	
	int ccpid = getppid();
        int merger_pid = atoi(argv[4]) + ccpid +1;
	printf("Killing %d\n",merger_pid);
	kill(merger_pid,SIGUSR1);
	return 0;
}
