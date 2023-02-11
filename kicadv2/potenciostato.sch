EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 2
Title "Potenciostato"
Date "22/12/22"
Rev "4"
Comp "UTN Facultad Regional Avellaneda"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Connection ~ 4550 3900
Connection ~ 5150 3900
Connection ~ 6200 2750
Connection ~ 6200 3800
Connection ~ 7200 3800
Connection ~ 8200 5150
NoConn ~ 4950 7850
Wire Wire Line
	4050 2750 4550 2750
Wire Wire Line
	4550 3900 4050 3900
Wire Wire Line
	5150 3900 4550 3900
Wire Wire Line
	5150 3900 5300 3900
Wire Wire Line
	5150 4350 5150 3900
Wire Wire Line
	4300 7000 4400 7000
Wire Wire Line
	4400 7000 4400 7100
Wire Wire Line
	5900 4000 6000 4000
Wire Wire Line
	5750 2750 6200 2750
Wire Wire Line
	6000 4000 6000 4350
Wire Wire Line
	6000 4350 5150 4350
Wire Wire Line
	6200 2750 6650 2750
Wire Wire Line
	6200 3150 6200 2750
Wire Wire Line
	6200 3450 6200 3800
Wire Wire Line
	6200 3800 5900 3800
Wire Wire Line
	6550 2950 6550 3050
Wire Wire Line
	6650 2950 6550 2950
Wire Wire Line
	7200 3800 6200 3800
Wire Wire Line
	7200 3800 7350 3800
Wire Wire Line
	7200 4250 7200 3800
Wire Wire Line
	7250 2850 8200 2850
Wire Wire Line
	7850 5350 7950 5350
Wire Wire Line
	7950 3700 8600 3700
Wire Wire Line
	7950 3900 8050 3900
Wire Wire Line
	7950 5350 7950 5450
Wire Wire Line
	8050 3900 8050 4250
Wire Wire Line
	8050 4250 7200 4250
Wire Wire Line
	8200 2850 8200 3600
Wire Wire Line
	8200 3600 8750 3600
Wire Wire Line
	8200 4600 8200 5150
Wire Wire Line
	8200 5150 7850 5150
Wire Wire Line
	8600 3700 8600 3900
Wire Wire Line
	8600 3900 8900 3900
Wire Wire Line
	8600 4000 8600 5150
Wire Wire Line
	8600 5150 8200 5150
Wire Wire Line
	8750 3600 8750 3800
Wire Wire Line
	8750 3800 9000 3800
Wire Wire Line
	9000 4000 8600 4000
Text Notes 3500 7600 0    50   ~ 0
Amplificador Tension Inversor\n(AMP I1)
Text Notes 7300 2550 0    50   ~ 0
Amplificador Tension Inversor\n(AMP T3)
Text Notes 7050 6050 0    50   ~ 0
Amplificador Transresistencia\n(AMP TR)
Text Notes 8250 5400 0    50   ~ 0
Calculamos para una entrada de 1mA \npara que no sature en las primeras mediciones
$Comp
L potenciostato-rescue:-5V-power #PWR0103
U 1 1 601CC2C2
P 4100 6600
F 0 "#PWR0103" H 4100 6700 50  0001 C CNN
F 1 "-5V" H 4115 6777 50  0000 C CNN
F 2 "" H 4100 6600 50  0001 C CNN
F 3 "" H 4100 6600 50  0001 C CNN
	1    4100 6600
	1    0    0    -1  
$EndComp
$Comp
L potenciostato-rescue:+5V-power #PWR0108
U 1 1 601CC639
P 4100 7200
F 0 "#PWR0108" H 4100 7050 50  0001 C CNN
F 1 "+5V" H 4115 7377 50  0000 C CNN
F 2 "" H 4100 7200 50  0001 C CNN
F 3 "" H 4100 7200 50  0001 C CNN
	1    4100 7200
	-1   0    0    1   
$EndComp
$Comp
L potenciostato-rescue:+5V-power #PWR0102
U 1 1 601CC0FC
P 5700 3600
F 0 "#PWR0102" H 5700 3450 50  0001 C CNN
F 1 "+5V" H 5715 3777 50  0000 C CNN
F 2 "" H 5700 3600 50  0001 C CNN
F 3 "" H 5700 3600 50  0001 C CNN
	1    5700 3600
	1    0    0    -1  
$EndComp
$Comp
L potenciostato-rescue:-5V-power #PWR0101
U 1 1 601CC089
P 5700 4200
F 0 "#PWR0101" H 5700 4300 50  0001 C CNN
F 1 "-5V" H 5715 4377 50  0000 C CNN
F 2 "" H 5700 4200 50  0001 C CNN
F 3 "" H 5700 4200 50  0001 C CNN
	1    5700 4200
	-1   0    0    1   
