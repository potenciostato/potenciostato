EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 2
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
L salida_dac-rescue:R-Device R2
U 1 1 5F8A81B2
P 7100 5300
AR Path="/5F8A81B2" Ref="R2"  Part="1" 
AR Path="/5F899696/5F8A81B2" Ref="R7"  Part="1" 
AR Path="/6013BA2D/5F8A81B2" Ref="R7"  Part="1" 
F 0 "R7" V 7300 5300 50  0000 C CNN
F 1 "10K" V 7200 5300 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 7030 5300 50  0001 C CNN
F 3 "~" H 7100 5300 50  0001 C CNN
	1    7100 5300
	0    1    1    0   
$EndComp
Text HLabel 9100 5200 2    50   Output ~ 0
VIN
Text HLabel 9200 1500 2    50   Input ~ 0
I_IN
Wire Wire Line
	8950 1500 9200 1500
$Comp
L salida_dac-rescue:R-Device R1
U 1 1 5F8A5925
P 7100 5100
AR Path="/5F8A5925" Ref="R1"  Part="1" 
AR Path="/5F899696/5F8A5925" Ref="R6"  Part="1" 
AR Path="/6013BA2D/5F8A5925" Ref="R6"  Part="1" 
F 0 "R6" V 6893 5100 50  0000 C CNN
F 1 "10K" V 6984 5100 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 7030 5100 50  0001 C CNN
F 3 "~" H 7100 5100 50  0001 C CNN
	1    7100 5100
	0    1    1    0   
$EndComp
Wire Wire Line
	2500 6750 2750 6750
$Comp
L salida_dac-rescue:TL064-Amplifier_Operational U7
U 1 1 604B7F16
P 7950 5200
AR Path="/604B7F16" Ref="U7"  Part="1" 
AR Path="/6013BA2D/604B7F16" Ref="U7"  Part="1" 
F 0 "U7" H 8000 5500 50  0000 C CNN
F 1 "TL064" H 8200 5300 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W7.62mm_Socket_LongPads" H 7900 5300 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl061.pdf" H 8000 5400 50  0001 C CNN
	1    7950 5200
	1    0    0    1   
$EndComp
$Comp
L salida_dac-rescue:TL064-Amplifier_Operational U7
U 3 1 604BBA82
P 7850 1600
AR Path="/604BBA82" Ref="U7"  Part="3" 
AR Path="/6013BA2D/604BBA82" Ref="U7"  Part="3" 
F 0 "U7" H 7850 1967 50  0000 C CNN
F 1 "TL064" H 7850 1876 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W7.62mm_Socket_LongPads" H 7800 1700 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl061.pdf" H 7900 1800 50  0001 C CNN
	3    7850 1600
	-1   0    0    -1  
$EndComp
$Comp
L salida_dac-rescue:TL064-Amplifier_Operational U7
U 4 1 604BCA31
P 10400 6100
AR Path="/604BCA31" Ref="U7"  Part="4" 
AR Path="/6013BA2D/604BCA31" Ref="U7"  Part="4" 
F 0 "U7" H 10450 6300 50  0000 C CNN
F 1 "TL064" H 10400 6376 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W7.62mm_Socket_LongPads" H 10350 6200 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl061.pdf" H 10450 6300 50  0001 C CNN
	4    10400 6100
	1    0    0    -1  
$EndComp
$Comp
L salida_dac-rescue:+5V-power #PWR0108
U 1 1 5F9BDFA6
P 7900 4900
AR Path="/5F9BDFA6" Ref="#PWR0108"  Part="1" 
AR Path="/5F899696/5F9BDFA6" Ref="#PWR017"  Part="1" 
AR Path="/6013BA2D/5F9BDFA6" Ref="#PWR0117"  Part="1" 
F 0 "#PWR0117" H 7900 4750 50  0001 C CNN
F 1 "+5V" H 7750 4950 50  0000 C CNN
F 2 "" H 7900 4900 50  0001 C CNN
F 3 "" H 7900 4900 50  0001 C CNN
	1    7900 4900
	1    0    0    -1  
