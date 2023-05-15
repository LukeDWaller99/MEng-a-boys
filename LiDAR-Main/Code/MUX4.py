"""
##Multiplexer control class

Jack Pendlebury 2023
"""
from machine import Pin

class MUX4:
    def __init__(self,control_pin_list):
        ##create control pins
        self.current_chan=0
        self.A= Pin(control_pin_list[0],Pin.OUT)
        self.B= Pin(control_pin_list[1],Pin.OUT)
        
    def select(self,pin_number):
        """
        Takes an integer input and selects that channel in the MUX.
        Must be value between 0 and 3
        """
        if (pin_number > 3) or (pin_number < 0):
            print("Invalid channel")
        else:
            if pin_number==0:
                self.A.off()
                self.B.off()
                self.current_chan = 0
            elif pin_number==1:
                self.A.on()
                self.B.off()
                self.current_chan = 1
            elif pin_number==2:
                self.A.off()
                self.B.on()
                self.current_chan = 2
            else:
                self.A.on()
                self.B.on()
                self.current_chan = 3
        
    def get_chan(self):
        """
        method to get current setting
        """
        return self.current_chan
    def advance(self):
        self.current_chan = (self.current_chan + 1) % 4
        self.select(self.current_chan)