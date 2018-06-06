#include <stdio.h> 
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/sem.h> 
#include <unistd.h> 
#include <stdlib.h>
#include <time.h> 

union semun 
{ 
        int val;
        struct semid_ds *buf; 
        ushort *array;
};

int main(int argc, char* argv[])
{
	int sem_id, sem_value, NS, k;
	key_t ipc_key;
	struct semid_ds sem_buf;
	union semun arg;

	ipc_key = ftok(".",'S');
	
	//input validation
	if(argc < 4)
	{
		printf("The number of arguements must be at least 4 or more.\n");
		exit(1);
	}

	NS = atoi(argv[2]);
	
	if(strcmp(argv[1],"n") != 0 && strcmp(argv[1],"r") != 0) 
	{
		printf("The first argument must be either 'n' or 'r'.\n");
		exit(1);
	}
	
	if(NS < 1)
  	{
  		printf("The second argument must be a positive integer.\n");
		exit(1);
	}

	if(argc - 3 != NS)
	{
  		printf("Arguments not matched. Number of semaphores is %d.\n", NS);
		exit(1);
	}
	
	for(int i = 3; i < argc; i++){
		sscanf(argv[i], "%i", &k);
		if(k < 0)
		{
			printf("Arguments need to be positive integers.\n");
			exit(1);
		}	
	}

	//create sem_array with the size of NS
	ushort sem_array[NS];

	//create the semaphores               
	if ((sem_id = semget(ipc_key, NS, IPC_CREAT | 0666| IPC_EXCL)) == -1) 
        { 
        	perror ("semget: IPC | 0666"); 
                exit(1); 
        }
	
	//convert argument to unsigned short and store it into the sem_array.
	for (int i = 0; i < NS; i++)
        {
                sem_array[i] = (unsigned short)strtoul(argv[i+3], NULL, 0);
	}

	//print out the semaphore identifier number.
	printf("Semaphore identifier %d\n", sem_id);

	//Set arg (the union) to the address of the storage location for
	//returned semid_ds value
	arg.buf = &sem_buf;
 
	//return the current values of the semid_ds for the indicated semaphore identifier.
        if (semctl(sem_id, 0, IPC_STAT, arg) == -1) 
        { 
        	perror ("semctl: IPC_STAT"); 
        	exit(2); 
        }
	
	//print out the time the semaphor set was created.
	printf ("Create %s", ctime(&sem_buf.sem_ctime));

	//set arg (the union) to the address of the initializing vector 
	arg.array = sem_array; 
	
	//set all the values for the individual semaphores.
	if (semctl(sem_id, 0, SETALL, arg) == -1) 
        { 
        	perror("semctl: SETALL"); 
        	exit(3); 
	}
	
	//print out the values of the individual semaphores.
	for (int i = 0; i < NS; ++i)
        { 
		if ((sem_value = semctl(sem_id, i, GETVAL, 0)) == -1)
		{ 
			perror("semctl : GETVAL"); 
			exit(4); 
                } 
                printf ("Semaphore %d has value of %d\n",i, sem_value); 
	}
	
	//remove the semaphores if 'r' was selected.
	if(strcmp(argv[1], "r") == 0) 
	{
		if (semctl(sem_id, 0, IPC_RMID, 0) == -1)
		{
			perror ("semctl: IPC_RMID");
			exit(5);
		}
	}    
}
