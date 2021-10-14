#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
 
int main(int argc, char *argv[])
{
    // Checks for two arguments
    if (argc != 2)
    {
        printf("Only one argument allowed\n");
        return 1;
    }
    
    // Opening file
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Couldn't open file\n");
        return 1;
    }
    
    
    // Variables
    int count = 0;
    int index = 0;
    
    BYTE buffer[512];
    char filename[100000];
    
    // Image file name
    sprintf(filename, "%03i.jpg", index);
    index++;
    
    // Opening output file
    FILE *output = fopen(filename, "w");
    if (output == NULL)
    {
        printf("Couldn't open file\n");
        return 1;
         
    }
    
    
    // Reading from input file to output file
    while (fread(buffer, sizeof(BYTE), 512, input))
    {
        // Checking signature of jpg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xe0) == 0xe0))
        {
            fwrite(buffer, sizeof(BYTE), 512, output);
            break;
            
        }
        
    }
    
    // Reading from input file to output file
    while (fread(buffer, sizeof(BYTE), 512, input))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xe0) == 0xe0))
        {
            count++;
            
        }
        
        if (count == 0)
        {
            fwrite(buffer, sizeof(BYTE), 512, output);
        }
        else
        {
            // Closing output file
            fclose(output);
            count = 0;
            
            sprintf(filename, "%03i.jpg", index);
            index++;
            
            // Opening output file for writing
            FILE *output1 = fopen(filename, "w");
            if (output1 == NULL)
            {
                printf("Couldn't open file\n");
                return 1;
         
            }
            
            
            // Assigning pointer
            output = output1;
            fwrite(buffer, sizeof(BYTE), 512, output);
            
        }
        
    }
    
    // Closing file
    fclose(output);
    fclose(input);
    
    
}