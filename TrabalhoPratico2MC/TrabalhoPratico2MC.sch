EESchema Schematic File Version 4
EELAYER 29 0
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
L power:+5V #PWR?
U 1 1 5CF6348E
P 4100 850
F 0 "#PWR?" H 4100 700 50  0001 C CNN
F 1 "+5V" H 4115 1023 50  0000 C CNN
F 2 "" H 4100 850 50  0001 C CNN
F 3 "" H 4100 850 50  0001 C CNN
	1    4100 850 
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5CF63AA4
P 4100 4650
F 0 "#PWR?" H 4100 4400 50  0001 C CNN
F 1 "GND" H 4105 4477 50  0000 C CNN
F 2 "" H 4100 4650 50  0001 C CNN
F 3 "" H 4100 4650 50  0001 C CNN
	1    4100 4650
	1    0    0    -1  
$EndComp
$Comp
L MCU_Microchip_ATmega:ATmega168A-PU U?
U 1 1 5CF63EA6
P 4100 2700
F 0 "U?" H 3457 2746 50  0000 R CNN
F 1 "ATmega168A-PU" H 3457 2655 50  0000 R CNN
F 2 "Package_DIP:DIP-28_W7.62mm" H 4100 2700 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega48A_88A_168A-Data-Sheet-40002007A.pdf" H 4100 2700 50  0001 C CNN
	1    4100 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4050 4650 4100 4650
Connection ~ 4100 4650
Wire Wire Line
	4100 850  4100 950 
$Comp
L Motor:Motor_Servo M?
U 1 1 5CF6957D
P 6700 1600
F 0 "M?" H 7032 1665 50  0000 L CNN
F 1 "Motor_Servo" H 7032 1574 50  0000 L CNN
F 2 "" H 6700 1410 50  0001 C CNN
F 3 "http://forums.parallax.com/uploads/attachments/46831/74481.png" H 6700 1410 50  0001 C CNN
	1    6700 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4700 1500 6400 1500
Wire Wire Line
	6400 1600 5450 1600
Wire Wire Line
	5450 1600 5450 950 
Wire Wire Line
	5450 950  4100 950 
Connection ~ 4100 950 
Wire Wire Line
	4100 950  4100 1200
Wire Wire Line
	4100 4200 4100 4400
Wire Wire Line
	4100 4400 6400 4400
Wire Wire Line
	6400 4400 6400 3350
Connection ~ 4100 4400
Wire Wire Line
	4100 4400 4100 4650
Wire Wire Line
	6650 2350 5250 2350
Wire Wire Line
	5250 2350 5250 1600
Wire Wire Line
	5250 1600 4700 1600
$Comp
L Switch:SW_Push SW?
U 1 1 5CF6E023
P 6850 2350
F 0 "SW?" H 6850 2635 50  0000 C CNN
F 1 "SW_Push" H 6850 2544 50  0000 C CNN
F 2 "" H 6850 2550 50  0001 C CNN
F 3 "~" H 6850 2550 50  0001 C CNN
	1    6850 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 950  7850 950 
Wire Wire Line
	7850 950  7850 2350
Wire Wire Line
	7850 2350 7050 2350
Connection ~ 5450 950 
$Comp
L Device:LED D?
U 1 1 5CF6F9B1
P 6850 2700
F 0 "D?" H 6843 2445 50  0000 C CNN
F 1 "LED" H 6843 2536 50  0000 C CNN
F 2 "" H 6850 2700 50  0001 C CNN
F 3 "~" H 6850 2700 50  0001 C CNN
	1    6850 2700
	-1   0    0    1   
$EndComp
Wire Wire Line
	7050 2700 7000 2700
Wire Wire Line
	7050 2700 7050 3350
Wire Wire Line
	7050 3350 6400 3350
Connection ~ 6400 3350
Wire Wire Line
	6400 3350 6400 1700
Wire Wire Line
	4700 3900 5850 3900
Wire Wire Line
	5850 3900 5850 2700
Wire Wire Line
	5850 2700 6700 2700
$EndSCHEMATC
