from math import *
def cos_law(b,c,A):
    return sqrt(pow(b,2)+pow(c,2)-(2*b*c*(cos(radians(A)))))

def sine_law(side1,side2,angle):
    return asin((side1/side2)*sin(radians(angle)))
def tri_stats(c,b,A):
    a = sqrt(pow(b,2)+pow(c,2)-(2*b*c*(cos(radians(A)))))
    #sine law for b
    B = sine_law(b,a,A)
    B = degrees(B)
    if (b>c):
        B = 180-B
    C = 180-A-B
    stat_list = [a,b,c,A,B,C]
    return stat_list