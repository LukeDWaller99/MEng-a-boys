import pimoroni_i2c
import breakout_vl53l5cx
from machine import Pin,UART
import time
import micropython
import gc
import _thread

#this is normally bad, but it's my module so meh
#MAKE SURE THIS FILE IS PRESENT ON THE BOARD FIRST! IF IT CAN'T FIND IT, THAT'S WHY!
from L_Proc import *
from Tran_Bus import *
from LiDAR_Handler import *
from LiDAR_Interface import *
#LED pins, for debugging only
led1 = Pin(13,Pin.OUT)
led2 = Pin(12, Pin.OUT)
led3 = Pin(11, Pin.OUT)
internal_led = Pin(25, Pin.OUT)
int_led = 0;

#lidar pins
lidar_control_pins = [18,19]
int_pins = [16,17]

#UART TIME
uart = UART(0, baudrate = 115200, tx=Pin(0), rx=Pin(1))
uart.init(bits=8, parity=None, stop=2)
led = Pin ("LED",Pin.OUT)
num=177

#kick thread off
interface = LiDAR_Interface(lidar_control_pins,int_pins)
def thread2():
    while True:
        #wait until data is requested
        if uart.any():
            uart_in_data=uart.readline()
            print(uart_in_data)
            if uart_in_data==b's':
            #if uart_in_data.find(b's'):
        #uart.write(str(num))
        #print("interface reading: ")
        #print(interface.avg_reading)
                #uart.write(str(interface.avg_readings[0]))
                uart.write(f"{interface.avg_readings[0]},{interface.avg_readings[1]}")
        time.sleep(0.01)
        print(interface.avg_readings)
gc.enable()
gc.threshold(100000) #prevents memory errors
thread2()
