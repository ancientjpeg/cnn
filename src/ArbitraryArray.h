/******************************
 * - This is a heap-based implementation
 * - Each subarray has its own separate heap allocation
 * - A better future implementation may allocate the whole block at once
 *  - This would allow for dynamic access while also maintaining contiguity
 ******************************/
#ifndef ARBITRARY_ARRAY_H
#define ARBITRARY_ARRAY_H
#include "stdarg.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct ArbArr {
  size_t  num_dims;
  size_t *dims;
  size_t  data_size;
  size_t *dim_block_sizes;
  float  *data;

} ArbitraryArray;

#define ARB_ARR_ERR (ArbitraryArray){0, 0, 0, 0, 0};

ArbitraryArray newArbArray(int *d, size_t num_d);
void           freeArbArray(ArbitraryArray *a);
size_t         calc_block_size(const ArbitraryArray *a, size_t dim);
float        **gen_array_recursively(ArbitraryArray *a, size_t dim_num);
const float    readElement(const ArbitraryArray *a, ...);
void           writeToElement(const ArbitraryArray *a, double value, ...);
void           printAll(const ArbitraryArray *a);
void           freeArbArray(ArbitraryArray *a);
#endif