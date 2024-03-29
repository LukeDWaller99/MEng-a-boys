EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Device:LED D?
U 1 1 6206EEE4
P 850 850
F 0 "D?" V 889 732 50  0000 R CNN
F 1 "LED" V 798 732 50  0000 R CNN
F 2 "" H 850 850 50  0001 C CNN
F 3 "~" H 850 850 50  0001 C CNN
	1    850  850 
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 62071445
P 850 1150
F 0 "R?" H 920 1196 50  0000 L CNN
F 1 "1K" H 920 1105 50  0000 L CNN
F 2 "" V 780 1150 50  0001 C CNN
F 3 "~" H 850 1150 50  0001 C CNN
	1    850  1150
	1    0    0    -1  
$EndComp
$Comp
L Transistor_BJT:2N2219 Q?
U 1 1 62073873
P 950 1500
F 0 "Q?" H 1141 1454 50  0000 L CNN
F 1 "S9013" H 1141 1545 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-39-3" H 1150 1425 50  0001 L CIN
F 3 "http://www.onsemi.com/pub_link/Collateral/2N2219-D.PDF" H 950 1500 50  0001 L CNN
	1    950  1500
	-1   0    0    1   
$EndComp
$Comp
L power:Earth #PWR0101
U 1 1 620753C5
P 850 1800
F 0 "#PWR0101" H 850 1550 50  0001 C CNN
F 1 "Earth" H 850 1650 50  0001 C CNN
F 2 "" H 850 1800 50  0001 C CNN
F 3 "~" H 850 1800 50  0001 C CNN
	1    850  1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	850  1700 850  1800
$Comp
L Device:R R?
U 1 1 62076135
P 1300 1500
F 0 "R?" H 1370 1546 50  0000 L CNN
F 1 "4K7" H 1370 1455 50  0000 L CNN
F 2 "" V 1230 1500 50  0001 C CNN
F 3 "~" H 1300 1500 50  0001 C CNN
	1    1300 1500
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 62076BAE
P 1800 1500
F 0 "R?" H 1870 1546 50  0000 L CNN
F 1 "4K7" H 1870 1455 50  0000 L CNN
F 2 "" V 1730 1500 50  0001 C CNN
F 3 "~" H 1800 1500 50  0001 C CNN
	1    1800 1500
	0    1    1    0   
$EndComp
$Comp
L Transistor_BJT:2N2219 Q?
U 1 1 6207754D
P 2150 1500
F 0 "Q?" H 2340 1546 50  0000 L CNN
F 1 "S9013" H 2340 1455 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-39-3" H 2350 1425 50  0001 L CIN
F 3 "http://www.onsemi.com/pub_link/Collateral/2N2219-D.PDF" H 2150 1500 50  0001 L CNN
	1    2150 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 1500 1550 1500
Text GLabel 1550 1350 0    50   Input ~ 0
BUZZER
Wire Wire Line
	1550 1350 1550 1500
Connection ~ 1550 1500
Wire Wire Line
	1550 1500 1650 1500
$Comp
L power:Earth #PWR0102
U 1 1 62078B9E
P 2250 1800
F 0 "#PWR0102" H 2250 1550 50  0001 C CNN
F 1 "Earth" H 2250 1650 50  0001 C CNN
F 2 "" H 2250 1800 50  0001 C CNN
F 3 "~" H 2250 1800 50  0001 C CNN
	1    2250 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2250 1700 2250 1800
$Comp
L Device:R R?
U 1 1 6207DE62
P 2150 950
F 0 "R?" H 2220 996 50  0000 L CNN
F 1 "10K" H 2220 905 50  0000 L CNN
F 2 "" V 2080 950 50  0001 C CNN
F 3 "~" H 2150 950 50  0001 C CNN
	1    2150 950 
	-1   0    0    1   
$EndComp
$Comp
L Device:Buzzer BZ?
U 1 1 6207EA88
P 2450 950
F 0 "BZ?" H 2602 979 50  0000 L CNN
F 1 "Buzzer" H 2602 888 50  0000 L CNN
F 2 "" V 2425 1050 50  0001 C CNN
F 3 "~" V 2425 1050 50  0001 C CNN
	1    2450 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	2250 1300 2150 1300
Wire Wire Line
	2150 1300 2150 1100
Connection ~ 2250 1300
Wire Wire Line
	2150 800  2150 700 
Wire Wire Line
	2350 700  2350 850 
Wire Wire Line
	2350 1300 2350 1050
Wire Wire Line
	2250 1300 2350 1300
$Comp
L Device:R_POT POT_1
U 1 1 620E4CE9
P 850 5900
F 0 "POT_1" H 781 5946 50  0000 R CNN
F 1 "R_POT" H 781 5855 50  0000 R CNN
F 2 "" H 850 5900 50  0001 C CNN
F 3 "~" H 850 5900 50  0001 C CNN
	1    850  5900
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 620E4CEF
P 1150 6050
F 0 "C?" H 1265 6096 50  0000 L CNN
F 1 "100nF" H 1265 6005 50  0000 L CNN
F 2 "" H 1188 5900 50  0001 C CNN
F 3 "~" H 1150 6050 50  0001 C CNN
	1    1150 6050
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 620E4CF5
P 1600 5900
F 0 "R?" H 1670 5946 50  0000 L CNN
F 1 "620" H 1670 5855 50  0000 L CNN
F 2 "" V 1530 5900 50  0001 C CNN
F 3 "~" H 1600 5900 50  0001 C CNN
	1    1600 5900
	0    1    1    0   
$EndComp
Wire Wire Line
	1000 5900 1150 5900
Wire Wire Line
	1150 6200 850  6200
Wire Wire Line
	850  6200 850  6050
