#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n, i, j, k, m;
    n = get_int("n: ");
    m = n-1;
    
    for(i = 1; i <= n; i++){
        
        for(k = 1; k <= m; k++)
        {
            printf(" ");
        }
        
        for(j = 1; j <= i; j++)
        {
            printf("#");
        }
        
        printf("  ");
        
        for(j = 1; j <= i; j++)
        {
            printf("#");
        }
        
        printf("\n");
        m--;
    }
}