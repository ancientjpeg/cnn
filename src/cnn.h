#ifndef CNN_H
#define CNN_H

#include "imago2.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct Globals {
  int   *dimensions;
  size_t num_dims;
} Globals;

#include "activations.h"
#include "cnnImaging.h"
#include "cnnNetwork.h"

/*==================================================
=           ArbitraryArray Declarations            =
==================================================*/

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
float         *getElementPointer(const ArbitraryArray *a, ...);
void           writeToElement(const ArbitraryArray *a, double value, ...);
void           printAll(const ArbitraryArray *a);
void           freeArbArray(ArbitraryArray *a);

/*==================================================
=             cnnParse Declarations                =
==================================================*/

void    printBits(const void *b, size_t size);

Globals cnn_parse(int argc, char *argv[]);
void    freeGlobals(Globals *g);

off_t   getFileSize(const char *filepath);
void readLabelsFromFile(const char *filepath, uint32_t **buffer, int numLabels);
void readDataFromFile(ArbitraryArray *data_buffer, const char *filepath,
                      size_t num_leading_ints);
void reverseBufferEndianness(void *buf, size_t size);
void reverseDatasetHeaders(size_t num_leading_ints, const char *inPath,
                           const char *outPath);

/*==================================================
=             cnnNetwork Declarations              =
==================================================*/

typedef struct Network {
  ArbitraryArray *layers;
} Network;

float sigmoid(float x);
float LeakyReLu(float x);

#endif