EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 4
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
L salida_dac-rescue:R-Device R8
U 1 1 5F8A592F
P 4500 2450
AR Path="/5F8A592F" Ref="R8"  Part="1" 
AR Path="/5F899696/5F8A592F" Ref="R13"  Part="1" 
AR Path="/6013BA2D/5F8A592F" Ref="R13"  Part="1" 
F 0 "R13" V 4293 2450 50  0000 C CNN
F 1 "4K7" V 4384 2450 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 4430 2450 50  0001 C CNN
F 3 "~" H 4500 2450 50  0001 C CNN
	1    4500 2450
	0    1    1    0   
$EndComp
$Comp
L salida_dac-rescue:4016-4xxx U7
U 1 1 5F8A5949
P 4000 2450
AR Path="/5F8A5949" Ref="U7"  Part="1" 
AR Path="/5F899696/5F8A5949" Ref="U7"  Part="1" 
AR Path="/6013BA2D/5F8A5949" Ref="U6"  Part="1" 
F 0 "U6" H 4000 2274 50  0000 C CNN
F 1 "4016" H 4000 2181 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W10.16mm_LongPads" H 4000 2450 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/cd4016b.pdf" H 4000 2450 50  0001 C CNN
	1    4000 2450
	1    0    0    -1  
$EndComp
$Comp
L salida_dac-rescue:R-Device R7
U 1 1 5F8A5CC8
P 4500 1850
AR Path="/5F8A5CC8" Ref="R7"  Part="1" 
AR Path="/5F899696/5F8A5CC8" Ref="R12"  Part="1" 
AR Path="/6013BA2D/5F8A5CC8" Ref="R12"  Part="1" 
F 0 "R12" V 4293 1850 50  0000 C CNN
F 1 "3K3" V 4384 1850 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 4430 1850 50  0001 C CNN
F 3 "~" H 4500 1850 50  0001 C CNN
	1    4500 1850
	0    1    1    0   
$EndComp
$Comp
L salida_dac-rescue:4016-4xxx U5
U 2 1 5F8A5D2D
P 2700 5150
AR Path="/5F8A5D2D" Ref="U5"  Part="2" 
AR Path="/6013BA2D/5F8A5D2D" Ref="U5"  Part="2" 
F 0 "U5" H 2700 4974 50  0000 C CNN
F 1 "4016" H 2700 4881 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W10.16mm_LongPads" H 2700 5150 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/cd4016b.pdf" H 2700 5150 50  0001 C CNN
	2    2700 5150
	1    0    0    -1  
$EndComp
$Comp
L salida_dac-rescue:4016-4xxx U5
U 5 1 5F8A5F7E
P 1000 6200
AR Path="/5F8A5F7E" Ref="U5"  Part="5" 
AR Path="/6013BA2D/5F8A5F7E" Ref="U5"  Part="5" 
F 0 "U5" H 1230 6247 50  0000 L CNN
F 1 "4016" H 1230 6154 50  0000 L CNN
F 2 "Package_DIP:DIP-14_W10.16mm_LongPads" H 1000 6200 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/cd4016b.pdf" H 1000 6200 50  0001 C CNN
	5    1000 6200
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 2450 3550 2450
Wire Wire Line
	3700 1850 3550 1850
Wire Wire Line
	3550 1850 3550 2450
Wire Wire Line
	4350 1850 4300 1850
Wire Wire Line
	4350 2450 4300 2450
$Comp
L salida_dac-rescue:R-Device R2
U 1 1 5F8A81B2
P 3200 3050
AR Path="/5F8A81B2" Ref="R2"  Part="1" 
AR Path="/5F899696/5F8A81B2" Ref="R7"  Part="1" 
AR Path="/6013BA2D/5F8A81B2" Ref="R7"  Part="1" 
F 0 "R7" V 3400 3050 50  0000 C CNN
F 1 "1K" V 3300 3050 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 3130 3050 50  0001 C CNN
F 3 "~" H 3200 3050 50  0001 C CNN
	1    3200 3050
	0    1    1    0   
$EndComp
Wire Wire Line
	4200 3050 3350 3050
Wire Wire Line
	3050 2850 2550 2850
$Comp
L salida_dac-rescue:GND-power #PWR0109
U 1 1 5F8A9D3B
P 1000 6700
F 0 "#PWR0109" H 1000 6450 50  0001 C CNN
F 1 "GND" H 1005 6523 50  0000 C CNN
F 2 "" H 1000 6700 50  0001 C CNN
F 3 "" H 1000 6700 50  0001 C CNN
	1    1000 6700
	1    0    0    -1  
$EndComp
$Comp
L salida_dac-rescue:+5V-power #PWR0110
U 1 1 5F8A9F05
P 1000 5700
F 0 "#PWR0110" H 1000 5550 50  0001 C CNN
F 1 "+5V" H 1015 5877 50  0000 C CNN
F 2 "" H 1000 5700 50  0001 C CNN
F 3 "" H 1000 5700 50  0001 C CNN
	1    1000 5700
	1    0    0    -1  
$EndComp
Wire Wire Line
	2850 2150 2850 1650
Wire Wire Line
	2850 1650 1900 1650
Text HLabel 2550 2850 0    50   Input ~ 0
DAC1
Text HLabel 2400 12250 3    50   Input ~ 0
SW_FILTRO1
Text HLabel 2500 12250 3    50   Input ~ 0
SW_FILTRO2
Text HLabel 1900 1550 0    50   Input ~ 0
SW_GAIN1
Text HLabel 1900 1650 0    50   Input ~ 0
SW_GAIN2
Text HLabel 5650 2950 2    50   Input ~ 0
VIN
$Comp
L salida_dac-rescue:R-Device R9
U 1 1 5F9506D4
P 4400 6200
AR Path="/5F9506D4" Ref="R9"  Part="1" 
AR Path="/5F899696/5F9506D4" Ref="R14"  Part="1" 
AR Path="/6013BA2D/5F9506D4" Ref="R14"  Part="1" 
F 0 "R14" V 4193 6200 50  0000 C CNN
F 1 "1K" V 4284 6200 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 4330 6200 50  0001 C CNN
F 3 "~" H 4400 6200 50  0001 C CNN
	1    4400 6200
	0    -1   1    0   
$EndComp
$Comp
L salida_dac-rescue:R-Device R4
U 1 1 5F9506DA
P 3200 5750
AR Path="/5F9506DA" Ref="R4"  Part="1" 
AR Path="/5F899696/5F9506DA" Ref="R9"  Part="1" 
AR Path="/6013BA2D/5F9506DA" Ref="R9"  Part="1" 
F 0 "R9" V 2993 5750 50  0000 C CNN
F 1 "4K7" V 3084 5750 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 3130 5750 50  0001 C CNN
F 3 "~" H 3200 5750 50  0001 C CNN
	1    3200 5750
	0    1    1    0   
