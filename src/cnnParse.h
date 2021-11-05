#ifndef CNN_PARSE_H
#define CNN_PARSE_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "sys/stat.h"

typedef struct Globals {
  int   *dimensions;
  size_t num_dims;
} Globals;

void    parse_dims(int *buffer, int num_dims, char *dims[]);
Globals cnn_parse(int argc, char *argv[]);
void    freeGlobals(Globals *g);

void    printBits(const void *b, size_t size);

off_t   getFileSize(const char *filepath);
off_t   readLabelsFromFile(const char *filepath, u_int32_t **buffer);
void    readDataFromFile(const char *filepath, ArbitraryArray *data_buffer,
                         size_t num_leading_ints);
void    reverseBufferEndianness(void *buf, size_t size);
void    reverseDatasetHeaders(size_t num_leading_ints, const char *inPath,
                              const char *outPath);

#endif