$EndComp
$Comp
L potenciostato-rescue:-5V-power #PWR0105
U 1 1 601CC42A
P 6850 2550
F 0 "#PWR0105" H 6850 2650 50  0001 C CNN
F 1 "-5V" H 6865 2727 50  0000 C CNN
F 2 "" H 6850 2550 50  0001 C CNN
F 3 "" H 6850 2550 50  0001 C CNN
	1    6850 2550
	1    0    0    -1  
$EndComp
$Comp
L potenciostato-rescue:+5V-power #PWR0106
U 1 1 601CC539
P 6850 3150
F 0 "#PWR0106" H 6850 3000 50  0001 C CNN
F 1 "+5V" H 6865 3327 50  0000 C CNN
F 2 "" H 6850 3150 50  0001 C CNN
F 3 "" H 6850 3150 50  0001 C CNN
	1    6850 3150
	-1   0    0    1   
$EndComp
$Comp
L potenciostato-rescue:-5V-power #PWR0104
U 1 1 601CC383
P 7650 4950
F 0 "#PWR0104" H 7650 5050 50  0001 C CNN
F 1 "-5V" H 7665 5127 50  0000 C CNN
F 2 "" H 7650 4950 50  0001 C CNN
F 3 "" H 7650 4950 50  0001 C CNN
	1    7650 4950
	1    0    0    -1  
$EndComp
$Comp
L potenciostato-rescue:+5V-power #PWR0107
U 1 1 601CC592
P 7650 5550
F 0 "#PWR0107" H 7650 5400 50  0001 C CNN
F 1 "+5V" H 7665 5727 50  0000 C CNN
F 2 "" H 7650 5550 50  0001 C CNN
F 3 "" H 7650 5550 50  0001 C CNN
	1    7650 5550
	-1   0    0    1   
$EndComp
$Comp
L potenciostato-rescue:Conn_01x01_Female-Connector I_IN1
U 1 1 6185139C
P 2550 3500
F 0 "I_IN1" V 2488 3412 50  0000 R CNN
F 1 "test_I" V 2397 3412 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 2550 3500 50  0001 C CNN
F 3 "~" H 2550 3500 50  0001 C CNN
	1    2550 3500
	0    -1   -1   0   
$EndComp
$Comp
L potenciostato-rescue:Conn_01x01_Female-Connector VIN1
U 1 1 61851D11
P 4550 2550
F 0 "VIN1" V 4488 2462 50  0000 R CNN
F 1 "test_VIN" V 4397 2462 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 4550 2550 50  0001 C CNN
F 3 "~" H 4550 2550 50  0001 C CNN
	1    4550 2550
	0    -1   -1   0   
$EndComp
$Comp
L potenciostato-rescue:GND-power #PWR06
U 1 1 5F9FAD4A
P 4400 7100
F 0 "#PWR06" H 4400 6850 50  0001 C CNN
F 1 "GND" H 4405 6927 50  0000 C CNN
F 2 "" H 4400 7100 50  0001 C CNN
F 3 "" H 4400 7100 50  0001 C CNN
	1    4400 7100
	1    0    0    -1  
$EndComp
$Comp
L potenciostato-rescue:GND-power #PWR07
U 1 1 5CC2A149
P 6550 3050
F 0 "#PWR07" H 6550 2800 50  0001 C CNN
F 1 "GND" H 6555 2877 50  0000 C CNN
F 2 "" H 6550 3050 50  0001 C CNN
F 3 "" H 6550 3050 50  0001 C CNN
	1    6550 3050
	1    0    0    -1  
$EndComp
$Comp
L potenciostato-rescue:GND-power #PWR08
U 1 1 5CC2AC7B
P 7950 5450
F 0 "#PWR08" H 7950 5200 50  0001 C CNN
F 1 "GND" H 7955 5277 50  0000 C CNN
F 2 "" H 7950 5450 50  0001 C CNN
F 3 "" H 7950 5450 50  0001 C CNN
	1    7950 5450
	1    0    0    -1  
$EndComp
$Comp
L potenciostato-rescue:TL082-Amplifier_Operational U2
U 3 1 601CBFB9
P 5800 3900
F 0 "U2" H 5761 3947 50  0000 L CNN
F 1 "TL082" H 5761 3854 50  0000 L CNN
F 2 "Package_DIP:DIP-8_W7.62mm_LongPads" H 5800 3900 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl081.pdf" H 5800 3900 50  0001 C CNN
	3    5800 3900
	1    0    0    -1  
