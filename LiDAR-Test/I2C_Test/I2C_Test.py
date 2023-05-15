from machine import I2C,Pin

sda_pin = Pin(8, Pin.PULL_UP)
scl_pin = Pin(9, Pin.PULL_UP)

i2c = I2C(0,sda=sda_pin,scl=scl_pin,freq=400000)          # create I2C peripheral at frequency of 400kHz
                                # depending on the port, extra parameters may be required
                                # to select the peripheral and/or pins to use

i2c.scan()                      # scan for peripherals, returning a list of 7-bit addresses

i2c.writeto(0x50, b'beans')         # write 3 bytes to peripheral with 7-bit address 42
test=i2c.readfrom(0x50, 4)             # read 4 bytes from peripheral with 7-bit address 42
print(test)