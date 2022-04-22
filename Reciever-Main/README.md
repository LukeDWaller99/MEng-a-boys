# Reciever/Main Board Specifications
----
## Requirements
The Main Craft will need to communicate with the controller using bi-directional communication. This will involve serveral design considerations including:
1. [ ] Microcontroller
	1. [ ] NUCELO-F429ZI
2. [ ] Inputs
	1. [ ] Sensor for detecting how full the basket is
	2. [ ] Battery Level detector 
3. [ ] Outputs
	1. [ ] 4 BLDC Motors for locomotion
	2. [ ] 2 H-Bridges for conveyer belt
4. [ ] Power
	1. [ ] Power Indicator LEDs
	2. [ ] Battery Powered
		1. [ ] Li-Po battery
		2. [ ] Battery Charger
	3. [ ] Suitable Buck Converter to supply appropriate voltages
	4. [ ] Reverse polarity protection
	5. [ ] Low voltage detection chip
	6. [ ] ON/OFF power switch
5. [ ] Communication with Controller
	1. [ ] RF chip (nRF24L01)
	2. [ ] Bi-directional communication
6. [ ] Body
7. [ ] PCB/Electronics
	1. [ ] Schematic  
	2. [ ] PCB Layout
8. [ ] Testing
	1. [ ] Testing individual assemblies on a breadboard
	2. [ ] Debugging code to test all individual components on the PCB

## Dependancies/Libraries Used
`nRF24L01P.h` Authored by Owne Edwards (c) - Modified by Luke Waller 2022
`ESC.h` Authored by Luke Waller 2022
`Buzzer.h` Authored by Luke Waller 2022 
----
## Contributions
**Luke Waller**

*Authored*