$EndComp
$Comp
L potenciostato-rescue:R-Device R1
U 1 1 5F9FAD44
P 5400 6100
F 0 "R1" V 5193 6100 50  0000 C CNN
F 1 "1K" V 5284 6100 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 5330 6100 50  0001 C CNN
F 3 "~" H 5400 6100 50  0001 C CNN
	1    5400 6100
	-1   0    0    1   
$EndComp
$Comp
L potenciostato-rescue:R-Device R2
U 1 1 5CC25964
P 5600 2750
F 0 "R2" V 5393 2750 50  0000 C CNN
F 1 "100K" V 5484 2750 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 5530 2750 50  0001 C CNN
F 3 "~" H 5600 2750 50  0001 C CNN
	1    5600 2750
	0    1    1    0   
$EndComp
$Comp
L potenciostato-rescue:R-Device R3
U 1 1 5CC2629B
P 6200 3300
F 0 "R3" V 5993 3300 50  0000 C CNN
F 1 "100K" V 6084 3300 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 6130 3300 50  0001 C CNN
F 3 "~" H 6200 3300 50  0001 C CNN
	1    6200 3300
	1    0    0    -1  
$EndComp
$Comp
L potenciostato-rescue:R-Device R4
U 1 1 5F9FD20A
P 6500 5250
F 0 "R4" V 6293 5250 50  0000 C CNN
F 1 "10K" V 6384 5250 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 6430 5250 50  0001 C CNN
F 3 "~" H 6500 5250 50  0001 C CNN
	1    6500 5250
	0    1    1    0   
$EndComp
$Comp
L potenciostato-rescue:R-Device R5
U 1 1 5CC26B83
P 7550 4600
F 0 "R5" V 7343 4600 50  0000 C CNN
F 1 "6K8" V 7434 4600 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 7480 4600 50  0001 C CNN
F 3 "~" H 7550 4600 50  0001 C CNN
	1    7550 4600
	0    1    1    0   
$EndComp
$Comp
L potenciostato-rescue:Conn_01x03_Male-Connector AUX1
U 1 1 5D250C0E
P 9200 3900
F 0 "AUX1" H 9172 3832 50  0000 R CNN
F 1 "Conn_01x03_Male" H 9172 3923 50  0000 R CNN
F 2 "Connector_Phoenix_MC_HighVoltage:PhoenixContact_MCV_1,5_3-G-5.08_1x03_P5.08mm_Vertical" H 9200 3900 50  0001 C CNN
F 3 "~" H 9200 3900 50  0001 C CNN
	1    9200 3900
	-1   0    0    1   
$EndComp
$Comp
L potenciostato-rescue:TL082-Amplifier_Operational U2
U 2 1 601CBED5
P 5600 3900
F 0 "U2" H 5800 4250 50  0000 C CNN
F 1 "TL082" H 5750 4150 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm_LongPads" H 5600 3900 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl081.pdf" H 5600 3900 50  0001 C CNN
	2    5600 3900
	-1   0    0    -1  
$EndComp
$Comp
L potenciostato-rescue:TL082-Amplifier_Operational U2
U 1 1 601CBD2D
P 7650 3800
F 0 "U2" H 7650 4170 50  0000 C CNN
F 1 "TL082" H 7650 4077 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm_LongPads" H 7650 3800 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl081.pdf" H 7650 3800 50  0001 C CNN
	1    7650 3800
	-1   0    0    -1  
$EndComp
$Comp
L potenciostato-rescue:OP77-Amplifier_Operational U1
U 1 1 5F9FAD3E
P 4000 6900
F 0 "U1" H 4344 6854 50  0000 L CNN
F 1 "OP77" H 4344 6945 50  0000 L CNN
F 2 "Package_SO:HSOP-8-1EP_3.9x4.9mm_P1.27mm_EP2.41x3.1mm" H 4050 6950 50  0001 C CNN
F 3 "https://www.analog.com/media/en/technical-documentation/data-sheets/OP77.pdf" H 4050 7050 50  0001 C CNN
	1    4000 6900
	-1   0    0    1   
$EndComp
$Comp
L potenciostato-rescue:OP77-Amplifier_Operational U3
U 1 1 5CC225D1
P 6950 2850
F 0 "U3" H 7294 2804 50  0000 L CNN
F 1 "OP77" H 7294 2895 50  0000 L CNN
F 2 "Package_SO:HSOP-8-1EP_3.9x4.9mm_P1.27mm_EP2.41x3.1mm" H 7000 2900 50  0001 C CNN
F 3 "https://www.analog.com/media/en/technical-documentation/data-sheets/OP77.pdf" H 7000 3000 50  0001 C CNN
	1    6950 2850
	1    0    0    1   
