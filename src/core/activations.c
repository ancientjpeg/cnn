#include "cnn.h"

float sigmoid(float x) { return 1.f / (1.f + exp(x)); }

float derivSigmoid(float x) { return sigmoid(x) * (1 - sigmoid(x)); }

float LeakyReLu(float x)
{
  if (x < 0.f)
    return 0.01f * x;
  return x;
}

float derivLeakyReLu(float x)
{
  if (x < 0.f)
    return -0.01f;
  return 1.f;
}