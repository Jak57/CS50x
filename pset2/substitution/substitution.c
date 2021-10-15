#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // Variables
    int n, i, count[30], id;
    char array[30], ch;
   
    // Initializing count array with 0
    for (i = 0; i < 30; i++)
    {
        count[i] = 0;
    }

    // Checking number of arguments
    if (argc == 2)
    {
        n = strlen(argv[1]);
        // Checking number of elements of string
        if (n != 26)
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }
        
       
        // Counting number of occurance of each character
        for (i = 0; i < n; i++)
        {
            ch = argv[1][i];
            
            // isupper() checks if a character is uppercase or not
            if (isupper(ch))
            {
                array[i] = ch;
                id = ch - 'A';
                count[id] += 1;
            }
            else if (islower(ch))
            {
                array[i] = ch;
                id = ch - 'a';
                count[id] += 1;
            }
            else
            {
                // Invalid key
                printf("Usage: ./substitution key\n");
                return 1;
            }
            
            
        }
        
        // Checking every alphabet occurs once or not
        int a = 0;
        for (i = 0; i < 26; i++)
        {
            
            if (count[i] != 1)
            {
                a++;
                printf("Usage: ./substitution key\n");
                return 1;
            }
        }
        
        // Taking input
        string s = get_string("plaintext: ");
        
        // Length of string
        int m = strlen(s);
    
        // Obtaining the encrypted text
        for (i = 0; i < m; i++)
        {
            if (isupper(s[i]))
            {
                id = s[i] - 'A';
                
                if (isupper(array[id]))
                {
                    s[i] = array[id];
                }
                else
                {
                    s[i] = array[id] - 'a' + 'A';
                }
                        
                    
            }
            else if (islower(s[i]))
            {
                id = s[i] - 'a';
                
                if (isupper(array[id]))
                {
                    s[i] = array[id] - 'A' + 'a';
                }
                else
                {
                    s[i] = array[id];
                }
                      
            }
            
        }
        
        // Printing solution
        printf("ciphertext: %s\n", s);
        
    }
    else
    {
        // Invalid key
        printf("Usage: ./substitution key\n");
        return 1;
    }
    
    return 0;
}