$EndComp
$Comp
L salida_dac-rescue:4016-4xxx U6
U 1 1 5F9506ED
P 2700 5750
AR Path="/5F9506ED" Ref="U6"  Part="1" 
AR Path="/5F899696/5F9506ED" Ref="U6"  Part="1" 
AR Path="/6013BA2D/5F9506ED" Ref="U5"  Part="1" 
F 0 "U5" H 2700 5500 50  0000 C CNN
F 1 "4016" H 2700 5600 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W10.16mm_LongPads" H 2700 5750 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/cd4016b.pdf" H 2700 5750 50  0001 C CNN
	1    2700 5750
	1    0    0    -1  
$EndComp
$Comp
L salida_dac-rescue:R-Device R3
U 1 1 5F9506F4
P 3200 5150
AR Path="/5F9506F4" Ref="R3"  Part="1" 
AR Path="/5F899696/5F9506F4" Ref="R8"  Part="1" 
AR Path="/6013BA2D/5F9506F4" Ref="R8"  Part="1" 
F 0 "R8" V 2993 5150 50  0000 C CNN
F 1 "3K3" V 3084 5150 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 3130 5150 50  0001 C CNN
F 3 "~" H 3200 5150 50  0001 C CNN
	1    3200 5150
	0    1    1    0   
$EndComp
$Comp
L salida_dac-rescue:4016-4xxx U5
U 3 1 5F950700
P 5350 6950
AR Path="/5F950700" Ref="U5"  Part="3" 
AR Path="/6013BA2D/5F950700" Ref="U5"  Part="3" 
F 0 "U5" H 5350 6774 50  0000 C CNN
F 1 "4016" H 5350 6681 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W10.16mm_LongPads" H 5350 6950 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/cd4016b.pdf" H 5350 6950 50  0001 C CNN
	3    5350 6950
	0    1    1    0   
$EndComp
$Comp
L salida_dac-rescue:4016-4xxx U5
U 4 1 5F950706
P 3700 6950
AR Path="/5F950706" Ref="U5"  Part="4" 
AR Path="/6013BA2D/5F950706" Ref="U5"  Part="4" 
F 0 "U5" H 3700 6774 50  0000 C CNN
F 1 "4016" H 3700 6681 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W10.16mm_LongPads" H 3700 6950 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/cd4016b.pdf" H 3700 6950 50  0001 C CNN
	4    3700 6950
	0    1    -1   0   
$EndComp
$Comp
L salida_dac-rescue:4016-4xxx U6
U 5 1 5F95070C
P 1000 1300
AR Path="/5F95070C" Ref="U6"  Part="5" 
AR Path="/6013BA2D/5F95070C" Ref="U6"  Part="5" 
F 0 "U6" H 1230 1347 50  0000 L CNN
F 1 "4016" H 1230 1254 50  0000 L CNN
F 2 "Package_DIP:DIP-14_W10.16mm_LongPads" H 1000 1300 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/cd4016b.pdf" H 1000 1300 50  0001 C CNN
	5    1000 1300
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2400 5750 2250 5750
Wire Wire Line
	2400 5150 2250 5150
Wire Wire Line
	2250 5150 2250 5750
Connection ~ 2250 5750
Wire Wire Line
	3050 5150 3000 5150
Wire Wire Line
	3050 5750 3000 5750
$Comp
L salida_dac-rescue:R-Device R10
U 1 1 5F95073B
P 4950 7500
AR Path="/5F95073B" Ref="R10"  Part="1" 
AR Path="/5F899696/5F95073B" Ref="R15"  Part="1" 
AR Path="/6013BA2D/5F95073B" Ref="R15"  Part="1" 
F 0 "R15" V 4743 7500 50  0000 C CNN
F 1 "10K" V 4834 7500 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 4880 7500 50  0001 C CNN
F 3 "~" H 4950 7500 50  0001 C CNN
	1    4950 7500
	0    1    -1   0   
$EndComp
$Comp
L salida_dac-rescue:GND-power #PWR0111
U 1 1 5F950745
P 1000 1800
F 0 "#PWR0111" H 1000 1550 50  0001 C CNN
F 1 "GND" H 1005 1623 50  0000 C CNN
F 2 "" H 1000 1800 50  0001 C CNN
F 3 "" H 1000 1800 50  0001 C CNN
	1    1000 1800
	-1   0    0    -1  
$EndComp
$Comp
L salida_dac-rescue:+5V-power #PWR0112
U 1 1 5F95074B
P 1000 800
F 0 "#PWR0112" H 1000 650 50  0001 C CNN
F 1 "+5V" H 1015 977 50  0000 C CNN
F 2 "" H 1000 800 50  0001 C CNN
F 3 "" H 1000 800 50  0001 C CNN
	1    1000 800 
	-1   0    0    -1  
$EndComp
Text HLabel 4800 6200 2    50   Input ~ 0
I_IN
Text HLabel 4250 6950 2    50   Input ~ 0
OFF_I_2
Text HLabel 1800 4850 0    50   Input ~ 0
SW_I_GAIN1
Text HLabel 1800 5450 0    50   Input ~ 0
SW_I_GAIN2
Text HLabel 1700 6300 0    50   Input ~ 0
I_ADC
Wire Wire Line
	1700 6300 2250 6300
Wire Wire Line
	2250 5750 2250 6300
Connection ~ 2250 6300
Wire Wire Line
	2250 6300 2550 6300
Wire Wire Line
	2700 4850 1800 4850
$Comp
L salida_dac-rescue:R-Device R11
U 1 1 5F971DA5
P 5750 7500
AR Path="/5F971DA5" Ref="R11"  Part="1" 
AR Path="/5F899696/5F971DA5" Ref="R16"  Part="1" 
AR Path="/6013BA2D/5F971DA5" Ref="R16"  Part="1" 
F 0 "R16" V 5543 7500 50  0000 C CNN
F 1 "1K" V 5634 7500 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 5680 7500 50  0001 C CNN
F 3 "~" H 5750 7500 50  0001 C CNN
	1    5750 7500
	0    1    -1   0   
$EndComp
$Comp
L salida_dac-rescue:R_POT-Device RV6
U 1 1 5F972A62
P 5350 7500
F 0 "RV6" V 5234 7500 50  0000 C CNN
F 1 "1K" V 5141 7500 50  0000 C CNN
F 2 "Potentiometer_THT:Potentiometer_Bourns_3266Y_Vertical" H 5350 7500 50  0001 C CNN
F 3 "~" H 5350 7500 50  0001 C CNN
	1    5350 7500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5600 7500 5500 7500
Wire Wire Line
	5200 7500 5100 7500
