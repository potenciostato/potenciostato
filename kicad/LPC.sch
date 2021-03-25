EESchema Schematic File Version 4
LIBS:potenciostato-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 3
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
L LPCXPRESSO_LPC1769:LPCXPRESSO_LPC1769 LPC?
U 1 1 6014AC32
P 4000 3100
AR Path="/6014AC32" Ref="LPC?"  Part="1" 
AR Path="/60147E53/6014AC32" Ref="LPC?"  Part="1" 
F 0 "LPC?" H 4150 4770 50  0000 C CNN
F 1 "LPCXPRESSO_LPC1769" H 4150 4679 50  0000 C CNN
F 2 "LPCXPRESSO_LPC1769:LPCXPRESSO_LPC1769" H 4000 3100 50  0001 L BNN
F 3 "" H 4000 3100 50  0001 L BNN
	1    4000 3100
	1    0    0    -1  
$EndComp
Text HLabel 2550 1700 0    50   Input ~ 0
GND
Wire Wire Line
	2550 1700 2800 1700
Text HLabel 6050 1650 2    50   Input ~ 0
3.3V
Wire Wire Line
	5500 1700 6050 1700
Wire Wire Line
	6050 1700 6050 1650
$EndSCHEMATC
