#include "activations.h"

float sigmoid(float x) { return 1.f / (1.f + exp(x)); }

float LeakyReLu(float x)
{
  if (x < 0.f)
    return 0.01 * x;
  return x;
}