$EndComp
$Comp
L potenciostato-rescue:OP77-Amplifier_Operational U4
U 1 1 5CC24F96
P 7550 5250
F 0 "U4" H 7894 5204 50  0000 L CNN
F 1 "OP77" H 7894 5295 50  0000 L CNN
F 2 "Package_SO:HSOP-8-1EP_3.9x4.9mm_P1.27mm_EP2.41x3.1mm" H 7600 5300 50  0001 C CNN
F 3 "https://www.analog.com/media/en/technical-documentation/data-sheets/OP77.pdf" H 7600 5400 50  0001 C CNN
	1    7550 5250
	-1   0    0    1   
$EndComp
$Comp
L 4316:4316 U5
U 1 1 631861B4
P 5400 5550
F 0 "U5" V 5446 5422 50  0000 R CNN
F 1 "4316" V 5355 5422 50  0000 R CNN
F 2 "Package_DIP:DIP-16_W7.62mm_LongPads" H 5400 5550 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/cd4016b.pdf" H 5400 5550 50  0001 C CNN
	1    5400 5550
	0    -1   -1   0   
$EndComp
$Comp
L 4316:4316 U5
U 2 1 6318F37A
P 4800 5550
F 0 "U5" V 4846 5422 50  0000 R CNN
F 1 "4316" V 4755 5422 50  0000 R CNN
F 2 "Package_DIP:DIP-16_W7.62mm_LongPads" H 4800 5550 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/cd4016b.pdf" H 4800 5550 50  0001 C CNN
	2    4800 5550
	0    -1   -1   0   
$EndComp
$Comp
L 4316:4316 U5
U 3 1 6318FF8F
P 4150 5500
F 0 "U5" V 4196 5372 50  0000 R CNN
F 1 "4316" V 4105 5372 50  0000 R CNN
F 2 "Package_DIP:DIP-16_W7.62mm_LongPads" H 4150 5500 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/cd4016b.pdf" H 4150 5500 50  0001 C CNN
	3    4150 5500
	0    -1   -1   0   
$EndComp
$Comp
L 4316:4316 U5
U 4 1 63190BC0
P 3550 5500
F 0 "U5" V 3596 5372 50  0000 R CNN
F 1 "4316" V 3505 5372 50  0000 R CNN
F 2 "Package_DIP:DIP-16_W7.62mm_LongPads" H 3550 5500 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/cd4016b.pdf" H 3550 5500 50  0001 C CNN
	4    3550 5500
	0    -1   -1   0   
$EndComp
$Comp
L 4316:4316 U5
U 5 1 631918AF
P 1400 3300
F 0 "U5" H 1630 3346 50  0000 L CNN
F 1 "4316" H 1630 3255 50  0000 L CNN
F 2 "Package_DIP:DIP-16_W7.62mm_LongPads" H 1400 3300 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/cd4016b.pdf" H 1400 3300 50  0001 C CNN
	5    1400 3300
	1    0    0    -1  
$EndComp
$Comp
L potenciostato-rescue:R-Device R15
U 1 1 63197D42
P 4800 6100
F 0 "R15" V 4593 6100 50  0000 C CNN
F 1 "10K" V 4684 6100 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 4730 6100 50  0001 C CNN
F 3 "~" H 4800 6100 50  0001 C CNN
	1    4800 6100
	-1   0    0    1   
$EndComp
$Comp
L potenciostato-rescue:R-Device R12
U 1 1 6319B403
P 4150 6100
F 0 "R12" V 3943 6100 50  0000 C CNN
F 1 "4K7" V 4034 6100 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 4080 6100 50  0001 C CNN
F 3 "~" H 4150 6100 50  0001 C CNN
	1    4150 6100
	-1   0    0    1   
$EndComp
$Comp
L potenciostato-rescue:R-Device R11
U 1 1 631A0511
P 3550 6100
F 0 "R11" V 3343 6100 50  0000 C CNN
F 1 "100K" V 3434 6100 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 3480 6100 50  0001 C CNN
F 3 "~" H 3550 6100 50  0001 C CNN
	1    3550 6100
	-1   0    0    1   
$EndComp
Wire Wire Line
	5400 6250 5400 6300
Wire Wire Line
	5400 6300 4800 6300
Wire Wire Line
	3550 6300 3550 6250
Wire Wire Line
	4150 6250 4150 6300
Connection ~ 4150 6300
Wire Wire Line
	4150 6300 3550 6300
Wire Wire Line
	4800 6250 4800 6300
Connection ~ 4800 6300
Wire Wire Line
	4800 5950 4800 5850
Wire Wire Line
	5400 5950 5400 5850
Wire Wire Line
	4150 5950 4150 5800
Wire Wire Line
	3550 5950 3550 5800
Wire Wire Line
	5400 5250 5400 5150
Wire Wire Line
	5400 5150 4800 5150
Wire Wire Line
	3550 5150 3550 5200
Wire Wire Line
	4150 5200 4150 5150
