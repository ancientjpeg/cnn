#include "cnn.h"

Network newNetwork(int layer_count, int *layer_dimensions)
{
  Network n;

  return n;
}

Layer *getLayerPointer(Network *n, int l)
{
  if (l > n->num_layers)
    return NULL;
  return n->layers + l;
}