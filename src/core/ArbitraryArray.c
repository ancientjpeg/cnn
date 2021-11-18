#include "cnn.h"
#include "stdarg.h"

ArbitraryArray newArbArray(int *d, size_t num_d)
{
  // add some num_d out of range setjmp handling here PLEASE
  if (num_d < 2) {
    printf("ERROR: Cannot instantiate 1-dimensional Arbitrary "
           "Array.");
    return ARB_ARR_ERR;
  }
  ArbitraryArray a;
  a.num_dims = num_d;
  a.dims     = (size_t *)malloc(a.num_dims * sizeof(size_t));
  for (int i = 0; i < a.num_dims; i++) {
    a.dims[i] = d[i]; // better than memcpy to account for int/short passed
  }
  a.data_size       = a.dims[0] * calc_block_size(&a, 0);
  a.data            = (float *)calloc(a.data_size, sizeof(float));

  a.dim_block_sizes = (size_t *)malloc(a.num_dims * sizeof(size_t));

  for (int i = 0; i < a.num_dims; i++) {
    a.dim_block_sizes[i] = calc_block_size(&a, i);
  }

  return a;
}

size_t calc_block_size(const ArbitraryArray *a, size_t dim)
{
  size_t lastDim = a->num_dims - 1;
  if (dim == lastDim)
    return 1;
  else if (dim < lastDim)
    return a->dims[dim + 1] * calc_block_size(a, dim + 1);
  return -1;
}

size_t calc_index(const ArbitraryArray *a, va_list args)
{
  size_t index = 0;
  for (int i = 0; i < a->num_dims; i++) {
    index += va_arg(args, int) * a->dim_block_sizes[i];
  }
  return index;
}

const float readElement(const ArbitraryArray *a, ...)
{
  va_list args;
  va_start(args, a);
  size_t index = calc_index(a, args);
  va_end(args);

  return a->data[index];
}

void writeToElement(const ArbitraryArray *a, double value, ...)
{
  // must take double as arg because of va_start fuckery that I don't understand
  va_list args;
  va_start(args, value);
  size_t index = calc_index(a, args);
  va_end(args);

  a->data[index] = (float)value;
}

float *getElementPointer(const ArbitraryArray *a, ...)
{
  // maybe set this so it can be passed args and used inside readElemnt
  // but i'm not going to do that right now
  va_list args;
  va_start(args, a);
  size_t index = calc_index(a, args);
  va_end(args);

  return a->data + index;
}

void printAll(const ArbitraryArray *a)
{
  for (size_t i = 0; i < a->data_size; i++) {
    printf("%f ", a->data[i]);
    size_t firstBlockSize = a->dim_block_sizes[a->num_dims - 2];
    if ((i % firstBlockSize) == firstBlockSize - 1)
      printf("\n");
  }
}

void freeArbArray(ArbitraryArray *a)
{
  free(a->dims);
  free(a->dim_block_sizes);
  free(a->data);
  return;
}