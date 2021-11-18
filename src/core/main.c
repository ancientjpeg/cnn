#include "cnn.h"
#include "imago2.h"

#include "../metal/libcnnmetal.h"

int main(int argc, char *argv[])
{
  // int            dims[3] = {60000, 28, 28};
  // ArbitraryArray a       = newArbArray(dims, 3);
  // readDataFromFile(&a, "mnist/mnist_images_rev", 4);
  // const float *image = getElementPointer(&a, 10534, 0, 0);

  // writeImageFromDataBlock(image, 28, 28, "im/out.png");
  system("clear");
  printf("yeah...\n");
  spawnGPU();
  return 0;
}