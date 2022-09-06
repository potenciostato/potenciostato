EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 3
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
L potenciostato-rescue:ICL7660-Regulator_SwitchedCapacitor U8
U 1 1 61FEE6DB
P 5250 3300
F 0 "U8" H 5250 3867 50  0000 C CNN
F 1 "ICL7660" H 5250 3776 50  0000 C CNN
F 2 "" H 5350 3200 50  0001 C CNN
F 3 "http://datasheets.maximintegrated.com/en/ds/ICL7660-MAX1044.pdf" H 5350 3200 50  0001 C CNN
	1    5250 3300
	1    0    0    -1  
$EndComp
$Comp
L potenciostato-rescue:GNDREF-power #PWR?
U 1 1 61FEFED8
P 5250 3800
F 0 "#PWR?" H 5250 3550 50  0001 C CNN
F 1 "GNDREF" H 5255 3627 50  0000 C CNN
F 2 "" H 5250 3800 50  0001 C CNN
F 3 "" H 5250 3800 50  0001 C CNN
	1    5250 3800
	1    0    0    -1  
$EndComp
$Comp
L potenciostato-rescue:GNDREF-power #PWR?
U 1 1 61FF03CE
P 4150 3500
F 0 "#PWR?" H 4150 3250 50  0001 C CNN
F 1 "GNDREF" H 4155 3327 50  0000 C CNN
F 2 "" H 4150 3500 50  0001 C CNN
F 3 "" H 4150 3500 50  0001 C CNN
	1    4150 3500
	1    0    0    -1  
$EndComp
$Comp
L potenciostato-rescue:CP-Device C10
U 1 1 61FF1C90
P 5900 3400
F 0 "C10" H 6018 3446 50  0000 L CNN
F 1 "10uF" H 6018 3355 50  0000 L CNN
F 2 "" H 5938 3250 50  0001 C CNN
F 3 "~" H 5900 3400 50  0001 C CNN
	1    5900 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 3200 5900 3200
Wire Wire Line
	5900 3200 5900 3250
Wire Wire Line
	5650 3600 5900 3600
Wire Wire Line
	5900 3600 5900 3550
$Comp
L potenciostato-rescue:+5V-power #PWR?
U 1 1 61FF3A6D
P 6600 2600
F 0 "#PWR?" H 6600 2450 50  0001 C CNN
F 1 "+5V" V 6615 2728 50  0000 L CNN
F 2 "" H 6600 2600 50  0001 C CNN
F 3 "" H 6600 2600 50  0001 C CNN
	1    6600 2600
	0    1    1    0   
$EndComp
Wire Wire Line
	4500 2600 4850 2600
Wire Wire Line
	4850 3000 4850 2600
Connection ~ 4850 2600
$Comp
L potenciostato-rescue:CP-Device C11
U 1 1 61FF5FA6
P 6350 3400
F 0 "C11" H 6468 3446 50  0000 L CNN
F 1 "10uF" H 6468 3355 50  0000 L CNN
F 2 "" H 6388 3250 50  0001 C CNN
F 3 "~" H 6350 3400 50  0001 C CNN
	1    6350 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 3250 6350 3000
Wire Wire Line
	6350 3000 5650 3000
$Comp
L potenciostato-rescue:GNDREF-power #PWR?
U 1 1 61FF65C1
P 6650 3950
F 0 "#PWR?" H 6650 3700 50  0001 C CNN
F 1 "GNDREF" H 6655 3777 50  0000 C CNN
F 2 "" H 6650 3950 50  0001 C CNN
F 3 "" H 6650 3950 50  0001 C CNN
	1    6650 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 3550 6650 3550
Wire Wire Line
	6650 3550 6650 3950
$Comp
L potenciostato-rescue:-5V-power #PWR?
U 1 1 61FF6BA0
P 6600 3000
F 0 "#PWR?" H 6600 3100 50  0001 C CNN
F 1 "-5V" V 6615 3128 50  0000 L CNN
F 2 "" H 6600 3000 50  0001 C CNN
F 3 "" H 6600 3000 50  0001 C CNN
	1    6600 3000
	0    1    1    0   
$EndComp
Wire Wire Line
	6600 3000 6350 3000
Connection ~ 6350 3000
$Comp
L potenciostato-rescue:USB_B_Micro-Connector J3
U 1 1 61FEEB78
P 4200 2800
F 0 "J3" H 4257 3267 50  0000 C CNN
F 1 "USB_B_Micro" H 4257 3176 50  0000 C CNN
F 2 "" H 4350 2750 50  0001 C CNN
F 3 "~" H 4350 2750 50  0001 C CNN
	1    4200 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 3500 4150 3200
Wire Wire Line
	4100 3200 4150 3200
Wire Wire Line
	4150 3200 4200 3200
Connection ~ 4150 3200
Wire Wire Line
	4850 2600 6600 2600
$EndSCHEMATC
