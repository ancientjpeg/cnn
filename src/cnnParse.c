#include "cnn.h"

void parse_dims(int *buffer, int num_dims, char *dims[])
{
  for (size_t i = 0; i < num_dims; i++) {
    int arg = atoi(dims[i]);
    if (arg == 0) {
      printf("Error: dimensional argument was 0 or unparsable\n");
      exit(1);
    }
    buffer[i] = arg;
  }
}

Globals cnn_parse(int argc, char *argv[])
{
  Globals temp         = {};
  char    options[]    = {'h', 'v'};
  char    args[]       = {'d'};
  char  **numeric_args = (char **)calloc(argc - 1, sizeof(char *));
  memcpy(numeric_args, argv + 1, (argc - 1) * sizeof(char *));
  temp.num_dims   = argc - 1;
  temp.dimensions = calloc(temp.num_dims, sizeof(int));
  parse_dims(temp.dimensions, temp.num_dims, numeric_args);

  return temp;
}

void freeGlobals(Globals *g) { free(g->dimensions); }

// this is all the shit for big-endian parsing

void printBits(const void *b, size_t size)
{
  const char *bytes = (char *)b;
  for (size_t i = 0; i < size; i++) {
    for (int j = 7; j >= 0; j--) {
      uint64_t mask = (1ULL << (j));
      printf("%c", (bytes[i] & mask ? '1' : '0'));
    }
    printf("\n");
  }
  printf("\n");
}

off_t getFileSize(const char *filepath)
{
  struct stat buffer;
  stat(filepath, &buffer);
  return buffer.st_size;
}

off_t readLabelsFromFile(const char *filepath, uint32_t **buffer)
{
  // return the labels
  FILE *file = fopen(filepath, "rb");
  if (!file) {
    fclose(file);
    return 0;
  }
  off_t fileSize = getFileSize(filepath);

  for (off_t byte = 0; byte < fileSize; byte++) {
    fseek(file, 1, SEEK_CUR);
  }

  return fileSize;
}

void reverseBufferEndianness(void *buf, size_t size)
{
  char *buffer = (char *)buf;

  for (int i = 0; i < (size / 2); i++) {
    size_t end  = size - 1 - i;
    char   temp = buffer[i];
    buffer[i]   = buffer[end];
    buffer[end] = temp;
  }
}

void reverseDatasetHeaders(size_t num_leading_ints, const char *inPath,
                           const char *outPath)
{
  FILE *infile  = fopen(inPath, "rb");
  FILE *outfile = fopen(outPath, "wb");
  if (!infile || !outfile) {
    printf("Input or output file failed to open. Sorry I didn't differentiate "
           "lol\n");
    fclose(infile);
    fclose(outfile);
    return;
  }

  // orient the leading big-endian 32-bit floats;
  for (off_t header = 0; header < num_leading_ints; header++) {
    u_int32_t temp;
    fread(&temp, 4, 1, infile);
    reverseBufferEndianness(&temp, 4);
    fwrite(&temp, 4, 1, outfile);
  }
  off_t   buffer_size = 1 << 12;
  uint8_t write_buffer[buffer_size];
  size_t  bytes_read;

  while ((bytes_read = fread(write_buffer, 1, buffer_size, infile)) ==
         buffer_size) {
    fwrite(write_buffer, 1, buffer_size, outfile);
  }
  fwrite(write_buffer, bytes_read, 1, outfile);
  fclose(infile);
  fclose(outfile);
}

void readDataFromFile(const char *filepath, ArbitraryArray *data_buffer,
                      size_t num_leading_ints)
{
  // return an arbitrary array, formatted properly??? i GUESS?????
  FILE *file = fopen(filepath, "rb");
  if (!file) {
    printf("You fucked up the file while trying to read its data.\n");
    fclose(file);
    exit(-1);
  }
  off_t fileSize = getFileSize(filepath) - num_leading_ints * 4;
  if (fileSize != data_buffer->data_size) {
    printf("FATAL ERROR: array size is not equal to projected dataset size.\n");
    exit(-5);
  }

  fseek(file, num_leading_ints * 4, SEEK_SET);

  size_t  block_size = 1 << 13;
  uint8_t temp[block_size];
  size_t  bytes_read = block_size;
  size_t  blocks_req = fileSize / block_size + 1;
  for (size_t i = 0; i <= blocks_req; i++) {
    bytes_read = fread(temp, 1, block_size, file);
    for (size_t j = 0; j < block_size; j++) {
      // printf("%lu\n", j);
      if (bytes_read < block_size && j >= bytes_read)
        break;
      data_buffer->data[i * block_size + j] = temp[j];
    }
  }
}
