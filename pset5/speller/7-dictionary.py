# Set of words without duplicates
words = set()

# Checking if word in dictionary
def check(word):
    if word.lower() in words:
        return True
    else:
        return False

# define a function using def
def load(dictionary):
    file = open(dictionary, "r")

    # Iterating the file line by line
    for line in file:

        # Adding words in set
        # removing end line '\n' from string using rstrip()
        words.add(line.rstrip())

    file.close()
    return True

def size():
    return len(words)

def unload():
    return True