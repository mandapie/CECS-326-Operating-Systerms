/*Description: Write a program using C/C++ to generate a binary tree of processes. 
 *             The input to the program includes the number of levels in the tree. 
 *			   The maximum number of levels is 5, but the program should work for a
 *             general case of any number.  
 *Author: Jian Guo, Alvin Chong, Mark Mendoza
 *Date: 2/9/2016
 */
#include <stdlib.h>
#include <stdio.h>
# include <sys/types.h>
# include <unistd.h>

void createBinaryTree(int maxLevel) {
	printf("Level\tProcs\tParent\tChild 1\tChild 2\n");//print out the first two rows of result
	printf("No.\tID\tID\tID\tID\n");
	int currentLevel;//declare a variable currentLevel
	pid_t child1pid, child2pid;//declare two variables child1pid and child2pid for two children
	for (currentLevel = 0; currentLevel <= maxLevel; currentLevel++) {//for-loop to generate two children processes of one parent process
		child1pid = 0;//initialize pids of two children processes 
		child2pid = 0;
		if (currentLevel >= maxLevel) {//if this is the last level of binary tree, print out leaves infromation without children(these leaves are not parents)
			printf("%d\t%ld\t%ld\t%ld\t%ld\t\n", currentLevel, (long)getpid(), (long)getppid(), (long)child1pid, (long)child2pid);
			break;
		}
		if (child1pid = fork()) {//if this is a parent process, to generate the other child process once more, and then print out this process information
			if (child2pid = fork()) {
				printf("%d\t%ld\t%ld\t%ld\t%ld\t\n", currentLevel, (long)getpid(), (long)getppid(), (long)child1pid, (long)child2pid);
				sleep(maxLevel+1);//set sleep time so that this parent process would not end when displaying its children processes information
				break;
			}
		}
		sleep(1);//make the child process sleeps and then goes to for-loop one more time
	}
}

int main(int argc, char *argv[]) {
	if (argc != 2) {//print out a message if the arguments are inappropriate
        printf("Usage: %s maximum-level\n", argv[0]);
        exit(1);
    }
	int maxLevel = atoi(argv[1]);
	if (maxLevel < 0 || maxLevel > 10) {//print out a message if the maximum level of binary tree is inappropriate
		printf("The maximum level of binary tree must be nonnegative and be less than 10!!!\n");
		exit(0);
	}

	createBinaryTree(maxLevel);//invoke the function to create a binary tree
	return 0;
}