$EndComp
$Comp
L salida_dac-rescue:-5V-power #PWR0107
U 1 1 5F9BBD75
P 7900 5500
AR Path="/5F9BBD75" Ref="#PWR0107"  Part="1" 
AR Path="/5F899696/5F9BBD75" Ref="#PWR018"  Part="1" 
AR Path="/6013BA2D/5F9BBD75" Ref="#PWR0124"  Part="1" 
F 0 "#PWR0124" H 7900 5600 50  0001 C CNN
F 1 "-5V" H 8050 5600 50  0000 C CNN
F 2 "" H 7900 5500 50  0001 C CNN
F 3 "" H 7900 5500 50  0001 C CNN
	1    7900 5500
	-1   0    0    1   
$EndComp
$Comp
L salida_dac-rescue:TL064-Amplifier_Operational U7
U 5 1 604BE6F2
P 8000 5200
AR Path="/604BE6F2" Ref="U7"  Part="5" 
AR Path="/6013BA2D/604BE6F2" Ref="U7"  Part="5" 
F 0 "U7" H 8100 4900 50  0000 L CNN
F 1 "TL064" H 8050 5000 50  0000 L CNN
F 2 "Package_DIP:DIP-14_W7.62mm_Socket_LongPads" H 7950 5300 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl061.pdf" H 8050 5400 50  0001 C CNN
	5    8000 5200
	1    0    0    -1  
$EndComp
Text Notes 8500 2800 0    50   ~ 0
Amplificador No Inversor con ganancia unitaria y VOffset,\nadapta la se??al a 0-3.3V\n(AMP T2)
$Comp
L salida_dac-rescue:R-Device R8
U 1 1 5F8A592F
P 7850 4700
AR Path="/5F8A592F" Ref="R8"  Part="1" 
AR Path="/5F899696/5F8A592F" Ref="R13"  Part="1" 
AR Path="/6013BA2D/5F8A592F" Ref="R13"  Part="1" 
F 0 "R13" V 7643 4700 50  0000 C CNN
F 1 "10K" V 7734 4700 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 7780 4700 50  0001 C CNN
F 3 "~" H 7850 4700 50  0001 C CNN
	1    7850 4700
	0    1    1    0   
$EndComp
$Comp
L potenciostato-rescue:R-Device R8
U 1 1 6174E172
P 8800 1700
F 0 "R8" V 8900 1700 50  0000 C CNN
F 1 "10K" V 9000 1700 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 8730 1700 50  0001 C CNN
F 3 "~" H 8800 1700 50  0001 C CNN
	1    8800 1700
	0    1    1    0   
$EndComp
$Comp
L salida_dac-rescue:R-Device R9
U 1 1 5F9506D4
P 8800 1500
AR Path="/5F9506D4" Ref="R9"  Part="1" 
AR Path="/5F899696/5F9506D4" Ref="R14"  Part="1" 
AR Path="/6013BA2D/5F9506D4" Ref="R14"  Part="1" 
F 0 "R14" V 8593 1500 50  0000 C CNN
F 1 "10K" V 8684 1500 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 8730 1500 50  0001 C CNN
F 3 "~" H 8800 1500 50  0001 C CNN
	1    8800 1500
	0    -1   1    0   
$EndComp
Wire Wire Line
	8250 5200 8300 5200
$Comp
L salida_dac-rescue:R-Device R4
U 1 1 5F9506DA
P 7800 2150
AR Path="/5F9506DA" Ref="R4"  Part="1" 
AR Path="/5F899696/5F9506DA" Ref="R9"  Part="1" 
AR Path="/6013BA2D/5F9506DA" Ref="R9"  Part="1" 
F 0 "R9" V 7593 2150 50  0000 C CNN
F 1 "10K" V 7684 2150 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 7730 2150 50  0001 C CNN
F 3 "~" H 7800 2150 50  0001 C CNN
	1    7800 2150
	0    1    1    0   
