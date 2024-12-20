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

// void queue_push(stack* s, stacktype d){
//    if(s){
//       dataframe* f = ncalloc(1, sizeof(dataframe));
//       f->i = d;
//       f->next = NULL;
//       if(!(s->start)){
//          s->start = f;
//          s->end = f;
//       } 
//       else{
//          f = s->start;
//          f->next->i = d;
//          s->start->next = f;
//          s->end = f;
//          s->end->next = NULL;
//       }
//       s->size = s->size + 1;
//    }
// }

// bool queue_pop(stack* s, stacktype* d)
// {
//    if(s->start == NULL){
//       return false;
//    }
//    dataframe* f = s->start->next;
//    *d = s->start->i; 
//    free(s->start);
//    s->start = f;
//    if(s->start == NULL) {
//       s->end = NULL;
//    }
//    s->size = s->size - 1;
//    return true;
// }

void stack_tostring(stack* s, char* str)
{
   char tmp[ELEMSIZE];
   str[0] = '\0';
   if((s==NULL) || (s->size <1)){
      return;
   }
   dataframe* p = s->start;
   while(p){
      sprintf(tmp, "%s", p->i); 
      strcat(str, tmp);
      strcat(str, "|");
      p = p->next;
   }
   str[strlen(str)-1] = '\0';
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