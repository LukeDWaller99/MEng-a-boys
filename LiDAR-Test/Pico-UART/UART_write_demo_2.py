from machine import Pin,UART
import time

uart = UART(0, baudrate = 115200, tx=Pin(0), rx=Pin(1))
uart.init(bits=8, parity=None, stop=2)
led = Pin ("LED",Pin.OUT)


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
    time.sleep(0.05)