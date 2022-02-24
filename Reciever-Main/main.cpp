/**
    @file Main.cpp
    Main file for Final Year project Receiver - Luke Waller
**/

#include <mbed.h>
#include <nRF24L01P.h>
#include "HARDWARE.h"

#define TRANSMITTER     1
#define TRANSFER_SIZE   10
#define DEFAULT_PIPE    0

// MOSI, MISO, SCK, CNS, CE, IRQ - must be an interrupt pin 6 
nRF24L01P nRF24L01(MOSI, MISO, SCK, CSN, CE, IRQ);

char rxData[TRANSFER_SIZE];

int rxDataCnt = 0;

int main() {

    nRF24L01.powerUp();

// Display the (default) setup of the nRF24L01+ chip
    printf("nRF24L01 Frequency    : %d MHz\n",  nRF24L01.getRfFrequency() );
    printf("nRF24L01 Output power : %d dBm\n",  nRF24L01.getRfOutputPower() );
    printf("nRF24L01 Data Rate    : %d kbps\n", nRF24L01.getAirDataRate() );
    printf("nRF24L01 TX Address   : 0x%010llX\n", nRF24L01.getTxAddress() );
    printf("nRF24L01 RX Address   : 0x%010llX\n", nRF24L01.getRxAddress() );

    nRF24L01.setTransferSize(TRANSFER_SIZE);

    if (TRANSMITTER == 0) {
        nRF24L01.setReceiveMode();
    }
    else if (TRANSMITTER == 1){
        nRF24L01.setTransmitMode();
    }
    else {
        // error?
    }

    while (true) {
    if (nRF24L01.readable(0)) {
            rxDataCnt = nRF24L01.read(0, rxData, sizeof(rxData));
            printf("%s\n", rxData);
        }
    }

}