$Comp
L power:Earth #PWR?
U 1 1 620E4CFE
P 850 6300
F 0 "#PWR?" H 850 6050 50  0001 C CNN
F 1 "Earth" H 850 6150 50  0001 C CNN
F 2 "" H 850 6300 50  0001 C CNN
F 3 "~" H 850 6300 50  0001 C CNN
	1    850  6300
	1    0    0    -1  
$EndComp
Wire Wire Line
	850  6200 850  6300
Connection ~ 850  6200
Wire Wire Line
	1150 5900 1450 5900
Connection ~ 1150 5900
Text GLabel 1750 5900 2    50   Input ~ 0
POT_1
$Comp
L power:+3.3V #PWR?
U 1 1 620E4D09
P 850 5750
F 0 "#PWR?" H 850 5600 50  0001 C CNN
F 1 "+3.3V" H 865 5923 50  0000 C CNN
F 2 "" H 850 5750 50  0001 C CNN
F 3 "" H 850 5750 50  0001 C CNN
	1    850  5750
	1    0    0    -1  
$EndComp
$Comp
L Device:R_POT POT_2
U 1 1 620E6861
P 850 6800
F 0 "POT_2" H 781 6846 50  0000 R CNN
F 1 "R_POT" H 781 6755 50  0000 R CNN
F 2 "" H 850 6800 50  0001 C CNN
F 3 "~" H 850 6800 50  0001 C CNN
	1    850  6800
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 620E6867
P 1150 6950
F 0 "C?" H 1265 6996 50  0000 L CNN
F 1 "100nF" H 1265 6905 50  0000 L CNN
F 2 "" H 1188 6800 50  0001 C CNN
F 3 "~" H 1150 6950 50  0001 C CNN
	1    1150 6950
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 620E686D
P 1600 6800
F 0 "R?" H 1670 6846 50  0000 L CNN
F 1 "620" H 1670 6755 50  0000 L CNN
F 2 "" V 1530 6800 50  0001 C CNN
F 3 "~" H 1600 6800 50  0001 C CNN
	1    1600 6800
	0    1    1    0   
$EndComp
Wire Wire Line
	1000 6800 1150 6800
Wire Wire Line
	1150 7100 850  7100
Wire Wire Line
	850  7100 850  6950
$Comp
L power:Earth #PWR?
U 1 1 620E6876
P 850 7200
F 0 "#PWR?" H 850 6950 50  0001 C CNN
F 1 "Earth" H 850 7050 50  0001 C CNN
F 2 "" H 850 7200 50  0001 C CNN
F 3 "~" H 850 7200 50  0001 C CNN
	1    850  7200
	1    0    0    -1  
$EndComp
Wire Wire Line
	850  7100 850  7200
Connection ~ 850  7100
Wire Wire Line
	1150 6800 1450 6800
Connection ~ 1150 6800
Text GLabel 1750 6800 2    50   Input ~ 0
POT_2
$Comp
L power:+3.3V #PWR?
U 1 1 620E6881
P 850 6650
F 0 "#PWR?" H 850 6500 50  0001 C CNN
F 1 "+3.3V" H 865 6823 50  0000 C CNN
F 2 "" H 850 6650 50  0001 C CNN
F 3 "" H 850 6650 50  0001 C CNN
	1    850  6650
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 620EA4AB
P 1500 3050
F 0 "R?" V 1600 3000 50  0000 L CNN
F 1 "1K" V 1600 2850 50  0000 L CNN
F 2 "" V 1430 3050 50  0001 C CNN
F 3 "~" H 1500 3050 50  0001 C CNN
	1    1500 3050
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 620EAE13
P 1650 3300
F 0 "R?" H 1720 3346 50  0000 L CNN
F 1 "10K" H 1720 3255 50  0000 L CNN
F 2 "" V 1580 3300 50  0001 C CNN
F 3 "~" H 1650 3300 50  0001 C CNN
	1    1650 3300
	-1   0    0    1   
$EndComp
Text GLabel 1350 3050 0    50   Input ~ 0
Btn_L3
$Comp
L power:Earth #PWR?
U 1 1 620EB4E6
P 1650 3450
F 0 "#PWR?" H 1650 3200 50  0001 C CNN
F 1 "Earth" H 1650 3300 50  0001 C CNN
F 2 "" H 1650 3450 50  0001 C CNN
F 3 "~" H 1650 3450 50  0001 C CNN
	1    1650 3450
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST Btn_1
U 1 1 62105B68
P 3400 1000
F 0 "Btn_1" V 3354 1098 50  0000 L CNN
F 1 "SW_SPST" V 3445 1098 50  0000 L CNN
F 2 "" H 3400 1000 50  0001 C CNN
F 3 "~" H 3400 1000 50  0001 C CNN
	1    3400 1000
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 62105B6E
P 3100 1100
F 0 "R?" H 3170 1146 50  0000 L CNN
F 1 "1K" H 3170 1055 50  0000 L CNN
F 2 "" V 3030 1100 50  0001 C CNN
F 3 "~" H 3100 1100 50  0001 C CNN
	1    3100 1100
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 62105B74
P 3400 1450
F 0 "R?" H 3470 1496 50  0000 L CNN
F 1 "10K" H 3470 1405 50  0000 L CNN
F 2 "" V 3330 1450 50  0001 C CNN
F 3 "~" H 3400 1450 50  0001 C CNN
	1    3400 1450
	-1   0    0    1   
$EndComp
Text GLabel 3100 950  1    50   Input ~ 0
Btn_1
$Comp
L power:Earth #PWR?
U 1 1 62105B7B
P 3400 1600
F 0 "#PWR?" H 3400 1350 50  0001 C CNN
F 1 "Earth" H 3400 1450 50  0001 C CNN
F 2 "" H 3400 1600 50  0001 C CNN
F 3 "~" H 3400 1600 50  0001 C CNN
	1    3400 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 1250 3400 1250
Wire Wire Line
	3400 1250 3400 1300
Wire Wire Line
	3400 1200 3400 1250
