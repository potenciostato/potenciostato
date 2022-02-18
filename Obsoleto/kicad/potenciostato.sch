EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 4
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
L potenciostato-rescue:OP77-Amplifier_Operational U4
U 1 1 5CC24F96
P 8300 4700
F 0 "U4" H 8644 4654 50  0000 L CNN
F 1 "OP77" H 8644 4745 50  0000 L CNN
F 2 "Package_DIP:DIP-8_W7.62mm_LongPads" H 8350 4750 50  0001 C CNN
F 3 "https://www.analog.com/media/en/technical-documentation/data-sheets/OP77.pdf" H 8350 4850 50  0001 C CNN
	1    8300 4700
	-1   0    0    1   
$EndComp
$Comp
L potenciostato-rescue:R-Device R2
U 1 1 5CC25964
P 6600 2200
F 0 "R2" V 6393 2200 50  0000 C CNN
F 1 "100K" V 6484 2200 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 6530 2200 50  0001 C CNN
F 3 "~" H 6600 2200 50  0001 C CNN
	1    6600 2200
	0    1    1    0   
$EndComp
$Comp
L potenciostato-rescue:R-Device R3
U 1 1 5CC2629B
P 6950 2750
F 0 "R3" V 6743 2750 50  0000 C CNN
F 1 "100K" V 6834 2750 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 6880 2750 50  0001 C CNN
F 3 "~" H 6950 2750 50  0001 C CNN
	1    6950 2750
	1    0    0    -1  
$EndComp
$Comp
L potenciostato-rescue:R-Device R5
U 1 1 5CC26B83
P 8000 4050
F 0 "R5" V 7793 4050 50  0000 C CNN
F 1 "1M" V 7884 4050 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 7930 4050 50  0001 C CNN
F 3 "~" H 8000 4050 50  0001 C CNN
	1    8000 4050
	0    1    1    0   
$EndComp
$Comp
L potenciostato-rescue:GND-power #PWR08
U 1 1 5CC2AC7B
P 8700 4900
F 0 "#PWR08" H 8700 4650 50  0001 C CNN
F 1 "GND" H 8705 4727 50  0000 C CNN
F 2 "" H 8700 4900 50  0001 C CNN
F 3 "" H 8700 4900 50  0001 C CNN
	1    8700 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	8600 4800 8700 4800
Wire Wire Line
	8700 4800 8700 4900
Wire Wire Line
	8700 3350 8800 3350
Wire Wire Line
	8800 3700 7950 3700
Wire Wire Line
	7950 3700 7950 3250
Wire Wire Line
	8800 3350 8800 3700
Wire Wire Line
	7950 3250 8100 3250
Wire Wire Line
	8950 4050 8950 4600
Wire Wire Line
	8950 4600 8600 4600
Wire Wire Line
	7850 4050 7500 4050
Wire Wire Line
	7500 4050 7500 4700
Wire Wire Line
	7500 4700 8000 4700
$Comp
L potenciostato-rescue:GND-power #PWR01
U 1 1 5CD2A3FD
P 1000 1100
F 0 "#PWR01" H 1000 850 50  0001 C CNN
F 1 "GND" H 1005 927 50  0000 C CNN
F 2 "" H 1000 1100 50  0001 C CNN
F 3 "" H 1000 1100 50  0001 C CNN
	1    1000 1100
	1    0    0    -1  
$EndComp
$Comp
L potenciostato-rescue:Conn_01x03_Female-Connector J1
U 1 1 5CDF8979
P 1850 1100
F 0 "J1" H 1550 900 50  0000 L CNN
F 1 "Conn_01x03_Female" H 1250 1300 50  0000 L CNN
F 2 "Connector:FanPinHeader_1x03_P2.54mm_Vertical" H 1850 1100 50  0001 C CNN
F 3 "~" H 1850 1100 50  0001 C CNN
	1    1850 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	1150 1000 1650 1000
Wire Wire Line
	1150 1200 1650 1200
