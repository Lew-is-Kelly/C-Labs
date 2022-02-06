#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// include the header files with the declarations of listset
#include "listset.h"

// create a new, empty linked list set
struct listset *listset_new()
{
  struct listset *list = malloc(sizeof(struct listset));
  list->head = NULL;
  return list;
}

/* check to see if an item is in the set
   returns 1 if in the set, 0 if not */
int listset_lookup(struct listset *this, char *item)
{
  struct listnode *curr_node;
  for (curr_node = this->head; curr_node != NULL; curr_node = curr_node->next)
  {
    if (strcmp(item, curr_node->str) == 0)
    {
      return 1;
    }
  }
  return 0;
}

// add an item, with number 'item' to the set
// has no effect if the item is already in the set.
// New items that are not already in the set should
// be added to the start of the list
void listset_add(struct listset *this, char *item)
{
  if (listset_lookup(this, item) == 0)
  {
    struct listnode *new_node = malloc(sizeof(struct listnode));
    new_node->next = this->head;
    this->head = new_node;
    new_node->str = item;
  }
}

// remove an item with number 'item' from the set
void listset_remove(struct listset *this, char *item)
{
  if (listset_lookup(this, item))
  {
    struct listnode *n;
    // if the list is empty and/or the head is the node we want
    if (strcmp(this->head->str, item) == 0)
    {
      struct listnode *temp = this->head;
      this->head = this->head->next;
      free(temp);
    }
    else
    {
      for (n = this->head; n != NULL; n = n->next)
      {
        if (strcmp(n->next->str, item) == 0)
        {
          struct listnode *temp = n->next;
          n->next = n->next->next;
          free(temp);
          return;
        }
      }
    }
  }
}

// place the union of src1 and src2 into dest
void listset_union(struct listset *dest, struct listset *src1, struct listset *src2)
{
  struct listnode *temp_node;
  for (temp_node = src1->head; temp_node != NULL; temp_node = temp_node->next)
  {
    listset_add(dest, temp_node->str);
  }
  for (temp_node = src2->head; temp_node != NULL; temp_node = temp_node->next)
  {
    listset_add(dest, temp_node->str);
  }
}

// place the intersection of src1 and src2 into dest
void listset_intersect(struct listset *dest, struct listset *src1, struct listset *src2)
{
  struct listnode *temp_node;
  for (temp_node = src1->head; temp_node != NULL; temp_node = temp_node->next)
  {
    if (listset_lookup(src2, temp_node->str))
    {
      listset_add(dest, temp_node->str);
    }
  }
}

// return the number of items in the listset
int listset_cardinality(struct listset *this)
{
  struct listnode *n;
  int count = 0;
  for (n = this->head; n != NULL; n = n->next)
  {
    count++;
  }
  return count;
}

// print the elements of the list set
void listset_print(struct listset *this)
{
  struct listnode *p;

  for (p = this->head; p != NULL; p = p->next)
  {
    printf("%s, ", p->str);
  }
  printf("\n");
}
