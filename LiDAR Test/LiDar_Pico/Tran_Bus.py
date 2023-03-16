"""
Transistor bus class
Will take pointers to six gpio pins, and allow them to be toggled easily
"""
from machine import Pin

class Tran_Bus:
    def __init__(self, pin_list):
        """
        Constructor for the Transistor Bus.
        Args:
        - pin_list
        """
        print("Initialising Tran Bus")
        print("Pin args: {}".format(
            pin_list))
        self.tran_pins += [Pin(pin_number, Pin.OUT) for pin_number in pin_list]
        print("Initialising complete. Initialised {} pins".format(
            len(self.tran_pins)))
        