Wire Wire Line
	1000 1100 1650 1100
Wire Wire Line
	8000 2300 8950 2300
Wire Wire Line
	7300 2400 7300 2500
Wire Wire Line
	7400 2400 7300 2400
$Comp
L potenciostato-rescue:GND-power #PWR07
U 1 1 5CC2A149
P 7300 2500
F 0 "#PWR07" H 7300 2250 50  0001 C CNN
F 1 "GND" H 7305 2327 50  0000 C CNN
F 2 "" H 7300 2500 50  0001 C CNN
F 3 "" H 7300 2500 50  0001 C CNN
	1    7300 2500
	1    0    0    -1  
$EndComp
$Comp
L potenciostato-rescue:Conn_01x03_Male-Connector J3
U 1 1 5D250C0E
P 9950 3350
F 0 "J3" H 9922 3282 50  0000 R CNN
F 1 "Conn_01x03_Male" H 9922 3373 50  0000 R CNN
F 2 "Connector:FanPinHeader_1x03_P2.54mm_Vertical" H 9950 3350 50  0001 C CNN
F 3 "~" H 9950 3350 50  0001 C CNN
	1    9950 3350
	-1   0    0    1   
$EndComp
Wire Wire Line
	6750 2200 6950 2200
Wire Wire Line
	6950 2600 6950 2200
Connection ~ 6950 2200
Wire Wire Line
	6950 2200 7400 2200
Wire Wire Line
	6950 2900 6950 3250
Wire Wire Line
	7950 3250 6950 3250
Connection ~ 7950 3250
$Comp
L potenciostato-rescue:+5V-power #PWR02
U 1 1 5F8AF7F8
P 1150 1000
F 0 "#PWR02" H 1150 850 50  0001 C CNN
F 1 "+5V" H 1165 1177 50  0000 C CNN
F 2 "" H 1150 1000 50  0001 C CNN
F 3 "" H 1150 1000 50  0001 C CNN
	1    1150 1000
	1    0    0    -1  
$EndComp
$Comp
L potenciostato-rescue:-5V-power #PWR03
U 1 1 5F8AF868
P 1150 1200
F 0 "#PWR03" H 1150 1300 50  0001 C CNN
F 1 "-5V" H 1165 1377 50  0000 C CNN
F 2 "" H 1150 1200 50  0001 C CNN
F 3 "" H 1150 1200 50  0001 C CNN
	1    1150 1200
	-1   0    0    1   
$EndComp
Wire Wire Line
	8150 4050 8950 4050
NoConn ~ 5700 7300
$Comp
L potenciostato-rescue:OP77-Amplifier_Operational U1
U 1 1 5F9FAD3E
P 6200 4800
F 0 "U1" H 6544 4754 50  0000 L CNN
F 1 "OP77" H 6544 4845 50  0000 L CNN
F 2 "Package_DIP:DIP-8_W7.62mm_LongPads" H 6250 4850 50  0001 C CNN
F 3 "https://www.analog.com/media/en/technical-documentation/data-sheets/OP77.pdf" H 6250 4950 50  0001 C CNN
	1    6200 4800
	-1   0    0    1   
$EndComp
$Comp
L potenciostato-rescue:R-Device R1
U 1 1 5F9FAD44
P 6050 4200
F 0 "R1" V 5843 4200 50  0000 C CNN
F 1 "15K" V 5934 4200 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 5980 4200 50  0001 C CNN
F 3 "~" H 6050 4200 50  0001 C CNN
	1    6050 4200
	0    1    1    0   
$EndComp
$Comp
L potenciostato-rescue:GND-power #PWR06
U 1 1 5F9FAD4A
P 6600 5000
F 0 "#PWR06" H 6600 4750 50  0001 C CNN
F 1 "GND" H 6605 4827 50  0000 C CNN
F 2 "" H 6600 5000 50  0001 C CNN
F 3 "" H 6600 5000 50  0001 C CNN
	1    6600 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 4900 6600 4900
