#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]){
	int c;
	char* cval = NULL;
	char* type = NULL;
	char* finalOutput = NULL;
	char* col = NULL;
	char* fileToSort = NULL;
	char* orderSort = NULL;
	int pid;
	pid = fork();
	char buff[100];
	FILE* fp;
	FILE* fpw;

	if (pid==0){
		int cpid = getpid();
		printf("Coord pid is %d\n",getpid());
		while((c = getopt(argc,argv,"s:i:k:e:a:t:o:")) != -1){
			switch(c){
				case 'a':
					col = optarg;
					break;
				case 'o':
					orderSort = optarg;
					break;
				case 't':
					type = optarg; 
					break;
				case 's':
					finalOutput = optarg;
					break;
				case 'i':
					fileToSort = optarg;
					break;
				//Here the coord is making k workers 
				case 'k':
					cval = optarg;
//					execl("coordinator","coordinator",cval,fileToSort,finalOutput,NULL);
					break;
				default:
					printf("Also something else\n");	
			}
		}
		if(cval != NULL){
			printf("going to coord now\n");
			 execl("coordinator","coordinator",cval,fileToSort,finalOutput,type,orderSort,NULL);
		}
		//execv(argv[1],argv);
	}
	else{
		wait(NULL);
		printf("Parent %d exiting now\n", getpid());
	}
	return 0;
}


/*
Getopt help from:
gnu.org/software/libc/manual/html_node/Example-of_getopt.html
stackoverflow.com/questions/6450152/getopt-value-stays-null
*/
