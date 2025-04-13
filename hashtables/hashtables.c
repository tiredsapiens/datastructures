#include "hashtables.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
hashtable *create_hashtable() {
  hashtable *ht = malloc(sizeof(hashtable));
  ht->size = 53;
  ht->table = (entry **)malloc(ht->size * sizeof(entry *));
  ht->count = 0;
  ht->resize_factor = 2;
  return ht;
}
hashtable *create_hashtable_with_size(unsigned int size) {

  hashtable *ht = malloc(sizeof(hashtable));
  ht->size = size;
  ht->table = (entry **)malloc(ht->size * sizeof(entry *));
  ht->count = 0;
  ht->resize_factor = 2;
  return ht;
}

void hashtable_add_entry(hashtable *h_table, char *key, void *value,
                         unsigned int size) {
  entry *new_entry = malloc(sizeof(entry));
  new_entry->key = key;
  new_entry->next = NULL;
  new_entry->size = size;
  new_entry->value = malloc(size);
  memcpy(new_entry->value, value, size);
  unsigned int index = get_index(key, h_table->size);
  if (h_table->table[index] == NULL) {
    h_table->table[index] = new_entry;
  } else {
    // handle conflicts
    entry *iterating_entry = h_table->table[index];
    for (int i = 0; iterating_entry->next != NULL;
         iterating_entry = iterating_entry->next, i++)
      ;
    iterating_entry->next = new_entry;
    new_entry->next = NULL;
  }
  h_table->count++;
  if (check_for_resize(h_table)) {
    printf("Resizing\n");
    resize_hashtable(h_table);
  }
}

unsigned int dbj_hash(const char *str) {
  unsigned long hash = 5381;
  int c;
  while ((c = *str++)) {

    hash = ((hash << 5) + hash) + c;
  }
  return hash;
}

unsigned int get_index(const char *key, unsigned int table_size) {
  unsigned int hash = dbj_hash(key);
  return hash % table_size;
}

char check_for_resize(hashtable *h_table) {
  return (float)h_table->count / (float)h_table->size > 0.75 ? 1 : 0;
}

void resize_hashtable(hashtable *h_table) {
  hashtable *new_hashtable =
      create_hashtable_with_size(h_table->resize_factor * h_table->size);
  new_hashtable->count = h_table->count;
  for (int i = 0; i < h_table->size; i++) {
    entry *item = h_table->table[i];
    if (item != NULL) {
      entry *iterating_item = item;
      hashtable_add_entry(new_hashtable, iterating_item->key,
                          iterating_item->value, iterating_item->size);
      while (iterating_item->next != NULL) {
        iterating_item = iterating_item->next;
        hashtable_add_entry(new_hashtable, iterating_item->key,
                            iterating_item->value, iterating_item->size);
      }
    }
  }
  free(h_table->table);
  h_table->table = new_hashtable->table;
  h_table->size = new_hashtable->size;
  h_table->resize_factor = new_hashtable->resize_factor;
  free(new_hashtable);
  // free(h_table);
}

void *get_value_by_key(hashtable *h_table, const char *key) {
  unsigned int index = get_index(key, h_table->size);
  // printf("%s got key %d\n", key, index);
  entry *entry_ = h_table->table[index];
  if (entry_ == NULL) {
    return 0;
  }
  while (entry_->next != NULL) {
    if (entry_->key == key)
      break;
    entry_ = entry_->next;
  }
  if (entry_->key == key)
    return entry_->value;
  else
    return 0;
}

char **get_all_keys(hashtable *h_table) {
  char **ret = malloc(h_table->count * sizeof(char *));
  int j = 0;
  for (int i = 0; i < h_table->size; i++) {
    entry *dataentry = h_table->table[i];
    if (dataentry == NULL) {
      continue;
    }
    if (dataentry->next == NULL) {

      ret[j] = dataentry->key;
      j++;
    } else {

      ret[j] = dataentry->key;
      j++;
      while (dataentry->next != NULL) {
        dataentry = dataentry->next;
        ret[j] = dataentry->key;
        j++;
      }
    }
  }
  return ret;
}
void **get_all_values(hashtable *h_table) {
  // taking the size of a char pointer since all pointers have the same size
  void **ret = malloc(h_table->count * sizeof(char *));
  char **keys = get_all_keys(h_table);
  for (int i = 0; i < h_table->count; i++) {
    char *key = keys[i];
    void *value = get_value_by_key(h_table, key);
    ret[i] = value;
  }
  return ret;
}
