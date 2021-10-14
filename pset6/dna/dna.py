import csv
import sys

# Checking valid input
if len(sys.argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    sys.exit(1)

# Opening csv file and reading
file = open(sys.argv[1], "r")
reader = csv.DictReader(file)

# Lists
strs = []
dict_list = []

# Adding element to dictionary
for dictionary in reader:
    dict_list.append(dictionary)

# Storing STRS  
for row in dict_list:
    for key in row:
        if key != "name":
            strs.append(key)
    break

# Count total STRS
total = len(strs)
count = 0
ans = 0

# Opening text file and reading
text_file = open(sys.argv[2], "r")
dna = text_file.read()

# Length of text file
dna_length = len(dna)
count_strs = []

array = []   

# Iterating through the text file
for i in range(total):
    s = strs[i]
    strs_length = len(s)
    limit = dna_length - strs_length + 1 
        
    j = 0
    count = 0
    ans = 0
    
    # Checking STRS and counting consequitive occurances
    while j < limit:
        k = j
        
        # Check for matching
        while (s == dna[k: k + strs_length]):
            count += 1
            k += strs_length
            ans = max(ans, count)
            
        j += 1
        ans = max(ans, count)
        count = 0
    
    # Storing occurances  
    array.append(ans)
    
count = 0

# Iterating through the dictionary
for dic in dict_list:
    tmp = []
    
    # Storing STRS count
    for key in dic:
        if key == "name":
            name = dic[key]
        else:
            tmp.append(int(dic[key]))
    
    # Checking for matching
    if tmp == array:
        
        # Print solution
        print(name)
        count += 1
        break
    

if count == 0:
    print("No match")

# Closing file
file.close()
text_file.close()
sys.exit(0)