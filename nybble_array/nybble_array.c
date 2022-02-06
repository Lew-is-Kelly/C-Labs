//   nybble_array.c
//   David Gregg
//   December 2021

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "nybble_array.h"

// create a new array of nybbles with space for "size"
// nybbles and initialize the values of the array to zero
struct nybble_array *nybble_array_new(int size)
{
    //allocate space for the new array
    struct nybble_array *array = malloc(sizeof(struct nybble_array));

    //set the size variables of the new array
    array->size_in_nybbles = size;
    array->size_in_bytes = size / 2;

    //make the array within that stores the data
    unsigned char *data = malloc(sizeof(unsigned char) * array->size_in_bytes);

    //set it all to 0
    for (int i = 0; i < array->size_in_bytes; i++)
    {
        data[i] = 0;
    }

    //assigning the data to the structure
    array->data_bytes = data;

    return array;
}

// return the nybble value at position index
unsigned get_nybble_value(struct nybble_array *this, int index)
{
    int value;
    //if the index is even the value will be the last 4 bits at the index over 2 (index/2)
    if (index % 2 == 0)
    {
        //and the value with 15 (00001111) to get just the last 4 bits of the byte
        value = this->data_bytes[index / 2] >> 4;
    }
    else
    {
        value = this->data_bytes[index / 2] & 15;
    }

    //otherwise, the value will be the first 4 bits of a byte at the index over 2 (index/2) so shift them over
    return value;
}

// set the nybble at position index to value
void set_nybble_value(struct nybble_array *this, int index, unsigned value)
{
    //if the index is even the value will be the 4 most significant bits of the byte at index / 2
    if (index % 2 == 0)
    {
        //clears existing value
        this->data_bytes[index / 2] = this->data_bytes[index / 2] & 15;

        value = value << 4;
        this->data_bytes[index / 2] |= value;
    }
    else    //otherwise, the index is odd and the value is the 4 least significant bits
    {
        //clears existing value
        this->data_bytes[index / 2] = this->data_bytes[index / 2] & 240;

        this->data_bytes[index / 2] |= value;
    }
}

// free the memory used by a nybble array
void nybble_array_free(struct nybble_array *this)
{
    free(this);
}

// given an array of unsigned integers with values 0 to 15 create
// a new nybble_array with the same values
struct nybble_array *unsigned_to_nybble_array(unsigned *array, int size)
{
    //create the array we are going to return
    struct nybble_array *nybble_array = nybble_array_new(size);

    //set each nybble by calling set_nybble_value function
    for(int i = 0; i < nybble_array->size_in_nybbles; i++)
    {
        set_nybble_value(nybble_array, i, array[i]);
    }

    return nybble_array;
}

// given an array of nybbles, create a new array of unsigned integers
// with the same values
unsigned *nybble_array_to_unsigned(struct nybble_array *this)
{
    //create array we are going to return
    unsigned *array = malloc(sizeof(unsigned) * this->size_in_nybbles);

    //get each value from the nybble_array and set each item by using get_nybble_value
    for (int i = 0; i < this->size_in_nybbles; i++)
    {
        array[i] = get_nybble_value(this, i);
    }

    return array;
}

// print the raw byte content of the nybble array
void print_raw_bytes_nybble_array(struct nybble_array *this)
{
    printf("\n");
    for (int i = 0; i < this->size_in_bytes; i++)
    {
        printf("%x ", this->data_bytes[i]);
    }
    printf("\n");
}