Connection ~ 4150 5150
Wire Wire Line
	4150 5150 3550 5150
Wire Wire Line
	4800 5250 4800 5150
Connection ~ 4800 5150
Wire Wire Line
	4800 5150 4150 5150
Wire Wire Line
	3550 5150 3050 5150
Wire Wire Line
	3050 5150 3050 6900
Wire Wire Line
	3050 6900 3700 6900
Connection ~ 3550 5150
Wire Wire Line
	3850 5500 3800 5500
Wire Wire Line
	3250 5500 3200 5500
Wire Wire Line
	5100 5550 5050 5550
Wire Wire Line
	5050 4700 2950 4700
Wire Wire Line
	2950 4700 2950 4400
Wire Wire Line
	2950 4400 3050 4400
Wire Wire Line
	5050 4700 5050 5550
Wire Wire Line
	4500 4800 2850 4800
Wire Wire Line
	2850 4800 2850 4250
Wire Wire Line
	2850 4250 3050 4250
Wire Wire Line
	4500 4800 4500 5550
Wire Wire Line
	3800 4900 2750 4900
Wire Wire Line
	2750 4900 2750 4100
Wire Wire Line
	2750 4100 3050 4100
Wire Wire Line
	3800 4900 3800 5500
Wire Wire Line
	3200 5500 3200 5000
Wire Wire Line
	3200 5000 2650 5000
Wire Wire Line
	2650 5000 2650 3950
Wire Wire Line
	2650 3950 3050 3950
Wire Wire Line
	6350 5250 6150 5250
Wire Wire Line
	6150 5250 6150 6800
$Comp
L potenciostato-rescue:+5V-power #PWR02
U 1 1 631EA218
P 1400 2800
F 0 "#PWR02" H 1400 2650 50  0001 C CNN
F 1 "+5V" H 1415 2977 50  0000 C CNN
F 2 "" H 1400 2800 50  0001 C CNN
F 3 "" H 1400 2800 50  0001 C CNN
	1    1400 2800
	1    0    0    -1  
$EndComp
$Comp
L potenciostato-rescue:-5V-power #PWR03
U 1 1 631EAA23
P 1500 3800
F 0 "#PWR03" H 1500 3900 50  0001 C CNN
F 1 "-5V" H 1515 3977 50  0000 C CNN
F 2 "" H 1500 3800 50  0001 C CNN
F 3 "" H 1500 3800 50  0001 C CNN
	1    1500 3800
	-1   0    0    1   
$EndComp
Wire Wire Line
	1300 3800 1300 3850
Wire Wire Line
	1300 3850 950  3850
Wire Wire Line
	950  3850 950  3300
Wire Wire Line
	950  3300 1000 3300
$Comp
L potenciostato-rescue:GND-power #PWR01
U 1 1 631F5715
P 950 3850
F 0 "#PWR01" H 950 3600 50  0001 C CNN
F 1 "GND" H 955 3677 50  0000 C CNN
F 2 "" H 950 3850 50  0001 C CNN
F 3 "" H 950 3850 50  0001 C CNN
	1    950  3850
	1    0    0    -1  
$EndComp
Connection ~ 950  3850
$Sheet
S 3050 2650 1000 1900
U 6013BA2D
F0 "salida_dac" 50
F1 "salida_dac.sch" 50
F2 "VIN" O R 4050 2750 50 
F3 "I_IN" I L 3050 3700 50 
F4 "V_IN" I R 4050 3900 50 
F5 "gan_x1" O L 3050 4250 50 
F6 "gan_x5" O L 3050 4100 50 
F7 "gan_x0.1" O L 3050 4400 50 
F8 "gan_x10" O L 3050 3950 50 
$EndSheet
Wire Wire Line
	3050 6900 2550 6900
Wire Wire Line
	2550 6900 2550 3700
Connection ~ 3050 6900
Connection ~ 2550 3700
Wire Wire Line
	2550 3700 3050 3700
$Comp
L potenciostato-rescue:Conn_01x01_Female-Connector V_IN1
U 1 1 61851AC8
P 4550 3700
F 0 "V_IN1" V 4488 3612 50  0000 R CNN
F 1 "test_V" V 4397 3612 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 4550 3700 50  0001 C CNN
F 3 "~" H 4550 3700 50  0001 C CNN
	1    4550 3700
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7700 4600 8200 4600
Wire Wire Line
	7400 4600 6850 4600
Wire Wire Line
	6850 4600 6850 5250
Connection ~ 6850 5250
Wire Wire Line
	6850 5250 7250 5250
Wire Wire Line
	4300 6800 5400 6800
Wire Wire Line
	4150 6300 4800 6300
Wire Wire Line
	5400 6300 5400 6800
