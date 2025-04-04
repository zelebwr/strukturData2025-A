# my own edit
def hash_function(value):
    sum_of_chars = 0
    for char in value:
        sum_of_chars += ord(char)
        # print("This is the character",char)
        # print(ord(char))
        # print(sum_of_chars)
        # print()
    return sum_of_chars % 10

def contains(name):
    index = hash_function(name)
    return my_hash_set[index] == name

# arrays
my_array = ['Pete', 'Jones', 'Lisa', 'Bob', 'Siri']
my_hash_set = [None,None,None,None,None,None,None,None,None,None]

print("'Bob' has hash code:",hash_function('Bob'))
my_hash_set[hash_function('Bob')] = 'Bob'
print("'Lisa' has hash code:",hash_function('Lisa'))
my_hash_set[hash_function('Lisa')] = 'Lisa'
print("'Jones' has hash code:",hash_function('Jones'))
my_hash_set[hash_function('Jones')] = 'Jones'
print("'Siri' has hash code:",hash_function('Siri'))
my_hash_set[hash_function('Siri')] = 'Siri'
print("'Pete' has hash code:",hash_function('Pete'),"\n")
my_hash_set[hash_function('Pete')] = 'Pete'


iteration = 0
for value in my_hash_set:
    print(iteration, '.', value)
    iteration += 1

# Check if 'Pete' is in the Hash Set
print("\n'Pete' is in the Hash Set:",contains('Pete'))


# the proper w3schools code
my_hash_set = [
    [None],
    ['Jones'],
    [None],
    ['Lisa'],
    [None],
    ['Bob'],
    [None],
    ['Siri'],
    ['Pete'],
    [None]
]

def hash_function(value):
    return sum(ord(char) for char in value) % 10
    
def add(value):
    index = hash_function(value)
    bucket = my_hash_set[index]
    if value not in bucket:
        bucket.append(value)
        
def contains(value):
    index = hash_function(value)
    bucket = my_hash_set[index]
    return value in bucket

add('Stuart')

print(my_hash_set)
print('Contains Stuart:',contains('Stuart'))

#Python