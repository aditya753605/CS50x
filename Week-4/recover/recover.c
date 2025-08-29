#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;
int main(int argc, char *argv[])
{
  if(argc != 2)
  {
    printf("Usage: ./recover FILE\n");
    return 1;
  }
  FILE *input_file = fopen(argv[1], "r");
  if(input_file == NULL)
  {
    printf("Could not open file");
    return 2;
  }
  BYTE buffer[512];
  int count_image = 0;
  FILE *output_file = NULL;
  char *filename = malloc(8 * sizeof(char));
  while (fread(buffer, sizeof(BYTE), 512, input_file))
  {
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] ==0xff && (buffer[3] & 0xf0)== 0xe0)
    {
      if(output_file != NULL)
      {
        fclose(output_file);
      }
      sprintf(filename, "%03i.jpg", count_image);

      output_file = fopen(filename, "w");

      count_image++;
    }
    if(output_file != NULL)
    {
      fwrite(buffer, sizeof(BYTE), 512, output_file);
    }
  }
  free(filename);

  fclose(output_file);
  fclose(input_file);
}
