/**
 * Copyright (c) 2026 Abhinav.
 * May be freely redistributed, but copyright notice must be retained.
 * https://github.com/abhicodes07
 */

#include "bsTree.h"
#include <stdio.h>
#include <stdlib.h>

/* private functions */
static void transplant(bsTree *bst, bsNode *u, bsNode *v);
static void destroy(bsTree *bst, bsNode *node);
static void print(bsTree *bst, bsNode *node, void (*print_func)(void *),
                  int depth, char label);
static int checkOrder(bsTree *bst, bsNode *n, void *min, void *max);

/* initialze tree */
bsTree *bsTreeCreate(int (*compare)(const void *, const void *),
                     void (*destroy)(void *)) {
  bsTree *bst = (bsTree *)malloc(sizeof(bsTree));
  if (bst == NULL)
    return NULL;

  bst->compare = compare;
  bst->destroy = destroy;

  /* initialize sentinels */
  bst->root.left = bst->root.right = BST_NIL(bst);
  bst->root.data = NULL;

  bst->nil.left = bst->nil.right = BST_NIL(bst);
  bst->root.data = NULL;

#ifdef BST_MIN
  bst->min = NULL;
#endif /* ifdef BST_MIN */

  return bst;
}
