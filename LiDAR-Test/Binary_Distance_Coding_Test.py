'''
Binary output test
'''

import random

def generate_number_list(n, a, b):
    if a >= b:
        raise ValueError("Lower threshold (a) must be less than upper threshold (b).")
    
    number_list = []
    for _ in range(n):
        number = random.uniform(a, b)
        number_list.append(round(number,1))
    
    return number_list

#distances = [2.3, 4.5, 3.2, 1.8, 5.1, 4.7, 2.5, 3.9]
distances = [3.8, 2.9, 4.2, 3.4, 1.5, 5.1, 3.7, 4.9]
thresholds = [3.0, 4.0, 5.0]

def compare_thresholds(distances, thresholds):
    result = 0

    for i in range(0, len(distances), 2):
        side1 = distances[i]
        side2 = distances[i + 1]
        binary = 0
        for threshold in thresholds:
            if side1 > threshold and side2 > threshold:
                binary += 0
            else:
                binary += 1
        print(f"{side1} {side2} = {format(binary,'#04b')}")
        result += binary<<len(distances)-i-2

    return format(result,'#010b')

for i in range (10):
    gen_list=generate_number_list(8,2.5,5.5)
    print(gen_list)
    print(compare_thresholds(gen_list,thresholds))
    print("\n")