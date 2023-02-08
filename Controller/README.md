# Controller Specifications
----
## Requirements
The Controller will need to remotely control the craft with bi-directional communication. This will involve serveral design considerations including:
1. [x] Microcontroller
	1. [x] NUCELO-L432KC
2. [x] Inputs
	1. [x] 2 Analogue Joysticks
	2. [x] 4 buttons
		1. [x] 3 discreet buttons
		2. [x] Reset Button
	3. [x] 1 SPDT toggling switches
3. [x] Outputs
	1. [x] Buzzer for feedback to user
	2. [x] 1 Status LEDs
4. [ ] Power
	1. [x] Power Indicator LEDs
	2. [ ] Battery Powered
		1. [ ] 18650 Li-Po battery
		2. [ ] Battery Charger
	3. [ ] Suitable Buck Converter to supply appropriate voltages
	4. [ ] Reverse polarity protection
	5. [ ] Low voltage detection chip
	6. [x] ON/OFF power switch
5. [ ] Communication with main craft
	1. [x] RF chip (nRF24L01)
	2. [ ] Bi-directional communication
6. [ ] Case
	1. [ ] Comfortable
	2. [ ] Ergonomic 
	3. [ ] Light and easy to tranport 
	4. [ ] 3D printed
	5. [ ] Easy to use
7. [ ] PCB/Electronics
	1. [x] Schematic  
	2. [ ] PCB Layout
8. [ ] Testing
	1. [x] Testing individual assemblies on a breadboard
	2. [ ] Debugging code to test all individual components on the PCB

## Dependancies/Libraries Used

`nRF24L01P.h` Authored by Owen Edwards (c) 2010 (Modified by Luke Waller - 2022)
----
## Contributions
**Luke Waller**

*Authored*

