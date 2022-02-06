#include "bitset.h"
#include <stdbool.h>
#include <stdlib.h>

// create a new, empty bit vector set with a universe of 'size' items
struct bitset *bitset_new(int size)
{
    struct bitset *set = malloc(sizeof(struct bitset));
    set->universe_size = size;
    set->word_size = sizeof(unsigned int) * 8;

    if (size % set->word_size)
        set->size_in_words = size / set->word_size;
    else
        set->size_in_words = (size / set->word_size) + 1;

    set->bits = calloc(set->size_in_words, sizeof(unsigned int));

    return set;
}

// get the size of the universe of items that could be stored in the set
int bitset_size(struct bitset *this)
{
    return this->universe_size;
}

// get the number of items that are stored in the set
int bitset_cardinality(struct bitset *this)
{
    unsigned int *ptr = this->bits;
    unsigned int *endPtr = ptr + this->size_in_words;
    int count = 0;

    while (ptr < endPtr)
    {
        while (*ptr)
        {
            count += *ptr & 1;
            *ptr >>= 1;
        }
        count += *ptr++ & 1;
    }
    return count;
}

// check to see if an item is in the set
bool bitset_lookup(struct bitset *this, int item)
{
    int word_position = item / this->word_size;
    int inside_position = item % this->word_size;

    return (this->bits[word_position] & (1 << inside_position));
}

// add an item, with number 'item' to the set
// has no effect if the item is already in the set
void bitset_add(struct bitset *this, int item)
{
    int word_position = item / this->word_size;
    int inside_position = item % this->word_size;

    this->bits[word_position] |= 1 << inside_position;
}

// remove an item with number 'item' from the set
void bitset_remove(struct bitset *this, int item)
{
    int word_position = item / this->word_size;
    int inside_position = item % this->word_size;

    this->bits[word_position] &= ~(1 << inside_position);
}

// place the union of src1 and src2 into dest;
// all of src1, src2, and dest must have the same size universe
void bitset_union(struct bitset *dest, struct bitset *src1,
                  struct bitset *src2)
{
    int size = src1->universe_size;
    for (int item = 0; item < size; item++)
    {
        if (bitset_lookup(src1, item) || bitset_lookup(src2, item))
            bitset_add(dest, item);
    }
}

// place the intersection of src1 and src2 into dest
// all of src1, src2, and dest must have the same size universe
void bitset_intersect(struct bitset *dest, struct bitset *src1,
                      struct bitset *src2)
{
    int size = src1->universe_size;
    for (int item = 0; item < size; item++)
    {
        if (bitset_lookup(src1, item) && bitset_lookup(src2, item))
            bitset_add(dest, item);
    }
}
