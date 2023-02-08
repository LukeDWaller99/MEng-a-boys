# Reciever/Main Board Specifications
----
## Requirements
The Main Craft will need to communicate with the controller using bi-directional communication. This will involve serveral design considerations including:
1. [x] Microcontroller
	1. [x] NUCELO-F429ZI
2. [x] Inputs
	1. [x] Sensor for detecting how full the basket is
	2. [x] Battery Level detector 
3. [x] Outputs
	1. [x] 4 BLDC Motors for locomotion
	2. [x] 2 H-Bridges for conveyer belt
4. [x] Power
	1. [x] Power Indicator LEDs
	2. [x] Battery Powered
		1. [x] Li-Ion battery
		2. [x] Battery Charger
	3. [x] Suitable Buck Converter to supply appropriate voltages
	4. [x] Reverse polarity protection
	5. [x] Low voltage detection chip
	6. [x] ON/OFF power switch
5. [x] Communication with Controller
	1. [x] RF chip (nRF24L01)
6. [x] Body
7. [x] PCB/Electronics
	1. [x] Schematic  
	2. [x] PCB Layout
8. [x] Testing
	1. [x] Testing individual assemblies on a breadboard
	2. [x] Debugging code to test all individual components on the PCB

## Dependancies/Libraries Used
`nRF24L01P.h` Authored by Owen Edwards (c) - Modified by Luke Waller 2022
`ESC.h` Authored by Luke Waller 2022
`Buzzer.h` Authored by Luke Waller 2022 
----
## Contributions
**Luke Waller**

*Authored*
