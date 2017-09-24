#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>

#include "uncomment.h"

char ch;

char *infile;
char *outfile;

FILE *file_in;
FILE *file_out;
FILE *file_tmp;

void after_split(int *retval);

void getch(void){
	ch = getc(file_in);
}

void direct_put(int *retval){
	if(EOF == putc(D2UAsciiTable[ch],file_tmp))
		*retval = -1;
}

void space_refill(){
	char *ch_fill;
	ch_fill = (char *)stack_get_top()
}

void skip_white_space(int *retval){
	int i;
	while(' ' == ch || '\t' == ch || '\r' == ch){
		if('\r' == ch){
			getch();
			if('\n' == ch)
				return ;
		}
		else
			stack_push(stack_space,(void *)&ch,sizeof(ch));
		getch();
		
	}
	/* maybe a comment ? */
	if('/' == ch)
		after_split(retval);
	/* something after white space ? */
	else if('\n' != ch)
		/* refill recorded white space */
		space_refill();
			putc(D2UAsciiTable[' '],file_tmp);
	else
		direct_put(retval);
}

void char_put(int *retval){
	if(EOF == ch)
		return ;
	if(' ' == ch || '\t' == ch || '\r' == ch)
		skip_white_space(retval);
	else
		direct_put(retval);
}

void parse_comment(void){
	getch();
	do{
		do{
			if(EOF == ch || '*' == ch)
				break;
			else
				getch();
		}
		while(1);
		if('*' == ch){
			getch();
			if('/' == ch){
				getch();
				return ;
			}
		}
		else{
			fprintf(stderr,"no comment end\n");
			return ;
		}
	}
	while(1);
}

void parse_comment_cpp(void){
	int retval;
	do{
		do{
			if(EOF == ch || '\n' == ch)
				break;
			else
				getch();
		}
		while(1);
		if('\n' == ch)
			direct_put(&retval);
		return ;
	}
	while(1);
}

void after_split(int *retval){
	getch();
	/* /\*... like C style */
	if('*' == ch)
		parse_comment();
	/* /\/... like C++ style */
	else if('/' == ch)
		parse_comment_cpp();
	/* /... , not a comment */
	else{
		if(EOF == putc(D2UAsciiTable['/'],file_tmp))
			*retval = -1;
		char_put(retval);
	}
}

int uncomment(void){
	int retval = 0;

	do{
		getch();
		/* strip dos stuff... */
		if('\x0d' != ch){
			/* /..., maybe comment */
			if('/' == ch)
				after_split(&retval);
			/* oridinary character */
			else
				char_put(&retval);
		}
	}
	while(EOF != ch);

	return retval;
}

int uncomment_onold(void){
	int retval = 0;
	char tmp_path[16];

	struct stat stat_buf;

	if(stat(infile,&stat_buf))
		retval = -1;

	/* make a temp file */
	strcpy(tmp_path,"./uctmp");
	strcat(tmp_path,"XXXXXX");
	mkstemp(tmp_path);

	/* open infile */
	if(!retval && NULL == (file_in = fopen(infile,"r")))
		retval = -1;

	/* open outfile */
	if(!retval && file_in && NULL == (file_tmp = fopen(tmp_path,"w"))){
		fclose(file_in);
		retval = -1;
	}

	/* start convertion */
	if(!retval && uncomment())
		retval = -1;

	/* close infile */
	if(file_in && EOF == fclose(file_in))
		retval = -1;

	/* close outfile */
	if(file_tmp && EOF == fclose(file_tmp))
		retval = -1;

	/* delete infile */
	if(!retval && -1 == unlink(infile))
		retval = -1;

	/* any error ? */
	if(retval && unlink(tmp_path))
		retval = -1;

	/* rename outfile to infile */
	if(!retval && -1 == rename(tmp_path,infile))
		retval = -1;

	if(-1 == chmod(infile,stat_buf.st_mode))
		retval = -1;

	return retval;
}

int main(int argc,char **argv){
	int i;
	for(i = 1;i < argc;i++){
		infile = argv[i];
		fprintf(stderr,"striping comment of %s...\n",infile);
		uncomment_onold();
	}
	return 0;
}
