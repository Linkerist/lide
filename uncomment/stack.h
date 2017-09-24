#ifndef __STACK_H__
#define __STACK_H__

typedef struct stack_st {
 void ** base;
 void ** top;
 int stacksize;
} stack;

void *stack_push(stack *pstack,void *element,int size);

#endif
