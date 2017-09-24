#include "stack.h"

#include <stdlib.h>

void *stack_push(stack * pstack, void * element, int size)
{
 int newsize;

 if(pstack->base + pstack->stacksize <= pstack->top){
  newsize = pstack->stacksize * 2;
  pstack->base = (void **)realloc(pstack->base,sizeof(void **) * newsize);

  if(NULL == pstack->base)
   return NULL;

  pstack->top = pstack->base + pstack->stacksize;
  pstack->stacksize = newsize;
 }

 *pstack->top = (void **)malloc(size);
 memcpy(*pstack->top,element,size);
 pstack->top++;
 return *(pstack->top - 1);
}
