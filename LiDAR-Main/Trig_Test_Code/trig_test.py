from math import *



L1=50 #c
L2=120 #b
A = 11.125
c=L1
b=L2
#cosine law for a
a = sqrt(pow(b,2)+pow(c,2)-(2*b*c*(cos(radians(A)))))
#sine law for b
B = asin((L2/a)*sin(radians(11.125)))
B = degrees(B)
if (L2>L1):
    B = 180-B
C = 180-A-B
print(a)
print(L2)
print(L1)
print(A)
print(B)
print(C)