$EndComp
Wire Wire Line
	7650 2150 7400 2150
Wire Wire Line
	7400 1600 7400 2150
Wire Wire Line
	7700 4700 7450 4700
Wire Wire Line
	7450 4700 7450 5100
Connection ~ 7450 5100
Wire Wire Line
	7450 5100 7650 5100
Wire Wire Line
	8000 4700 8300 4700
Wire Wire Line
	8300 4700 8300 5200
Connection ~ 8300 5200
Wire Wire Line
	8300 5200 9100 5200
Wire Wire Line
	7250 5100 7450 5100
$Comp
L potenciostato-rescue:Conn_01x01_Female-Connector J?
U 1 1 6318DCEB
P 6400 3550
AR Path="/60147E53/6318DCEB" Ref="J?"  Part="1" 
AR Path="/6013BA2D/6318DCEB" Ref="DAC1"  Part="1" 
F 0 "DAC1" H 6300 3350 50  0000 L CNN
F 1 "test_DAC" H 6300 3450 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 6400 3550 50  0001 C CNN
F 3 "~" H 6400 3550 50  0001 C CNN
	1    6400 3550
	1    0    0    1   
$EndComp
Wire Wire Line
	1300 1700 1300 1850
$Comp
L potenciostato-rescue:USB_B_Micro-Connector J?
U 1 1 6318DCB8
P 1300 2250
AR Path="/6318DCB8" Ref="J?"  Part="1" 
AR Path="/60147E53/6318DCB8" Ref="J?"  Part="1" 
AR Path="/6013BA2D/6318DCB8" Ref="USB1"  Part="1" 
F 0 "USB1" H 1070 2146 50  0000 R CNN
F 1 "USB_B_Micro" H 1070 2239 50  0000 R CNN
F 2 "kicadv2:ModuloUSB-Micro" H 1450 2200 50  0001 C CNN
F 3 "~" H 1450 2200 50  0001 C CNN
	1    1300 2250
	1    0    0    1   
$EndComp
$Comp
L potenciostato-rescue:LPCXPRESSO_LPC1769-LPCXPRESSO_LPC1769 LPC?
U 1 1 6318DCAF
P 3300 2750
AR Path="/6318DCAF" Ref="LPC?"  Part="1" 
AR Path="/60147E53/6318DCAF" Ref="LPC?"  Part="1" 
AR Path="/6013BA2D/6318DCAF" Ref="LPC1"  Part="1" 
F 0 "LPC1" H 3450 4420 50  0000 C CNN
F 1 "LPCXPRESSO_LPC1769" H 3450 4329 50  0000 C CNN
F 2 "kicadv2:LPCXPRESSO_LPC1769" H 3300 2750 50  0001 L BNN
F 3 "" H 3300 2750 50  0001 L BNN
	1    3300 2750
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5100 1350 4500 1350
Wire Wire Line
	5100 1450 4500 1450
$Comp
L potenciostato-rescue:Jumper-Device JP?
U 1 1 6318DCDD
P 5400 1450
AR Path="/60147E53/6318DCDD" Ref="JP?"  Part="1" 
AR Path="/6013BA2D/6318DCDD" Ref="+5V_LPC1"  Part="1" 
F 0 "+5V_LPC1" H 5400 1350 50  0000 C CNN
F 1 "alimentacion_lpc" H 5400 1250 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 5400 1450 50  0001 C CNN
F 3 "~" H 5400 1450 50  0001 C CNN
	1    5400 1450
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1800 3950 1600 3950
Wire Wire Line
	1800 2250 1600 2250
Wire Wire Line
	1800 2150 1600 2150
Wire Wire Line
	8650 3100 8450 3100