Connection ~ 5400 6300
Connection ~ 5400 6800
Wire Wire Line
	5400 6800 6150 6800
$Comp
L Regulator_Linear:L7805 U?
U 1 1 6322EB68
P 4300 950
AR Path="/6214974F/6322EB68" Ref="U?"  Part="1" 
AR Path="/6322EB68" Ref="U6"  Part="1" 
F 0 "U6" H 4300 1192 50  0000 C CNN
F 1 "L7805" H 4300 1101 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 4325 800 50  0001 L CIN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/41/4f/b3/b0/12/d4/47/88/CD00000444.pdf/files/CD00000444.pdf/jcr:content/translations/en.CD00000444.pdf" H 4300 900 50  0001 C CNN
	1    4300 950 
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:L7905 U?
U 1 1 6322EB6E
P 4300 2000
AR Path="/6214974F/6322EB6E" Ref="U?"  Part="1" 
AR Path="/6322EB6E" Ref="U8"  Part="1" 
F 0 "U8" H 4300 1851 50  0000 C CNN
F 1 "L7905" H 4300 1760 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 4300 1800 50  0001 C CIN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/c9/16/86/41/c7/2b/45/f2/CD00000450.pdf/files/CD00000450.pdf/jcr:content/translations/en.CD00000450.pdf" H 4300 2000 50  0001 C CNN
	1    4300 2000
	1    0    0    -1  
$EndComp
$Comp
L potenciostato-rescue:CP-Device C?
U 1 1 6322EB74
P 3350 1800
AR Path="/6214974F/6322EB74" Ref="C?"  Part="1" 
AR Path="/6322EB74" Ref="C2"  Part="1" 
F 0 "C2" H 3468 1846 50  0000 L CNN
F 1 "10uF" H 3468 1755 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.00mm" H 3388 1650 50  0001 C CNN
F 3 "~" H 3350 1800 50  0001 C CNN
	1    3350 1800
	1    0    0    -1  
$EndComp
$Comp
L potenciostato-rescue:CP-Device C?
U 1 1 6322EB7A
P 3350 1150
AR Path="/6214974F/6322EB7A" Ref="C?"  Part="1" 
AR Path="/6322EB7A" Ref="C1"  Part="1" 
F 0 "C1" H 3468 1196 50  0000 L CNN
F 1 "10uF" H 3468 1105 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.00mm" H 3388 1000 50  0001 C CNN
F 3 "~" H 3350 1150 50  0001 C CNN
	1    3350 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 1700 4300 1450
Wire Wire Line
	4300 1450 3800 1450
Connection ~ 4300 1450
Wire Wire Line
	4300 1450 4300 1250
Wire Wire Line
	4000 2000 3800 2000
Wire Wire Line
	4000 950  3800 950 
Wire Wire Line
	3350 1650 3350 1450
Connection ~ 3350 1450
Wire Wire Line
	3350 1300 3350 1450
Wire Wire Line
	3350 1000 3350 950 
Connection ~ 3350 950 
Wire Wire Line
	3350 1950 3350 2000
Connection ~ 3350 2000
$Comp
L Transformer:ADT2-71T TR?
U 1 1 6322EB8D
P 1350 1450
AR Path="/6214974F/6322EB8D" Ref="TR?"  Part="1" 
AR Path="/6322EB8D" Ref="TR1"  Part="1" 
F 0 "TR1" H 1350 1831 50  0000 C CNN
F 1 "ADT2-71T" H 1350 1740 50  0000 C CNN
F 2 "kicadv2:Transformador_7.5V" H 1350 1100 50  0001 C CNN
F 3 "https://www.minicircuits.com/pdfs/ADT2-71T+.pdf" H 1350 1450 50  0001 C CNN
	1    1350 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 950  4950 950 
Wire Wire Line
	4600 2000 4950 2000
Wire Wire Line
	4300 1450 4950 1450
$Comp
L potenciostato-rescue:CP-Device C?
U 1 1 6322EB96
P 4950 1800
AR Path="/6214974F/6322EB96" Ref="C?"  Part="1" 
AR Path="/6322EB96" Ref="C6"  Part="1" 
F 0 "C6" H 5068 1846 50  0000 L CNN
F 1 "10uF" H 5068 1755 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.00mm" H 4988 1650 50  0001 C CNN
F 3 "~" H 4950 1800 50  0001 C CNN
	1    4950 1800
	1    0    0    -1  
$EndComp
$Comp
L potenciostato-rescue:CP-Device C?
U 1 1 6322EB9C
P 4950 1150
AR Path="/6214974F/6322EB9C" Ref="C?"  Part="1" 
AR Path="/6322EB9C" Ref="C5"  Part="1" 
F 0 "C5" H 5068 1196 50  0000 L CNN
F 1 "10uF" H 5068 1105 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.00mm" H 4988 1000 50  0001 C CNN
F 3 "~" H 4950 1150 50  0001 C CNN
	1    4950 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4950 1300 4950 1450
