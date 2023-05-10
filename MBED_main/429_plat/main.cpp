#include "mbed.h"

SPISlave myspi(PB_5, PB_4, PB_3, PA_4); // mosi, miso, sclk, nSS

int main() {
    
    myspi.frequency(1000000);

    myspi.format(8, 0);
    myspi.reply(0x5A);
    //myspi.format(16, 0);
    //myspi.reply(0x5A69);

    while(1) {
         if (myspi.receive()) {
             
             int data = myspi.read();
             printf("Recieved %2x\n", data);
             myspi.reply(data); // Read byte from master and transmit it at the next transaction
         } 
    }
}
