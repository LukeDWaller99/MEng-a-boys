"""
Tran Bus test enviroment
"""
#import the tran bus
from Tran_Bus import *
import time

#dummy pin list
dummy_pin_list = [11,12,13]

bus = Tran_Bus(dummy_pin_list)
print("Done.")
print(bus)
while True:
    bus.all_on()
    time.sleep(1)
    bus.all_off()
    time.sleep(1)
    for x in range(3):
        bus.enable(x)
        time.sleep(1)