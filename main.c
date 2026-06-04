/**
 * Copyright (c) 2026 Abhinav.
 * May be freely redistributed, but copyright notice must be retained.
 * https://github.com/abhicodes07
 */

#include "bsTree.h"
#include "bsdata.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  bsTree *bst;
  bst = bsTreeCreate(compareFunc, destroyFunc);

  if (bst == NULL) {
    fprintf(stderr, "Initialization of Binary Search Tree failed\n");
    return 1;
  }

  char a[] = {'B', 'I', 'N', 'A', 'R', 'Y', 'S', 'T', 'R', 'E', 'E'};
  int size = sizeof(a) / sizeof(a[0]);

  /* insert data */
  myData *data;
  for (int i = 0; i < size; i++) {
    data = makeData(a[i]);
    if (data == NULL || bsTreeInsert(bst, data) == NULL) {
      fprintf(stderr, "Insert %c: Out of memory\n", a[i]);
      free(data);
      break;
    }
    printf("Insert %c", a[i]);
    bsTreePrint(bst, printCharFunc);
    printf("\n");
  }

  /* delete data */
  bsNode *node;
  myData query;
  query.key = 'S';
  printf("Delete %c", query.key);
  node = bsTreeFind(bst, &query);

  if (node != NULL)
    bsTreeDelete(bst, node, 0);

  bsTreePrint(bst, printCharFunc);

  bsTreeDestroy(bst);

  return EXIT_SUCCESS;
}
