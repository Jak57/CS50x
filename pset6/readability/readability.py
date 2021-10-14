from cs50 import get_string

# Taking input
s = get_string("Text: ")

# Variables
n = len(s)
count1 = 0
count2 = 0
count3 = 0

# Iterating through the string
for i in range(n):
    
    # Counting total letters
    if ((s[i] >= 'a' and s[i] <= 'z') or (s[i] >= 'A' and s[i] <= 'Z')):
        count1 += 1
        
    # Counting total words   
    if (s[i] == ' '):
        count2 += 1
    
    # Counting total sentences
    if (s[i] == '.' or s[i] == '!' or s[i] == '?'):
        count3 += 1

count2 += 1
L = (count1 * 100) / count2
S = (count3 * 100) / count2

# Calculating index
index = 0.0588 * L - 0.296 * S - 15.8

# Rounding
ans = int(round(index))

# Printing solution
if ans < 1:
    print("Before Grade 1")

elif ans >= 16:
    print("Grade 16+")
else:
    print(f"Grade {ans}")
    