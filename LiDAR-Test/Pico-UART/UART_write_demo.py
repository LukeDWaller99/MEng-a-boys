from machine import Pin,UART
import time

uart = UART(1, baudrate = 9600, tx=Pin(4), rx=Pin(5))
uart.init(bits=8, parity=None, stop=2)
led = Pin ("LED",Pin.OUT)


while True:
    #t_sta=time.ticks_cpu()
    #uart.write('Hello World')
    #t_stop=time.ticks_cpu()
    #print(t_stop-t_sta)
    if uart.any():
        data = uart.read()
        print(data)
        led.toggle()
    time.sleep(1)