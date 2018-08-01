#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

// Quick Sort Algorithm for sorters to use 

int orderSort;

void reverse(int* array, int length){
	int i;
	int j;
	int temp;
	for(i=0;i<length/2;i++){
		for(j=length;j>length/2;j--){
			temp = array[i];
			array[i] = array[j];
			array[j] = temp;
		}
	}

}


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
	int i;
	if(orderSort==1){
		i = l - 1;
	}else{
		i = l +1;
	}
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

int main(int argc, char* argv[]){
	printf("Sorter here\n");
	char buff[100];	
	FILE *fp = fopen(argv[1],"r");
	int myMinRange = atoi(argv[2]);
	int myMaxRange = atoi(argv[3]);
//	char name[] = "outputFromSort";
//	char myOffsetString[1];
//	sprintf(myOffsetString,"%d", myOffset);
//	strcat(name,myOffsetString);
//	strcat(name,".txt");
//	printf("name is: %s\n",name);
	int u = 0;
	int myArrayLength;
        while(fgets(buff,100,(FILE*)fp)){
		if(u>=myMinRange && u<myMaxRange){
			myArrayLength++;
        	}
		u++;
	}
	int range = u / atoi(argv[4]);
//	int myMaxRange = atoi(argv[3]);
	orderSort = atoi(argv[6]);
        int myOffset = myMinRange / range;
	 char name[] = "outputFromSort";
        char myOffsetString[1];
        sprintf(myOffsetString,"%d", myOffset);
        strcat(name,myOffsetString);
//      strcat(name,".txt");
        printf("name is: %s\n",name); 
        printf("my off %d my min range %d range %d\n",myOffset, myMinRange, range);
	int n = 10;
	int* myA = (int*)calloc(myArrayLength,sizeof(int));
	int c = 0;
	int place = 0;
	rewind(fp);
	while(fgets(buff,100,(FILE*)fp)){
		if(c>=myMinRange && c<myMaxRange){
			strtok(buff, " \n");
			int buffNum = atoi(buff); 
			myA[place] = buffNum;
			place++;
		}
		c++;
	}
	quickSort(myA,0,myArrayLength-1);
	if(orderSort == 1){reverse(myA,myArrayLength-1);}	
	printf("Finished Sorting\n");
	int r;
	FILE* fps;
	strcat(name,".txt");
	printf("name is %s\n",name);
	fps = fopen(name,"w+");
	if (fps ==NULL){
		printf("OPen error\n");
	}
	for(r=0;r<myArrayLength;r++){
		fprintf(fps,"%d",myA[r]);
		fprintf(fps,"\n");
		fflush(fps);
	}
	
	int ccpid = getppid();
        int merger_pid = atoi(argv[4]) + ccpid +1;
	printf("Killing %d\n",merger_pid);
	kill(merger_pid,SIGUSR1);
	return 0;
}
