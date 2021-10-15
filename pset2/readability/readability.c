#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void)
{
    // Taking input
    string s = get_string("Text: ");
    
    // Variables
    double L, S, index;
    int ans;
   
    // Initialization
    int n = strlen(s), count1 = 0, count2 = 0, count3 = 0;
    
    for (int i = 0; i < n; i++)
    {
        // Counting total letters
        if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
        {
            count1++;
        }
        
        // Counting total words
        if (s[i] == ' ')
        {
            count2++;
        }
        
        // Counting total sentences
        if (s[i] == '.' || s[i] == '!' || s[i] == '?')
        {
            count3++;
        }
        
    }
    
    count2 += 1;
    
    L = (count1 * 100) / (1.0 * count2);
    S = (count3 * 100) / (1.0 * count2);
    
    
    // Calculating index
    index = 0.0588 * L - 0.296 * S - 15.8;
    
    // Rounding
    ans = (int) round(index);
    
    // Printing solution
    if (ans < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (ans >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", ans);
    }
}