$Comp
L potenciostato-rescue:R-Device R10
U 1 1 6174BBEA
P 8800 3300
F 0 "R10" V 8900 3300 50  0000 C CNN
F 1 "10K" V 9000 3300 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 8730 3300 50  0001 C CNN
F 3 "~" H 8800 3300 50  0001 C CNN
	1    8800 3300
	0    1    1    0   
$EndComp
$Comp
L salida_dac-rescue:TL064-Amplifier_Operational U7
U 2 1 604BA8D0
P 7850 3200
AR Path="/604BA8D0" Ref="U7"  Part="2" 
AR Path="/6013BA2D/604BA8D0" Ref="U7"  Part="2" 
F 0 "U7" H 8050 3100 50  0000 C CNN
F 1 "TL064" H 8050 3000 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W7.62mm_Socket_LongPads" H 7800 3300 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl061.pdf" H 7900 3400 50  0001 C CNN
	2    7850 3200
	-1   0    0    -1  
$EndComp
Wire Wire Line
	8950 3100 9200 3100
Text HLabel 9200 3100 2    50   Input ~ 0
V_IN
$Comp
L salida_dac-rescue:R-Device R13
U 1 1 5F9D8928
P 7800 3650
AR Path="/5F9D8928" Ref="R13"  Part="1" 
AR Path="/5F899696/5F9D8928" Ref="R18"  Part="1" 
AR Path="/6013BA2D/5F9D8928" Ref="R18"  Part="1" 
F 0 "R18" V 7593 3650 50  0000 C CNN
F 1 "10K" V 7684 3650 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 7730 3650 50  0001 C CNN
F 3 "~" H 7800 3650 50  0001 C CNN
	1    7800 3650
	0    -1   -1   0   
$EndComp
$Comp
L salida_dac-rescue:R-Device R16
U 1 1 5F9D8922
P 8800 3100
AR Path="/5F9D8922" Ref="R16"  Part="1" 
AR Path="/5F899696/5F9D8922" Ref="R21"  Part="1" 
AR Path="/6013BA2D/5F9D8922" Ref="R21"  Part="1" 
F 0 "R21" V 8593 3100 50  0000 C CNN
F 1 "10K" V 8684 3100 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 8730 3100 50  0001 C CNN
F 3 "~" H 8800 3100 50  0001 C CNN
	1    8800 3100
	0    -1   1    0   
$EndComp
Wire Wire Line
	6300 3200 6300 3050
Connection ~ 6300 3050
Wire Wire Line
	6300 3050 6300 2850
Wire Wire Line
	6200 3050 6200 3550
$Comp
L potenciostato-rescue:Conn_01x01_Female-Connector J?
U 1 1 6318DCF3
P 6500 3050
AR Path="/60147E53/6318DCF3" Ref="J?"  Part="1" 
AR Path="/6013BA2D/6318DCF3" Ref="V1"  Part="1" 
F 0 "V1" H 6450 2850 50  0000 R CNN
F 1 "test_V" H 6600 2950 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 6500 3050 50  0001 C CNN
F 3 "~" H 6500 3050 50  0001 C CNN
	1    6500 3050
	1    0    0    1   
$EndComp
$Comp
L potenciostato-rescue:+5V-power #PWR?
U 1 1 6322594C
P 5800 1350
AR Path="/6322594C" Ref="#PWR?"  Part="1" 
AR Path="/6013BA2D/6322594C" Ref="#PWR017"  Part="1" 
F 0 "#PWR017" H 5800 1200 50  0001 C CNN
F 1 "+5V" H 5815 1527 50  0000 C CNN
F 2 "" H 5800 1350 50  0001 C CNN
F 3 "" H 5800 1350 50  0001 C CNN
	1    5800 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	5700 1450 5800 1450
Wire Wire Line
	5800 1450 5800 1350
Wire Wire Line
	5100 1350 5100 950 
Wire Wire Line
	5100 950  5250 950 
Wire Wire Line
	5250 950  5250 1000
