// #define PY_SSIZE_T_CLEAN
// #include <Python.h>

#include "cnn_tests.h"

void testArbArr(int argc, char *argv[])
{
  Globals globals = cnn_parse(argc, argv);

  for (int i = 0; i < globals.num_dims; i++) {
    printf("arg%i: %15i\n", i, globals.dimensions[i]);
  }

  int            dims[3] = {3, 3};
  ArbitraryArray arr     = newArbArray(dims, sizeof(dims) / sizeof(int));
  printf("datacount = %lu\n", arr.data_size);
  writeToElement(&arr, 4.72, 1, 1, 1);
  printAll(&arr);
  freeArbArray(&arr);
  freeGlobals(&globals);
}

void writeRandImgBytes()
{
  FILE *dat = fopen("output.dat", "wb");
  if (dat) {
    unsigned char pixels[28 * 28] = {};
    for (int i = 0; i < 28 * 28; i++) {
      pixels[i] = i % 256;
      printf("pixels[%i]: %i\n", i, pixels[i]);
    }
    fwrite(pixels, sizeof(unsigned char), sizeof(pixels), dat);
  }
  fclose(dat);
}

void testFileConverter()
{
  reverseDatasetHeaders(4, "mnist/mnist_images", "mnist/mnist_images_rev");
  reverseDatasetHeaders(4, "mnist/mnist_images_test",
                        "mnist/mnist_images_test_rev");
  reverseDatasetHeaders(2, "mnist/mnist_labels", "mnist/mnist_labels_rev");
  reverseDatasetHeaders(2, "mnist/mnist_labels_test",
                        "mnist/mnist_labels_test_rev");

  FILE *file  = fopen("mnist/mnist_images", "rb");
  FILE *after = fopen("mnist_images_rev", "rb");
  if (!file || !after) {
    fclose(file);
    fclose(after);
    exit(-1);
  }
  for (int i = 0; i < 10; i++) {
    uint32_t temp, temp2;
    fread(&temp, sizeof(uint32_t), 1, file);
    fread(&temp2, sizeof(uint32_t), 1, after);
    // reverseBufferEndianness(&temp2, sizeof(uint32_t));
    if (temp > 0 && temp2 > 0) {
      printf("\n\n%i\n\n", i);
      printf("orig\n");
      printf("temp1=%u\n", temp);
      printBits(&temp, 4);
      printf("rev\n");
      printf("temp2=%u\n", temp2);
      printBits(&temp2, 4);
    }
  }
  fclose(file);
  fclose(after);
}
