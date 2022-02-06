//   nybble_array.h
//   David Gregg
//   December 2021

#ifndef NYBBLE_ARRAY_H
#define NYBBLE_ARRAY_H

struct nybble_array {
  unsigned char * data_bytes;   // contents of the array values
  int size_in_nybbles;          // number of nybbles in the array
  int size_in_bytes;            // number of bytes of raw nybble data
};

// create a new array of nybbles
struct nybble_array * nybble_array_new(int size);

// return the nybble value at position index
unsigned get_nybble_value(struct nybble_array * this, int index);

// set the nybble at position index to value
void set_nybble_value(struct nybble_array * this, int index, unsigned value);

// free the memory used by a nybble array
void nybble_array_free(struct nybble_array * this);

// given an array of unsigned integers with values 0 to 15 create
// a new nybble_array with the same values
struct nybble_array * unsigned_to_nybble_array(unsigned * array, int size);

// given an array of nybbles, create a new array of unsigned integers
// with the same values
unsigned * nybble_array_to_unsigned(struct nybble_array * this);

// print the raw byte content of the nybble array
void print_raw_bytes_nybble_array(struct nybble_array * this);

#endif
