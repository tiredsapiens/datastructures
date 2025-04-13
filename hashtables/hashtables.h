#pragma once

typedef struct entry{
  char* key;
  void *value;
  unsigned int size;
  struct entry *next;
}entry;


typedef struct hashtable{
  entry** table;
  unsigned int size;
  unsigned int count;
  char resize_factor;
}hashtable;
#define TRUE 1
#define FALSE 0

hashtable* create_hashtable();
hashtable* create_hashtable_with_size(unsigned int size);
unsigned int dbj_hash(const char* str);
void hashtable_add_entry(hashtable* table,char* key,void* value,unsigned int size);
unsigned int get_index(const char*key,unsigned int table_size);
char check_for_resize(hashtable*);
void resize_hashtable(hashtable*);
void* get_value_by_key(hashtable*,const char*);
char** get_all_keys(hashtable*);
void** get_all_values(hashtable*);
