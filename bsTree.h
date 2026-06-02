/**
 * Copyright (c) 2026 Abhinav.
 * May be freely redistributed, but copyright notice must be retained.
 * https://github.com/abhicodes07
 */

#ifndef _BINARY_SEARCH_TREE_HEADER
#define _BINARY_SEARCH_TREE_HEADER

#define BST_DUP 1
#define BST_MIN 1

typedef struct bstnode {
  struct bstnode *left;  // left nodes
  struct bstnode *right; // right nodes
  void *data;            // generic data
} bstNode;

typedef struct bstree {
  int (*compare)(const void *, const void *); // comparator
  void (*print)(void *);                      // optional print
  void (*destroy)(void *);                    // destroyer

  bstNode root; // sentinel root
  bstNode nil;  // sentinel nil

#ifdef RB_MIN
  bstNode *min;
#endif // RB_MIN
} bsTree;

#endif // !_BINARY_SEARCH_TREE_HEADER
