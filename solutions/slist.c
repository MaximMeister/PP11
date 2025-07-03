#include "slist.h"
#include <stdlib.h>

SNode *add_node(SNode *head, int value) {
  SNode *new_node = malloc(sizeof(SNode));
  if (!new_node)
    return head; // malloc fehlgeschlagen

  new_node->value = value;
  new_node->next = head;
  return new_node;
}

int count_nodes(SNode *head) {
  int count = 0;
  for (SNode *p = head; p != NULL; p = p->next) {
    count = count + 1;
  }
  return count;
}

void free_list(SNode *head) {
  while (head != NULL) {
    SNode *temp = head;
    head = head->next;
    free(temp);
  }
}