$Comp
L salida_dac-rescue:-5V-power #PWR0103
U 1 1 5F97ACB1
P 5900 7500
AR Path="/5F97ACB1" Ref="#PWR0103"  Part="1" 
AR Path="/5F899696/5F97ACB1" Ref="#PWR020"  Part="1" 
AR Path="/6013BA2D/5F97ACB1" Ref="#PWR0113"  Part="1" 
F 0 "#PWR0113" H 5900 7600 50  0001 C CNN
F 1 "-5V" H 5915 7677 50  0000 C CNN
F 2 "" H 5900 7500 50  0001 C CNN
F 3 "" H 5900 7500 50  0001 C CNN
	1    5900 7500
	0    1    1    0   
$EndComp
$Comp
L salida_dac-rescue:+5V-power #PWR0104
U 1 1 5F980950
P 4800 7500
AR Path="/5F980950" Ref="#PWR0104"  Part="1" 
AR Path="/5F899696/5F980950" Ref="#PWR019"  Part="1" 
AR Path="/6013BA2D/5F980950" Ref="#PWR0114"  Part="1" 
F 0 "#PWR0114" H 4800 7350 50  0001 C CNN
F 1 "+5V" H 4815 7677 50  0000 C CNN
F 2 "" H 4800 7500 50  0001 C CNN
F 3 "" H 4800 7500 50  0001 C CNN
	1    4800 7500
	0    -1   -1   0   
$EndComp
$Comp
L salida_dac-rescue:R-Device R5
U 1 1 5F98484D
P 3300 7500
AR Path="/5F98484D" Ref="R5"  Part="1" 
AR Path="/5F899696/5F98484D" Ref="R10"  Part="1" 
AR Path="/6013BA2D/5F98484D" Ref="R10"  Part="1" 
F 0 "R10" V 3093 7500 50  0000 C CNN
F 1 "10K" V 3184 7500 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 3230 7500 50  0001 C CNN
F 3 "~" H 3300 7500 50  0001 C CNN
	1    3300 7500
	0    1    -1   0   
$EndComp
$Comp
L salida_dac-rescue:R-Device R6
U 1 1 5F984853
P 4100 7500
AR Path="/5F984853" Ref="R6"  Part="1" 
AR Path="/5F899696/5F984853" Ref="R11"  Part="1" 
AR Path="/6013BA2D/5F984853" Ref="R11"  Part="1" 
F 0 "R11" V 3893 7500 50  0000 C CNN
F 1 "1K" V 3984 7500 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 4030 7500 50  0001 C CNN
F 3 "~" H 4100 7500 50  0001 C CNN
	1    4100 7500
	0    1    -1   0   
$EndComp
$Comp
L salida_dac-rescue:R_POT-Device RV3
U 1 1 5F984859
P 3700 7500
F 0 "RV3" V 3584 7500 50  0000 C CNN
F 1 "1K" V 3491 7500 50  0000 C CNN
F 2 "Potentiometer_THT:Potentiometer_Bourns_3266Y_Vertical" H 3700 7500 50  0001 C CNN
F 3 "~" H 3700 7500 50  0001 C CNN
	1    3700 7500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3950 7500 3850 7500
Wire Wire Line
	3550 7500 3450 7500
$Comp
L salida_dac-rescue:-5V-power #PWR0105
U 1 1 5F984861
P 4250 7500
AR Path="/5F984861" Ref="#PWR0105"  Part="1" 
AR Path="/5F899696/5F984861" Ref="#PWR016"  Part="1" 
AR Path="/6013BA2D/5F984861" Ref="#PWR0115"  Part="1" 
F 0 "#PWR0115" H 4250 7600 50  0001 C CNN
F 1 "-5V" H 4265 7677 50  0000 C CNN
F 2 "" H 4250 7500 50  0001 C CNN
F 3 "" H 4250 7500 50  0001 C CNN
	1    4250 7500
	0    1    1    0   
$EndComp
$Comp
L salida_dac-rescue:+5V-power #PWR0106
U 1 1 5F984867
P 3150 7500
AR Path="/5F984867" Ref="#PWR0106"  Part="1" 
AR Path="/5F899696/5F984867" Ref="#PWR015"  Part="1" 
AR Path="/6013BA2D/5F984867" Ref="#PWR0116"  Part="1" 
F 0 "#PWR0116" H 3150 7350 50  0001 C CNN
F 1 "+5V" H 3165 7677 50  0000 C CNN
F 2 "" H 3150 7500 50  0001 C CNN
F 3 "" H 3150 7500 50  0001 C CNN
	1    3150 7500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3700 7250 3700 7350
Wire Wire Line
	3150 6400 3700 6400
Wire Wire Line
	3700 6400 3700 6650
Wire Wire Line
	5350 7250 5350 7350
Wire Wire Line
	5350 6650 5350 6400
Wire Wire Line
	5350 6400 3700 6400
Connection ~ 3700 6400
Text HLabel 5950 6950 2    50   Input ~ 0
OFF_I_1
Wire Wire Line
	5950 6950 5650 6950
Wire Wire Line
	4250 6950 4000 6950
Wire Wire Line
	3150 6200 3850 6200
$Comp
L salida_dac-rescue:R_POT-Device RV2
U 1 1 5F9A1C6C
P 3600 5750
F 0 "RV2" V 3484 5750 50  0000 C CNN
F 1 "R_POT" V 3391 5750 50  0000 C CNN
F 2 "Potentiometer_THT:Potentiometer_Bourns_3266Y_Vertical" H 3600 5750 50  0001 C CNN
F 3 "~" H 3600 5750 50  0001 C CNN
	1    3600 5750
	0    -1   -1   0   
$EndComp
$Comp
L salida_dac-rescue:R_POT-Device RV1
U 1 1 5F9A1D79
P 3600 5150
F 0 "RV1" V 3484 5150 50  0000 C CNN
F 1 "R_POT" V 3391 5150 50  0000 C CNN
F 2 "Potentiometer_THT:Potentiometer_Bourns_3266Y_Vertical" H 3600 5150 50  0001 C CNN
F 3 "~" H 3600 5150 50  0001 C CNN
	1    3600 5150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3850 6200 3850 5750
Wire Wire Line
	3850 5150 3750 5150
Connection ~ 3850 6200
Wire Wire Line
	3750 5750 3850 5750
Connection ~ 3850 5750
Wire Wire Line
	3850 5750 3850 5550
Wire Wire Line
	3450 5750 3350 5750
Wire Wire Line
	3450 5150 3350 5150
Wire Wire Line
	3600 5000 3600 4950
Wire Wire Line
	3600 4950 3850 4950
Wire Wire Line
	3850 4950 3850 5150
Connection ~ 3850 5150
Wire Wire Line
	3600 5600 3600 5550
Wire Wire Line
	3600 5550 3850 5550
Connection ~ 3850 5550
Wire Wire Line
	3850 5550 3850 5150
Wire Wire Line
	4550 6200 4800 6200
Wire Wire Line
	3850 6200 4250 6200