Wire Wire Line
	6600 4900 6600 5000
$Comp
L potenciostato-rescue:R-Device R4
U 1 1 5F9FD20A
P 7100 4700
F 0 "R4" V 6893 4700 50  0000 C CNN
F 1 "1K" V 6984 4700 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 7030 4700 50  0001 C CNN
F 3 "~" H 7100 4700 50  0001 C CNN
	1    7100 4700
	0    1    1    0   
$EndComp
Wire Wire Line
	6500 4700 6700 4700
Wire Wire Line
	6700 4700 6700 4200
Wire Wire Line
	6700 4200 6200 4200
Wire Wire Line
	5900 4200 5500 4200
Wire Wire Line
	5500 4200 5500 4800
Wire Wire Line
	5500 4800 5900 4800
Wire Wire Line
	6950 4700 6700 4700
Connection ~ 6700 4700
Wire Wire Line
	7250 4700 7500 4700
Connection ~ 7500 4700
Wire Wire Line
	9350 3150 9350 3350
Wire Wire Line
	9350 3350 9750 3350
Wire Wire Line
	8700 3150 9350 3150
Wire Wire Line
	8950 3050 9500 3050
Wire Wire Line
	9500 3050 9500 3250
Wire Wire Line
	9500 3250 9750 3250
Wire Wire Line
	8950 2300 8950 3050
Wire Wire Line
	9750 3450 9350 3450
Wire Wire Line
	9350 3450 9350 4600
Wire Wire Line
	9350 4600 8950 4600
Connection ~ 8950 4600
Wire Wire Line
	6650 3450 6750 3450
Wire Wire Line
	6750 3800 5900 3800
Wire Wire Line
	5900 3800 5900 3350
Wire Wire Line
	6750 3450 6750 3800
Wire Wire Line
	5900 3350 6050 3350
Wire Wire Line
	6950 3250 6650 3250
Connection ~ 6950 3250
$Sheet
S 3800 2100 1000 1900
U 6013BA2D
F0 "salida_dac" 50
F1 "salida_dac.sch" 50
F2 "DAC1" I L 3800 2250 50 
F3 "OFF_DAC_1" I L 3800 2650 50 
F4 "OFF_DAC_2" I L 3800 2750 50 
F5 "SW_GAIN1" I L 3800 2450 50 
F6 "SW_GAIN2" I L 3800 2550 50 
F7 "VIN" I R 4800 2200 50 
F8 "I_IN" I R 4800 3800 50 
F9 "OFF_I_2" I L 3800 3800 50 
F10 "SW_I_GAIN1" I L 3800 3500 50 
F11 "SW_I_GAIN2" I L 3800 3600 50 
F12 "I_ADC" I L 3800 3900 50 
F13 "OFF_I_1" I L 3800 3700 50 
F14 "V_IN" I R 4800 3350 50 
F15 "OFF_V_2" I L 3800 3250 50 
F16 "SW_V_GAIN1" I L 3800 2950 50 
F17 "SW_V_GAIN2" I L 3800 3050 50 
F18 "V_ADC" I L 3800 3350 50 
F19 "OFF_V_1" I L 3800 3150 50 
$EndSheet
$Sheet
S 2300 2100 1050 1900
U 60147E53
F0 "LPC" 50
F1 "LPC.sch" 50
F2 "GND" I L 2300 3100 50 
F3 "3.3V" I L 2300 3000 50 
F4 "DAC" I R 3350 2250 50 
F5 "ADC1" I R 3350 3350 50 
F6 "ADC0" I R 3350 3900 50 
F7 "5V" I L 2300 2350 50 
F8 "P2.1" I R 3350 2450 50 
F9 "P2.2" I R 3350 2550 50 
F10 "P2.3" I R 3350 2650 50 
F11 "P2.4" I R 3350 2750 50 
F12 "P2.5" I R 3350 2950 50 
F13 "P2.6" I R 3350 3050 50 
F14 "P2.7" I R 3350 3150 50 
F15 "P2.8" I R 3350 3250 50 
F16 "P0.2" I R 3350 3500 50 
F17 "P0.3" I R 3350 3600 50 
F18 "P0.21" I R 3350 3700 50 
F19 "P0.22" I R 3350 3800 50 
$EndSheet
Wire Wire Line
	4800 2200 6450 2200
