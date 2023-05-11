from machine import Pin,UART
import time

uart = UART(0, baudrate = 9600, tx=Pin(0), rx=Pin(1))
uart.init(bits=8, parity=None, stop=2)
led = Pin ("LED",Pin.OUT)


while True:
    if uart.any():
        t_sta=time.ticks_cpu()
        data = uart.readline()
        t_stop=time.ticks_cpu()
        print(t_stop-t_sta)
        print(data.decode('UTF-8'))
        print(data)
        #if data.decode('UTF-8') == "beans":
        led.toggle()
    time.sleep(1)