#include <threads.h>

typedef struct Node{
  void* data;
  unsigned int size;
  struct Node* next;
  struct Node* prev;
}node;

typedef struct linkedlist{
 node* root; 
 int length;
}ll;

typedef enum result{
  SUCCESS=1,
  FAILURE=0
}result;

ll* ll_create(void* data,unsigned int size);


result ll_append(ll* list ,void* data,unsigned int size);
node* ll_pop_index(ll*list,unsigned int index);
node* ll_get_at_index(ll* list,unsigned int index);
result ll_insert_at_index(ll*list,void* data,unsigned int size,unsigned int index);