Connection ~ 3400 1250
$Comp
L Switch:SW_SPST Btn_?
U 1 1 6210840B
P 4350 1000
F 0 "Btn_?" V 4304 1098 50  0000 L CNN
F 1 "SW_SPST" V 4395 1098 50  0000 L CNN
F 2 "" H 4350 1000 50  0001 C CNN
F 3 "~" H 4350 1000 50  0001 C CNN
	1    4350 1000
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 62108411
P 4050 1100
F 0 "R?" H 4120 1146 50  0000 L CNN
F 1 "1K" H 4120 1055 50  0000 L CNN
F 2 "" V 3980 1100 50  0001 C CNN
F 3 "~" H 4050 1100 50  0001 C CNN
	1    4050 1100
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 62108417
P 4350 1450
F 0 "R?" H 4420 1496 50  0000 L CNN
F 1 "10K" H 4420 1405 50  0000 L CNN
F 2 "" V 4280 1450 50  0001 C CNN
F 3 "~" H 4350 1450 50  0001 C CNN
	1    4350 1450
	-1   0    0    1   
$EndComp
Text GLabel 4050 950  1    50   Input ~ 0
Btn_2
$Comp
L power:Earth #PWR?
U 1 1 6210841E
P 4350 1600
F 0 "#PWR?" H 4350 1350 50  0001 C CNN
F 1 "Earth" H 4350 1450 50  0001 C CNN
F 2 "" H 4350 1600 50  0001 C CNN
F 3 "~" H 4350 1600 50  0001 C CNN
	1    4350 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4050 1250 4350 1250
Wire Wire Line
	4350 1250 4350 1300
Wire Wire Line
	4350 1200 4350 1250
Connection ~ 4350 1250
$Comp
L Device:R R?
U 1 1 6210AEEF
P 5050 1100
F 0 "R?" H 5120 1146 50  0000 L CNN
F 1 "1K" H 5120 1055 50  0000 L CNN
F 2 "" V 4980 1100 50  0001 C CNN
F 3 "~" H 5050 1100 50  0001 C CNN
	1    5050 1100
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 6210AEF5
P 5350 1450
F 0 "R?" H 5420 1496 50  0000 L CNN
F 1 "10K" H 5420 1405 50  0000 L CNN
F 2 "" V 5280 1450 50  0001 C CNN
F 3 "~" H 5350 1450 50  0001 C CNN
	1    5350 1450
	-1   0    0    1   
$EndComp
Text GLabel 5050 950  1    50   Input ~ 0
SW_1
$Comp
L power:Earth #PWR?
U 1 1 6210AEFC
P 5350 1600
F 0 "#PWR?" H 5350 1350 50  0001 C CNN
F 1 "Earth" H 5350 1450 50  0001 C CNN
F 2 "" H 5350 1600 50  0001 C CNN
F 3 "~" H 5350 1600 50  0001 C CNN
	1    5350 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 1250 5350 1250
Wire Wire Line
	5350 1250 5350 1300
Wire Wire Line
	5350 1200 5350 1250
Connection ~ 5350 1250
$Comp
L Device:R R?
U 1 1 6210D005
P 6000 1100
F 0 "R?" H 6070 1146 50  0000 L CNN
F 1 "1K" H 6070 1055 50  0000 L CNN
F 2 "" V 5930 1100 50  0001 C CNN
F 3 "~" H 6000 1100 50  0001 C CNN
	1    6000 1100
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 6210D00B
P 6300 1450
F 0 "R?" H 6370 1496 50  0000 L CNN
F 1 "10K" H 6370 1405 50  0000 L CNN
F 2 "" V 6230 1450 50  0001 C CNN
F 3 "~" H 6300 1450 50  0001 C CNN
	1    6300 1450
	-1   0    0    1   
$EndComp
Text GLabel 6000 950  1    50   Input ~ 0
SW_2
$Comp
L power:Earth #PWR?
U 1 1 6210D012
P 6300 1600
F 0 "#PWR?" H 6300 1350 50  0001 C CNN
F 1 "Earth" H 6300 1450 50  0001 C CNN
F 2 "" H 6300 1600 50  0001 C CNN
F 3 "~" H 6300 1600 50  0001 C CNN
	1    6300 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6000 1250 6300 1250
Wire Wire Line
	6300 1250 6300 1300
Wire Wire Line
	6300 1200 6300 1250
Connection ~ 6300 1250
$Comp
L Device:LED D?
U 1 1 6210EC5B
P 8750 900
F 0 "D?" V 8789 782 50  0000 R CNN
F 1 "LED" V 8698 782 50  0000 R CNN
F 2 "" H 8750 900 50  0001 C CNN
F 3 "~" H 8750 900 50  0001 C CNN
	1    8750 900 
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D?
U 1 1 6211074E
P 9150 900
F 0 "D?" V 9189 782 50  0000 R CNN
F 1 "LED" V 9098 782 50  0000 R CNN
F 2 "" H 9150 900 50  0001 C CNN
F 3 "~" H 9150 900 50  0001 C CNN
	1    9150 900 
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 62114399
P 8750 1200
F 0 "R?" H 8820 1246 50  0000 L CNN
F 1 "1K" H 8820 1155 50  0000 L CNN
F 2 "" V 8680 1200 50  0001 C CNN
F 3 "~" H 8750 1200 50  0001 C CNN
	1    8750 1200
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 621173DE
P 9150 1200
F 0 "R?" H 9220 1246 50  0000 L CNN
F 1 "1K" H 9220 1155 50  0000 L CNN
F 2 "" V 9080 1200 50  0001 C CNN
F 3 "~" H 9150 1200 50  0001 C CNN
	1    9150 1200
	1    0    0    -1  