Connection ~ 4950 1450
Wire Wire Line
	4950 1450 5450 1450
Wire Wire Line
	4950 1650 4950 1450
Wire Wire Line
	4950 1950 4950 2000
Connection ~ 4950 2000
Wire Wire Line
	4950 2000 5500 2000
Wire Wire Line
	4950 1000 4950 950 
Connection ~ 4950 950 
Wire Wire Line
	4950 950  5450 950 
$Comp
L Device:C C?
U 1 1 6322EBAC
P 3800 1150
AR Path="/6214974F/6322EBAC" Ref="C?"  Part="1" 
AR Path="/6322EBAC" Ref="C3"  Part="1" 
F 0 "C3" H 3915 1196 50  0000 L CNN
F 1 "100nF" H 3915 1105 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 3838 1000 50  0001 C CNN
F 3 "~" H 3800 1150 50  0001 C CNN
	1    3800 1150
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 6322EBB2
P 3800 1800
AR Path="/6214974F/6322EBB2" Ref="C?"  Part="1" 
AR Path="/6322EBB2" Ref="C4"  Part="1" 
F 0 "C4" H 3915 1846 50  0000 L CNN
F 1 "100nF" H 3915 1755 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 3838 1650 50  0001 C CNN
F 3 "~" H 3800 1800 50  0001 C CNN
	1    3800 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 1650 3800 1450
Connection ~ 3800 1450
Wire Wire Line
	3800 1450 3350 1450
Wire Wire Line
	3800 1450 3800 1300
Wire Wire Line
	3800 1000 3800 950 
Connection ~ 3800 950 
Wire Wire Line
	3800 950  3350 950 
Wire Wire Line
	3800 1950 3800 2000
Connection ~ 3800 2000
Wire Wire Line
	3800 2000 3350 2000
Wire Wire Line
	2350 1150 2350 950 
Wire Wire Line
	2350 950  3350 950 
Wire Wire Line
	2350 1750 2350 2000
Wire Wire Line
	2350 2000 3350 2000
Wire Wire Line
	1900 1450 2050 1450
Wire Wire Line
	2650 1450 2750 1450
Wire Wire Line
	1550 1450 1650 1450
Wire Wire Line
	1650 1450 1650 1500
$Comp
L power:GND #PWR?
U 1 1 6322EBD6
P 1650 1500
AR Path="/6214974F/6322EBD6" Ref="#PWR?"  Part="1" 
AR Path="/6322EBD6" Ref="#PWR04"  Part="1" 
F 0 "#PWR04" H 1650 1250 50  0001 C CNN
F 1 "GND" H 1655 1327 50  0000 C CNN
F 2 "" H 1650 1500 50  0001 C CNN
F 3 "" H 1650 1500 50  0001 C CNN
	1    1650 1500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6322EBDC
P 5450 1500
AR Path="/6214974F/6322EBDC" Ref="#PWR?"  Part="1" 
AR Path="/6322EBDC" Ref="#PWR09"  Part="1" 
F 0 "#PWR09" H 5450 1250 50  0001 C CNN
F 1 "GND" H 5455 1327 50  0000 C CNN
F 2 "" H 5450 1500 50  0001 C CNN
F 3 "" H 5450 1500 50  0001 C CNN
	1    5450 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 1500 5450 1450
Wire Wire Line
	5450 950  5450 850 
$Comp
L potenciostato-rescue:+5V-power #PWR05
U 1 1 6325C91B
P 5450 850
F 0 "#PWR05" H 5450 700 50  0001 C CNN
F 1 "+5V" H 5465 1027 50  0000 C CNN
F 2 "" H 5450 850 50  0001 C CNN
F 3 "" H 5450 850 50  0001 C CNN
	1    5450 850 
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 2000 5500 2100
$Comp
L potenciostato-rescue:-5V-power #PWR010
U 1 1 63262C72
P 5500 2100
F 0 "#PWR010" H 5500 2200 50  0001 C CNN
F 1 "-5V" H 5515 2277 50  0000 C CNN
F 2 "" H 5500 2100 50  0001 C CNN
F 3 "" H 5500 2100 50  0001 C CNN
	1    5500 2100
	-1   0    0    1   
$EndComp
$Comp
L potenciostato-rescue:GND-power #PWR0130
U 1 1 609B9D8E
P 1250 4750
F 0 "#PWR0130" H 1250 4500 50  0001 C CNN
F 1 "GND" H 1255 4577 50  0000 C CNN
F 2 "" H 1250 4750 50  0001 C CNN
F 3 "" H 1250 4750 50  0001 C CNN
	1    1250 4750
	1    0    0    -1  
