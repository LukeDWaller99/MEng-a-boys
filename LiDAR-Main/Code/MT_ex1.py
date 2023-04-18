#Basic multi thread example
 
import time
import _thread
from machine import Pin
internal_led = Pin(25, Pin.OUT)
def core0_thread():
    counter = 0
    while True:
        print(counter)
        counter += 2
        time.sleep(1)
 
 
def core1_thread(pin_in):
    int_led = 0
    while True:
        int_led = int_led ^ 1
        pin_in.value(int_led)
        time.sleep(1)
 
 
second_thread = _thread.start_new_thread(core1_thread, ([internal_led]))
 
core0_thread()