$EndComp
$Comp
L power:Earth #PWR?
U 1 1 62117743
P 8950 1350
F 0 "#PWR?" H 8950 1100 50  0001 C CNN
F 1 "Earth" H 8950 1200 50  0001 C CNN
F 2 "" H 8950 1350 50  0001 C CNN
F 3 "~" H 8950 1350 50  0001 C CNN
	1    8950 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	8750 1350 8950 1350
Wire Wire Line
	8950 1350 9150 1350
Connection ~ 8950 1350
$Comp
L MCU_Module:Arduino_Nano_v2.x A?
U 1 1 62120977
P 6650 3300
F 0 "A?" H 6650 2211 50  0000 C CNN
F 1 "Arduino_Nano_v2.x" H 6650 2120 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 6650 3300 50  0001 C CIN
F 3 "https://www.arduino.cc/en/uploads/Main/ArduinoNanoManual23.pdf" H 6650 3300 50  0001 C CNN
	1    6650 3300
	1    0    0    -1  
$EndComp
$Comp
L TickerForge:BAT_1049P J?
U 1 1 6208726E
P 7950 1050
F 0 "J?" H 8228 1071 50  0000 L CNN
F 1 "BAT_1049P" H 8228 980 50  0000 L CNN
F 2 "" H 8050 900 50  0001 C CNN
F 3 "" H 8050 900 50  0001 C CNN
	1    7950 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	7800 1200 7950 1200
Wire Wire Line
	7950 1200 7950 950 
Wire Wire Line
	7950 950  8100 950 
$Comp
L power:+BATT #PWR?
U 1 1 6208AB7D
P 7800 950
F 0 "#PWR?" H 7800 800 50  0001 C CNN
F 1 "+BATT" H 7815 1123 50  0000 C CNN
F 2 "" H 7800 950 50  0001 C CNN
F 3 "" H 7800 950 50  0001 C CNN
	1    7800 950 
	1    0    0    -1  
$EndComp
$Comp
L power:Earth #PWR?
U 1 1 6208B5B2
P 10100 3550
F 0 "#PWR?" H 10100 3300 50  0001 C CNN
F 1 "Earth" H 10100 3400 50  0001 C CNN
F 2 "" H 10100 3550 50  0001 C CNN
F 3 "~" H 10100 3550 50  0001 C CNN
	1    10100 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2150 700  2250 700 
Wire Wire Line
	8750 750  8950 750 
$Comp
L power:+5V #PWR?
U 1 1 6208D21D
P 6850 2300
F 0 "#PWR?" H 6850 2150 50  0001 C CNN
F 1 "+5V" H 6900 2450 50  0000 C CNN
F 2 "" H 6850 2300 50  0001 C CNN
F 3 "" H 6850 2300 50  0001 C CNN
	1    6850 2300
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 6208E5D4
P 6200 850
F 0 "#PWR?" H 6200 700 50  0001 C CNN
F 1 "+5V" H 6215 1023 50  0000 C CNN
F 2 "" H 6200 850 50  0001 C CNN
F 3 "" H 6200 850 50  0001 C CNN
	1    6200 850 
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 6208F1A9
P 8950 750
F 0 "#PWR?" H 8950 600 50  0001 C CNN
F 1 "+5V" H 8965 923 50  0000 C CNN
F 2 "" H 8950 750 50  0001 C CNN
F 3 "" H 8950 750 50  0001 C CNN
	1    8950 750 
	1    0    0    -1  
$EndComp
Connection ~ 8950 750 
Wire Wire Line
	8950 750  9150 750 
$Comp
L power:+5V #PWR?
U 1 1 62091695
P 5250 800
F 0 "#PWR?" H 5250 650 50  0001 C CNN
F 1 "+5V" H 5265 973 50  0000 C CNN
F 2 "" H 5250 800 50  0001 C CNN
F 3 "" H 5250 800 50  0001 C CNN
	1    5250 800 
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 62092806
P 4350 800
F 0 "#PWR?" H 4350 650 50  0001 C CNN
F 1 "+5V" H 4365 973 50  0000 C CNN
F 2 "" H 4350 800 50  0001 C CNN
F 3 "" H 4350 800 50  0001 C CNN
	1    4350 800 
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 62093125
P 3400 800
F 0 "#PWR?" H 3400 650 50  0001 C CNN
F 1 "+5V" H 3415 973 50  0000 C CNN
F 2 "" H 3400 800 50  0001 C CNN
F 3 "" H 3400 800 50  0001 C CNN
	1    3400 800 
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 62094BAE
P 2250 700
F 0 "#PWR?" H 2250 550 50  0001 C CNN
F 1 "+5V" H 2265 873 50  0000 C CNN
F 2 "" H 2250 700 50  0001 C CNN
F 3 "" H 2250 700 50  0001 C CNN
	1    2250 700 
	1    0    0    -1  
$EndComp
Connection ~ 2250 700 
Wire Wire Line
	2250 700  2350 700 
$Comp
L power:+5V #PWR?
U 1 1 62095677
P 850 700
F 0 "#PWR?" H 850 550 50  0001 C CNN
F 1 "+5V" H 865 873 50  0000 C CNN
F 2 "" H 850 700 50  0001 C CNN
F 3 "" H 850 700 50  0001 C CNN
	1    850  700 
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 620983A3
P 6750 2300
F 0 "#PWR?" H 6750 2150 50  0001 C CNN
F 1 "+3.3V" H 6765 2473 50  0000 C CNN
F 2 "" H 6750 2300 50  0001 C CNN
F 3 "" H 6750 2300 50  0001 C CNN
	1    6750 2300
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 620906FB
P 10850 750
F 0 "#PWR?" H 10850 600 50  0001 C CNN
F 1 "+5V" H 10865 923 50  0000 C CNN
F 2 "" H 10850 750 50  0001 C CNN
F 3 "" H 10850 750 50  0001 C CNN
	1    10850 750 
	1    0    0    -1  
