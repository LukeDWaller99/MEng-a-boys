from LiDAR_Trig import *
import time

L1=120 #c
L2=90 #b
A = 11.125
stat_list = tri_stats(L1,L2,A)
print(stat_list)
t_sta = time.ticks_ms()
iterations=100000
for x in range(iterations):
    stat_list = tri_stats(L1,L2,A)
t_end = time.ticks_ms()
duration = t_end - t_sta
print(duration)
avg_duration = duration/iterations
print(avg_duration)