$EndComp
$Comp
L potenciostato-rescue:Conn_01x01_Female-Connector GND3
U 1 1 6185D9DF
P 1600 4450
F 0 "GND3" H 1538 4362 50  0000 R CNN
F 1 "test_GND" H 1750 4250 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 1600 4450 50  0001 C CNN
F 3 "~" H 1600 4450 50  0001 C CNN
	1    1600 4450
	0    -1   -1   0   
$EndComp
$Comp
L potenciostato-rescue:Conn_01x01_Female-Connector GND2
U 1 1 6185DEE6
P 1250 4450
F 0 "GND2" H 1188 4362 50  0000 R CNN
F 1 "test_GND" H 1400 4250 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 1250 4450 50  0001 C CNN
F 3 "~" H 1250 4450 50  0001 C CNN
	1    1250 4450
	0    -1   -1   0   
$EndComp
$Comp
L potenciostato-rescue:Conn_01x01_Female-Connector GND1
U 1 1 6185E017
P 900 4450
F 0 "GND1" H 838 4362 50  0000 R CNN
F 1 "test_GND" H 1050 4250 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 900 4450 50  0001 C CNN
F 3 "~" H 900 4450 50  0001 C CNN
	1    900  4450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1250 4650 1250 4750
Wire Wire Line
	1250 4650 1600 4650
Wire Wire Line
	900  4650 1250 4650
Connection ~ 1250 4650
$Comp
L Device:D_Bridge_+-AA D?
U 1 1 6322EBC2
P 2350 1450
AR Path="/6214974F/6322EBC2" Ref="D?"  Part="1" 
AR Path="/6322EBC2" Ref="D1"  Part="1" 
F 0 "D1" V 2396 1106 50  0000 R CNN
F 1 "D_Bridge_+-AA" V 2305 1106 50  0000 R CNN
F 2 "Diode_SMD:Diode_Bridge_Vishay_DFS" H 2350 1450 50  0001 C CNN
F 3 "~" H 2350 1450 50  0001 C CNN
	1    2350 1450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2200 1250 2200 1100
Wire Wire Line
	2200 1100 2750 1100
Wire Wire Line
	2750 1100 2750 1450
Wire Wire Line
	1550 1250 2200 1250
Wire Wire Line
	1900 1650 1900 1450
Wire Wire Line
	1550 1650 1900 1650
Wire Wire Line
	6650 5250 6850 5250
Connection ~ 4550 2750
Wire Wire Line
	4550 2750 5450 2750
$Comp
L potenciostato-rescue:Conn_01x01_Female-Connector AC2
U 1 1 63685931
P 950 1650
F 0 "AC2" H 888 1562 50  0000 R CNN
F 1 "AC2" H 1100 1450 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 950 1650 50  0001 C CNN
F 3 "~" H 950 1650 50  0001 C CNN
	1    950  1650
	-1   0    0    1   
$EndComp
$Comp
L potenciostato-rescue:Conn_01x01_Female-Connector AC1
U 1 1 636995B8
P 950 1250
F 0 "AC1" H 888 1162 50  0000 R CNN
F 1 "AC1" H 1100 1050 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 950 1250 50  0001 C CNN
F 3 "~" H 950 1250 50  0001 C CNN
	1    950  1250
	-1   0    0    1   
$EndComp
$Comp
L power:GNDD #PWR0119
U 1 1 636D1318
P 5700 1500
F 0 "#PWR0119" H 5700 1250 50  0001 C CNN
F 1 "GNDD" H 5704 1345 50  0000 C CNN
F 2 "" H 5700 1500 50  0001 C CNN
F 3 "" H 5700 1500 50  0001 C CNN
	1    5700 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 1450 5700 1450
Wire Wire Line
	5700 1450 5700 1500
Connection ~ 5450 1450
$Comp
L Connector:Conn_Coaxial BNC1
U 1 1 636ED754
P 9200 4250
F 0 "BNC1" H 9300 4225 50  0000 L CNN
F 1 "Conn_Coaxial" H 9300 4134 50  0000 L CNN
F 2 "Connector_Coaxial:BNC_Amphenol_B6252HB-NPP3G-50_Horizontal" H 9200 4250 50  0001 C CNN
F 3 " ~" H 9200 4250 50  0001 C CNN
	1    9200 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	9000 4250 8750 4250
Wire Wire Line
	8750 4250 8750 3800
Connection ~ 8750 3800
Wire Wire Line
	9200 4450 8900 4450
Wire Wire Line
	8900 4450 8900 3900
Connection ~ 8900 3900
Wire Wire Line
	8900 3900 9000 3900
$EndSCHEMATC