Wire Wire Line
	5900 3350 4800 3350
Connection ~ 5900 3350
Wire Wire Line
	4800 3800 5500 3800
Wire Wire Line
	5500 3800 5500 4200
Connection ~ 5500 4200
$Comp
L potenciostato-rescue:TL082-Amplifier_Operational U2
U 1 1 601CBD2D
P 8400 3250
F 0 "U2" H 8400 3620 50  0000 C CNN
F 1 "TL082" H 8400 3527 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm_LongPads" H 8400 3250 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl081.pdf" H 8400 3250 50  0001 C CNN
	1    8400 3250
	-1   0    0    -1  
$EndComp
$Comp
L potenciostato-rescue:TL082-Amplifier_Operational U2
U 2 1 601CBED5
P 6350 3350
F 0 "U2" H 6550 3700 50  0000 C CNN
F 1 "TL082" H 6500 3600 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm_LongPads" H 6350 3350 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl081.pdf" H 6350 3350 50  0001 C CNN
	2    6350 3350
	-1   0    0    -1  
$EndComp
$Comp
L potenciostato-rescue:TL082-Amplifier_Operational U2
U 3 1 601CBFB9
P 6550 3350
F 0 "U2" H 6511 3397 50  0000 L CNN
F 1 "TL082" H 6511 3304 50  0000 L CNN
F 2 "Package_DIP:DIP-8_W7.62mm_LongPads" H 6550 3350 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl081.pdf" H 6550 3350 50  0001 C CNN
	3    6550 3350
	1    0    0    -1  
$EndComp
$Comp
L potenciostato-rescue:-5V-power #PWR0101
U 1 1 601CC089
P 6450 3650
F 0 "#PWR0101" H 6450 3750 50  0001 C CNN
F 1 "-5V" H 6465 3827 50  0000 C CNN
F 2 "" H 6450 3650 50  0001 C CNN
F 3 "" H 6450 3650 50  0001 C CNN
	1    6450 3650
	-1   0    0    1   
$EndComp
$Comp
L potenciostato-rescue:+5V-power #PWR0102
U 1 1 601CC0FC
P 6450 3050
F 0 "#PWR0102" H 6450 2900 50  0001 C CNN
F 1 "+5V" H 6465 3227 50  0000 C CNN
F 2 "" H 6450 3050 50  0001 C CNN
F 3 "" H 6450 3050 50  0001 C CNN
	1    6450 3050
	1    0    0    -1  
$EndComp
$Comp
L potenciostato-rescue:OP77-Amplifier_Operational U3
U 1 1 5CC225D1
P 7700 2300
F 0 "U3" H 8044 2254 50  0000 L CNN
F 1 "OP77" H 8044 2345 50  0000 L CNN
F 2 "Package_DIP:DIP-8_W7.62mm_LongPads" H 7750 2350 50  0001 C CNN
F 3 "https://www.analog.com/media/en/technical-documentation/data-sheets/OP77.pdf" H 7750 2450 50  0001 C CNN
	1    7700 2300
	1    0    0    1   
$EndComp
$Comp
L potenciostato-rescue:-5V-power #PWR0103
U 1 1 601CC2C2
P 6300 4500
F 0 "#PWR0103" H 6300 4600 50  0001 C CNN
F 1 "-5V" H 6315 4677 50  0000 C CNN
F 2 "" H 6300 4500 50  0001 C CNN
F 3 "" H 6300 4500 50  0001 C CNN
	1    6300 4500
	1    0    0    -1  
