from cs50 import get_int

# Prompting for valid input
while True:
    n = get_int("Height: ")
    # Checking input range
    if n >= 1 and n <= 8:
        break
    
# Printing pyramid
for i in range(n):
    
    # Printing spaces
    for j in range(n - i - 1):
        print(" ", end="")
   
    # Printing bricks
    for j in range(i + 1):
        print("#", end="")
    print()