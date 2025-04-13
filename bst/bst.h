#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

typedef long long i64;
typedef unsigned long long u64;

typedef enum traversal_order{
INORDER,
PREORDER,
POSTORDER
} traversal_order;
typedef struct leaf{
  i64 value;
  struct leaf* left;
  struct leaf* right;
}leaf;

typedef struct bst{
  leaf* root;
  u64 count;
  u64 depth;
}bst;



bst bst_create(i64 value);
char bst_add_node(bst*,leaf*);
leaf* bst_delete_value(bst*,i64);
char bst_invert(bst*);
void bst_print(bst*,traversal_order);
leaf* bst_search(bst*,i64);
char traverse_for_value(bst*, i64,leaf**);
void pprint_tree(bst*);


