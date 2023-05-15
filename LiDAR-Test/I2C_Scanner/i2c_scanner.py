import machine
sdaPIN=machine.Pin(8)
sclPIN=machine.Pin(9)
i2c=machine.I2C(0,sda=sdaPIN, scl=sclPIN, freq=400000)
devices = i2c.scan()
if len(devices) != 0:
    print('Number of I2C devices found=',len(devices))
    for device in devices:
        print("Device Hexadecimel Address= ",hex(device))
else:
    print("No device found")