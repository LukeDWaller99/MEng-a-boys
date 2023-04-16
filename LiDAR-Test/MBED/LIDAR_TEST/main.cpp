/*
 * Copyright (c) 2014-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

// Read temperature from LM75BD

I2C i2c(I2C_SDA, I2C_SCL);

const int addr7bit = 0x52;      // 7 bit I2C address
const int addr8bit = 0x52 << 1; // 8bit I2C address, 0x90

int main()
{
    char cmd[8];
    printf("Starting... \n");
    while (1) {
        cmd[0] = 0x01;
        cmd[1] = 0x00;
        //i2c.write(addr8bit, cmd, 2);

        ThisThread::sleep_for(500);

        cmd[0] = 0x00;
        //i2c.write(addr8bit, cmd, 1);
        i2c.read(addr8bit, cmd, 8);

        //float tmp = cmd[1];
        printf("Temp = %d\n", cmd[0]);
        printf("Temp = %d\n", cmd[1]);
        printf("Temp = %d\n", cmd[2]);
        printf("Temp = %d\n", cmd[3]);
        printf("Temp = %d\n", cmd[4]);
        printf("Temp = %d\n", cmd[5]);
        printf("Temp = %d\n", cmd[6]);
        printf("Temp = %d\n", cmd[7]);
        printf("\n");
    }
}
