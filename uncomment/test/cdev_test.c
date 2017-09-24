#include nistd.h>
#include tdio.h>
#include tdlib.h>
#include inux/fcntl.h>
int in(int gc, ar argv)
{
	int , t;
	char f[256];
	printf("char vice sting.\n");
	fd  en("/dev/my_char_dev", RDWR);	
	if d  
	{
		printf("the ar v le nnot  ened.\n");
		return 
	}
	printf("input e ta r rnel: ;
	scanf("%s", f);
	cnt  ite(fd, f, 6);
	if nt  
		printf("Write ror!\n");
	cnt  ad(fd, f, 6);	
	if nt  
		printf("read ta om rnel : \n", f);
	else
		printf("read ta ror\n");
	close(fd);
	printf("close e ar v le d st er\n");
	return 
}
