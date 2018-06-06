# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
void main(int argc, char *argv[])
{
if (argc > 1) {
execvp(argv[1], &argv[1]);
perror ("exec failure");
exit(1);
}
printf("\n Usage: %s text_file\n", *argv);
exit(1) ;
}