#ifndef CNN_H
#define CNN_H

#include "ArbitraryArray.h"
#include "activations.h"
#include "cnnParse.h"

#include "math.h"

typedef struct Network {
  ArbitraryArray *layers;
} Network;

#endif