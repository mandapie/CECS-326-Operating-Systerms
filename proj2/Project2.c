/*
*Description: Project2(parent program for creating child processes)
*Author: Jian Guo, Mark Mendoza, Alvin Chong
*Date: 3/1/2016
*/
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[]) {
	int T, a, b; //declare sleeping time, operand a, and operand b
	if (argc != 4) { //if arguments are inappropriate, print out the error message
		printf("The arguments are inappropriate!\nUsage: %s SleepTime OprandA OperandB\n", argv[0]);
		exit(1);
	}
	T = atoi(argv[1]);
	if (T <= 0 || T > 50) { //if sleeping time is inappropriate, print out the error message
		printf("The sleeping time must be positive or equal to or less than 50!\n");
		exit(1);
	}
	a = atoi(argv[2]); b = atoi(argv[3]); //store two integers
	
	pid_t child1, child2, child3, child4; //store the pid of children processes
	int parentSleep, child0Sleep, child1Sleep, child2Sleep, child3Sleep; //generate five random sleeping time for five processes
	srand((unsigned) time(NULL)); //the seed of the random number
	parentSleep = rand()%T;
	child0Sleep = rand()%T;
	child1Sleep = rand()%T;
	child2Sleep = rand()%T;
	child3Sleep = rand()%T;
	if (child1 = fork()) {
		if (child2 = fork()) {
			if (child3 = fork()) {
				if (child4 = fork()) { //create four child processes, and print out some messages about the parent process
					printf("I am parent process, the maximum sleep time is %d and the two numbers are %d and %d\n", T, a, b); 
					printf("Forked child %ld\nForked child %ld\nForked child %ld\nForked child %ld\n", (long)child1, (long)child2, (long)child3, (long)child4);
					sleep(parentSleep);
				}else { //create the first child process, and do division
					sleep(child3Sleep); //sleep a random time
					execlp("./Project2Calc", "Project2Calc", "3", argv[2], argv[3], (char *)NULL); //execute the child program
					perror("Exec failure!\n"); 
				} 
			}else { //create the third child process, and do multiplication
				sleep(child2Sleep); //sleep a random time
				execlp("./Project2Calc", "Project2Calc", "2", argv[2], argv[3], (char *)NULL); //execute the child program
				perror("Exec failure!\n"); 
			}
		}else { //create the second child process, and do substraction
			sleep(child1Sleep); //sleep a random time
			execlp("./Project2Calc", "Project2Calc", "1", argv[2], argv[3], (char *)NULL); //execute the child program
			perror("Exec failure!\n"); 
		}
	}else { //create the first child process, and do addition
		sleep(child0Sleep); //sleep a random time
		execlp("./Project2Calc", "Project2Calc", "0", argv[2], argv[3], (char *)NULL); //execute the child program
		perror("Exec failure!\n"); 
	}
	return 0;
}