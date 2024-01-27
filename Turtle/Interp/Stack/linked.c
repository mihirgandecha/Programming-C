#include "../interp.h"
#include "specific.h"

#define DOTFILE 5000

stack* stack_init(void)
{
   stack* s = (stack*) ncalloc(1, sizeof(stack));
   return s;
}

void stack_push(stack* s, stacktype d)
{
   if(s){
      dataframe* f = ncalloc(1, sizeof(dataframe));
      f->i = d;
      f->next = s->start;
      s->start = f;
      s->size = s->size + 1;
   }
}

bool stack_pop(stack* s, stacktype* d)
{
   if((s==NULL) || (s->start==NULL)){
      return false;
   }
   dataframe* f = s->start->next;
   *d = s->start->i; 
   s->start->i = NULL; 
   free(s->start);
   s->start = f;
   s->size = s->size - 1;
   return true;
}

void queue_push(stack* s, stacktype d)
{
   dataframe* f = ncalloc(1, sizeof(dataframe));
   f->i = d;
   f->next = NULL;
   if(s->start == NULL) {
      s->start = f;
   } 
   else {
      s->end->next = f;
   }
   s->end = f;
   s->size = s->size + 1;
}

bool queue_pop(stack* s, stacktype* d)
{
   if(s->start == NULL){
      return false;
   }
   dataframe* f = s->start->next;
   *d = s->start->i; 
   free(s->start);
   s->start = f;
   if(s->start == NULL) {
      s->end = NULL;
   }
   s->size = s->size - 1;
   return true;
}

bool stack_peek(stack* s, stacktype* d)
{
   if((s==NULL) || (s->start==NULL)){
      return false;
   }
   *d = s->start->i;
   return true;
}

bool stack_free(stack* s)
{
   if(s){
      dataframe* p = s->start;
      while(p!=NULL){
         dataframe* tmp = p->next;
         free(p);
         p = tmp;
      }
      free(s);
   }
   return true;
}

bool queue_free(stack* s)
{
   if(s){
      dataframe* p = s->start;
      while(p!=NULL){
         dataframe* tmp = p->next;
         free(p);
         p = tmp;
      }
      free(s);
   }
   return true;
}