$EndComp
Text GLabel 10550 950  1    50   Input ~ 0
LED_?
$Comp
L power:Earth #PWR?
U 1 1 621337C3
P 10850 1750
F 0 "#PWR?" H 10850 1500 50  0001 C CNN
F 1 "Earth" H 10850 1600 50  0001 C CNN
F 2 "" H 10850 1750 50  0001 C CNN
F 3 "~" H 10850 1750 50  0001 C CNN
	1    10850 1750
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 621337BD
P 10850 1200
F 0 "R?" H 10920 1246 50  0000 L CNN
F 1 "1K" H 10920 1155 50  0000 L CNN
F 2 "" V 10780 1200 50  0001 C CNN
F 3 "~" H 10850 1200 50  0001 C CNN
	1    10850 1200
	-1   0    0    1   
$EndComp
$Comp
L Transistor_BJT:2N2219 Q?
U 1 1 621337B7
P 10750 1550
F 0 "Q?" H 10940 1596 50  0000 L CNN
F 1 "S9013" H 10940 1505 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-39-3" H 10950 1475 50  0001 L CIN
F 3 "http://www.onsemi.com/pub_link/Collateral/2N2219-D.PDF" H 10750 1550 50  0001 L CNN
	1    10750 1550
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D?
U 1 1 621337AB
P 10850 900
F 0 "D?" V 10889 782 50  0000 R CNN
F 1 "LED" V 10798 782 50  0000 R CNN
F 2 "" H 10850 900 50  0001 C CNN
F 3 "~" H 10850 900 50  0001 C CNN
	1    10850 900 
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 6209E66F
P 10550 1400
F 0 "R?" H 10620 1446 50  0000 L CNN
F 1 "4K7" H 10620 1355 50  0000 L CNN
F 2 "" V 10480 1400 50  0001 C CNN
F 3 "~" H 10550 1400 50  0001 C CNN
	1    10550 1400
	-1   0    0    1   
$EndComp
Wire Wire Line
	10550 950  10550 1250
$Comp
L power:+5V #PWR?
U 1 1 620ABC71
P 10050 750
F 0 "#PWR?" H 10050 600 50  0001 C CNN
F 1 "+5V" H 10065 923 50  0000 C CNN
F 2 "" H 10050 750 50  0001 C CNN
F 3 "" H 10050 750 50  0001 C CNN
	1    10050 750 
	1    0    0    -1  
$EndComp
Text GLabel 9750 950  1    50   Input ~ 0
LED_?
$Comp
L power:Earth #PWR?
U 1 1 620ABC78
P 10050 1750
F 0 "#PWR?" H 10050 1500 50  0001 C CNN
F 1 "Earth" H 10050 1600 50  0001 C CNN
F 2 "" H 10050 1750 50  0001 C CNN
F 3 "~" H 10050 1750 50  0001 C CNN
	1    10050 1750
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 620ABC7E
P 10050 1200
F 0 "R?" H 10120 1246 50  0000 L CNN
F 1 "1K" H 10120 1155 50  0000 L CNN
F 2 "" V 9980 1200 50  0001 C CNN
F 3 "~" H 10050 1200 50  0001 C CNN
	1    10050 1200
	-1   0    0    1   
$EndComp
$Comp
L Transistor_BJT:2N2219 Q?
U 1 1 620ABC84
P 9950 1550
F 0 "Q?" H 10140 1596 50  0000 L CNN
F 1 "S9013" H 10140 1505 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-39-3" H 10150 1475 50  0001 L CIN
F 3 "http://www.onsemi.com/pub_link/Collateral/2N2219-D.PDF" H 9950 1550 50  0001 L CNN
	1    9950 1550
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D?
U 1 1 620ABC8A
P 10050 900
F 0 "D?" V 10089 782 50  0000 R CNN
F 1 "LED" V 9998 782 50  0000 R CNN
F 2 "" H 10050 900 50  0001 C CNN
F 3 "~" H 10050 900 50  0001 C CNN
	1    10050 900 
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 620ABC90
P 9750 1400
F 0 "R?" H 9820 1446 50  0000 L CNN
F 1 "4K7" H 9820 1355 50  0000 L CNN
F 2 "" V 9680 1400 50  0001 C CNN
F 3 "~" H 9750 1400 50  0001 C CNN
	1    9750 1400
	-1   0    0    1   
$EndComp
Wire Wire Line
	9750 950  9750 1250
$Comp
L Switch:SW_SPST Btn_?
U 1 1 620AF495
P 7250 1450
F 0 "Btn_?" V 7204 1548 50  0000 L CNN
F 1 "SW_SPST" V 7295 1548 50  0000 L CNN
F 2 "" H 7250 1450 50  0001 C CNN
F 3 "~" H 7250 1450 50  0001 C CNN
	1    7250 1450
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 620AF49B
P 6950 1000
F 0 "R?" H 7020 1046 50  0000 L CNN
F 1 "1K" H 7020 955 50  0000 L CNN
F 2 "" V 6880 1000 50  0001 C CNN
F 3 "~" H 6950 1000 50  0001 C CNN
	1    6950 1000
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 620AF4A1
P 7250 1000
F 0 "R?" H 7320 1046 50  0000 L CNN
F 1 "10K" H 7320 955 50  0000 L CNN
F 2 "" V 7180 1000 50  0001 C CNN
F 3 "~" H 7250 1000 50  0001 C CNN
	1    7250 1000
	-1   0    0    1   
$EndComp
Text GLabel 6950 850  1    50   Input ~ 0
RESET
$Comp
L power:Earth #PWR?
U 1 1 620AF4A8
P 7250 1650
F 0 "#PWR?" H 7250 1400 50  0001 C CNN
F 1 "Earth" H 7250 1500 50  0001 C CNN
F 2 "" H 7250 1650 50  0001 C CNN
F 3 "~" H 7250 1650 50  0001 C CNN
	1    7250 1650
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 620AF4B2
P 7250 850
F 0 "#PWR?" H 7250 700 50  0001 C CNN
F 1 "+5V" H 7265 1023 50  0000 C CNN
F 2 "" H 7250 850 50  0001 C CNN
F 3 "" H 7250 850 50  0001 C CNN
	1    7250 850 
	1    0    0    -1  
