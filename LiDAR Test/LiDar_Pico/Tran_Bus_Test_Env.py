"""
Tran Bus test enviroment
"""
#import the tran bus
from Tran_Bus import *

#dummy pin list
dummy_pin_list = [18,19,20,21]

bus = Tran_Bus(dummy_pin_list)
print("Done.")
print(bus)