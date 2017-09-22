#include "lide.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <termios.h>

#include <curses.h>

//#include <locale.h>

#define PROGRAM_NAME "lide"
#define VERSION "0.0.1"

#define TRUE 1
#define FALSE 0

#define LIDE_MAX_PATH_LEN 1024

unsigned flags[4] = {0, 0, 0, 0};

#define FLAGOFF(flag) ((flag) / (sizeof(unsigned) * 8))

#define FLAGS(flag) flags[FLAGOFF(flag)]

#define FLAGMASK(flag) (1 << ((flag) % (sizeof(unsigned) * 8)))

#define ISSET(flag) ((FLAGS(flag) & FLAGMASK(flag)) != 0)

char Lide_Root_Dir[LIDE_MAX_PATH_LEN];

void
version(void)
//lide_show_version(FILE * fp)
{
 fprintf(stderr, "%s-%s\n", PROGRAM_NAME, VERSION);
 //fprintf(fp, "%s-%s\n", PROGRAM_NAME, VERSION);
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

static int
main_initialize(int argc, char ** argv)
{
}

void
disable_extended_io(void)
{
 struct termios term;

 tcgetattr(0, &term);
 term.c_lflag &= ~IEXTEN;
 term.c_oflag &= ~OPOST;
 tcsetattr(0, TCSANOW, &term);
}

void
disable_signals(void)
{
 struct termios term;

 tcgetattr(0, &term);
 term.c_lflag &= ~ISIG;
 tcsetattr(0, TCSANOW, &term);
}

void
enable_signals(void)
{
 struct termios term;

 tcgetattr(0, &term);
 term.c_lflag |= ISIG;
 tcsetattr(0, TCSANOW, &term);
}

void
disable_flow_control(void)
{
 struct termios term;

 tcgetattr(0, &term);
 term.c_iflag &= ~IXON;
 tcsetattr(0, TCSANOW, &term);
}

void
enable_flow_control(void)
{
 struct termios term;

 tcgetattr(0, &term);
 term.c_iflag |= IXON;
 tcsetattr(0, TCSANOW, &term);
}

void
terminal_init(void)
{
 //static struct termios newterm;
 //static bool is_newterm = FALSE;

 //if (is_newterm) {
 // tcsetattr(0, TCSANOW, &newterm);
 //} else {
 //}

 raw();
 nonl();
 noecho();
 disable_extended_io();

 if (!ISSET(PRESERVE))
  disable_flow_control();

 disable_signals();
}

//void
//window_init(void)
//{
// topwin = newwin(2 - no_more_space(), COLS, 0, 0);
// edit = newwin(editwinrows, COLS, 2 - no_more_space(), 0);
// bottomwin = newwin(3 )
//}

int
main(int argc, char ** argv)
{
 int optchr;
 const struct option long_options[] = {
  {"version", 0, NULL, 'V'},
 };

 //setlocale(LC_ALL, "");
#if ENABLE_NLS
 bindtextdomain(PACKAGE, LOCALEDIR);
 textdomain(PACKAGE);
#endif

 while ((optchr = getopt_long(argc, argv, "", long_options, NULL)) != -1) {
  switch (optchr) {
   case 'V':
    version();
    exit(0);
   default:
    break;
  }
 }

 set_lide_root(
  //argv[0]
 );

 if (argc > 1) {
  if (!strcmp(argv[1], "--version")) {
   version();
   //lide_show_version(stdout);
   fprintf(stdout, "\nUsing LIDE_ROOT=%s\n", Lide_Root_Dir);
   exit(0);
  }
 }

 //if (main_initialize(argc, argv) == 0)
 // lide();

 terminal_init();

 curs_set(1);

 window_init();

 return 0;

 for (;;) {
  do_input();
 }

 assert(FALSE);
}
