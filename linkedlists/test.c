#include "linkedlists.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_list(ll *list) {
  node *curr = list->root;
  int i = 0;
  while (curr) {
    printf("Index %d: value=%d, size=%u\n", i, *(int *)(curr->data),
           curr->size);
    curr = curr->next;
    i++;
  }
  printf("List length: %d\n", list->length);
  puts("----------------------");
}

int main() {
  printf("TEST: Creating list with one item...\n");
  int val1 = 10;
  ll *list = ll_create(&val1, sizeof(int));
  print_list(list);

  printf("TEST: Appending items...\n");
  int val2 = 20, val3 = 30;
  ll_append(list, &val2, sizeof(int));
  ll_append(list, &val3, sizeof(int));
  print_list(list);

  printf("TEST: Inserting at index 1...\n");
  int val_insert = 99;
  ll_insert_at_index(list, &val_insert, sizeof(int), 1);
  print_list(list);

  printf("TEST: Getting value at index 1...\n");
  node *n = ll_get_at_index(list, 1);
  if (n) {
    printf("Retrieved value: %d\n", *(int *)(n->data));
  } else {
    printf("Failed to get value at index 1\n");
  }
  puts("----------------------");

  printf("TEST: Popping index 2...\n");
  node *popped = ll_pop_index(list, 2);
  if (popped) {
    printf("Popped value: %d\n", *(int *)(popped->data));
    // no free here
  } else {
    printf("Failed to pop index 2\n");
  }
  print_list(list);

  printf("TEST: Attempting to pop invalid index...\n");
  node *fail_pop = ll_pop_index(list, 99);
  if (!fail_pop) {
    printf("Correctly handled invalid index.\n");
  }
  puts("----------------------");

  printf("All tests done (no cleanup).\n");
  return 0;
}
