import pimoroni_i2c
import breakout_vl53l5cx
from machine import Pin
import time
#this is normally bad, but it's my module so meh
#MAKE SURE THIS FILE IS PRESENT ON THE BOARD FIRST! IF IT CAN'T FIND IT, THAT'S WHY!
from L_Proc import *
from Tran_Bus import *    
#LED pins, for debugging only
led1 = Pin(13,Pin.OUT)
led2 = Pin(12, Pin.OUT)
led3 = Pin(11, Pin.OUT)

#lidar pins
lidar_control_pins = [16,17]
#vl1 = Pin(16, Pin.OUT)
#vl2 = Pin(17, Pin.OUT)
#default 1 to active
#vl1.value(1)
#vl2.value(0)
bus = Tran_Bus(lidar_control_pins)
bus.all_off()
# The VL53L5CX requires a firmware blob to start up.
# Make sure you upload "vl53l5cx_firmware.bin" via Thonny to the root of your filesystem
# You can find it here: https://github.com/ST-mirror/VL53L5CX_ULD_driver/blob/no-fw/lite/en/vl53l5cx_firmware.bin

PINS_BREAKOUT_GARDEN = {"sda": 4, "scl": 5}
PINS_PICO_EXPLORER = {"sda": 20, "scl": 21}
iterations=0
sensor_mode = 8

# Sensor startup time is proportional to i2c baudrate
# HOWEVER many sensors may not run at > 400KHz (400000)
i2c = pimoroni_i2c.PimoroniI2C(**PINS_BREAKOUT_GARDEN, baudrate=2_000_000)

#boot all sensors
for x in range(2):
    bus.advance()
    print("Starting up sensor...")
    t_sta = time.ticks_ms()
    sensor = breakout_vl53l5cx.VL53L5CX(i2c)
    t_end = time.ticks_ms()
    print("Done in {}ms...".format(t_end - t_sta))

    if sensor_mode == 4:
        sensor.set_resolution(breakout_vl53l5cx.RESOLUTION_4X4)
    else:
        sensor.set_resolution(breakout_vl53l5cx.RESOLUTION_8X8)
    sensor.start_ranging()

while True:
    bus.advance()
    t_start = time.ticks_ms()
    if sensor.data_ready():
        # "data" is a namedtuple (attrtuple technically)
        # it includes average readings as "distance_avg" and "reflectance_avg"
        # plus a full 4x4 or 8x8 set of readings (as a 1d tuple) for both values.
        data = sensor.get_data()
        #diag_print(data, sensor_mode)
        #print(centre_grid(data.distance, sensor_mode))
        cent_reading = int(centre_grid_avg(centre_grid(data.distance, sensor_mode)))
        #print("Average: {}".format(
        #    cent_reading))
        t_end2 = time.ticks_ms()
        print("Sensing done in {}ms...".format(t_end2 - t_start))
        ##now, do the LEDS
        if cent_reading < 50:
            led1.value(1)
            led2.value(0)
            led3.value(0)
        elif (cent_reading > 50) and (cent_reading < 150):
            led1.value(0)
            led2.value(1)
            led3.value(0)
        else:
            led1.value(0)
            led2.value(0)
            led3.value(1)
        iterations = iterations +1
        print(iterations)