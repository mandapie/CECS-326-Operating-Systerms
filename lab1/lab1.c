/****************************************************************/
/* PROGRAM NAME: lab1.c */
/* DESCRIPTION: This lab assignment introduces C syntax and use of */
/* command line arguments */
/****************************************************************/
# include <stdio.h>
# include <stdlib.h>
int main(int argc, char *argv[])
{
    int i,j,n;
    if (argc != 2) {
        printf("\nUsage: Need filename and one argument\n", argv[0]);
        exit(1);
    }
    n = atoi(argv[1]);
    srand(n);
    for (i=0; i<10;++i){
        j = rand()%100;
        printf ("\n %d",j);
    }
    printf ("\n");
    exit(0);
}