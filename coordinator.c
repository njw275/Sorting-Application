#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]){

//	printf("my argc is: %d\n",argc);
	int numWorkers = atoi(argv[1]);
	char* fileToSort = argv[2];
	char* finalOutput = argv[3];
	char* type = argv[4];
	int u = 0;
	char buff[100];
	FILE* fp;
	fp = fopen(argv[2],"r");
	printf("okay\n");
	while(fgets(buff,100,(FILE*)fp)){
                u++;
        }
	printf("u %d\n",u);
	char range[100];
	int inRange = u /numWorkers;
	printf("iR %d\n",inRange);
	sprintf(range,"%d", inRange);
	printf("dead\n");
	char* orderSort = argv[5];
	int mypid = getpid();
	int c = 0;
	int largestOffset = 0;
	int pid;
	while(c<numWorkers+1){
		if((pid = fork()) == 0){
			break;
		}
		c++;
	}
	if (pid == 0){
		int offset = getpid() - getppid();
		if(offset == numWorkers+1){
			printf("making pre-merger no w os %s\n",orderSort);
			execl("premerger","premerger",range,argv[1],fileToSort,finalOutput,type,orderSort,NULL); 
                        printf("error in merger for\n");

		}
		else{
			int noffmin;
			if(offset == 1){
				noffmin = 0;
			}
			else{
				noffmin = ( (offset-1) * atoi(range)); // + 1;
			}
			int noffmax = atoi(range)*offset;
			char minRange[10];
			sprintf(minRange,"%d",noffmin);
			char maxRange[10];
			sprintf(maxRange,"%d",noffmax);
			printf("type: %s\n", type);
			if(type == NULL){
				printf("No type of sort selected || Automatically sorting by Numeric\n");
				if(orderSort == NULL){orderSort = 0;}
				else if(strcmp(orderSort,"d") == 0){orderSort = "1";}
				else if(strcmp(orderSort,"a") == 0){orderSort = "0";}
                                execl("myqsort","myqsort",fileToSort,minRange,maxRange,argv[1],range,orderSort,NULL);

			}
			else if (strcmp(type,"a") == 0){
				if(orderSort == NULL){orderSort = 0;}
				else if(strcmp(orderSort,"d") == 0){orderSort = "1";}
                                else if(strcmp(orderSort,"a") == 0){orderSort = "0";}

				execl("myalphaqsort","myalphaqsort",fileToSort,minRange,maxRange,argv[1],range,orderSort,NULL);
	
			}
			else if(strcmp(type,"n") == 0){
				if(orderSort == NULL){orderSort = 0;}
				else if(strcmp(orderSort,"d") == 0){orderSort = "1";}
                                else if(strcmp(orderSort,"a") == 0){orderSort = "0";}

				execl("myqsort","myqsort",fileToSort,minRange,maxRange,argv[1],range,orderSort,NULL);

			}
			printf("execl error\n");
		}
	}
	else{
		int i;
		for(i=0;i<=numWorkers;i++){
			wait(NULL);
		}
		/*
		char buff[100];
		int prev = 0;
		int p;
		int f;
		int r;
		int z = 0;
		int stringSize;
		int infoStart;
		char* listOfInfo[6];
		for(p=0;p<100;p++){
			infoStart = 0;
			if(buff[p] == '\n'){
				f++;
				stringSize = 1;
				infoStart = 0;
				char info[stringSize];
				for(r=prev;r<p;r++){
					if(buff[r] != '\n'){
						info[infoStart] = buff[r];
						infoStart++;
					}
				}
				info[2] = '\n';
				infoStart = 0;
				prev = p;
			}
		}
		printf("There are %d nlc in buff\n",f);
		int mpid;
		if((mpid = fork()) == 0){
			char largOff[10];
			sprintf(largOff,"%d",largestOffset);
			execl("merger","merger",range,argv[1],fileToSort,NULL);
			printf("error in merger for\n");
		}
		else{
		wait(NULL);*/
		printf("Im coord %d and im done last\n",mypid);
		//}
	}
	return 0;


}
