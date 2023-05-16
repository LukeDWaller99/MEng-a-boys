from machine import Pin,UART,I2C
import time,_thread
from MUX4 import *
from Data_Processor import *
uart = UART(0, baudrate = 115200, tx=Pin(0), rx=Pin(1))
uart.init(bits=8, parity=None, stop=2)
led = Pin ("LED",Pin.OUT)

sda_pin = Pin(8, Pin.PULL_UP)
scl_pin = Pin(9, Pin.PULL_UP)

i2c = I2C(0,sda=sda_pin,scl=scl_pin,freq=400000)  #1M casues lockup, leave at 800K

mux = MUX4([2,3])
mux.select(3)

data_proc = Data_Processor([sda_pin,scl_pin])
while True:
    #engage second thread
    
    #signal to the LiDAR board that we want a reading
    
    #print("requesting")
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
        try:
            print(int(data_list[0],10))
        except:
            print("invalid data")
            data_list=[None]
        if data_list==None:
            pass
        else:
            print("wake thread 2")
            data_list.append(mux.get_chan())
            print(data_list)
            data_proc.set_data(data_list)
            data_proc.wake()
        
    time.sleep(0.025)