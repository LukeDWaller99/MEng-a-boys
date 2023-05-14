"""
Transistor bus class
Will take pointers to n gpio pins, and allow them to be toggled easily
"""
from machine import Pin

class Tran_Bus:
    tran_pins = []
    pin_args = [] #store for repr call
    current_enable = 0;
    def __init__(self, pin_list):
        """
        Constructor for the Transistor Bus.
        Args:
        - pin_list
        """
        print("Initialising Tran Bus")
        self.pin_args = pin_list
        print("Pin args: {}".format(
            pin_list))
        self.tran_pins += [Pin(pin_number, Pin.OUT) for pin_number in pin_list]
        print("Initialising complete. Initialised {} pins".format(
            len(self.tran_pins)))
    
    def __str__(self):
        return 'Tran Bus has ' + str(len(self.tran_pins)) + ' pins: ' + str(self.tran_pins) + ' Enabled: ' +self.current_enable
    
    def __repr__(self):
        return str(self.tran_pins)
    
    def all_off(self):
        for pin in self.tran_pins:
            pin.value(0)
        current_enable = None
            
    def all_on(self):
        for pin in self.tran_pins:
            pin.value(1)
            
    def get_len(self):
        return len(self.tran_pins)
            
    def enable(self,pin):
        self.all_off()
        self.current_enable = pin
        self.tran_pins[pin].value(1)
        
    def advance(self):
        if self.current_enable is None:
            self.enable(0)
            print("enabled zero")
        else:
            next_pin = (self.current_enable + 1) % len(self.tran_pins)
            self.enable(next_pin)