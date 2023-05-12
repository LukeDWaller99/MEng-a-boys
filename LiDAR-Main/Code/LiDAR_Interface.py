from L_Proc import *
from Tran_Bus import *
from LiDAR_Handler import *
import pimoroni_i2c
import breakout_vl53l5cx
import time
import _thread
import micropython
import gc
class LiDAR_Interface:
     #hardcoded
    sensor_mode = 4
    def f_sensing_loop(self):
            while True:
                while self.debug == 1:
                    t_loop_sta = time.ticks_ms()
                    t_t1=time.ticks_ms()
                    t_t2=time.ticks_ms()
                #bus.advance()
                #t_start = time.ticks_ms()
                while (self.interrupt_lines[0].get_flag() == 0 and self.interrupt_lines[1].get_flag() == 0): #wait until a flag goes high
                    pass
                if (self.interrupt_lines[0].get_flag()):
                    self.bus.enable(0)
                    self.interrupt_lines[0].clear()
                    last_interrupt = 0
                    if self.debug==1:
                        t_t1s=time.ticks_ms()
                        print("T1 interval {}ms...".format(t_t1s - t_t1))
                        t_t1=time.ticks_ms()
                else:
                    self.bus.enable(1)
                    self.interrupt_lines[1].clear()
                    last_interrupt = 1
                    if self.debug==1:
                        t_t2s=time.ticks_ms()
                        print("T2 interval {}ms...".format(t_t2s - t_t2))
                        t_t2=time.ticks_ms()
                print(last_interrupt)
                if self.sensor.data_ready():
                    if self.debug ==1:
                        print("read")
                    # "data" is a namedtuple (attrtuple technically)
                    # it includes average readings as "distance_avg" and "reflectance_avg"
                    # plus a full 4x4 or 8x8 set of readings (as a 1d tuple) for both values.
                    self.data = self.sensor.get_data()
                    #diag_print(data, sensor_mode)
                    #print(centre_grid(data.distance, sensor_mode))
                    cent_reading = int(centre_grid_avg(centre_grid(self.data.distance, self.sensor_mode)))
                    print(cent_reading)
                    self.avg_readings[last_interrupt] = cent_reading
                    micropython.mem_info()
                    if self.debug == 1:
                        t_loop_end = time.ticks_ms()
                        print("Loop done in {}ms...".format(t_loop_end - t_loop_sta))
                    
    def __init__(self,lidar_control_pins,lidar_interrupt_pins):
        PINS_BREAKOUT_GARDEN = {"sda": 20, "scl": 21}
        self.debug = 0
        self.data = 0
        self.avg_readings = [0,0]
        self.bus = Tran_Bus(lidar_control_pins)
        self.bus.all_off()
        #create interrupts
        self.interrupt_lines = []
        self.interrupt_lines += [LiDAR_Handler(pin_number) for pin_number in lidar_interrupt_pins]
        #initialise sensors
        i2c = pimoroni_i2c.PimoroniI2C(**PINS_BREAKOUT_GARDEN, baudrate=1_000_000)
        t_sta = time.ticks_ms()
        for x in range(self.bus.get_len()):
            self.bus.advance()
            print("Starting up sensor...")
            self.sensor = breakout_vl53l5cx.VL53L5CX(i2c)
            if self.sensor_mode == 4:
                self.sensor.set_resolution(breakout_vl53l5cx.RESOLUTION_4X4)
            else:
                self.sensor.set_resolution(breakout_vl53l5cx.RESOLUTION_8X8)
            self.sensor.set_ranging_frequency_hz(10)
            self.sensor.start_ranging()
        t_end = time.ticks_ms()
        print("Done in {}ms...".format(t_end - t_sta))
        second_thread = _thread.start_new_thread(self.f_sensing_loop,[])
        
    def set_debug(self,new_val):
        self.debug=new_val