$EndComp
Wire Wire Line
	6950 1150 7250 1150
Wire Wire Line
	7250 1150 7250 1250
Connection ~ 7250 1150
NoConn ~ 7150 2800
Text GLabel 7150 2700 2    50   Input ~ 0
RESET
$Comp
L Regulator_Linear:LM1117-5.0 U?
U 1 1 620C219A
P 10100 3200
F 0 "U?" H 10100 3442 50  0000 C CNN
F 1 "LM1117-5.0" H 10100 3351 50  0000 C CNN
F 2 "" H 10100 3200 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm1117.pdf" H 10100 3200 50  0001 C CNN
	1    10100 3200
	1    0    0    -1  
$EndComp
$Comp
L power:Earth #PWR?
U 1 1 620C3F22
P 8100 1200
F 0 "#PWR?" H 8100 950 50  0001 C CNN
F 1 "Earth" H 8100 1050 50  0001 C CNN
F 2 "" H 8100 1200 50  0001 C CNN
F 3 "~" H 8100 1200 50  0001 C CNN
	1    8100 1200
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 620CB307
P 9600 3400
F 0 "C?" H 9715 3446 50  0000 L CNN
F 1 "100nF" H 9715 3355 50  0000 L CNN
F 2 "" H 9638 3250 50  0001 C CNN
F 3 "~" H 9600 3400 50  0001 C CNN
	1    9600 3400
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 620CD3F9
P 10600 3400
F 0 "C?" H 10715 3446 50  0000 L CNN
F 1 "100nF" H 10715 3355 50  0000 L CNN
F 2 "" H 10638 3250 50  0001 C CNN
F 3 "~" H 10600 3400 50  0001 C CNN
	1    10600 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	10400 3200 10450 3200
Wire Wire Line
	10600 3200 10600 3250
Wire Wire Line
	9600 3550 10100 3550
Wire Wire Line
	10100 3500 10100 3550
Connection ~ 10100 3550
Wire Wire Line
	10600 3550 10100 3550
Wire Wire Line
	9600 3250 9600 3200
Wire Wire Line
	9600 3200 9750 3200
$Comp
L power:+BATT #PWR?
U 1 1 620D8F66
P 9600 3200
F 0 "#PWR?" H 9600 3050 50  0001 C CNN
F 1 "+BATT" H 9615 3373 50  0000 C CNN
F 2 "" H 9600 3200 50  0001 C CNN
F 3 "" H 9600 3200 50  0001 C CNN
	1    9600 3200
	1    0    0    -1  
$EndComp
Connection ~ 9600 3200
$Comp
L power:+5V #PWR?
U 1 1 620D9A12
P 10600 3200
F 0 "#PWR?" H 10600 3050 50  0001 C CNN
F 1 "+5V" H 10615 3373 50  0000 C CNN
F 2 "" H 10600 3200 50  0001 C CNN
F 3 "" H 10600 3200 50  0001 C CNN
	1    10600 3200
	1    0    0    -1  
$EndComp
Connection ~ 10600 3200
$Comp
L Device:D D?
U 1 1 620DB9B0
P 10100 2850
F 0 "D?" H 10200 2950 50  0000 C CNN
F 1 "D" H 10000 2950 50  0000 C CNN
F 2 "" H 10100 2850 50  0001 C CNN
F 3 "~" H 10100 2850 50  0001 C CNN
	1    10100 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	10250 2850 10450 2850
Wire Wire Line
	10450 2850 10450 3200
Connection ~ 10450 3200
Wire Wire Line
	10450 3200 10600 3200
Wire Wire Line
	9950 2850 9750 2850
Wire Wire Line
	9750 2850 9750 3200
Connection ~ 9750 3200
Wire Wire Line
	9750 3200 9800 3200
$Comp
L Connector_Generic:Conn_02x04_Counter_Clockwise J?
U 1 1 620E8786
P 9900 2400
F 0 "J?" H 9950 2717 50  0000 C CNN
F 1 "Conn_02x04_Counter_Clockwise" H 9950 2626 50  0000 C CNN
F 2 "" H 9900 2400 50  0001 C CNN
F 3 "~" H 9900 2400 50  0001 C CNN
	1    9900 2400
	1    0    0    -1  
$EndComp
$Comp
L power:Earth #PWR?
U 1 1 620EA0AA
P 9200 2300
F 0 "#PWR?" H 9200 2050 50  0001 C CNN
F 1 "Earth" H 9200 2150 50  0001 C CNN
F 2 "" H 9200 2300 50  0001 C CNN
F 3 "~" H 9200 2300 50  0001 C CNN
	1    9200 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	9700 2300 9200 2300
$Comp
L power:+3.3V #PWR?
U 1 1 620F064F
P 10600 2300
F 0 "#PWR?" H 10600 2150 50  0001 C CNN
F 1 "+3.3V" H 10615 2473 50  0000 C CNN
F 2 "" H 10600 2300 50  0001 C CNN
F 3 "" H 10600 2300 50  0001 C CNN
	1    10600 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	10200 2300 10600 2300
Text GLabel 9700 2400 0    50   Input ~ 0
NRF_CE
Text GLabel 9700 2500 0    50   Input ~ 0
NRF_SCK
Text GLabel 9700 2600 0    50   Input ~ 0
NRF_MISO
Text GLabel 10200 2600 2    50   Input ~ 0
NRF_IRQ
Text GLabel 10200 2500 2    50   Input ~ 0
NRF_MOSI
Text GLabel 10200 2400 2    50   Input ~ 0
NRF_CSN
$Comp
L power:+3.3V #PWR?
U 1 1 620F525F
P 10950 2300
F 0 "#PWR?" H 10950 2150 50  0001 C CNN
F 1 "+3.3V" H 10965 2473 50  0000 C CNN
F 2 "" H 10950 2300 50  0001 C CNN
F 3 "" H 10950 2300 50  0001 C CNN
	1    10950 2300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 620F58B9
