"""
LiDAR Interrupt Handler

Creates and handles interrupts for the VL53L5CX
"""
from machine import Pin

class LiDAR_Handler:
    
    
    #constructor
    def __init__(self,int_pin):
        interrupt_pin = Pin(int_pin, Pin.IN) #assign pin
        interrupt_pin.irq(trigger=Pin.IRQ_RISING, handler=self.callback)
        self.status_flag=0
        
    def callback(self,sensor):
        self.status_flag = 1
    def clear(self):
        self.status_flag = 0
    def get_flag(self):
        return self.status_flag