$Comp
L salida_dac-rescue:R_POT-Device RV5
U 1 1 5F9C3DAC
P 4850 2450
F 0 "RV5" V 4734 2450 50  0000 C CNN
F 1 "R_POT" V 4641 2450 50  0000 C CNN
F 2 "Potentiometer_THT:Potentiometer_Bourns_3266Y_Vertical" H 4850 2450 50  0001 C CNN
F 3 "~" H 4850 2450 50  0001 C CNN
	1    4850 2450
	0    -1   -1   0   
$EndComp
$Comp
L salida_dac-rescue:R_POT-Device RV4
U 1 1 5F9C427E
P 4850 1850
F 0 "RV4" V 4734 1850 50  0000 C CNN
F 1 "R_POT" V 4641 1850 50  0000 C CNN
F 2 "Potentiometer_THT:Potentiometer_Bourns_3266Y_Vertical" H 4850 1850 50  0001 C CNN
F 3 "~" H 4850 1850 50  0001 C CNN
	1    4850 1850
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4650 1850 4700 1850
Wire Wire Line
	4650 2450 4700 2450
Wire Wire Line
	5000 2450 5150 2450
Wire Wire Line
	5150 2450 5150 2950
Connection ~ 5150 2450
Wire Wire Line
	5150 2950 5650 2950
$Comp
L salida_dac-rescue:R-Device R16
U 1 1 5F9D8922
P 9150 3650
AR Path="/5F9D8922" Ref="R16"  Part="1" 
AR Path="/5F899696/5F9D8922" Ref="R21"  Part="1" 
AR Path="/6013BA2D/5F9D8922" Ref="R21"  Part="1" 
F 0 "R21" V 8943 3650 50  0000 C CNN
F 1 "1K" V 9034 3650 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 9080 3650 50  0001 C CNN
F 3 "~" H 9150 3650 50  0001 C CNN
	1    9150 3650
	0    -1   1    0   
$EndComp
$Comp
L salida_dac-rescue:R-Device R13
U 1 1 5F9D8928
P 7950 3200
AR Path="/5F9D8928" Ref="R13"  Part="1" 
AR Path="/5F899696/5F9D8928" Ref="R18"  Part="1" 
AR Path="/6013BA2D/5F9D8928" Ref="R18"  Part="1" 
F 0 "R18" V 7743 3200 50  0000 C CNN
F 1 "4K7" V 7834 3200 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 7880 3200 50  0001 C CNN
F 3 "~" H 7950 3200 50  0001 C CNN
	1    7950 3200
	0    1    1    0   
$EndComp
$Comp
L salida_dac-rescue:4016-4xxx U8
U 1 1 5F9D893B
P 7450 3200
AR Path="/5F9D893B" Ref="U8"  Part="1" 
AR Path="/5F899696/5F9D893B" Ref="U8"  Part="1" 
AR Path="/6013BA2D/5F9D893B" Ref="U8"  Part="1" 
F 0 "U8" H 7450 3024 50  0000 C CNN
F 1 "4016" H 7450 2931 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W10.16mm_LongPads" H 7450 3200 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/cd4016b.pdf" H 7450 3200 50  0001 C CNN
	1    7450 3200
	1    0    0    -1  
$EndComp
$Comp
L salida_dac-rescue:R-Device R12
U 1 1 5F9D8941
P 7950 2600
AR Path="/5F9D8941" Ref="R12"  Part="1" 
AR Path="/5F899696/5F9D8941" Ref="R17"  Part="1" 
AR Path="/6013BA2D/5F9D8941" Ref="R17"  Part="1" 
F 0 "R17" V 7743 2600 50  0000 C CNN
F 1 "3K3" V 7834 2600 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 7880 2600 50  0001 C CNN
F 3 "~" H 7950 2600 50  0001 C CNN
	1    7950 2600
	0    1    1    0   
$EndComp
$Comp
L salida_dac-rescue:4016-4xxx U8
U 3 1 5F9D8947
P 10100 4400
AR Path="/5F9D8947" Ref="U8"  Part="3" 
AR Path="/6013BA2D/5F9D8947" Ref="U8"  Part="3" 
F 0 "U8" H 10100 4224 50  0000 C CNN
F 1 "4016" H 10100 4131 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W10.16mm_LongPads" H 10100 4400 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/cd4016b.pdf" H 10100 4400 50  0001 C CNN
	3    10100 4400
	0    1    1    0   
$EndComp
$Comp
L salida_dac-rescue:4016-4xxx U8
U 4 1 5F9D894D
P 8450 4400
AR Path="/5F9D894D" Ref="U8"  Part="4" 
AR Path="/6013BA2D/5F9D894D" Ref="U8"  Part="4" 
F 0 "U8" H 8450 4224 50  0000 C CNN
F 1 "4016" H 8450 4131 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W10.16mm_LongPads" H 8450 4400 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/cd4016b.pdf" H 8450 4400 50  0001 C CNN
	4    8450 4400
	0    1    -1   0   
$EndComp
$Comp
L salida_dac-rescue:4016-4xxx U8
U 5 1 5F9D8953
P 9450 2350
AR Path="/5F9D8953" Ref="U8"  Part="5" 
AR Path="/6013BA2D/5F9D8953" Ref="U8"  Part="5" 
F 0 "U8" H 9680 2397 50  0000 L CNN
F 1 "4016" H 9680 2304 50  0000 L CNN
F 2 "Package_DIP:DIP-14_W10.16mm_LongPads" H 9450 2350 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/cd4016b.pdf" H 9450 2350 50  0001 C CNN
	5    9450 2350
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7150 3200 7000 3200
Wire Wire Line
	7150 2600 7000 2600
Wire Wire Line
	7000 2600 7000 3200
Connection ~ 7000 3200
Wire Wire Line
	7800 2600 7750 2600
Wire Wire Line
	7800 3200 7750 3200
$Comp
L salida_dac-rescue:R-Device R17
U 1 1 5F9D895F
P 9700 4950
AR Path="/5F9D895F" Ref="R17"  Part="1" 
AR Path="/5F899696/5F9D895F" Ref="R22"  Part="1" 
AR Path="/6013BA2D/5F9D895F" Ref="R22"  Part="1" 
F 0 "R22" V 9493 4950 50  0000 C CNN
F 1 "10K" V 9584 4950 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 9630 4950 50  0001 C CNN
F 3 "~" H 9700 4950 50  0001 C CNN
	1    9700 4950
	0    1    -1   0   
$EndComp
$Comp
L salida_dac-rescue:GND-power #PWR0118
U 1 1 5F9D8965
P 9450 2850
F 0 "#PWR0118" H 9450 2600 50  0001 C CNN
F 1 "GND" H 9455 2673 50  0000 C CNN
F 2 "" H 9450 2850 50  0001 C CNN
F 3 "" H 9450 2850 50  0001 C CNN
	1    9450 2850
	-1   0    0    -1  
