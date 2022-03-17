#ifndef __TRASMISSION_CODES_H__
#define __TRASMISSION_CODES_H__

/*
    Transmittion Codes - 
    1xxx - POTs
        x1xx - Left Pitch
        x2xx - Left Roll
        x3xx - Right Pitch
        x4xx - Right Roll
            xx0x - Forwards
            xx1x - Reverse
                xxx0 - value of throttle
    2xxx - Buttons
        x1xx - Button 1
        x2xx - Button 2
        x3xx - Button 3
    3xxx - SW1 
        xx10 - ON
        xx01 - OFF
*/

#define LEFT_PITCH_FWD  '1','1','0','0','\0'
#define LEFT_ROLL_FWD   '1','2','0','0','\0'
#define RIGHT_PITCH_FWD '1','3','0','0','\0'
#define RIGHT_ROLL_FWD  '1','4','0','0','\0'

#define LEFT_PITCH_REV  '1','1','1','0','\0'
#define LEFT_ROLL_REV   '1','2','1','0','\0'
#define RIGHT_PITCH_REV '1','3','1','0','\0'
#define RIGHT_ROLL_REV  '1','4','1','0','\0'

#define BUTTON_1    '2','1','x','x','\0'
#define BUTTON_2    '2','2','x','x','\0'
#define BUTTON_3    '2','3','x','x','\0'

#define SW1_ON      '3','0','x','0','\0'
#define SW1_OFF     '3','0','x','1','\0'

#define TX_DATA  'T','E','S','T','\0'
#define RX_DATA  '0','0','0','0','\0'

#endif