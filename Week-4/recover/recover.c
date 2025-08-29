#include <stdint.h>   // for unit8_t
#include <stdio.h>    // printf(), FILE, fread(), fwrite, etc.
#include <stdlib.h>   // malloc(), free()

typedef uint8_t BYTE;
int main(int argc, char *argv[])
{
  // checking command line argument
  if(argc != 2)
  {
    printf("Usage: ./recover FILE\n");
    return 1;
  }
  // opening file in read mode
  FILE *input_file = fopen(argv[1], "r");
  if(input_file == NULL)
  {
    printf("Could not open file");
    return 2;
  }
  BYTE buffer[512];

  // to track number of image
  int count_image = 0;

  // opening outputfile
  FILE *output_file = NULL;
  
  // allocate memory to filename
  char *filename = malloc(8 * sizeof(char));

  // reading blocks of 512 bytes
  while (fread(buffer, sizeof(BYTE), 512, input_file))
  {
    // checking if the bytes indicate for JPEG file
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] ==0xff && (buffer[3] & 0xf0)== 0xe0)
    {
      // closing file if new file opens
      if(output_file != NULL)
      {
        fclose(output_file);
      }
      // giving name to JPG file
      sprintf(filename, "%03i.jpg", count_image);

      // opening new file to enter next data
      output_file = fopen(filename, "w");

      count_image++;
    }

    // writing in output file
    if(output_file != NULL)
    {
      fwrite(buffer, sizeof(BYTE), 512, output_file);
    }
  }
  // freeing allocated memory
  free(filename);

  // closing opened files
  fclose(output_file);
  fclose(input_file);
}