$EndComp
$Comp
L salida_dac-rescue:+5V-power #PWR0119
U 1 1 5F9D896B
P 9450 1850
F 0 "#PWR0119" H 9450 1700 50  0001 C CNN
F 1 "+5V" H 9465 2027 50  0000 C CNN
F 2 "" H 9450 1850 50  0001 C CNN
F 3 "" H 9450 1850 50  0001 C CNN
	1    9450 1850
	-1   0    0    -1  
$EndComp
Text HLabel 9550 3650 2    50   Input ~ 0
V_IN
Text HLabel 9000 4400 2    50   Input ~ 0
OFF_V_2
Text HLabel 6550 1600 0    50   Input ~ 0
SW_V_GAIN1
Text HLabel 6550 1700 0    50   Input ~ 0
SW_V_GAIN2
Text HLabel 6450 3750 0    50   Input ~ 0
V_ADC
Wire Wire Line
	6450 3750 7000 3750
Wire Wire Line
	7000 3200 7000 3750
Connection ~ 7000 3750
Wire Wire Line
	7000 3750 7300 3750
Wire Wire Line
	7450 2300 7450 1600
Wire Wire Line
	7450 1600 6550 1600
Wire Wire Line
	7450 2900 6850 2900
Wire Wire Line
	6850 2900 6850 1700
Wire Wire Line
	6850 1700 6550 1700
$Comp
L salida_dac-rescue:R-Device R18
U 1 1 5F9D897F
P 10500 4950
AR Path="/5F9D897F" Ref="R18"  Part="1" 
AR Path="/5F899696/5F9D897F" Ref="R23"  Part="1" 
AR Path="/6013BA2D/5F9D897F" Ref="R23"  Part="1" 
F 0 "R23" V 10293 4950 50  0000 C CNN
F 1 "15K" V 10384 4950 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 10430 4950 50  0001 C CNN
F 3 "~" H 10500 4950 50  0001 C CNN
	1    10500 4950
	0    1    -1   0   
$EndComp
$Comp
L salida_dac-rescue:R_POT-Device RV10
U 1 1 5F9D8985
P 10100 4950
F 0 "RV10" V 9984 4950 50  0000 C CNN
F 1 "1K" V 9891 4950 50  0000 C CNN
F 2 "Potentiometer_THT:Potentiometer_Bourns_3266Y_Vertical" H 10100 4950 50  0001 C CNN
F 3 "~" H 10100 4950 50  0001 C CNN
	1    10100 4950
	0    -1   -1   0   
$EndComp
Wire Wire Line
	10350 4950 10250 4950
Wire Wire Line
	9950 4950 9850 4950
$Comp
L salida_dac-rescue:-5V-power #PWR0111
U 1 1 5F9D8999
P 10650 4950
AR Path="/5F9D8999" Ref="#PWR0111"  Part="1" 
AR Path="/5F899696/5F9D8999" Ref="#PWR028"  Part="1" 
AR Path="/6013BA2D/5F9D8999" Ref="#PWR0120"  Part="1" 
F 0 "#PWR0120" H 10650 5050 50  0001 C CNN
F 1 "-5V" H 10665 5127 50  0000 C CNN
F 2 "" H 10650 4950 50  0001 C CNN
F 3 "" H 10650 4950 50  0001 C CNN
	1    10650 4950
	0    1    1    0   
$EndComp
$Comp
L salida_dac-rescue:+5V-power #PWR0112
U 1 1 5F9D899F
P 9550 4950
AR Path="/5F9D899F" Ref="#PWR0112"  Part="1" 
AR Path="/5F899696/5F9D899F" Ref="#PWR027"  Part="1" 
AR Path="/6013BA2D/5F9D899F" Ref="#PWR0121"  Part="1" 
F 0 "#PWR0121" H 9550 4800 50  0001 C CNN
F 1 "+5V" H 9565 5127 50  0000 C CNN
F 2 "" H 9550 4950 50  0001 C CNN
F 3 "" H 9550 4950 50  0001 C CNN
	1    9550 4950
	0    -1   -1   0   
$EndComp
$Comp
L salida_dac-rescue:R-Device R14
U 1 1 5F9D89A5
P 8050 4950
AR Path="/5F9D89A5" Ref="R14"  Part="1" 
AR Path="/5F899696/5F9D89A5" Ref="R19"  Part="1" 
AR Path="/6013BA2D/5F9D89A5" Ref="R19"  Part="1" 
F 0 "R19" V 7843 4950 50  0000 C CNN
F 1 "10K" V 7934 4950 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 7980 4950 50  0001 C CNN
F 3 "~" H 8050 4950 50  0001 C CNN
	1    8050 4950
	0    1    -1   0   
$EndComp
$Comp
L salida_dac-rescue:R-Device R15
U 1 1 5F9D89AB
P 8850 4950
AR Path="/5F9D89AB" Ref="R15"  Part="1" 
AR Path="/5F899696/5F9D89AB" Ref="R20"  Part="1" 
AR Path="/6013BA2D/5F9D89AB" Ref="R20"  Part="1" 
F 0 "R20" V 8643 4950 50  0000 C CNN
F 1 "1K" V 8734 4950 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 8780 4950 50  0001 C CNN
F 3 "~" H 8850 4950 50  0001 C CNN
	1    8850 4950
	0    1    -1   0   
$EndComp
$Comp
L salida_dac-rescue:R_POT-Device RV9
U 1 1 5F9D89B1
P 8450 4950
F 0 "RV9" V 8334 4950 50  0000 C CNN
F 1 "1K" V 8241 4950 50  0000 C CNN
F 2 "Potentiometer_THT:Potentiometer_Bourns_3266Y_Vertical" H 8450 4950 50  0001 C CNN
F 3 "~" H 8450 4950 50  0001 C CNN
	1    8450 4950
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8700 4950 8600 4950
Wire Wire Line
	8300 4950 8200 4950
$Comp
L salida_dac-rescue:-5V-power #PWR0113
U 1 1 5F9D89B9
P 9000 4950
AR Path="/5F9D89B9" Ref="#PWR0113"  Part="1" 
AR Path="/5F899696/5F9D89B9" Ref="#PWR024"  Part="1" 
AR Path="/6013BA2D/5F9D89B9" Ref="#PWR0122"  Part="1" 
F 0 "#PWR0122" H 9000 5050 50  0001 C CNN
F 1 "-5V" H 9015 5127 50  0000 C CNN
F 2 "" H 9000 4950 50  0001 C CNN
F 3 "" H 9000 4950 50  0001 C CNN
	1    9000 4950
	0    1    1    0   
