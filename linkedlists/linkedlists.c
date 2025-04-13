#include "linkedlists.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ll *ll_create(void *data, unsigned int size) {
  node *root = (node *)malloc(sizeof(node));
  ll *linkedlist = (ll *)malloc(sizeof(ll));
  root->prev = NULL;
  root->next = NULL;
  root->data = malloc(size);
  memcpy(root->data, data, size);
  root->size = size;
  linkedlist->root = root;
  linkedlist->length = 1;
  return linkedlist;
}

result ll_append(ll *list, void *data, unsigned int size) {
  node *list_node = malloc(sizeof(node));
  list_node->next = NULL;
  list_node->data = malloc(size);
  memcpy(list_node->data, data, size);
  list_node->size = size;
  node *last_node = list->root;
  for (int i = 0; i < list->length - 1; ++i, last_node = last_node->next)
    ;
  if (last_node->next != NULL) {
    printf("FAILED TO FIND LAST NODE");
    return FAILURE;
  } else {
    last_node->next = list_node;
    list_node->prev = last_node;
    list->length++;
    return SUCCESS;
  }
}

node *ll_get_at_index(ll *list, unsigned int index) {
  if (index >= list->length)
    return NULL;

  node *index_node = list->root;
  for (int i = 0; i < index; ++i, index_node = index_node->next)
    ;
  return index_node;
}

node *ll_pop_index(ll *list, unsigned int index) {
  if (index >= list->length)
    return NULL;

  node *index_node = list->root;
  if (index == 0) {
    node *deleted_node = list->root;
    list->root = list->root->next;
    list->length--;
    deleted_node->next = NULL;
    return deleted_node;
  }
  for (int i = 0; i < index; i++, index_node = index_node->next)
    ;

  node *prev_node = index_node->prev;

  if (index < list->length - 1) {
    node *next_node = index_node->next;
    prev_node->next = next_node;
    next_node->prev = prev_node;
  } else {
    prev_node->next = NULL;
  }
  list->length--;
  return index_node;
}

result ll_insert_at_index(ll *list, void *data, unsigned int size,
                          unsigned int index) {
  if (index > list->length)
    return FAILURE;

  node *node_to_insert = malloc(sizeof(node));
  if (!node_to_insert)
    return FAILURE;

  node_to_insert->data = malloc(size);
  if (!node_to_insert->data) {
    free(node_to_insert);
    return FAILURE;
  }

  memcpy(node_to_insert->data, data, size);
  node_to_insert->size = size;

  if (index == 0) {
    node_to_insert->next = list->root;
    node_to_insert->prev = NULL;
    if (list->root)
      list->root->prev = node_to_insert;
    list->root = node_to_insert;
  } else {
    node *prev = list->root;
    for (int i = 0; i < index - 1; ++i) {
      prev = prev->next;
    }

    node *next = prev->next;
    node_to_insert->next = next;
    node_to_insert->prev = prev;
    prev->next = node_to_insert;
    if (next)
      next->prev = node_to_insert;
  }

  list->length++;
  return SUCCESS;
}