Wire Wire Line
	1900 6850 1700 6850
Wire Wire Line
	1700 7300 2750 7300
Wire Wire Line
	2750 6450 3000 6450
Connection ~ 2750 6750
Text Label 3000 6450 0    50   ~ 0
VOffset
Wire Wire Line
	6950 5300 6800 5300
Wire Wire Line
	8950 3300 9200 3300
Wire Wire Line
	8950 1700 9200 1700
Text Label 6800 5300 2    50   ~ 0
-VOffset
Text Label 9200 3300 0    50   ~ 0
VOffset
Text Label 9200 1700 0    50   ~ 0
VOffset
$Comp
L salida_dac-rescue:R-Device R?
U 1 1 63256A9B
P 1300 6300
AR Path="/63256A9B" Ref="R?"  Part="1" 
AR Path="/5F899696/63256A9B" Ref="R?"  Part="1" 
AR Path="/6013BA2D/63256A9B" Ref="R17"  Part="1" 
F 0 "R17" V 1093 6300 50  0000 C CNN
F 1 "4K7" V 1184 6300 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 1230 6300 50  0001 C CNN
F 3 "~" H 1300 6300 50  0001 C CNN
	1    1300 6300
	-1   0    0    1   
$EndComp
$Comp
L salida_dac-rescue:R-Device R?
U 1 1 63257614
P 1300 7000
AR Path="/63257614" Ref="R?"  Part="1" 
AR Path="/5F899696/63257614" Ref="R?"  Part="1" 
AR Path="/6013BA2D/63257614" Ref="R19"  Part="1" 
F 0 "R19" V 1093 7000 50  0000 C CNN
F 1 "5K6" V 1184 7000 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 1230 7000 50  0001 C CNN
F 3 "~" H 1300 7000 50  0001 C CNN
	1    1300 7000
	-1   0    0    1   
$EndComp
$Comp
L Device:R_POT RV1
U 1 1 6325355B
P 1300 6650
F 0 "RV1" H 1231 6696 50  0000 R CNN
F 1 "10K" H 1231 6605 50  0000 R CNN
F 2 "Potentiometer_THT:Potentiometer_Bourns_3296W_Vertical" H 1300 6650 50  0001 C CNN
F 3 "~" H 1300 6650 50  0001 C CNN
	1    1300 6650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 6800 1300 6850
Wire Wire Line
	1300 6450 1300 6500
Wire Wire Line
	1300 7150 1300 7250
$Comp
L potenciostato-rescue:GND-power #PWR?
U 1 1 6325E51B
P 1300 7250
AR Path="/60147E53/6325E51B" Ref="#PWR?"  Part="1" 
AR Path="/6013BA2D/6325E51B" Ref="#PWR015"  Part="1" 
F 0 "#PWR015" H 1300 7000 50  0001 C CNN
F 1 "GND" H 1305 7073 50  0000 C CNN
F 2 "" H 1300 7250 50  0001 C CNN
F 3 "" H 1300 7250 50  0001 C CNN
	1    1300 7250
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1300 6050 1300 6150
Wire Wire Line
	1450 6650 1900 6650
Text Notes 8500 4700 0    50   ~ 0
Amplificador Tension Inversor de ganancia unitaria (-1)\nla se??al de dac y agrega -VOffset para que la salida\ntenga valor medio nulo\n(AMP T1)
Text Notes 8500 1150 0    50   ~ 0
Amplificador Inversor con ganancia unitaria y offset,\nadapta la se??al a 0-3.3V\n(AMP I2)
Text Notes 2250 6100 0    50   ~ 0
Buffer, tension de offset + y - para los \namplificadores que adaptan se??al
Text HLabel 1800 3250 0    50   Output ~ 0
gan_x1
Text HLabel 1800 3350 0    50   Output ~ 0
gan_x5
Text HLabel 1800 3550 0    50   Output ~ 0
gan_x10
Text HLabel 1800 3450 0    50   Output ~ 0
gan_x0.1
Text Label 1300 6050 2    50   ~ 0
3V3
Text Label 1800 1350 2    50   ~ 0
3V3
Wire Wire Line
	4450 6750 4700 6750
