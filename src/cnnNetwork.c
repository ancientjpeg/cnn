#include "cnn.h"

typedef struct Layer {
  ArbitraryArray *weights;
  ArbitraryArray *biases;
  ArbitraryArray *zValues;
  ArbitraryArray *activations;
  ArbitraryArray *errors;
} Layer;