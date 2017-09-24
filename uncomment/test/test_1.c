
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

main(){
	int fd = creat("./fasdfa",0666);
	char append = '\x0d';                 
	write(fd,&append,1);
	
	close(fd);
}



