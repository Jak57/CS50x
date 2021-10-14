#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int Height, i, j, k, m;
    
    //Taking Height
    
    do
    {
        Height = get_int("Height: ");
    }
    while (Height < 1 || Height > 8);
    
    m = Height - 1;
    
    //Printing Pyramids
    
    for (i = 1; i <= Height; i++)
    {
        // Printing Left Pyramid
        
        for (k = 1; k <= m; k++)
        {
            printf(" ");
        }
        
        for (j = 1; j <= i; j++)
        {
            printf("#");
        }
        
        printf("  ");
        
        // Printing Right Pyramid
        
        for (j = 1; j <= i; j++)
        {
            printf("#");
        }
        
        printf("\n");
        m--;
    }
}