import pimoroni_i2c
import breakout_vl53l5cx
import time
#this is normally bad, but it's my module so meh
from L_Proc import *

#fun little number to find the average of a list
def average(lst):
    return sum(lst)/len(lst)



# The VL53L5CX requires a firmware blob to start up.
# Make sure you upload "vl53l5cx_firmware.bin" via Thonny to the root of your filesystem
# You can find it here: https://github.com/ST-mirror/VL53L5CX_ULD_driver/blob/no-fw/lite/en/vl53l5cx_firmware.bin

PINS_BREAKOUT_GARDEN = {"sda": 4, "scl": 5}
PINS_PICO_EXPLORER = {"sda": 20, "scl": 21}

sensor_mode = 4;

# Sensor startup time is proportional to i2c baudrate
# HOWEVER many sensors may not run at > 400KHz (400000)
i2c = pimoroni_i2c.PimoroniI2C(**PINS_BREAKOUT_GARDEN, baudrate=2_000_000)


print("Starting up sensor...")
t_sta = time.ticks_ms()
sensor = breakout_vl53l5cx.VL53L5CX(i2c)
t_end = time.ticks_ms()
print("Done in {}ms...".format(t_end - t_sta))

# Make sure to set resolution and other settings *before* you start ranging
#sensor.set_resolution(breakout_vl53l5cx.RESOLUTION_4X4)
sensor.set_resolution(breakout_vl53l5cx.RESOLUTION_8X8)
sensor.start_ranging()

while True:
    if sensor.data_ready():
        # "data" is a namedtuple (attrtuple technically)
        # it includes average readings as "distance_avg" and "reflectance_avg"
        # plus a full 4x4 or 8x8 set of readings (as a 1d tuple) for both values.
        data = sensor.get_data()
        data_length = len(data.distance)
        print("{}mm {}% (avg: {}mm {}%)".format(
            data.distance[0],
            data.reflectance[0],
            data.distance_avg,
            data.reflectance_avg))
        print("TL={} TR={} BL={} BR={}".format(
            data.distance[55],
            data.distance[63],
            data.distance[0],
            data.distance[7]))
        lst_low= data.distance[0:8]
        lst_top= data.distance[-8:64]
        print("TOP={} LOW={} LEFT={} RIGHT={}".format(
            average(lst_top),
            average(lst_low),
            average(grab_left(data.distance,sensor_mode)),
            average(grab_right(data.distance,sensor_mode))))
        print("Number of distance samples:",data_length)