Wire Wire Line
	3850 6850 3650 6850
Wire Wire Line
	4700 6750 4950 6750
Connection ~ 4700 6750
Text Label 5200 6500 0    50   ~ 0
-VOffset
Wire Wire Line
	3200 6750 3200 6650
$Comp
L salida_dac-rescue:R-Device R?
U 1 1 635F7680
P 4250 6200
AR Path="/635F7680" Ref="R?"  Part="1" 
AR Path="/5F899696/635F7680" Ref="R?"  Part="1" 
AR Path="/6013BA2D/635F7680" Ref="R20"  Part="1" 
F 0 "R20" V 4043 6200 50  0000 C CNN
F 1 "10K" V 4134 6200 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 4180 6200 50  0001 C CNN
F 3 "~" H 4250 6200 50  0001 C CNN
	1    4250 6200
	0    1    1    0   
$EndComp
$Comp
L salida_dac-rescue:R-Device R?
U 1 1 635FE6C2
P 3550 6650
AR Path="/635FE6C2" Ref="R?"  Part="1" 
AR Path="/5F899696/635FE6C2" Ref="R?"  Part="1" 
AR Path="/6013BA2D/635FE6C2" Ref="R16"  Part="1" 
F 0 "R16" V 3343 6650 50  0000 C CNN
F 1 "10K" V 3434 6650 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 3480 6650 50  0001 C CNN
F 3 "~" H 3550 6650 50  0001 C CNN
	1    3550 6650
	0    1    1    0   
$EndComp
Wire Wire Line
	2750 6750 3200 6750
$Comp
L Amplifier_Operational:TL082 U9
U 1 1 63602CFE
P 2200 6750
F 0 "U9" H 2300 7100 50  0000 C CNN
F 1 "TL082" H 2300 7000 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm_LongPads" H 2200 6750 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl081.pdf" H 2200 6750 50  0001 C CNN
	1    2200 6750
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:TL082 U9
U 2 1 63604C97
P 4150 6750
F 0 "U9" H 4150 7117 50  0000 C CNN
F 1 "TL082" H 4150 7026 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm_LongPads" H 4150 6750 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl081.pdf" H 4150 6750 50  0001 C CNN
	2    4150 6750
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:TL082 U9
U 3 1 63615A45
P 2200 6750
F 0 "U9" H 2158 6796 50  0000 L CNN
F 1 "TL082" H 2158 6705 50  0000 L CNN
F 2 "Package_DIP:DIP-8_W7.62mm_LongPads" H 2200 6750 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl081.pdf" H 2200 6750 50  0001 C CNN
	3    2200 6750
	1    0    0    -1  
$EndComp
Wire Wire Line
	10100 6000 10000 6000
Wire Wire Line
	10000 6000 10000 6200
Wire Wire Line
	10000 6200 10100 6200
Wire Wire Line
	3850 6650 3800 6650
Wire Wire Line
	4100 6200 3800 6200
Wire Wire Line
	3800 6200 3800 6650
Connection ~ 3800 6650
Wire Wire Line
	3800 6650 3700 6650
Wire Wire Line
	4400 6200 4700 6200
$Comp
L power:-5V #PWR0109
U 1 1 6365A963
P 2100 7050
F 0 "#PWR0109" H 2100 7150 50  0001 C CNN
F 1 "-5V" H 2115 7223 50  0000 C CNN
F 2 "" H 2100 7050 50  0001 C CNN
F 3 "" H 2100 7050 50  0001 C CNN
	1    2100 7050
	-1   0    0    1   
$EndComp
Wire Wire Line
	2750 6750 2750 7300
Wire Wire Line
	1700 6850 1700 7300
