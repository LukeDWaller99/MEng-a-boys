import pimoroni_i2c
import breakout_vl53l5cx
from machine import Pin
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
interface = LiDAR_Interface(lidar_control_pins,int_pins)

gc.enable()
