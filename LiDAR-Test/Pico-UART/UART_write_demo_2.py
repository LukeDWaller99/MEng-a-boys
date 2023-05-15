from machine import Pin,UART,I2C
import time
from MUX4 import *
uart = UART(0, baudrate = 115200, tx=Pin(0), rx=Pin(1))
uart.init(bits=8, parity=None, stop=2)
led = Pin ("LED",Pin.OUT)

sda_pin = Pin(8, Pin.PULL_UP)
scl_pin = Pin(9, Pin.PULL_UP)

i2c = I2C(0,sda=sda_pin,scl=scl_pin,freq=400000)  

mux = MUX4([2,3])
mux.select(3)

dev_list=i2c.scan()                      # scan for peripherals, returning a list of 7-bit addresses
TARGET_ADDR = dev_list[0]
i2c.writeto(TARGET_ADDR, b'LIVE')         # write 3 bytes to peripheral with 7-bit address 42

while True:
    #signal to the LiDAR board that we want a reading
    
    print("requesting")
    uart.write('s') #for send
    if uart.any():
        t_sta=time.ticks_cpu()
        data = uart.readline()
        t_stop=time.ticks_cpu()
        print(t_stop-t_sta)
        print(data.decode('UTF-8'))
        data_str=str(data)
        data_list=(data.decode('UTF-8')).split(',')
        print(data_list)
        led.toggle()
        print(int(data_list[0],10))
        if (int(data_list[0],10)<100) or (int(data_list[0],10)<100):
            print("SEND I2C")
            i2c.writeto(TARGET_ADDR,b'STOP')
        else:
            i2c.writeto(TARGET_ADDR,b'GO')
    time.sleep(0.025)