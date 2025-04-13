#include "bst.h"

leaf *__bst_search__(leaf *root, i64 value) {
  if (root == NULL) {

    printf("NULL was passed ,error\n");
    return NULL;
  } else if (root->value == value) {
    return root;
  } else if (value > root->value) {
    if (root->right == NULL)
      return NULL;
    return __bst_search__(root->right, value);
  } else {

    if (root->left == NULL)
      return NULL;

    return __bst_search__(root->left, value);
  }
}
leaf *bst_search(bst *tree, i64 value) {
  leaf *t = __bst_search__(tree->root, value);
  return t;
}

bst bst_create(i64 value) {
  leaf *root = malloc(sizeof(leaf));
  root->value = value;
  root->left = NULL;
  root->right = NULL;
  bst tree = {.root = root, .count = 0, .depth = 1};
  return tree;
}

leaf *__traverse__(leaf *root, i64 value) {
  if (root == NULL) {
    printf("NULL was passed ,error\n");
    return 0;
  } else {
    if (value > root->value) {
      if (root->right != NULL) {
        return __traverse__(root->right, value);
      } else {
        return root;
      }
    } else {
      if (root->left != NULL) {
        return __traverse__(root->left, value);
      } else {
        return root;
      }
    }
  }
}

char traverse_for_value(bst *tree, i64 value, leaf **ret) {
  if (tree->root == NULL) {
    return 0;
  } else {
    *ret = __traverse__(tree->root, value);
    if (!ret) {
      return 0;
    } else {

      return 1;
    }
  }
}

char bst_add_node(bst *tree, leaf *node) {
  node->right = NULL;
  node->left = NULL;
  leaf *parent;
  char res = traverse_for_value(tree, node->value, &parent);
  if (res) {
    if (node->value > parent->value) {
      parent->right = node;
    } else {
      parent->left = node;
    }
  }
  return res;
}

void __inorder_print__(leaf *node) {
  if (node->left != NULL) {
    __inorder_print__(node->left);
  }
  printf("%lld,", node->value);
  if (node->right != NULL) {
    __inorder_print__(node->right);
  }
}

void __preorder_print__(leaf *node) {
  printf("%lld,", node->value);
  if (node->left != NULL) {
    __inorder_print__(node->left);
  }
  if (node->right != NULL) {
    __inorder_print__(node->right);
  }
}

void __postorder_print__(leaf *node) {
  if (node->left != NULL) {
    __inorder_print__(node->left);
  }
  if (node->right != NULL) {
    __inorder_print__(node->right);
  }
  printf("%lld,", node->value);
}
void bst_print(bst *tree, traversal_order order) {

  switch (order) {
  case INORDER:
    __inorder_print__(tree->root);
    printf("\n");
    break;
  case PREORDER:
    __preorder_print__(tree->root);
    printf("\n");
    break;
  case POSTORDER:
    __postorder_print__(tree->root);
    printf("\n");
    break;
  default:
    __inorder_print__(tree->root);
    printf("\n");
    break;
  }
}
leaf *__search_leaf_parent__(leaf *node, i64 value) {
  // assumes the node exists
  if (node->left != NULL) {
    if (value == node->left->value) {
      return node;
    } else {
      return __search_leaf_parent__(node->left, value);
    }
  }
  if (node->right != NULL) {
    if (value == node->right->value) {
      return node;
    } else {
      return __search_leaf_parent__(node->left, value);
    }
  }
  return 0;
}
leaf *bst_delete_value(bst *tree, i64 value) {
  leaf *tbd_node = bst_search(tree, value);
  if (!tbd_node) {
    return 0;
  }
  leaf *tbd_node_parent = __search_leaf_parent__(tree->root, value);
  if (!tbd_node_parent) {
    return 0;
  }
  leaf *max_right_side_node = tbd_node;
  while (max_right_side_node->right != NULL) {
    max_right_side_node = max_right_side_node->right;
  }
  leaf *parent_max_right_side =
      __search_leaf_parent__(tree->root, max_right_side_node->value);
  /*
   * make it so the parent node of tbd_node now points to the
   * max_right_side_node
   */
  if (tbd_node_parent->right == tbd_node) {
    // if the tbd_node is the right side node child of parent node
    tbd_node_parent->right = max_right_side_node;
  } else {
    // its the left one instead
    tbd_node_parent->left = max_right_side_node;
  }

  // delete reference from parent_max_right_side to max_right_side_node
  if (parent_max_right_side->right == max_right_side_node) {
    parent_max_right_side->right = NULL;
  } else {
    parent_max_right_side->left = NULL;
  }
  return tbd_node;
}
void __print_node_children(leaf *node, int position, char *buffer, int depth) {
  for (int i = 0; i < position - 1; i++) {
    putchar(' ');
  }
  printf("%lld", node->left->value);
}
void pprint_tree(bst *tree) {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w); // get terminal size

  int width = w.ws_col;           // total width of terminal
  int point_to_write = width / 2; // starting from the middle
  char *buffer[1000];
}
