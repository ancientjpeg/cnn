#ifndef CNN_H
#define CNN_H

#include "ArbitraryArray.h"
#include "activations.h"
#include "cnnImaging.h"
#include "cnnParse.h"
#include "cnn_tests.h"

#include "math.h"

typedef struct Network {
  ArbitraryArray *layers;
} Network;

#endif