$EndComp
$Comp
L salida_dac-rescue:+5V-power #PWR0114
U 1 1 5F9D89BF
P 7900 4950
AR Path="/5F9D89BF" Ref="#PWR0114"  Part="1" 
AR Path="/5F899696/5F9D89BF" Ref="#PWR023"  Part="1" 
AR Path="/6013BA2D/5F9D89BF" Ref="#PWR0123"  Part="1" 
F 0 "#PWR0123" H 7900 4800 50  0001 C CNN
F 1 "+5V" H 7915 5127 50  0000 C CNN
F 2 "" H 7900 4950 50  0001 C CNN
F 3 "" H 7900 4950 50  0001 C CNN
	1    7900 4950
	0    -1   -1   0   
$EndComp
$Comp
L salida_dac-rescue:4016-4xxx U8
U 2 1 5F9D89C5
P 7450 2600
AR Path="/5F9D89C5" Ref="U8"  Part="2" 
AR Path="/6013BA2D/5F9D89C5" Ref="U8"  Part="2" 
F 0 "U8" H 7450 2424 50  0000 C CNN
F 1 "4016" H 7450 2331 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W10.16mm_LongPads" H 7450 2600 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/cd4016b.pdf" H 7450 2600 50  0001 C CNN
	2    7450 2600
	-1   0    0    -1  
$EndComp
Wire Wire Line
	8450 4700 8450 4800
Wire Wire Line
	7900 3850 8450 3850
Wire Wire Line
	8450 3850 8450 4100
Wire Wire Line
	10100 4700 10100 4800
Wire Wire Line
	10100 4100 10100 3850
Wire Wire Line
	10100 3850 8450 3850
Connection ~ 8450 3850
Text HLabel 10700 4400 2    50   Input ~ 0
OFF_V_1
Wire Wire Line
	10700 4400 10400 4400
Wire Wire Line
	9000 4400 8750 4400
Wire Wire Line
	7900 3650 8600 3650
$Comp
L salida_dac-rescue:R_POT-Device RV8
U 1 1 5F9D89D6
P 8350 3200
F 0 "RV8" V 8234 3200 50  0000 C CNN
F 1 "1K" V 8141 3200 50  0000 C CNN
F 2 "Potentiometer_THT:Potentiometer_Bourns_3266Y_Vertical" H 8350 3200 50  0001 C CNN
F 3 "~" H 8350 3200 50  0001 C CNN
	1    8350 3200
	0    -1   -1   0   
$EndComp
$Comp
L salida_dac-rescue:R_POT-Device RV7
U 1 1 5F9D89DC
P 8350 2600
F 0 "RV7" V 8234 2600 50  0000 C CNN
F 1 "1K" V 8141 2600 50  0000 C CNN
F 2 "Potentiometer_THT:Potentiometer_Bourns_3266Y_Vertical" H 8350 2600 50  0001 C CNN
F 3 "~" H 8350 2600 50  0001 C CNN
	1    8350 2600
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8600 3650 8600 3200
Wire Wire Line
	8600 2600 8500 2600
Connection ~ 8600 3650
Wire Wire Line
	8500 3200 8600 3200
Connection ~ 8600 3200
Wire Wire Line
	8600 3200 8600 3000
Wire Wire Line
	8200 3200 8100 3200
Wire Wire Line
	8200 2600 8100 2600
Wire Wire Line
	8350 2450 8350 2400
Wire Wire Line
	8350 2400 8600 2400
Wire Wire Line
	8600 2400 8600 2600
Connection ~ 8600 2600
Wire Wire Line
	8350 3050 8350 3000
Wire Wire Line
	8350 3000 8600 3000
Connection ~ 8600 3000
Wire Wire Line
	8600 3000 8600 2600
Wire Wire Line
	9300 3650 9550 3650
Wire Wire Line
	8600 3650 9000 3650
Wire Wire Line
	3350 2850 3550 2850
$Comp
L salida_dac-rescue:R-Device R1
U 1 1 5F8A5925
P 3200 2850
AR Path="/5F8A5925" Ref="R1"  Part="1" 
AR Path="/5F899696/5F8A5925" Ref="R6"  Part="1" 
AR Path="/6013BA2D/5F8A5925" Ref="R6"  Part="1" 
F 0 "R6" V 2993 2850 50  0000 C CNN
F 1 "1K" V 3084 2850 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 3130 2850 50  0001 C CNN
F 3 "~" H 3200 2850 50  0001 C CNN
	1    3200 2850
	0    1    1    0   
$EndComp
Wire Wire Line
	3550 2450 3550 2850
Connection ~ 3550 2450
Connection ~ 3550 2850
Wire Wire Line
	3550 2850 4200 2850
Wire Wire Line
	6600 5450 6850 5450
Wire Wire Line
	5750 5350 6000 5350
Wire Wire Line
	5750 5350 5750 5550
Wire Wire Line
	5750 5550 6000 5550
Connection ~ 5750 5350
$Comp
L salida_dac-rescue:GND-power #PWR0125
U 1 1 601B8CB3
P 5750 5550
F 0 "#PWR0125" H 5750 5300 50  0001 C CNN
F 1 "GND" H 5755 5373 50  0000 C CNN
F 2 "" H 5750 5550 50  0001 C CNN
F 3 "" H 5750 5550 50  0001 C CNN
	1    5750 5550
	1    0    0    -1  
$EndComp
Connection ~ 5750 5550
Wire Wire Line
	4000 2150 2850 2150
Wire Wire Line
	4850 2300 4850 2200
Wire Wire Line
	4850 2200 5150 2200
Connection ~ 5150 2200
Wire Wire Line
	5150 2200 5150 2450
Wire Wire Line
	4850 1700 4850 1600
Wire Wire Line
	4850 1600 5150 1600
Wire Wire Line
	5150 1600 5150 1850
Wire Wire Line
	5000 1850 5150 1850
Connection ~ 5150 1850
Wire Wire Line
	5150 1850 5150 2200
$Comp
L salida_dac-rescue:TL064-Amplifier_Operational U7
U 1 1 604B7F16
P 4500 2950
AR Path="/604B7F16" Ref="U7"  Part="1" 
AR Path="/6013BA2D/604B7F16" Ref="U7"  Part="1" 
F 0 "U7" H 4550 3250 50  0000 C CNN
F 1 "TL064" H 4750 3050 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W10.16mm_LongPads" H 4450 3050 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl061.pdf" H 4550 3150 50  0001 C CNN
	1    4500 2950
	1    0    0    1   
$EndComp
$Comp
L salida_dac-rescue:TL064-Amplifier_Operational U7
U 2 1 604BA8D0
P 7600 3750
AR Path="/604BA8D0" Ref="U7"  Part="2" 
AR Path="/6013BA2D/604BA8D0" Ref="U7"  Part="2" 
F 0 "U7" H 7800 4000 50  0000 C CNN
F 1 "TL064" H 7800 3850 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W10.16mm_LongPads" H 7550 3850 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl061.pdf" H 7650 3950 50  0001 C CNN
	2    7600 3750
	-1   0    0    1   
