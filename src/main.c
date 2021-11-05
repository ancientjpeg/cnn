#include "cnn_tests.h"
#include "imago2.h"

int main(int argc, char *argv[])
{
  int            dims[3] = {60000, 28, 28};
  ArbitraryArray a       = newArbArray(dims, 3);
  readDataFromFile("mnist/mnist_images_rev", &a, 4);
  printf("[");
  for (int i = 0; i < (28 * 28); i++) {
    if (i % 28 == 0)
      printf("[");
    printf("%.1f,", readElement(&a, 0, i / 28, i % 28));
    if (i % 28 == 27)
      printf("],");
  }
  printf("]\n");
  return 0;
}