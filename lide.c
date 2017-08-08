#include <stdio.h>

#define PROGRAM_NAME "lide"
#define VERSION "0.0.1"

#define TRUE 1
#define FALSE 0

void
version(void)
{
 printf("%s-%s\n", PROGRAM_NAME, VERSION);
}

int
get_input(void)
{
 int input = 0;
 return input;
}

int
do_input(void)
{
 int input = get_input();

 return input;
}

int
main(int argc, char ** argv)
{
 for (;;) {
  do_input();
 }

 assert(FALSE);
}
