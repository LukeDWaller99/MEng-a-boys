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
        self.chan_limit = None
        
    def select(self,pin_number):
        """
        Takes an integer input and selects that channel in the MUX.
        Must be value between 0 and 3
        """
        if not self.chan_limit == None: #if a limit is in effect
            if pin_number>self.chan_limit-1:
                print("Invalid channel - limit breached")
                return
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
        try:
            int(self.chan_limit) # check if limit is none
        except:	#the limit is none, so substitue 4
            self.current_chan = (self.current_chan + 1) % 4
        else: #the limit is a number, proceed as normal
            self.current_chan = (self.current_chan + 1) % self.chan_limit
        finally:
            self.select(self.current_chan)
    def set_chan_limit(self,new_limit):
        """
        Method to limit the number of channels to less than four
        """
        if new_limit<4 and new_limit>0:
            self.chan_limit=new_limit
        else:
            print("invalid selection")
    def get_chan_limit(self):
        return self.chan_limit
    def clear_chan_limit(self):
        self.chan_limit = None