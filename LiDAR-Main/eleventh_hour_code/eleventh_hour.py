import pimoroni_i2c
import breakout_vl53l5cx
import time
import _thread
from machine import Pin,UART
# The VL53L5CX requires a firmware blob to start up.
# Make sure you upload "vl53l5cx_firmware.bin" via Thonny to the root of your filesystem
# You can find it here: https://github.com/ST-mirror/VL53L5CX_ULD_driver/blob/no-fw/lite/en/vl53l5cx_firmware.bin

# This example attempts to track a "bright" object (such as a white business card).
# It uses reflectance to identify the target and compute the X/Y coordinates
# of its "center of mass" in the sensors view.
# We then use the object tracking to drive a little robot towards a business card onna stick!

# Motion indication only works at distances > 400mm so it's not
# really useful as a method to reject data.

# Configure your distance and brightness thresholds to suit your object
DISTANCE_THRESHOLD = 400  # Distance in mm
REFLECTANCE_THRESHOLD = 60  # Estimated reflectance in %

PINS_BREAKOUT_GARDEN = {"sda": 20, "scl": 21}
PINS_PICO_EXPLORER = {"sda": 20, "scl": 21}
vl1 = Pin(18,Pin.OUT)
vl1.value(1)
vl2 = Pin(19,Pin.OUT)
vl2.value(0)
# Sensor startup time is proportional to i2c baudrate
# HOWEVER many sensors may not run at > 400KHz (400000)
i2c = pimoroni_i2c.PimoroniI2C(**PINS_BREAKOUT_GARDEN, baudrate=2_000_000)
# Setup the VL53L5CX sensor
print("Starting up sensor...")
t_sta = time.ticks_ms()
sensor = breakout_vl53l5cx.VL53L5CX(i2c)
t_end = time.ticks_ms()
print("Done in {}ms...".format(t_end - t_sta))

# Make sure to set resolution and other settings *before* you start ranging
sensor.set_resolution(breakout_vl53l5cx.RESOLUTION_8X8)
sensor.set_ranging_frequency_hz(15)
sensor.start_ranging()

#UART TIME
uart = UART(0, baudrate = 115200, tx=Pin(0), rx=Pin(1))
uart.init(bits=8, parity=None, stop=2)
led = Pin ("LED",Pin.OUT)	#status LED
data_avg=0
#kick thread off
def thread2(uart):
    print("starting thread 2")
    while True:
        #wait until data is requested
        if uart.any():
            uart_in_data=uart.readline()
            if uart_in_data==b's':
                uart.write(f"{data_avg}")
        #time.sleep(0.01)
second_thread = _thread.start_new_thread(thread2,[uart])
while True:
    if sensor.data_ready():
        # "data" is a namedtuple (attrtuple technically)
        # it includes average readings as "distance_avg" and "reflectance_avg"
        # plus a full 4x4 or 8x8 set of readings (as a 1d tuple) for both values.
        data = sensor.get_data()
        data_avg=data.distance_avg
        print(data.distance_avg)
        