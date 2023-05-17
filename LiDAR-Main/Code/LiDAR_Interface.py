from L_Proc import *
from Tran_Bus import *
from LiDAR_Handler import *
import pimoroni_i2c
import breakout_vl53l5cx
import time
import _thread
import micropython
import gc
import machine
from machine import Timer
class LiDAR_Interface:
     #hardcoded
    sensor_mode = 8
    def __init__(self,lidar_control_pins,lidar_interrupt_pins):
        PINS_BREAKOUT_GARDEN = {"sda": 20, "scl": 21}
        self.debug = 0
        
        
        self.data = 0
        self.avg_readings = [0,0]
        self.sense_ref=self.sense
        self.bus = Tran_Bus(lidar_control_pins)
        self.bus.all_off()
        self.thread_flag = 0 #thread flag for sensing loop
        self.last_interrupt=0
        self.internal_led = Pin(25, Pin.OUT)
        self.flag1=0
        self.flag2=0
        
        #initialise sensors
        i2c = pimoroni_i2c.PimoroniI2C(**PINS_BREAKOUT_GARDEN, baudrate=2_000_000)
        t_sta = time.ticks_ms()
        for x in range(self.bus.get_len()):
            self.bus.advance()
            print("Starting up sensor...")
            self.sensor = breakout_vl53l5cx.VL53L5CX(i2c)
            if self.sensor_mode == 4:
                self.sensor.set_resolution(breakout_vl53l5cx.RESOLUTION_4X4)
            else:
                self.sensor.set_resolution(breakout_vl53l5cx.RESOLUTION_8X8)
            self.sensor.set_ranging_frequency_hz(45)
            self.sensor.start_ranging()
        t_end = time.ticks_ms()
        print("Done in {}ms...".format(t_end - t_sta))
        
        #create interrupts
        self.interrupt_pin1 = Pin(17, Pin.IN) #assign pin
        self.interrupt_pin1.irq(trigger=Pin.IRQ_RISING, handler=self.callback1)
        #self.interrupt_pin2 = Pin(16, Pin.IN) #assign pin
        #self.interrupt_pin2.irq(trigger=Pin.IRQ_RISING, handler=self.callback2)
        soft_timer = Timer(mode=Timer.PERIODIC, period=100, callback=self.callback2)
        self.wdt=machine.WDT(timeout=8000) #watchdog timer to catch lock-ups. Resets after eight seconds.
        #second_thread = _thread.start_new_thread(self.sense,[])
    def sense(self):
        
        while True:
            while (self.flag1 == 0 and self.flag2 == 0): #wait until a flag goes high
                pass
            gc.collect()
            self.bus.enable(0)
            self.flag1=0
            self.flag2=0
            self.last_interrupt = 0
            #print(self.last_interrupt)
            if self.sensor.data_ready():
                self.data = self.sensor.get_data()
                cent_reading = int(centre_grid_avg(centre_grid(self.data.distance, self.sensor_mode)))
                #print(cent_reading)
                self.avg_readings[self.last_interrupt] = cent_reading
            #read the second sensor
            self.bus.enable(1)
            self.last_interrupt=1
            if self.sensor.data_ready():
                self.data = self.sensor.get_data()
                cent_reading = int(centre_grid_avg(centre_grid(self.data.distance, self.sensor_mode)))
                #print(cent_reading)
                self.avg_readings[self.last_interrupt] = cent_reading

            self.thread_flag=0
            self.wdt.feed()	#feed watchdog
            print("fed")
            micropython.mem_info()
            
    def callback1(self,sensor):
        #self.bus.enable(0) #swap sensor
        #self.internal_led.toggle()
        self.flag1=1
        self.thread_flag=1
    def callback2(self,sensor):
        #self.bus.enable(1) #swap sensor
        self.flag2=1
        print("fired")
    def set_debug(self,new_val):
        self.debug=new_val
