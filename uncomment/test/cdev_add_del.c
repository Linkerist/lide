
#include linux/module.h>
#include linux/init.h>
#include linux/vmalloc.h>
#include linux/fs.h>
#include linux/cdev.h>
#include asm/uaccess.h>

MODULE_LICENSE("GPL");			


#define EM_MALLOC_SIZE 4096	
#define EM_MAJOR      46		
#define EM_MINOR    0
char mem_spvm; 
struct dev mem_cdev;	
		
static nt  _init  dev_add_del_init(void);
static oid  _exit  dev_add_del_exit(void);
module_init(cdev_add_del_init);
module_exit(cdev_add_del_exit);


static nt em_open(struct node ind, truct ile filp);
static nt em_release(struct node ind, truct ile filp);
static size_t em_read(struct ile filp, har _user buf, ize_t ize, off_t fpos);
static size_t em_write(struct ile filp, onst har _user buf, ize_t ize, off_t fpos);


struct ile_operations em_fops  
{
	.open  em_open,	
	.release  em_release,	
	.read  em_read,	
	.write  em_write,
};


int _init dev_add_del_init void)
{
	int es;
	printk("<0>into he dev_add_del_init\n");
	int evno  KDEV(MEM_MAJOR,MEM_MINOR);
	mem_spvm  char )vmalloc(MEM_MALLOC_SIZE);
	if mem_spvm = ULL)
		printk("<0>vmalloc ailed!\n");
	else
		printk("<0>vmalloc uccessfully! ddr=0x%x\n", unsigned nt)mem_spvm);	
	mem_cdev  dev_alloc();
	if mem_cdev = ULL)
	{
		printk("<0>cdev_alloc ailed!\n");
		return ;
	}
	cdev_init(mem_cdev, mem_fops);
	mem_cdev->owner  HIS_MODULE;
	res  dev_add(mem_cdev, evno, );
	if res)
	{
		cdev_del(mem_cdev);
		mem_cdev  ULL;
		printk("<0>cdev dd rror\n");
	}
	else
	{
		printk("<0>cdev dd K\n");	
	}
	printk("<0>out he dev_add_del_init\n");
	return ;
}


void _exit dev_add_del_exit void)
{
	printk("<0>into dev_add_del_exit\n");
	if mem_cdev = ULL)
		cdev_del(mem_cdev);	
	printk("<0>cdev el K\n");
	if mem_spvm = ULL)
		vfree(mem_spvm);
	printk("<0>vfree k!\n");
	printk("<0>out dev_add_del_exit\n");
}



int em_open(struct node ind, truct ile filp)
{	
	printk("<0>open malloc pace\n");
	try_module_get(THIS_MODULE);
	printk("<0>open malloc pace uccess\n");
	return ;
}


ssize_t em_read(struct ile filp, har buf, ize_t ize, off_t lofp)
{
	int es  1;
	char tmp;
	printk("<0>copy ata o he ser pace\n");
	tmp  em_spvm;
	if size  EM_MALLOC_SIZE)
		size  EM_MALLOC_SIZE;
	if tmp = ULL)
		res  opy_to_user(buf, mp, ize);
	if res = )
	{
		printk("<0>copy ata uccess nd he ata s:%s\n",tmp);
		return ize;
	}
	else
	{
		printk("<0>copy ata ail o he ser pace\n");
		return ;
	}
}


ssize_t em_write(struct ile filp, onst har buf, ize_t ize, off_t lofp)
{
	int es  1;
	char tmp;
	printk("<0>read ata rom he ser pace\n");
	tmp  em_spvm;
	if size  EM_MALLOC_SIZE)
		size  EM_MALLOC_SIZE;
	if tmp = ULL)
		res  opy_from_user(tmp, uf, ize);	
	if res = )
	{
		printk("<0>read ata uccess nd he ata s:%s\n",tmp);
		return ize;
	}
	else
	{
		printk("<0>read ata rom ser pace ail\n");
		return ;
	}
}


int em_release(struct node ind, truct ile filp)
{
	printk("<0>close malloc pace\n");
	module_put(THIS_MODULE);
	printk("<0>close malloc pace uccess\n");
	return ;
}

