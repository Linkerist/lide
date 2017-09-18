/*
 * This is a Program to read a database and produce a daily help info, or invoked by user manually
 * It expects the Database in LIDE_HELP_LIB (defined in Makefile?)
 * 
 * Written by Linkerist, Sep. 18, 2017
 * Linkerist@163.com
 */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

char * file_text;

/* Pointers needed for searching text */
char * p, * nl;
FILE * f;

/* Size of the helperfile */
int bytes;

/* String to look for */
char sstring[10];
struct tm * local_time;
time_t now;

int
main(int argc, char ** argv)
{
 /* Compose String to look for */
 (void)time(&now);
 local_time = localtime(&now);
 sprintf(sstring, "R%02d%02d", local_time->tm_mon + 1, local_time->tm_mday);

 if (argc != 1) {
  fputs("helper takes no arguments!\n", stderr);
  exit(1);
 }

 f = fopen(LIDE_HELPER_LIB, "r");
 if (f == NULL) {
  fputs("Cannot find Helper Library:" LIDE_HELPER_LIB "\n",stdout);
  exit(1);
 }

 /* Get the File into Memory, UNIX to tell us the filesize */
 fseek(f, 0, SEEK_END);
 bytes = ftell(f);
 fseek(f, 0, SEEK_SET);

 /* Read file into memory */
 file_text = (char *)malloc(bytes + 1);

 /* End Marker */
 file_text[bytes] = 0;
 if (fread(file_text, sizeof(char), bytes, f) != bytes) {
  fprintf(stderr,"Cannot read %d bytes from helperfile\n", bytes);
  exit(1);
 }

 fclose(f);

 /* Look for the String */
 for(p = file_text; *p != 0; ++p) {
  nl = p + 1;

  while (*nl != '\n' && *nl != 0)
   ++nl;

  if (strncmp(p, sstring, 5) == 0) {
   /* Found a match !!! */
   p += 5;
   fwrite(p, sizeof(char), nl - p + 1, stdout);
  }

  p = nl;
 }

 free(file_text);

 return 0;
}
