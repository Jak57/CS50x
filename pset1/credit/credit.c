#include<cs50.h>
#include<stdio.h>

int main()
{
    //Variables
    
    long num, tem1, tem2, tem3, ans1 = 0, ans2 = 0, n, cnt = 0, a;
    
    //Taking Number
    
    num = get_long("Number: ");
    
    //Testing
    
    while (num > 0)
    {
        tem1 = num % 10;
        ans1 += tem1;
        num /= 10;
        
        //Counting digits
        
        cnt++;
        
        if (num == 0)
        {
            continue;
        }
            
        
        tem2 = num % 10;
        n = 2 * tem2;
        
        while (n > 0)
        {
            tem3 = n % 10;
            n /= 10;
            ans2 += tem3;
        }
        
        num /= 10;
        cnt++;
        
    }
    
    a = ans1 + ans2;
    
    //Printing Solution
    
    if (a % 10 == 0)
    {
        //Checking for American Express
        
        if (cnt == 15 && (tem1 == 3) && (tem2 == 4 || tem2 == 7))
        {
            printf("AMEX\n");
        }
        
        //Checking for MasterCard
        
        else if (cnt == 16 && (tem2 == 5) && (tem1 == 1 || tem1 == 2 || tem1 == 3 || tem1 == 4 || tem1 == 5))
        {
            printf("MASTERCARD\n");
        }
        
        //Checking for Visa
        
        else if ((cnt == 16 && tem2 == 4) || (cnt == 13 || tem1 == 4))
        {
            printf("VISA\n");
        }
        
        //Invalid
        
        else
        {
            printf("INVALID\n");
        }
        
    }
    else
    {
        printf("INVALID\n");
    }
    
    
}