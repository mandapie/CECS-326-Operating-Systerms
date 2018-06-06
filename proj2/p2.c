# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h> 
# include <unistd.h>
#include <time.h>

int main (int argc, char*argv[]){
	
	int long a, b, s, sleepTime, status;
	pid_t pid;

	if(argc != 4){
		printf("Need the program name and 3 arguments.\n");
		exit(1);
	}

	sleepTime = atoi(argv[1]);
	a = atoi(argv[2]);
	b = atoi(argv[3]);

	if(sleepTime <= 0 || sleepTime > 50){
		printf("Enter a sleep time that is greater than 0 or 50 and less.\n");
		exit(1);
	}
	
	printf("I am parent process, the maximum sleep time is %ld and the two numbers are %ld and %ld.\n",sleepTime,a,b);
	//Fork 4 child processes
	for(int long i = 0; i < 4; i++){
		char k[1];//to take in the i as char type
		sprintf(k, "%ld", i);
		pid = fork();
		if(pid > 0){
			printf("Forked child %d.\n",(int)pid);
			// srand(time(NULL));
			// s = rand() % sleepTime;
			// sleep(s);
		}
		else if(pid == 0){
			char*args[6] = {0};
			args[0] = "./p2c";
			args[1] = argv[1];
			args[2] = argv[2];
			args[3] = argv[3];
			args[4] = k;
			args[5] = (char*)NULL;
			execvp(args[0],args);
			perror("Exec Failure");
			exit(1);
		}
		else{
			printf("Forked failed.\n");
		}
	}
	//Parent program goes to sleep and wait for child processess to terminate
	srand(time(NULL));
	s = rand() % sleepTime;
	sleep(s);
	waitpid(pid,&status,0);
	exit(0);
}
