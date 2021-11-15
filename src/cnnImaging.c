#include "cnn.h"
#include "imago2.h"

void writeImageFromDataBlock(const float *raw_pix, int width, int height,
                             const char *outfile)
{
  struct img_pixmap holder;
  int               x = IMG_OPTARG(1, 2);
  img_init(&holder);
  if (img_set_pixels(&holder, width, height, IMG_FMT_GREY8, 0) == -1) {
    perror("Somehow failed to set up pixmap.\n");
    return;
  }

  // Can't just memcpy because we're doing float to byte conversions
  char mask = 0;
  mask      = ~mask;
  for (int w = 0; w < width; w++) {
    for (int h = 0; h < height; h++) {
      ((uint8_t *)holder.pixels)[w * height + h] =
          (uint8_t)raw_pix[w * height + h];
    }
  }

  if (img_save(&holder, outfile) == -1) {
    printf("Image save failure, image = %s\n", outfile);
  }
}