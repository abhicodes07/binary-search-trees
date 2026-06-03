/**
 * Copyright (c) 2026 Abhinav.
 * May be freely redistributed, but copyright notice must be retained.
 * https://github.com/abhicodes07
 */

#include "bsTree.h"
#include <stdio.h>
#include <stdlib.h>

/* private functions */
static void print(bsTree *bst, bsNode *node, void (*print_func)(void *),
                  int depth, char *label);
static int checkOrder(bsTree *bst, bsNode *n, void *min, void *max);
static bsNode *helper(bsTree *bst, bsNode *node);
static void destroy(bsTree *bst, bsNode *node);
static bsNode *findLastRight(bsTree *bst, bsNode *node);

/* initialze tree */
bsTree *bsTreeCreate(int (*compare)(const void *, const void *),
                     void (*destroy)(void *)) {
  bsTree *bst = (bsTree *)malloc(sizeof(bsTree));
  if (bst == NULL)
    return NULL;

  bst->compare = compare;
  bst->destroy = destroy;

  /* initialize sentinels */
  bst->root.left = bst->root.right = NULL;
  bst->root.data = NULL;
  bst->root.parent = NULL;

#ifdef BST_MIN
  bst->min = NULL;
#endif /* ifdef BST_MIN */

  return bst;
}

/* destroy tree */
void bsTreeDestroy(bsTree *bst) {
  destroy(bst, BST_FIRST(bst));
  free(bst);
}

/* find node */
bsNode *bsTreeFindNode(bsTree *bst, void *data) {
  bsNode *temp;
  temp = BST_FIRST(bst);

  while (temp != NULL) {
    int cmp = bst->compare(temp->data, data);
    if (cmp == 0)
      return temp;
    temp = cmp < 0 ? temp->left : temp->right;
  }
  return NULL;
}

/* insert node in the tree */
bsNode *bsTreeInsert(bsTree *bst, void *data) {
  bsNode *current, *new_node, *parent;

  parent = BST_ROOT(bst);
  current = BST_FIRST(bst);

  while (current != NULL) {
    int cmp = bst->compare(current->data, data);

    /* if duplicates are allowed then update the data and return */
#ifndef BST_DUP
    if (cmp == 0) {
      bst->destroy(current->data);
      current->data = data;
      return current;
    }
#endif /* ifndef BST_DUP */
    parent = current;
    current = cmp < 0 ? current->left : current->right;
  }

  /* initialize newnode at the current */
  current = new_node = (bsNode *)malloc(sizeof(bsNode));

  if (current == NULL)
    return NULL;

  current->data = data;
  current->parent = parent;
  current->left = current->right = NULL;

  /* update parent's pointer to newnode */
  if (parent == BST_ROOT(bst) ||
      bst->compare(current->data, parent->data) < 0) {
    parent->left = current;
  } else {
    parent->right = current;
  }

#ifdef BST_MIN
  if (bst->min != NULL && bst->compare(bst->min->data, current->data) < 0) {
    bst->min = current;
  }
#endif /* ifdef BST_MIN */

  return new_node;
}

/* successor */
bsNode *bsTreeSuccessor(bsTree *bst, bsNode *node) {
  bsNode *succ;

  succ = node->right;

  if (succ != NULL) {
    /* move down until we find successor */
    for (; succ->left != NULL; succ = succ->left)
      ;
  } else {
    for (succ = node->parent; node == succ->right;
         node = succ, succ = succ->parent)
      ;

    if (succ == BST_ROOT(bst)) {
      succ = NULL; /* not found */
    }
  }
  return succ;
}

/* delete node from the tree */
void *bsTreeDelete(bsTree *bst, bsNode *node, int keep) {
  bsNode *target, *child;
  void *data;

  /* choose in-order successor of a node */
  data = node->data;

  /* node has 0 or 1 child */
  if (node->left == NULL || node->right == NULL) {
    target = node;

    /* if the target is minimum then after deletion it's successor becomes min
     */
#ifdef BST_MIN
    if (bst->min == target)
      bst->min = bsTreeSuccessor(bst, target);
#endif /* ifdef BST_MIN */
  } else {
    target = bsTreeSuccessor(bst, target);

    /* swap data */
    node->data = target->data;
  }

  child = (target->left == NULL) ? target->right : target->left;

  if (child != NULL)
    child->parent = target->parent;

  if (target == target->parent->left)
    target->parent->left = child;
  else
    target->parent->right = child;

  free(target);

  if (keep == 0) {
    bst->destroy(data);
    data = NULL;
  }

  return data;
}

/* print tree */
void bsTreePrint(bsTree *bst, void (*print_func)(void *)) {
  printf("\n--\n");
  print(bst, BST_FIRST(bst), print_func, 0, "T");
}

/* print helper */
void print(bsTree *bst, bsNode *node, void (*print_func)(void *), int depth,
           char *label) {
  if (node != NULL) {
    /* traverse left subtree */
    print(bst, node->right, print_func, depth + 1, "R");

    /*
     * (%*s, 24, "") means ("%24s", "")
     * which prints an empty string right-aligned in a field of width 24
     * so when depth is 1, it prints 8 spaces
     * when depth is 2, it prints 16 spaces
     */
    printf("%*s", 8 * depth, "");
    if (label)
      printf("%s: ", label);
    print_func(node->data);
    printf("\n");

    /* traverse rigth subtree */
    print(bst, node->left, print_func, depth + 1, "L");
  }
}

/* destroy nodes recursively */
void destroy(bsTree *bst, bsNode *node) {
  if (node != NULL) {
    destroy(bst, node->left);
    destroy(bst, node->right);
    bst->destroy(node->data);
    free(node);
  }
}

/* check BST order property */
int bsTreeCheckOrder(bsTree *bst, bsNode *n, void *min, void *max) {
  return checkOrder(bst, n, min, max);
}

/* BST property verification helper */
int checkOrder(bsTree *bst, bsNode *n, void *min, void *max) {
  if (n == NULL)
    return 1;

#ifdef BST_DUP
  if (bst->compare(n->data, min) < 0 || bst->compare(n->data, max) > 0)
#else
  if (bst->compare(n->data, min) <= 0 || bst->compare(n->data, max) >= 0)
#endif /* ifdef BST_DUP */
    return 0;

  return checkOrder(bst, n->left, min, n->data) &&
         checkOrder(bst, n->right, n->data, max);
}
