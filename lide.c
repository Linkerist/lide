#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PROGRAM_NAME "lide"
#define VERSION "0.0.1"

#define TRUE 1
#define FALSE 0

#define LIDE_MAX_PATH_LEN 1024

char Lide_Root_Dir[LIDE_MAX_PATH_LEN];

void
version(void)
{
 printf("%s-%s\n", PROGRAM_NAME, VERSION);
}

static void
set_lide_root(
 void
 //const char * argv
)
{
 char * lr;
 //char lide_root

 lr = getenv("LIDE_ROOT");

#ifdef LIDE_ROOT
 if (lr == NULL
  //&&
 )
  lr = LIDE_ROOT;
#endif

 if (lr != NULL)
  strcpy(Lide_Root_Dir, lr);
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
 set_lide_root(
  //argv[0]
 );

 version();

 return 0;

 for (;;) {
  do_input();
 }

 assert(FALSE);
}