$EndComp
$Comp
L potenciostato-rescue:-5V-power #PWR0104
U 1 1 601CC383
P 8400 4400
F 0 "#PWR0104" H 8400 4500 50  0001 C CNN
F 1 "-5V" H 8415 4577 50  0000 C CNN
F 2 "" H 8400 4400 50  0001 C CNN
F 3 "" H 8400 4400 50  0001 C CNN
	1    8400 4400
	1    0    0    -1  
$EndComp
$Comp
L potenciostato-rescue:-5V-power #PWR0105
U 1 1 601CC42A
P 7600 2000
F 0 "#PWR0105" H 7600 2100 50  0001 C CNN
F 1 "-5V" H 7615 2177 50  0000 C CNN
F 2 "" H 7600 2000 50  0001 C CNN
F 3 "" H 7600 2000 50  0001 C CNN
	1    7600 2000
	1    0    0    -1  
$EndComp
$Comp
L potenciostato-rescue:+5V-power #PWR0106
U 1 1 601CC539
P 7600 2600
F 0 "#PWR0106" H 7600 2450 50  0001 C CNN
F 1 "+5V" H 7615 2777 50  0000 C CNN
F 2 "" H 7600 2600 50  0001 C CNN
F 3 "" H 7600 2600 50  0001 C CNN
	1    7600 2600
	-1   0    0    1   
$EndComp
$Comp
L potenciostato-rescue:+5V-power #PWR0107
U 1 1 601CC592
P 8400 5000
F 0 "#PWR0107" H 8400 4850 50  0001 C CNN
F 1 "+5V" H 8415 5177 50  0000 C CNN
F 2 "" H 8400 5000 50  0001 C CNN
F 3 "" H 8400 5000 50  0001 C CNN
	1    8400 5000
	-1   0    0    1   
$EndComp
$Comp
L potenciostato-rescue:+5V-power #PWR0108
U 1 1 601CC639
P 6300 5100
F 0 "#PWR0108" H 6300 4950 50  0001 C CNN
F 1 "+5V" H 6315 5277 50  0000 C CNN
F 2 "" H 6300 5100 50  0001 C CNN
F 3 "" H 6300 5100 50  0001 C CNN
	1    6300 5100
	-1   0    0    1   
$EndComp
Text Notes 7800 5500 0    50   ~ 0
Amplificador Transresistencia\n(AMP TR)
Text Notes 5700 5500 0    50   ~ 0
Amplificador Tension Inversor\n(AMP I1)
Text Notes 7200 1700 0    50   ~ 0
Amplificador Tension Inversor\n(AMP T3)
Wire Wire Line
	3800 3250 3350 3250
Wire Wire Line
	3350 3150 3800 3150
Wire Wire Line
	3800 3050 3350 3050
Wire Wire Line
	3350 2950 3800 2950
Wire Wire Line
	3800 2750 3350 2750
Wire Wire Line
	3350 2650 3800 2650
Wire Wire Line
	3800 2550 3350 2550
Wire Wire Line
	3350 2450 3800 2450
Wire Wire Line
	3800 3800 3350 3800
Wire Wire Line
	3350 3700 3800 3700
Wire Wire Line
	3800 3600 3350 3600
Wire Wire Line
	3350 3500 3800 3500
Wire Wire Line
	3800 3900 3350 3900
Wire Wire Line
	3350 2250 3800 2250
Wire Wire Line
	2300 3100 2050 3100
Wire Wire Line
	2050 3100 2050 3200
$Comp
L potenciostato-rescue:GND-power #PWR0130
U 1 1 609B9D8E
P 2050 3200
F 0 "#PWR0130" H 2050 2950 50  0001 C CNN
F 1 "GND" H 2055 3027 50  0000 C CNN
F 2 "" H 2050 3200 50  0001 C CNN
F 3 "" H 2050 3200 50  0001 C CNN
	1    2050 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 3350 3350 3350
$Sheet
S 2150 6100 1150 1200
U 61FF691F
F0 "Fuente_partida" 50
F1 "Fuente_partida.sch" 50
$EndSheet
$EndSCHEMATC