$EndComp
$Comp
L salida_dac-rescue:TL064-Amplifier_Operational U7
U 3 1 604BBA82
P 2850 6300
AR Path="/604BBA82" Ref="U7"  Part="3" 
AR Path="/6013BA2D/604BBA82" Ref="U7"  Part="3" 
F 0 "U7" H 2850 6667 50  0000 C CNN
F 1 "TL064" H 2850 6576 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W10.16mm_LongPads" H 2800 6400 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl061.pdf" H 2900 6500 50  0001 C CNN
	3    2850 6300
	-1   0    0    1   
$EndComp
$Comp
L salida_dac-rescue:TL064-Amplifier_Operational U7
U 4 1 604BCA31
P 6300 5450
AR Path="/604BCA31" Ref="U7"  Part="4" 
AR Path="/6013BA2D/604BCA31" Ref="U7"  Part="4" 
F 0 "U7" H 6350 5650 50  0000 C CNN
F 1 "TL064" H 6300 5726 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W10.16mm_LongPads" H 6250 5550 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl061.pdf" H 6350 5650 50  0001 C CNN
	4    6300 5450
	1    0    0    -1  
$EndComp
$Comp
L salida_dac-rescue:+5V-power #PWR0108
U 1 1 5F9BDFA6
P 4450 2650
AR Path="/5F9BDFA6" Ref="#PWR0108"  Part="1" 
AR Path="/5F899696/5F9BDFA6" Ref="#PWR017"  Part="1" 
AR Path="/6013BA2D/5F9BDFA6" Ref="#PWR0117"  Part="1" 
F 0 "#PWR0117" H 4450 2500 50  0001 C CNN
F 1 "+5V" H 4300 2700 50  0000 C CNN
F 2 "" H 4450 2650 50  0001 C CNN
F 3 "" H 4450 2650 50  0001 C CNN
	1    4450 2650
	1    0    0    -1  
$EndComp
$Comp
L salida_dac-rescue:-5V-power #PWR0107
U 1 1 5F9BBD75
P 4450 3250
AR Path="/5F9BBD75" Ref="#PWR0107"  Part="1" 
AR Path="/5F899696/5F9BBD75" Ref="#PWR018"  Part="1" 
AR Path="/6013BA2D/5F9BBD75" Ref="#PWR0124"  Part="1" 
F 0 "#PWR0124" H 4450 3350 50  0001 C CNN
F 1 "-5V" H 4600 3350 50  0000 C CNN
F 2 "" H 4450 3250 50  0001 C CNN
F 3 "" H 4450 3250 50  0001 C CNN
	1    4450 3250
	-1   0    0    1   
$EndComp
$Comp
L salida_dac-rescue:TL064-Amplifier_Operational U7
U 5 1 604BE6F2
P 4550 2950
AR Path="/604BE6F2" Ref="U7"  Part="5" 
AR Path="/6013BA2D/604BE6F2" Ref="U7"  Part="5" 
F 0 "U7" H 4650 2650 50  0000 L CNN
F 1 "TL064" H 4600 2750 50  0000 L CNN
F 2 "Package_DIP:DIP-14_W10.16mm_LongPads" H 4500 3050 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl061.pdf" H 4600 3150 50  0001 C CNN
	5    4550 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 2950 5150 2950
Connection ~ 5150 2950
$Comp
L salida_dac-rescue:4016-4xxx U6
U 2 1 5F9506FA
P 4000 1850
AR Path="/5F9506FA" Ref="U6"  Part="2" 
AR Path="/6013BA2D/5F9506FA" Ref="U6"  Part="2" 
F 0 "U6" H 4000 1674 50  0000 C CNN
F 1 "4016" H 4000 1581 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W10.16mm_LongPads" H 4000 1850 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/cd4016b.pdf" H 4000 1850 50  0001 C CNN
	2    4000 1850
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4000 1550 1900 1550
Entry Wire Line
	2300 12550 2400 12450
$Comp
L salida_dac-rescue:4016-4xxx U6
U 4 1 605CEB54
P 2100 3550
AR Path="/605CEB54" Ref="U6"  Part="4" 
AR Path="/6013BA2D/605CEB54" Ref="U6"  Part="4" 
F 0 "U6" H 2100 3374 50  0000 C CNN
F 1 "4016" H 2100 3281 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W10.16mm_LongPads" H 2100 3550 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/cd4016b.pdf" H 2100 3550 50  0001 C CNN
	4    2100 3550
	0    1    -1   0   
$EndComp
Text HLabel 2650 3550 2    50   Input ~ 0
OFF_DAC_2
Wire Wire Line
	2650 3550 2400 3550
Text HLabel 4350 3550 2    50   Input ~ 0
OFF_DAC_1
Wire Wire Line
	4350 3550 4050 3550
$Comp
L salida_dac-rescue:4016-4xxx U6
U 3 1 5F8A5E88
P 3750 3550
AR Path="/5F8A5E88" Ref="U6"  Part="3" 
AR Path="/6013BA2D/5F8A5E88" Ref="U6"  Part="3" 
F 0 "U6" H 3750 3374 50  0000 C CNN
F 1 "4016" H 3750 3281 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W10.16mm_LongPads" H 3750 3550 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/cd4016b.pdf" H 3750 3550 50  0001 C CNN
	3    3750 3550
	0    1    -1   0   
$EndComp
Wire Wire Line
	3750 3850 3750 3950
Wire Wire Line
	2100 3850 2100 3950
$Comp
L salida_dac-rescue:+5V-power #PWR?
U 1 1 60544911
P 1550 4100
AR Path="/60544911" Ref="#PWR?"  Part="1" 
AR Path="/5F899696/60544911" Ref="#PWR?"  Part="1" 
AR Path="/6013BA2D/60544911" Ref="#PWR0126"  Part="1" 
F 0 "#PWR0126" H 1550 3950 50  0001 C CNN
F 1 "+5V" H 1565 4277 50  0000 C CNN
F 2 "" H 1550 4100 50  0001 C CNN
F 3 "" H 1550 4100 50  0001 C CNN
	1    1550 4100
	0    -1   -1   0   
$EndComp
$Comp
L salida_dac-rescue:-5V-power #PWR?
U 1 1 60544907
P 2650 4100
AR Path="/60544907" Ref="#PWR?"  Part="1" 
AR Path="/5F899696/60544907" Ref="#PWR?"  Part="1" 
AR Path="/6013BA2D/60544907" Ref="#PWR0127"  Part="1" 
F 0 "#PWR0127" H 2650 4200 50  0001 C CNN
F 1 "-5V" H 2665 4277 50  0000 C CNN
F 2 "" H 2650 4100 50  0001 C CNN
F 3 "" H 2650 4100 50  0001 C CNN
	1    2650 4100
	0    1    1    0   
