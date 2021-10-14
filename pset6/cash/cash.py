from cs50 import get_float

# Prompting user for valid input
while True:
    dollar = get_float("Change owed: ")
    if dollar >= 0:
        break
    
# Rounding cents to nearest integer
cent = round(dollar * 100)

# List of coins
money = []
money.append(25)
money.append(10)
money.append(5)
money.append(1)

# Iterating through list and counting total coin needed
count = 0
for i in range(4):
    
    if cent >= money[i]:
        tmp = int(cent / money[i])
        count += tmp
        cent -= (tmp * money[i])

# Printing solution   
print(count)