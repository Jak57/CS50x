#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Variables
    int n, count = 0, i, number = 0;
    char c;
    if (argc == 2)
    {
        // Length of string
        n = strlen(argv[1]);
        
        // Checking valid number
        for (i = 0; i < n; i++)
        {
            c = argv[1][i];
            if (c >= '0' && c <= '9')
            {
                continue;
            }
            else
            {
                count++;
                break;
            }
        }
        
        if (count == 0)
        {
            // Calculating the number
            int pow = 1;
            for (i = n - 1; i >= 0; i--)
            {
                c = argv[1][i];
                number += ((c - '0') * pow);
                pow *= 10;
            }
            
        }
        else
        {
            // Invalid key
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    else
    {
        // Invalid key
        printf("Usage: ./caesar key\n");
        return 1;
    }
    
    // Variables
    int id, k;
    
    // Taking input
    string s = get_string("plaintext: ");
    n = strlen(s);
    k = number;
    
    // Converting input text to cypher text
    for (i = 0; i < n; i++)
    {
        if (s[i] >= 'A' && s[i] <= 'Z')
        {
            id = (s[i] - 'A' + k) % 26;
            s[i] = id + 'A';
            
        }
        else if (s[i] >= 'a' && s[i] <= 'z')
        {
            id = (s[i] - 'a' + k) % 26;
            s[i] = id + 'a';
        }
    }
    
    // Printing solution
    printf("ciphertext: %s\n", s);
    
    return 0;
}