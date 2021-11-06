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

#include "ArbitraryArray.h"
#include "activations.h"
#include "cnnImaging.h"
#include "cnn_tests.h"

typedef struct Network {
  ArbitraryArray *layers;
} Network;

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

#endif