P 10950 2450
F 0 "C?" H 11065 2496 50  0000 L CNN
F 1 "10uF" H 11065 2405 50  0000 L CNN
F 2 "" H 10988 2300 50  0001 C CNN
F 3 "~" H 10950 2450 50  0001 C CNN
	1    10950 2450
	1    0    0    -1  
$EndComp
$Comp
L power:Earth #PWR?
U 1 1 620F67B9
P 10950 2600
F 0 "#PWR?" H 10950 2350 50  0001 C CNN
F 1 "Earth" H 10950 2450 50  0001 C CNN
F 2 "" H 10950 2600 50  0001 C CNN
F 3 "~" H 10950 2600 50  0001 C CNN
	1    10950 2600
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPDT SW?
U 1 1 620F8D01
P 5350 1000
F 0 "SW?" V 5400 850 50  0000 R CNN
F 1 "SW_SPDT" V 5300 950 50  0000 R CNN
F 2 "" H 5350 1000 50  0001 C CNN
F 3 "~" H 5350 1000 50  0001 C CNN
	1    5350 1000
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_SPDT SW?
U 1 1 620FA2D7
P 6300 1000
F 0 "SW?" V 6350 850 50  0000 R CNN
F 1 "SW_SPDT" V 6250 950 50  0000 R CNN
F 2 "" H 6300 1000 50  0001 C CNN
F 3 "~" H 6300 1000 50  0001 C CNN
	1    6300 1000
	0    -1   -1   0   
$EndComp
NoConn ~ 6400 800 
NoConn ~ 5450 800 
$Comp
L TickerForge:JOYSTICK_BUTTON U?
U 1 1 62093E61
P 2500 2650
F 0 "U?" H 3028 2703 60  0000 L CNN
F 1 "LEFT_JOYSTICK" H 3028 2597 60  0000 L CNN
F 2 "" H 2500 2650 60  0000 C CNN
F 3 "" H 2500 2650 60  0000 C CNN
	1    2500 2650
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 620E6CCC
P 800 2950
F 0 "#PWR?" H 800 2800 50  0001 C CNN
F 1 "+5V" H 815 3123 50  0000 C CNN
F 2 "" H 800 2950 50  0001 C CNN
F 3 "" H 800 2950 50  0001 C CNN
	1    800  2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 3050 1850 3050
Wire Wire Line
	1650 3050 1650 3150
Connection ~ 1650 3050
Wire Wire Line
	1850 2600 1750 2600
Wire Wire Line
	1750 2600 1750 2250
Wire Wire Line
	1750 2250 1850 2250
$Comp
L power:+3.3V #PWR?
U 1 1 620FB27E
P 1750 2250
F 0 "#PWR?" H 1750 2100 50  0001 C CNN
F 1 "+3.3V" H 1765 2423 50  0000 C CNN
F 2 "" H 1750 2250 50  0001 C CNN
F 3 "" H 1750 2250 50  0001 C CNN
	1    1750 2250
	1    0    0    -1  
$EndComp
Connection ~ 1750 2250
$Comp
L Device:R R?
U 1 1 620FBEC3
P 1050 2350
F 0 "R?" H 1120 2396 50  0000 L CNN
F 1 "620" H 1120 2305 50  0000 L CNN
F 2 "" V 980 2350 50  0001 C CNN
F 3 "~" H 1050 2350 50  0001 C CNN
	1    1050 2350
	0    1    1    0   
$EndComp
Text GLabel 900  2350 0    50   Input ~ 0
L_PITCH
$Comp
L Device:C C?
U 1 1 620FDDBF
P 1350 2450
F 0 "C?" V 1400 2300 50  0000 L CNN
F 1 "100nF" V 1400 2500 50  0000 L CNN
F 2 "" H 1388 2300 50  0001 C CNN
F 3 "~" H 1350 2450 50  0001 C CNN
	1    1350 2450
	0    1    1    0   
$EndComp
Wire Wire Line
	1200 2350 1850 2350
Wire Wire Line
	1500 2450 1800 2450
Wire Wire Line
	1200 2450 1200 2350
Connection ~ 1200 2350
Wire Wire Line
	1850 2800 1800 2800
Wire Wire Line
	1800 2800 1800 2450
Connection ~ 1800 2450
Wire Wire Line
	1800 2450 1850 2450
$Comp
L power:Earth #PWR?
U 1 1 6211BA50
P 1800 3450
F 0 "#PWR?" H 1800 3200 50  0001 C CNN
F 1 "Earth" H 1800 3300 50  0001 C CNN
F 2 "" H 1800 3450 50  0001 C CNN
F 3 "~" H 1800 3450 50  0001 C CNN
	1    1800 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 3450 1800 2800
Connection ~ 1800 2800
$Comp
L Device:R R?
U 1 1 62121E98
P 1050 2700
F 0 "R?" H 1120 2746 50  0000 L CNN
F 1 "620" H 1120 2655 50  0000 L CNN
F 2 "" V 980 2700 50  0001 C CNN
F 3 "~" H 1050 2700 50  0001 C CNN
	1    1050 2700
	0    1    1    0   
$EndComp
Text GLabel 900  2700 0    50   Input ~ 0
L_ROLL
$Comp
L Device:C C?
U 1 1 62121E9F
P 1350 2800
F 0 "C?" V 1400 2650 50  0000 L CNN
F 1 "100nF" V 1400 2850 50  0000 L CNN
F 2 "" H 1388 2650 50  0001 C CNN
F 3 "~" H 1350 2800 50  0001 C CNN
	1    1350 2800
	0    1    1    0   
