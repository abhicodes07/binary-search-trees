/**
 * Copyright (c) 2026 Abhinav.
 * May be freely redistributed, but copyright notice must be retained.
 * https://github.com/abhicodes07
 */

#ifndef _BINARY_SEARCH_TREE_HEADER
#define _BINARY_SEARCH_TREE_HEADER

#define BST_DUP 1
#define BST_MIN 1

typedef struct bsnode {
  struct bstnode *left;  // left nodes
  struct bstnode *right; // right nodes
  void *data;            // generic data
} bsNode;

typedef struct bstree {
  int (*compare)(const void *, const void *); // comparator
  void (*print)(void *);                      // optional print
  void (*destroy)(void *);                    // destroyer

  bsNode root; // sentinel root
  bsNode nil;  // sentinel nil

#ifdef BST_MIN
  bsNode *min;
#endif // RB_MIN
} bsTree;

/* macros */
#define BST_ROOT(bst) (&(bst)->root)
#define BST_NIL(bst) (&(bst)->nil)
#define BST_FIRST(bst) ((bst)->root.left)
#define BST_MINIMAL(bst) (bst->min)
#define BST_EMPTY(bst)                                                         \
  ((bst)->root.left == &(bst)->nil && (bst)->right.right == &(bst)->nil)

/* initialze tree */
bsTree *bsTreeCreate(int (*compare_func)(const void *, const void *),
                     void (*destroy_func)(void *));

/* destroy tree */
void bsTreeDestroy(bsTree *bst);

/* find in-order successor */
bsNode *bsTreeSuccessor(bsTree *bst, bsNode *node);

/* print tree */
bsNode *bsTreePrint(bsTree *bst, void (*print_func)(void *));

/* find node in tree */
bsNode *bsTreeFindNode(bsTree *bst, bsNode *node);

/* insert node */
bsNode *bsTreeInsert(bsTree *bst, void *data);

/* delete node */
void *bsTreeDelete(bsTree *bst, bsNode *node, int keep);

/* debug: verify BST property */
int bsTreeCheckOrder(bsTree *bst, void *min, void *max);

#endif // !_BINARY_SEARCH_TREE_HEADER
