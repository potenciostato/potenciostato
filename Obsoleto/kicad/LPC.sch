EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 4
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
L potenciostato-rescue:LPCXPRESSO_LPC1769-LPCXPRESSO_LPC1769 LPC?
U 1 1 6014AC32
P 4000 3100
AR Path="/6014AC32" Ref="LPC?"  Part="1" 
AR Path="/60147E53/6014AC32" Ref="LPC1"  Part="1" 
F 0 "LPC1" H 4150 4770 50  0000 C CNN
F 1 "LPCXPRESSO_LPC1769" H 4150 4679 50  0000 C CNN
F 2 "LPC:LPCXPRESSO_LPC1769" H 4000 3100 50  0001 L BNN
F 3 "" H 4000 3100 50  0001 L BNN
	1    4000 3100
	1    0    0    -1  
$EndComp
Text HLabel 2550 1700 0    50   Input ~ 0
GND
Text HLabel 6050 1650 2    50   Input ~ 0
3.3V
Wire Wire Line
	5500 1700 6050 1700
Wire Wire Line
	6050 1700 6050 1650
Wire Wire Line
	2800 3400 2200 3400
Text HLabel 2200 3400 0    50   Input ~ 0
DAC
$Comp
L potenciostato-rescue:USB_B_Micro-Connector J2
U 1 1 609A40C2
P 6850 2600
AR Path="/609A40C2" Ref="J2"  Part="1" 
AR Path="/60147E53/609A40C2" Ref="J2"  Part="1" 
F 0 "J2" H 6620 2496 50  0000 R CNN
F 1 "USB_B_Micro" H 6620 2589 50  0000 R CNN
F 2 "Connector_USB:USB_A_CNCTech_1001-011-01101_Horizontal" H 7000 2550 50  0001 C CNN
F 3 "~" H 7000 2550 50  0001 C CNN
	1    6850 2600
	-1   0    0    1   
$EndComp
Wire Wire Line
	5500 2500 6550 2500
Wire Wire Line
	5500 2600 6550 2600
Wire Wire Line
	5500 4300 5700 4300
Wire Wire Line
	7400 2050 6950 2050
Wire Wire Line
	6850 2050 6850 2200
Wire Wire Line
	2800 3100 2200 3100
Wire Wire Line
	2800 3200 2200 3200
Text HLabel 2200 3200 0    50   Input ~ 0
ADC1
Text HLabel 2200 3100 0    50   Input ~ 0
ADC0
Wire Wire Line
	2800 1800 2550 1800
Text HLabel 2550 1800 0    50   Input ~ 0
5V
Wire Wire Line
	2800 3700 2200 3700
Wire Wire Line
	2800 3800 2200 3800
Wire Wire Line
	2800 4000 2200 4000
Wire Wire Line
	2800 3900 2200 3900
Wire Wire Line
	5500 3900 5950 3900
Wire Wire Line
	5500 3800 5950 3800
Wire Wire Line
	5500 3700 5950 3700
Wire Wire Line
	5500 3600 5950 3600
Wire Wire Line
	5500 3500 5950 3500
Wire Wire Line
	5500 3400 5950 3400
Wire Wire Line
	5500 3200 5950 3200
Wire Wire Line
	5500 3300 5950 3300
Text HLabel 5950 3200 2    50   Input ~ 0
P2.1
Text HLabel 5950 3300 2    50   Input ~ 0
P2.2
Text HLabel 5950 3400 2    50   Input ~ 0
P2.3
Text HLabel 5950 3500 2    50   Input ~ 0
P2.4
Text HLabel 5950 3600 2    50   Input ~ 0
P2.5
Text HLabel 5950 3800 2    50   Input ~ 0
P2.7
Text HLabel 5950 3700 2    50   Input ~ 0
P2.6
Text HLabel 5950 3900 2    50   Input ~ 0
P2.8
Text HLabel 2200 3700 0    50   Input ~ 0
P0.2
Text HLabel 2200 3800 0    50   Input ~ 0
P0.3
Text HLabel 2200 3900 0    50   Input ~ 0
P0.21
Text HLabel 2200 4000 0    50   Input ~ 0
P0.22
$Comp
L potenciostato-rescue:GND-power #PWR0131
U 1 1 60A0C4F1
P 5700 4300
F 0 "#PWR0131" H 5700 4050 50  0001 C CNN
F 1 "GND" H 5705 4123 50  0000 C CNN
F 2 "" H 5700 4300 50  0001 C CNN
F 3 "" H 5700 4300 50  0001 C CNN
	1    5700 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 1700 2650 1700
$Comp
L potenciostato-rescue:GND-power #PWR0132
U 1 1 60A0D2ED
P 7400 2050
F 0 "#PWR0132" H 7400 1800 50  0001 C CNN
F 1 "GND" H 7405 1873 50  0000 C CNN
F 2 "" H 7400 2050 50  0001 C CNN
F 3 "" H 7400 2050 50  0001 C CNN
	1    7400 2050
	1    0    0    -1  
$EndComp
$Comp
L potenciostato-rescue:GND-power #PWR0133
U 1 1 60A0D30E
P 2800 1400
F 0 "#PWR0133" H 2800 1150 50  0001 C CNN
F 1 "GND" H 2805 1223 50  0000 C CNN
F 2 "" H 2800 1400 50  0001 C CNN
F 3 "" H 2800 1400 50  0001 C CNN
	1    2800 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 1400 2650 1400
Wire Wire Line
	2650 1400 2650 1700
Connection ~ 2650 1700
Wire Wire Line
	2650 1700 2800 1700
Wire Wire Line
	6950 2200 6950 2050
Connection ~ 6950 2050
Wire Wire Line
	6950 2050 6850 2050
Text Label 4200 3850 0    50   ~ 0
Pin13_U8
Text Label 4200 3650 0    50   ~ 0
Pin5_U8
Text Label 4200 3750 0    50   ~ 0
Pin6_U8
Text Label 4200 3950 0    50   ~ 0
Pin12_U8
$EndSCHEMATC
