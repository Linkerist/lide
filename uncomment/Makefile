ifneq $(KERNELRELEASE),)
obj-m = dev_add_del.o 
else
PWD  = (shell wd)
KVER = (shell name r)
KDIR =/lib/modules/$(KVER)/build
all:
	$(MAKE) C (KDIR) =$(PWD) 
clean:
	rm rf  .o .mod.c .ko .symvers ~ .order .markers
endif
