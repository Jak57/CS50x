#include <cs50.h>
#include <stdio.h>
#include <math.h>

float dollar;

int main(void)
{
    // Variables
    int cent, count = 0, money[5], i, tmp;
    
    // Assigning values in array
    money[1] = 25;
    money[2] = 10;
    money[3] = 5; 
    money[4] = 1;
    
    // Taking valid input
    do
    {
        dollar = get_float("Change owed: ");
    }
    while (dollar < 0);
    
    // Rounding cents
    cent = round(dollar * 100);
    
    // Calculating total coins needed
    for (i = 1; i <= 4; i++)
    {
        if (cent >= money[i])
        {
            tmp = cent / money[i];
            count += (cent / money[i]);
            cent -= (tmp * money[i]);
        }
    }
    
    printf("%d\n", count);
    
    
    
}