$EndComp
Wire Wire Line
	1200 2700 1850 2700
Wire Wire Line
	1500 2800 1800 2800
Wire Wire Line
	1200 2800 1200 2700
Connection ~ 1200 2700
Wire Wire Line
	800  2950 1850 2950
$Comp
L Device:R R?
U 1 1 62138556
P 1500 4700
F 0 "R?" V 1600 4650 50  0000 L CNN
F 1 "1K" V 1600 4500 50  0000 L CNN
F 2 "" V 1430 4700 50  0001 C CNN
F 3 "~" H 1500 4700 50  0001 C CNN
	1    1500 4700
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 6213855C
P 1650 4950
F 0 "R?" H 1720 4996 50  0000 L CNN
F 1 "10K" H 1720 4905 50  0000 L CNN
F 2 "" V 1580 4950 50  0001 C CNN
F 3 "~" H 1650 4950 50  0001 C CNN
	1    1650 4950
	-1   0    0    1   
$EndComp
Text GLabel 1350 4700 0    50   Input ~ 0
Btn_R3
$Comp
L power:Earth #PWR?
U 1 1 62138563
P 1650 5100
F 0 "#PWR?" H 1650 4850 50  0001 C CNN
F 1 "Earth" H 1650 4950 50  0001 C CNN
F 2 "" H 1650 5100 50  0001 C CNN
F 3 "~" H 1650 5100 50  0001 C CNN
	1    1650 5100
	1    0    0    -1  
$EndComp
$Comp
L TickerForge:JOYSTICK_BUTTON U?
U 1 1 62138569
P 2500 4300
F 0 "U?" H 3028 4353 60  0000 L CNN
F 1 "RIGHT_JOYSTICK" H 3028 4247 60  0000 L CNN
F 2 "" H 2500 4300 60  0000 C CNN
F 3 "" H 2500 4300 60  0000 C CNN
	1    2500 4300
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 6213856F
P 800 4600
F 0 "#PWR?" H 800 4450 50  0001 C CNN
F 1 "+5V" H 815 4773 50  0000 C CNN
F 2 "" H 800 4600 50  0001 C CNN
F 3 "" H 800 4600 50  0001 C CNN
	1    800  4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 4700 1850 4700
Wire Wire Line
	1650 4700 1650 4800
Connection ~ 1650 4700
Wire Wire Line
	1850 4250 1750 4250
Wire Wire Line
	1750 4250 1750 3900
Wire Wire Line
	1750 3900 1850 3900
$Comp
L power:+3.3V #PWR?
U 1 1 6213857B
P 1750 3900
F 0 "#PWR?" H 1750 3750 50  0001 C CNN
F 1 "+3.3V" H 1765 4073 50  0000 C CNN
F 2 "" H 1750 3900 50  0001 C CNN
F 3 "" H 1750 3900 50  0001 C CNN
	1    1750 3900
	1    0    0    -1  
$EndComp
Connection ~ 1750 3900
$Comp
L Device:R R?
U 1 1 62138582
P 1050 4000
F 0 "R?" H 1120 4046 50  0000 L CNN
F 1 "620" H 1120 3955 50  0000 L CNN
F 2 "" V 980 4000 50  0001 C CNN
F 3 "~" H 1050 4000 50  0001 C CNN
	1    1050 4000
	0    1    1    0   
$EndComp
Text GLabel 900  4000 0    50   Input ~ 0
R_PITCH
$Comp
L Device:C C?
U 1 1 62138589
P 1350 4100
F 0 "C?" V 1400 3950 50  0000 L CNN
F 1 "100nF" V 1400 4150 50  0000 L CNN
F 2 "" H 1388 3950 50  0001 C CNN
F 3 "~" H 1350 4100 50  0001 C CNN
	1    1350 4100
	0    1    1    0   
$EndComp
Wire Wire Line
	1200 4000 1850 4000
Wire Wire Line
	1500 4100 1800 4100
Wire Wire Line
	1200 4100 1200 4000
Connection ~ 1200 4000
Wire Wire Line
	1850 4450 1800 4450
Wire Wire Line
	1800 4450 1800 4100
Connection ~ 1800 4100
Wire Wire Line
	1800 4100 1850 4100
$Comp
L power:Earth #PWR?
U 1 1 62138597
P 1800 5100
F 0 "#PWR?" H 1800 4850 50  0001 C CNN
F 1 "Earth" H 1800 4950 50  0001 C CNN
F 2 "" H 1800 5100 50  0001 C CNN
F 3 "~" H 1800 5100 50  0001 C CNN
	1    1800 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 5100 1800 4450
Connection ~ 1800 4450
$Comp
L Device:R R?
U 1 1 6213859F
P 1050 4350
F 0 "R?" H 1120 4396 50  0000 L CNN
F 1 "620" H 1120 4305 50  0000 L CNN
F 2 "" V 980 4350 50  0001 C CNN
F 3 "~" H 1050 4350 50  0001 C CNN
	1    1050 4350
	0    1    1    0   
$EndComp
Text GLabel 900  4350 0    50   Input ~ 0
R_ROLL
$Comp
L Device:C C?
U 1 1 621385A6
P 1350 4450
F 0 "C?" V 1400 4300 50  0000 L CNN
F 1 "100nF" V 1400 4500 50  0000 L CNN
F 2 "" H 1388 4300 50  0001 C CNN
F 3 "~" H 1350 4450 50  0001 C CNN
	1    1350 4450
	0    1    1    0   
$EndComp
Wire Wire Line
	1200 4350 1850 4350
Wire Wire Line
	1500 4450 1800 4450
Wire Wire Line
	1200 4450 1200 4350
Connection ~ 1200 4350
Wire Wire Line
	800  4600 1850 4600
$EndSCHEMATC
