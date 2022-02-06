//   nybble_array_main.c
//   David Gregg
//   December 2021

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "nybble_array.h"

// check new nybble array
int check_new_nybble_array() {
  int error = 0;
  struct nybble_array * array;

  array = nybble_array_new(20);
  //fprintf(stderr, "%p %p\n", array, array->data_bytes);
  if (array->size_in_nybbles != 20) {
    fprintf(stderr, "Error: size in nybbles should be 20, is actually %d\n",
	    array->size_in_nybbles);
    error = 1;
  }
  if (array->size_in_bytes != 10) {
    fprintf(stderr, "Error: size in nybbles should be 10, is actually %d\n",
	    array->size_in_bytes);
    error = 1;
  }
  for ( int i = 0; i < array->size_in_bytes; i++ ) {
    if ( array->data_bytes[i] != 0 ) {
      fprintf(stderr,
	      "Error: newly allocated byte should be 0, is actually%d\n",
	      array->data_bytes[i]);
    error = 1;
    }
  }
  nybble_array_free(array);
  return error;
}


int check_set_nybble_array() {
  int error = 0;
  struct nybble_array * array;

  array = nybble_array_new(20);

  set_nybble_value(array, 12, 13);

  int byte = array->data_bytes[6];

  // fprintf(stderr, "%d\n", byte);
  if ( (byte != 13) && (byte != (13 << 4)) ) {
      fprintf(stderr, "Error: inserted 13 into empty nybble array\n");
      fprintf(stderr, "data_bytes 6 should contain %d or %d \n", 13, 13 << 4);
      error = 1;
  }
  nybble_array_free(array);
  return error;
}

int check_get_nybble_array() {
  int error = 0;
  struct nybble_array * array;

  array = nybble_array_new(20);

  array->data_bytes[3] = 5 + (3 << 4);
  
  int value6 = get_nybble_value(array, 6);
  int value7 = get_nybble_value(array, 7);

  // depending on whether the student stores the upper nybble of the
  // byte first or second, we should get these values in different orders
  
  if ( (value6 == 5 && value7 == 3) || (value6 == 3 && value7 == 5) ) {
    error = 0;
  }
  else {
    fprintf(stderr, "Error: array value[6] and [7] should be\n");
    fprintf(stderr, "5 and 3 or 3 and 5 respectively. They are\n");
    fprintf(stderr, "actually %d and %d\n", value6, value7);
    error = 1;
  }
  
  nybble_array_free(array);
  return error;
}

int check_unsigned_to_nybble_array() {
  int error = 0;
  struct nybble_array * dest;

  unsigned source[14];

  for ( int i = 0; i < 14; i++ ) {
    source[i] = i;
  }

  dest = unsigned_to_nybble_array(source, 14);
  
  for ( int i = 0; i < 7; i++ ) {
    int value1 = (i * 2) + (((i * 2) + 1) << 4);
    int value2 = ((i * 2) + 1) + ((i * 2) << 4);
    if ( dest->data_bytes[i] != value1 && dest->data_bytes[i] != value2 ) {
      fprintf(stderr, "Error: array value[%d] and [%d] should be\n", i*2, (i*2)+1);
      fprintf(stderr, "%d and %d or %d and %d respectively.\n", i*2, (i*2)+1, (i*2)+1, i*2);
      fprintf(stderr, "They are actually %d and %d\n",
	      dest->data_bytes[i] & 0xF, dest->data_bytes[i] >> 4);
      error = 1;
    }
  }

  nybble_array_free(dest);
  return error;
}



int main() {
  // keep track of the number of errors encountered
  int nerrors = 0;

  if ( check_new_nybble_array() == 1 ) {
    fprintf(stderr, "Error: check new nybble array failed 1\n");
    nerrors++;
  }

  if ( check_set_nybble_array() == 1 ) {
    fprintf(stderr, "Error: check set nybble array failed 2\n");
    nerrors++;
  }

  if ( check_get_nybble_array() == 1 ) {
    fprintf(stderr, "Error: check set nybble array failed 3\n");
    nerrors++;
  }

  if ( check_unsigned_to_nybble_array() ) {
    fprintf(stderr, "Error: check unsigned to nybble array failed 4\n");
    nerrors++;
  }
  
  fprintf(stderr, "%d errors reported\n", nerrors);
  
  return 0;
}
