#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

char* range;
char* num;
char* file;
char* finalOutput;
char* type;
char* orderSort;

void handler();

int main(int argc, char* argv[]){
	printf("PreMerger pid %d\n",getpid());
	int c;
	int numWorkers = atoi(argv[2]);
	orderSort = argv[6];
	num = argv[2];
	range = argv[1]; 
	file = argv[3];
	finalOutput = argv[4];
	type = argv[5];
	for(c=0;c<numWorkers;c++){
		signal(SIGUSR1,handler);
	}
	for(;;);
}

void handler(){
 	signal(SIGUSR1,handler);
	printf("pre merger calling NEW merger now\n");
	printf("type is %s in pre merge\n",type);
	if (strcmp(type,"n") == 0){
		printf("Printf calling new merger digit\n");
	        execl("newmerger","newmerger",range,num,file,finalOutput,orderSort,NULL);
	}
	else{
		execl("newmergeralpha","newmergeralpha",range,num,file,finalOutput,orderSort,NULL);
	}
//	exit(0);
}

