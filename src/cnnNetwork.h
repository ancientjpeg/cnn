#ifndef CNN_NETWORK_H
#define CNN_NETWORK_H

#include "cnn.h"

typedef struct Layer {
  ArbitraryArray *weights;
  ArbitraryArray *biases;
  ArbitraryArray *zValues;
  ArbitraryArray *activations;
  ArbitraryArray *errors;
} Layer;

#endif