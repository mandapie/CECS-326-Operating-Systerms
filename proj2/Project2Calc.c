/*
*Description: Project2(child program for calculation)
*Author: Jian Guo, Mark Mendoza, Alvin Chong
*Date: 3/1/2016
*/
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	int choice, a, b; //declare a variable choice
	choice = atoi(argv[1]);
	a = atoi(argv[2]); //save two operands to variables a and b
	b = atoi(argv[3]);
	switch (choice) { //do addition, substraction, multiplication, and division based on the choice
	case 0:
		printf("\nI am child number %d with PID %ld, the summation is %d\n", choice, (long)getpid(), a+b); //addition
		break;
	case 1:
		printf("\nI am child number %d with PID %ld, the difference is %d\n", choice, (long)getpid(), a-b); //substraction
		break;
	case 2:
		printf("\nI am child number %d with PID %ld, the product is %d\n", choice, (long)getpid(), a*b); //multiplication
		break;
	case 3:
		printf("\nI am child number %d with PID %ld, ", choice, (long)getpid());
		if (b == 0) { //if the divisor is zero, then print out a error message
			printf("the divisor cannot be zero");
		}else 
			printf("the quotient is %d with remainder %d\n", a/b, a%b); //division
		break;
	default:
		break;
	}
	return 0;
}