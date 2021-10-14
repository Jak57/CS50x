from cs50 import get_int

# Variables
ans1 = 0
ans2 = 0
cnt = 0

# Taking number
num = get_int("Number: ")

# Testing
while num > 0:
    tem1 = num % 10
    ans1 += tem1
    num = int(num / 10)

    cnt += 1
    if num == 0:
        continue

    tem2 = num % 10
    n = 2 * tem2

    while n > 0:
        tem3 = n % 10
        n = int(n / 10)
        ans2 += tem3

    num = int(num / 10)
    
    # Counting digits
    cnt += 1

a = ans1 + ans2

# Printing Solution
    
if (a % 10 == 0):
    # Checking for American Express
        
    if (cnt == 15 and (tem1 == 3) and (tem2 == 4 or tem2 == 7)):
        print("AMEX")
    
    # Checking for MasterCard
        
    elif (cnt == 16 and (tem2 == 5) and (tem1 == 1 or tem1 == 2 or tem1 == 3 or tem1 == 4 or tem1 == 5)):
        print("MASTERCARD")
        
    # Checking for Visa
        
    elif ((cnt == 16 and tem2 == 4) or (cnt == 13 or tem1 == 4)):
        print("VISA")
        
    # Invalid
        
    else:
        print("INVALID")
        
else:
    print("INVALID")
