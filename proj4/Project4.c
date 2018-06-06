/**
*Description: Project4
*			  Create NS semaphores in a semaphore set. The values of the semaphores are provided via the command
*             line arguments. Provide error checking to make sure the number of semaphore values is matched to the
*             number of semaphores NS.
*Author: Jian Guo, Mark Mendoza, Alvin Chong
*Date: 4/18/2016
*/
#include <stdio.h>
#include <sys/types.h> 
#include <sys/ipc.h>
#include <sys/sem.h> 
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/*
*check the arguments are numbers or not
*/
int checkArgument(const char *str) {
	int i;
	for (i = 0; i < strlen(str); i++) {
		if (!isdigit(str[i])) {
			return 0;
		}
	}
	return 1;
}
/*
*create an union which contains a integer variable val, 
*a pointer to a struct semid_ds, and a pointer to an array
*/
union semun { 
	int val;
	struct semid_ds *buf;
	ushort *array;
};

int main(int argc, char *argv[]) {
	int NS; //declare an integer variable to save the size of the semaphore array
	if (argc < 4) { //insure the minimum length of arguments is 4
		printf("Usage: %s r|n size value1 value2 value3...\n", argv[0]);
		exit(1);
	}
	NS = atoi(argv[2]);
	if (strcmp(argv[1],"r") != 0 && strcmp(argv[1],"n") != 0) { //insure the first argument is r or n
		printf("First argument must be either 'r' or 'n'\n");
		exit(1);
	}
	if (!checkArgument(argv[2])) { //insure the second argument is a positive integer
		printf("Second argument must be an positive integer\n");
		exit(1);
  	}
	if ((argc - 3) != NS){ //insure the number of arguments(from third on to the last one) is matched the second argument 
  		printf("Arguments not matched, number of sempahores is %d\n", NS);
		exit(1);
  	}
	
	/*deckare variables sem_id and sem_value to save the id and the value of the semaphore;
	*variable i for a loopl;
	*/
	int sem_id, sem_value, i;
	key_t ipc_key; //declare a key_t variable ipc_key
	struct semid_ds sem_buf; //delcare the struct semid_ds variable sem_buf
	union semun arg; //declare a pointer to the union semun
	
	ipc_key = ftok(".",'S'); //generate an ipc_key which is about to be used as an argument to generate the semaphore
  	ushort sem_array[NS]; //declare a semaphore array

  	for (i = 3;i < argc; i++) { //loop to save values into the semaphore array and make sure the values are positive integers
	  	if (!checkArgument(argv[i])) {
			printf("The value in the semaphore array must be an positive integer\n");
			exit(1);
	  	}
	  	sem_array[i-3] = ((ushort)atoi(argv[i]));
  	}
  	
	if ((sem_id = semget(ipc_key, NS, IPC_CREAT | IPC_EXCL | 0666))== -1) { //create a semaphore array with size NS
		perror("semget");
		exit(1);
	}
	printf("Semaphore identifier %d\n", sem_id); //display the semaphore indendifier
	
	arg.buf = &sem_buf; //make the pointer in union semun point the sem_buf
	printf("Create %s", ctime(&sem_buf.sem_ctime)); //dispaly the current time of creating the semaphore
	
	if (semctl(sem_id, 0, IPC_STAT, arg) == -1) { //Set arg (the union) to the address of the storage location for returned semid_ds value 
		perror("semctl: IPC_STAT");
		exit(2);
	}
	arg.array = sem_array; //Set arg (the union) to the address of the initializing vector
	if (semctl(sem_id, 0, SETALL, arg) == -1) { //set the values of the individual semaphore  
		perror("semctl: SETALL\n");
		exit(3);
	} 
	
	for (i = 0; i < NS; ++i) { //print out the values of the individual semaphore
		if((sem_value = semctl(sem_id, i, GETVAL, 0)) == -1) { //if the returned value is -1, display an error message
			perror("semctl: GETVAL\n");
			exit(4);
		}
		printf("Semaphore %d has a value of %u\n", i, sem_value);
	}
	if (strcmp(argv[1], "r") == 0) { //if the first argument is r, then remove semaphores
		semctl(sem_id, 0, IPC_RMID, 0);
	}
}
