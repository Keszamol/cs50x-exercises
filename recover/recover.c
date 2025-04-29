#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 512
#define JPEG_HEADER_SIZE 4

int main(int argc, char *argv[])
{
   
    if (argc != 2)
    {
        printf("Usage: ./recover card.raw\n");
        return 1;
    }


    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {

        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    unsigned char buffer[BLOCK_SIZE];
    int file_count = 0;
    FILE *img = NULL;

    while (fread(buffer, sizeof(unsigned char), BLOCK_SIZE, card) == BLOCK_SIZE)
    {

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] >= 0xe0 && buffer[3] <= 0xef))
        {

            if (img != NULL)
            {
                fclose(img);
            }


            char filename[8];
            sprintf(filename, "%03i.jpg", file_count);
            img = fopen(filename, "w");


            if (img == NULL)
            {
                printf("Could not create file %s.\n", filename);
                fclose(card);
                return 2;
            }

            file_count++;
        }


        if (img != NULL)
        {
            fwrite(buffer, sizeof(unsigned char), BLOCK_SIZE, img);
        }
    }


    if (file_count == 0)
    {
        printf("No JPEG files found.\n");
        fclose(card);
        return 1;
    }


    if (img != NULL)
    {
        fclose(img);
    }
    fclose(card);

    return 0;
}
