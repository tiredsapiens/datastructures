#include "bst.h"
int numbers[50] = {903, 158, 763, 498, 372, 821, 250, 611, 575, 904,
                   999, 473, 167, 845, 387, 349, 127, 412, 683, 526,
                   651, 914, 798, 105, 620, 352, 714, 191, 289, 713,
                   227, 634, 587, 91,  953, 339, 925, 106, 982, 707,
                   712, 237, 876, 325, 918, 310, 430, 868, 458, 103};

int main() {
  bst tree = bst_create(500);
  for (int i = 0; i < 50; i++) {
    leaf *node_to_insert = malloc(sizeof(leaf));
    node_to_insert->value = numbers[i];
    bst_add_node(&tree, node_to_insert);
  }
  printf("%lld\n", tree.root->value);
  printf("%lld\n", tree.root->left->value);
  printf("%lld\n", tree.root->right->value);
  printf("%lld\n", tree.root->right->right->value);
  printf("%lld\n", tree.root->right->left->value);
  // leaf *node;
  // for (int i = 0; i < 50; i++) {
  //   node = bst_search(&tree, numbers[i]);
  //   printf("node:%lld number %d\n", node->value, numbers[i]);
  // }
  bst_print(&tree, INORDER);
  leaf *t = bst_search(&tree, 9999);
  if (!t) {
    printf("not found\n");
  }
  leaf *delete_node = bst_delete_value(&tree, 91);
  if (!delete_node) {
    printf("not found\n");
  }
  printf("%lld\n", delete_node->value);
  bst_print(&tree, INORDER);
}