$Comp
L power:+5V #PWR0110
U 1 1 63667AD1
P 2100 6450
F 0 "#PWR0110" H 2100 6300 50  0001 C CNN
F 1 "+5V" H 2115 6623 50  0000 C CNN
F 2 "" H 2100 6450 50  0001 C CNN
F 3 "" H 2100 6450 50  0001 C CNN
	1    2100 6450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4700 6200 4700 6750
Wire Wire Line
	3200 6650 3400 6650
Wire Wire Line
	2750 6450 2750 6750
Wire Wire Line
	4950 6750 4950 6500
Wire Wire Line
	4950 6500 5200 6500
Wire Wire Line
	7450 5100 7450 5300
Wire Wire Line
	7450 5300 7250 5300
$Comp
L power:GND #PWR0111
U 1 1 63699AB5
P 7650 5300
F 0 "#PWR0111" H 7650 5050 50  0001 C CNN
F 1 "GND" H 7655 5127 50  0000 C CNN
F 2 "" H 7650 5300 50  0001 C CNN
F 3 "" H 7650 5300 50  0001 C CNN
	1    7650 5300
	1    0    0    -1  
$EndComp
Text Notes 8450 5750 0    50   ~ 0
Salida DAC uC de 0 a 3.3V\nSalida m??dulo amplificador:\n0V = -1.5V\n1.5V = 0V\n3.3V = +1.5V
Wire Wire Line
	8450 3100 8450 3300
Wire Wire Line
	8150 3300 8250 3300
Wire Wire Line
	8250 3300 8250 3650
Wire Wire Line
	7400 3650 7400 3200
Connection ~ 7400 3200
Wire Wire Line
	7400 3200 7550 3200
Wire Wire Line
	7650 3650 7400 3650
$Comp
L salida_dac-rescue:R-Device R?
U 1 1 636D2235
P 8250 3850
AR Path="/636D2235" Ref="R?"  Part="1" 
AR Path="/5F899696/636D2235" Ref="R?"  Part="1" 
AR Path="/6013BA2D/636D2235" Ref="R23"  Part="1" 
F 0 "R23" V 8043 3850 50  0000 C CNN
F 1 "10K" V 8134 3850 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 8180 3850 50  0001 C CNN
F 3 "~" H 8250 3850 50  0001 C CNN
	1    8250 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	8250 3650 8250 3700
Connection ~ 8250 3650
Wire Wire Line
	7950 3650 8250 3650
$Comp
L power:GND #PWR0112
U 1 1 636DBEAE
P 8250 4050
F 0 "#PWR0112" H 8250 3800 50  0001 C CNN
F 1 "GND" H 8255 3877 50  0000 C CNN
F 2 "" H 8250 4050 50  0001 C CNN
F 3 "" H 8250 4050 50  0001 C CNN
	1    8250 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	8250 4000 8250 4050
Connection ~ 8450 3100
Wire Wire Line
	8450 3300 8650 3300
Wire Wire Line
	8150 3100 8450 3100
Connection ~ 6200 3550
Wire Wire Line
	6200 3550 6200 5100
Connection ~ 7400 1600
Wire Wire Line
	7400 1600 7550 1600
Wire Wire Line
	8250 1700 8150 1700
Wire Wire Line
	8150 1500 8450 1500
Wire Wire Line
	8650 1700 8450 1700
Wire Wire Line
	8450 1700 8450 1500
Connection ~ 8450 1500
Wire Wire Line
	8450 1500 8650 1500
$Comp
L salida_dac-rescue:R-Device R?
U 1 1 63757CA9
P 8250 2350
AR Path="/63757CA9" Ref="R?"  Part="1" 
AR Path="/5F899696/63757CA9" Ref="R?"  Part="1" 
AR Path="/6013BA2D/63757CA9" Ref="R22"  Part="1" 
F 0 "R22" V 8043 2350 50  0000 C CNN
F 1 "10K" V 8134 2350 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 8180 2350 50  0001 C CNN
F 3 "~" H 8250 2350 50  0001 C CNN
	1    8250 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	8250 2150 8250 2200
