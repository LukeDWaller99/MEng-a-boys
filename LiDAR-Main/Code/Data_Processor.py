"""
Data_Processor Class

PRocesses LiDAR data and signals the main thread where appropriate
"""
from machine import Pin,UART,I2C
import _thread,time
class Data_Processor:
    def __init__(self,i2c_pins):
        #data buffer
        self.data_list = []
        self.i2c_thread_flag = 0
        #create I2C instance
        sda_pin=i2c_pins[0]
        scl_pin = i2c_pins[1]
        self.i2c = I2C(0,sda=sda_pin,scl=scl_pin,freq=400000)  #1M casues lockup, leave at 800K
        dev_list=self.i2c.scan()                      # scan for peripherals, returning a list of 7-bit addresses
        if not len(dev_list)==0:
            print("I2C Device found...")
        else:
            print("I2C failure")
            while len(dev_list) ==0:
                print("RETRYING...")
                time.sleep(1)
                dev_list=self.i2c.scan()
        print("I2C Connected")
        self.TARGET_ADDR = dev_list[0]
        self.i2c.writeto(self.TARGET_ADDR, b'LIVE')        
        
        second_thread = _thread.start_new_thread(self.I2C_Thread,[])
    
    def I2C_Thread(self):
        print("Thead 2 started")
        print("flag"+ str(self.i2c_thread_flag))
        while True:
            #wait until flag is raised
            while not self.i2c_thread_flag:
                pass
            print("woken")
            #process data
            try:
                a=self.data_list[1]
            except:
                pass	#do nothing, data is invalid, someone goofed.
            else:
                if (int(self.data_list[0],10)<50) or (int(self.data_list[1],10)<50):
                    print("SEND I2C")
                    self.i2c.writeto(self.TARGET_ADDR,b'STOP')
                elif (int(self.data_list[0],10)<100) or (int(self.data_list[1],10)<100):
                    print("SEND I2C")
                    self.i2c.writeto(self.TARGET_ADDR,b'OBS')
                else:
                    self.i2c.writeto(self.TARGET_ADDR,b'GO')
            self.i2c_thread_flag = 0
    
    def set_data(self,data):
        self.data_list=data
    def wake(self):
        self.i2c_thread_flag=1