$EndComp
Wire Wire Line
	1950 4100 1850 4100
Wire Wire Line
	2350 4100 2250 4100
$Comp
L salida_dac-rescue:R_POT-Device RV11
U 1 1 605448FB
P 2100 4100
F 0 "RV11" V 1984 4100 50  0000 C CNN
F 1 "1K" V 1891 4100 50  0000 C CNN
F 2 "Potentiometer_THT:Potentiometer_Bourns_3266Y_Vertical" H 2100 4100 50  0001 C CNN
F 3 "~" H 2100 4100 50  0001 C CNN
	1    2100 4100
	0    -1   -1   0   
$EndComp
$Comp
L salida_dac-rescue:R-Device R?
U 1 1 605448F1
P 2500 4100
AR Path="/605448F1" Ref="R?"  Part="1" 
AR Path="/5F899696/605448F1" Ref="R?"  Part="1" 
AR Path="/6013BA2D/605448F1" Ref="R25"  Part="1" 
F 0 "R25" V 2293 4100 50  0000 C CNN
F 1 "15K" V 2384 4100 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 2430 4100 50  0001 C CNN
F 3 "~" H 2500 4100 50  0001 C CNN
	1    2500 4100
	0    1    -1   0   
$EndComp
$Comp
L salida_dac-rescue:R-Device R?
U 1 1 605448E7
P 1700 4100
AR Path="/605448E7" Ref="R?"  Part="1" 
AR Path="/5F899696/605448E7" Ref="R?"  Part="1" 
AR Path="/6013BA2D/605448E7" Ref="R24"  Part="1" 
F 0 "R24" V 1493 4100 50  0000 C CNN
F 1 "10K" V 1584 4100 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 1630 4100 50  0001 C CNN
F 3 "~" H 1700 4100 50  0001 C CNN
	1    1700 4100
	0    1    -1   0   
$EndComp
$Comp
L salida_dac-rescue:+5V-power #PWR?
U 1 1 605448DD
P 3200 4100
AR Path="/605448DD" Ref="#PWR?"  Part="1" 
AR Path="/5F899696/605448DD" Ref="#PWR?"  Part="1" 
AR Path="/6013BA2D/605448DD" Ref="#PWR0128"  Part="1" 
F 0 "#PWR0128" H 3200 3950 50  0001 C CNN
F 1 "+5V" H 3215 4277 50  0000 C CNN
F 2 "" H 3200 4100 50  0001 C CNN
F 3 "" H 3200 4100 50  0001 C CNN
	1    3200 4100
	0    -1   -1   0   
$EndComp
$Comp
L salida_dac-rescue:-5V-power #PWR?
U 1 1 605448D3
P 4300 4100
AR Path="/605448D3" Ref="#PWR?"  Part="1" 
AR Path="/5F899696/605448D3" Ref="#PWR?"  Part="1" 
AR Path="/6013BA2D/605448D3" Ref="#PWR0129"  Part="1" 
F 0 "#PWR0129" H 4300 4200 50  0001 C CNN
F 1 "-5V" H 4315 4277 50  0000 C CNN
F 2 "" H 4300 4100 50  0001 C CNN
F 3 "" H 4300 4100 50  0001 C CNN
	1    4300 4100
	0    1    1    0   
$EndComp
Wire Wire Line
	3600 4100 3500 4100
Wire Wire Line
	4000 4100 3900 4100
$Comp
L salida_dac-rescue:R_POT-Device RV12
U 1 1 605448C7
P 3750 4100
F 0 "RV12" V 3634 4100 50  0000 C CNN
F 1 "1K" V 3541 4100 50  0000 C CNN
F 2 "Potentiometer_THT:Potentiometer_Bourns_3266Y_Vertical" H 3750 4100 50  0001 C CNN
F 3 "~" H 3750 4100 50  0001 C CNN
	1    3750 4100
	0    -1   -1   0   
$EndComp
$Comp
L salida_dac-rescue:R-Device R?
U 1 1 605448BD
P 4150 4100
AR Path="/605448BD" Ref="R?"  Part="1" 
AR Path="/5F899696/605448BD" Ref="R?"  Part="1" 
AR Path="/6013BA2D/605448BD" Ref="R27"  Part="1" 
F 0 "R27" V 3943 4100 50  0000 C CNN
F 1 "1K" V 4034 4100 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 4080 4100 50  0001 C CNN
F 3 "~" H 4150 4100 50  0001 C CNN
	1    4150 4100
	0    1    -1   0   
$EndComp
$Comp
L salida_dac-rescue:R-Device R?
U 1 1 605448B2
P 3350 4100
AR Path="/605448B2" Ref="R?"  Part="1" 
AR Path="/5F899696/605448B2" Ref="R?"  Part="1" 
AR Path="/6013BA2D/605448B2" Ref="R26"  Part="1" 
F 0 "R26" V 3143 4100 50  0000 C CNN
F 1 "10K" V 3234 4100 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 3280 4100 50  0001 C CNN
F 3 "~" H 3350 4100 50  0001 C CNN
	1    3350 4100
	0    1    -1   0   
$EndComp
Wire Wire Line
	1800 5450 2700 5450
Wire Wire Line
	3750 3250 3050 3250
Wire Wire Line
	3050 3050 3050 3250
Connection ~ 3050 3250
Wire Wire Line
	3050 3250 2100 3250
Wire Wire Line
	6850 5450 6850 5050
Wire Wire Line
	6850 5050 5750 5050
Wire Wire Line
	5750 5050 5750 5350
Text Notes 2200 2700 0    50   ~ 0
Salida DAC uC de 0 a 3V\nSalida módulo amplificador:\n0V = VEE (-5V)\n1.5V = 0V\n3V = VCC (5V)
Text Notes 1400 7050 0    50   ~ 0
Salida electrodo: VEE<0<VCC\nEntrada ADC: 0 a 5V (eventualmente 0 a 3.3V)
Text Notes 4100 1450 0    50   ~ 0
Amplificador Tension Inversor con selector\nde ganancia y offset\n(AMP T1)
Text Notes 7500 2200 0    50   ~ 0
Amplificador Tension Inversor con selector\nde ganancia y offset\n(AMP T2)
Text Notes 1500 4450 0    50   ~ 0
El offset de este amplificador se regulará para tener valor medio nulo
Text Notes 8150 5400 0    50   ~ 0
El offset de este amplificador se regulará para tener\nvalor medio igual a la mitad del rango del ADC (0 a 3.3V)
Text Notes 3800 6650 0    50   ~ 0
El offset de este amplificador se regulará para tener\nvalor medio igual a la mitad del rango del ADC (0 a 3.3V)
Text Notes 2550 4800 0    50   ~ 0
Amplificador Tension Inversor con selector\nde ganancia y offset\n(AMP I2)
$EndSCHEMATC