$Comp
L power:GND #PWR0113
U 1 1 63757CB2
P 8250 2550
F 0 "#PWR0113" H 8250 2300 50  0001 C CNN
F 1 "GND" H 8255 2377 50  0000 C CNN
F 2 "" H 8250 2550 50  0001 C CNN
F 3 "" H 8250 2550 50  0001 C CNN
	1    8250 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	8250 2500 8250 2550
Wire Wire Line
	8250 1700 8250 2150
Connection ~ 8250 2150
Wire Wire Line
	7950 2150 8250 2150
Wire Wire Line
	6300 3200 7400 3200
Wire Wire Line
	4500 2850 6300 2850
Connection ~ 6400 2450
Wire Wire Line
	6400 2450 6400 2750
Wire Wire Line
	6400 1600 6400 2450
$Comp
L potenciostato-rescue:Conn_01x01_Female-Connector J?
U 1 1 6318DCE3
P 6600 2450
AR Path="/60147E53/6318DCE3" Ref="J?"  Part="1" 
AR Path="/6013BA2D/6318DCE3" Ref="I1"  Part="1" 
F 0 "I1" H 6550 2250 50  0000 R CNN
F 1 "test_I" H 6650 2350 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 6600 2450 50  0001 C CNN
F 3 "~" H 6600 2450 50  0001 C CNN
	1    6600 2450
	1    0    0    1   
$EndComp
Wire Wire Line
	6200 5100 6950 5100
Wire Wire Line
	6400 1600 7400 1600
Wire Wire Line
	4500 2750 6400 2750
Wire Wire Line
	4500 3050 6200 3050
$Comp
L potenciostato-rescue:GND-power #PWR?
U 1 1 635F5223
P 3650 7250
AR Path="/60147E53/635F5223" Ref="#PWR?"  Part="1" 
AR Path="/6013BA2D/635F5223" Ref="#PWR0114"  Part="1" 
F 0 "#PWR0114" H 3650 7000 50  0001 C CNN
F 1 "GND" H 3655 7073 50  0000 C CNN
F 2 "" H 3650 7250 50  0001 C CNN
F 3 "" H 3650 7250 50  0001 C CNN
	1    3650 7250
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3650 6850 3650 7250
Wire Wire Line
	1200 1850 1200 1700
Connection ~ 1100 1700
Wire Wire Line
	1100 1850 1100 1700
Wire Wire Line
	1100 1700 1200 1700
$Comp
L power:GNDD #PWR0115
U 1 1 636CF2B0
P 1600 3950
F 0 "#PWR0115" H 1600 3700 50  0001 C CNN
F 1 "GNDD" H 1604 3795 50  0000 C CNN
F 2 "" H 1600 3950 50  0001 C CNN
F 3 "" H 1600 3950 50  0001 C CNN
	1    1600 3950
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR0116
U 1 1 636CF7F1
P 750 1700
F 0 "#PWR0116" H 750 1450 50  0001 C CNN
F 1 "GNDD" H 754 1545 50  0000 C CNN
F 2 "" H 750 1700 50  0001 C CNN
F 3 "" H 750 1700 50  0001 C CNN
	1    750  1700
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR0118
U 1 1 636CFCCA
P 5250 1000
F 0 "#PWR0118" H 5250 750 50  0001 C CNN
F 1 "GNDD" H 5254 845 50  0000 C CNN
F 2 "" H 5250 1000 50  0001 C CNN
F 3 "" H 5250 1000 50  0001 C CNN
	1    5250 1000
	1    0    0    -1  
$EndComp
Connection ~ 1200 1700
Wire Wire Line
	1200 1700 1300 1700
Wire Wire Line
	750  1700 1100 1700
$EndSCHEMATC
