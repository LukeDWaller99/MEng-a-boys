import pimoroni_i2c
import breakout_vl53l5cx
from machine import Pin
import time
import micropython
import gc
#this is normally bad, but it's my module so meh
#MAKE SURE THIS FILE IS PRESENT ON THE BOARD FIRST! IF IT CAN'T FIND IT, THAT'S WHY!
from L_Proc import *
from Tran_Bus import *
from LiDAR_Handler import *
#LED pins, for debugging only
led1 = Pin(13,Pin.OUT)
led2 = Pin(12, Pin.OUT)
led3 = Pin(11, Pin.OUT)
internal_led = Pin(25, Pin.OUT)
int_led = 0;

#lidar pins
lidar_control_pins = [16,17]
#interrupt lines
#interrupt1 = Pin(14, Pin.IN)
interrupt1 = LiDAR_Handler(14)
#interrupt2 = Pin(15, Pin.IN)
interrupt2 = LiDAR_Handler(15)
bus = Tran_Bus(lidar_control_pins)
bus.all_off()
# The VL53L5CX requires a firmware blob to start up.
# Make sure you upload "vl53l5cx_firmware.bin" via Thonny to the root of your filesystem
# You can find it here: https://github.com/ST-mirror/VL53L5CX_ULD_driver/blob/no-fw/lite/en/vl53l5cx_firmware.bin

PINS_BREAKOUT_GARDEN = {"sda": 4, "scl": 5}
PINS_PICO_EXPLORER = {"sda": 20, "scl": 21}
iterations=0
sensor_mode = 4

# Sensor startup time is proportional to i2c baudrate
# HOWEVER many sensors may not run at > 400KHz (400000)
i2c = pimoroni_i2c.PimoroniI2C(**PINS_BREAKOUT_GARDEN, baudrate=1_000_000)
#sensor callbacks
int1_flag = 0
int2_flag = 0
def sensor1_callback(sensor):
    global int1_flag
    print("int1")
    int1_flag=1
def sensor2_callback(sensor):
    global int2_flag
    print("int2")
    int2_flag=1
#boot all sensors
t_sta = time.ticks_ms()
for x in range(2):
    bus.advance()
    print("Starting up sensor...")
    sensor = breakout_vl53l5cx.VL53L5CX(i2c)
    if sensor_mode == 4:
        sensor.set_resolution(breakout_vl53l5cx.RESOLUTION_4X4)
    else:
        sensor.set_resolution(breakout_vl53l5cx.RESOLUTION_8X8)
    sensor.start_ranging()
t_end = time.ticks_ms()
print("Done in {}ms...".format(t_end - t_sta))
gc.enable()

#enable interrupts
#interrupt1.irq(trigger=Pin.IRQ_RISING, handler=sensor1_callback)
#interrupt2.irq(trigger=Pin.IRQ_RISING, handler=sensor2_callback)
t_t1=time.ticks_ms()
t_t2=time.ticks_ms()
while True:
    t_loop_sta = time.ticks_ms()
    t_t1=time.ticks_ms()
    t_t2=time.ticks_ms()
    #bus.advance()
    #t_start = time.ticks_ms()
    while (interrupt1.get_flag() == 0 and interrupt2.get_flag() == 0): #wait until a flag goes high
        pass
    if (interrupt1.get_flag()==1):
        bus.enable(0)
        interrupt1.clear()
        t_t1s=time.ticks_ms()
        print("T1 interval {}ms...".format(t_t1s - t_t1))
        t_t1=time.ticks_ms()
    else:
        bus.enable(1)
        interrupt2.clear()
        t_t2s=time.ticks_ms()
        print("T2 interval {}ms...".format(t_t2s - t_t2))
        t_t2=time.ticks_ms()
    if sensor.data_ready():
        print("read")
        print(bus.current_enable)
        int_led = int_led ^ 1
        internal_led.value(int_led)
        # "data" is a namedtuple (attrtuple technically)
        # it includes average readings as "distance_avg" and "reflectance_avg"
        # plus a full 4x4 or 8x8 set of readings (as a 1d tuple) for both values.
        data = sensor.get_data()
        #diag_print(data, sensor_mode)
        #print(centre_grid(data.distance, sensor_mode))
        cent_reading = int(centre_grid_avg(centre_grid(data.distance, sensor_mode)))
        #print("Average: {}".format(
        #    cent_reading))
        #t_end2 = time.ticks_ms()
        #print("Sensing done in {}ms...".format(t_end2 - t_start))
        ##now, do the LEDS
        #cent_reading = 100
        if cent_reading < 50:
            led1.value(1)
            led2.value(0)
            led3.value(0)
        elif (cent_reading > 50) and (cent_reading < 250):
            led1.value(0)
            led2.value(1)
            led3.value(0)
        else:
            led1.value(0)
            led2.value(0)
            led3.value(1)
        iterations = iterations +1
        print(iterations)
        #micropython.mem_info()
        gc.collect()##clean up memory
        t_loop_end = time.ticks_ms()
        print("Loop done in {}ms...".format(t_loop_end - t_loop_sta))