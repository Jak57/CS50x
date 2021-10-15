#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int start, end, count = 0;
    
    //Prompt for start size
    
    do
    {
        start = get_int("start: ");
    }
    while (start < 9);
    
    //Prompt for end size
    
    do
    {
        end = get_int("end: ");
    }
    while (end < start);
    
    //Calculate number of years until we reach threshold
    
    while (start < end)
    {
        
        start = start + (start / 3) - (start / 4);
        count++;
    }
    
    //Print number of years
    
    printf("Years: %d\n", count);

    
}