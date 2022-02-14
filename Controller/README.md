# Controller Specifications
----
## Requirements
The Controller will need to remotely control the craft with bi-directional communication. This will involve serveral design considerations including:
1. [ ] Microcontroller
	1. [ ] NUCLEO-8S207K8 or NUCLEO-G031K8
2. [ ] Inputs
	1. [ ] 2 Analogue Joysticks
	2. [ ] 5 buttons
		1. [ ] 4 discreet buttons
		2. [ ] Reset Button
	3. [ ] 2 Rotary Potentiometers
	4. [ ] 2 SPDT toggling switches
3. [ ] Outputs
	1. [ ] Buzzer for feedback to user
	2. [ ] Status LEDs
4. [ ] Power
	1. [ ] Power Indicator LED
	2. [ ] Battery Powered
		1. [ ] 18650 Li-Po battery
		2. [ ] Battery Charger - could use seperate charger to reduce complexity
	3. [ ] Suitable Buck Converter to supply appropriate voltage
	4. [ ] Reverse polarity protection
	5. [ ] Low voltage detection chip
	6. [ ] ON/OFF power switch
5. [ ] Communication with main craft
	1. [ ] RF chip (nRF24L01)
	2. [ ] Bi-directional communication
6. [ ] Case
	1. [ ] Comfortable
	2. [ ] Ergonomic 
	3. [ ] Light and easy to tranport 
	4. [ ] 3D printed
	
	----
## Dependancies/Libraries Used

`nRF24L01P.h` Authored by Owen Edwards (c) 2010
----
## Contributions
**Luke Waller**

*Authored*

