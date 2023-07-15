#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    FILE *raw_file = fopen(argv[1], "r");
    if (raw_file == NULL)
    {
        printf("Could not open file\n");
        return 2;
    }

    uint8_t buffer[BLOCK_SIZE];
    char *filename = malloc(sizeof(char) * 8);
    int number = 0;
    FILE *image = NULL;

    while (fread(buffer, sizeof(uint8_t) * BLOCK_SIZE, 1, raw_file) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (number == 0)
            {
                sprintf(filename, "%03i.jpg", 0);
                image = fopen(filename, "w");
                number++;
            }
            else
            {
                fclose(image);
                sprintf(filename, "%03i.jpg", number++);
                image = fopen(filename, "w");
            }
        }
        if (image != NULL)
        {
            fwrite(buffer, sizeof(uint8_t) * BLOCK_SIZE, 1, image);
        }
    }

    free(filename);
    fclose(image);
    fclose(raw_file);

    return 0;
}