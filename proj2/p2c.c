# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h> 
# include <unistd.h>

int main (int argc, char*argv[]){

	int long a, b, sleepTime, s, k, sum, sub, product, div, rem; 
	
	sleepTime = atoi(argv[1]); 
	a = atoi(argv[2]);
	b = atoi(argv[3]);
	k = atoi(argv[4]);
	
	//Child program goes to sleep for random number modulo sleeptime
	srand(getpid());
	s = rand() % sleepTime;
	sleep(s);

	if(k == 0){
		sum = a + b;
		printf("I am child number %d with PID %d, the sum is %ld.\n",k,getpid(),sum); 
		exit(0);
	}
	else if(k == 1){
		sub = a - b;
		printf("I am child number %d with PID %d, the difference is %ld.\n",k,getpid(),sub); 
		exit(0);
	}
	else if(k == 2){
		product = a * b;
		printf("I am child number %d with PID %d, the product is %ld.\n",k,getpid(),product); 
		exit(0);
	}
	else if(k == 3){
		if(b == 0){
			printf("I am child number %d with PID %d, you can not divide by zero.\n",k,getpid());
		exit(0);
		}
		else{
			div = a / b;
			rem = a % b;
			printf("I am child number %d with PID %d, the quotient is %ld with remainder %ld.\n",k,getpid(),div,rem);
			exit(0);
		}
	}
	else{
		exit(0);
	}
}
