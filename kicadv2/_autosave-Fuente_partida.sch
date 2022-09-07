EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 3
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
L Regulator_Linear:L7805 U?
U 1 1 63213BD6
P 6050 1950
F 0 "U?" H 6050 2192 50  0000 C CNN
F 1 "L7805" H 6050 2101 50  0000 C CNN
F 2 "" H 6075 1800 50  0001 L CIN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/41/4f/b3/b0/12/d4/47/88/CD00000444.pdf/files/CD00000444.pdf/jcr:content/translations/en.CD00000444.pdf" H 6050 1900 50  0001 C CNN
	1    6050 1950
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:L7905 U?
U 1 1 63214B98
P 6050 3000
F 0 "U?" H 6050 2851 50  0000 C CNN
F 1 "L7905" H 6050 2760 50  0000 C CNN
F 2 "" H 6050 2800 50  0001 C CIN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/c9/16/86/41/c7/2b/45/f2/CD00000450.pdf/files/CD00000450.pdf/jcr:content/translations/en.CD00000450.pdf" H 6050 3000 50  0001 C CNN
	1    6050 3000
	1    0    0    -1  
$EndComp
$Comp
L potenciostato-rescue:CP-Device C?
U 1 1 632154F2
P 5100 2800
F 0 "C?" H 5218 2846 50  0000 L CNN
F 1 "10uF" H 5218 2755 50  0000 L CNN
F 2 "" H 5138 2650 50  0001 C CNN
F 3 "~" H 5100 2800 50  0001 C CNN
	1    5100 2800
	1    0    0    -1  
$EndComp
$Comp
L potenciostato-rescue:CP-Device C?
U 1 1 63215B31
P 5100 2150
F 0 "C?" H 5218 2196 50  0000 L CNN
F 1 "10uF" H 5218 2105 50  0000 L CNN
F 2 "" H 5138 2000 50  0001 C CNN
F 3 "~" H 5100 2150 50  0001 C CNN
	1    5100 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 2700 6050 2450
Wire Wire Line
	6050 2450 5550 2450
Connection ~ 6050 2450
Wire Wire Line
	6050 2450 6050 2250
Wire Wire Line
	5750 3000 5550 3000
Wire Wire Line
	5750 1950 5550 1950
Wire Wire Line
	5100 2650 5100 2450
Connection ~ 5100 2450
Wire Wire Line
	5100 2300 5100 2450
Wire Wire Line
	5100 2000 5100 1950
Connection ~ 5100 1950
Wire Wire Line
	5100 2950 5100 3000
Connection ~ 5100 3000
Wire Wire Line
	5100 3000 4650 3000
$Comp
L Transformer:ADT2-71T TR?
U 1 1 632186DD
P 3550 2450
F 0 "TR?" H 3550 2831 50  0000 C CNN
F 1 "ADT2-71T" H 3550 2740 50  0000 C CNN
F 2 "RF_Mini-Circuits:Mini-Circuits_CD637_H5.23mm" H 3550 2100 50  0001 C CNN
F 3 "https://www.minicircuits.com/pdfs/ADT2-71T+.pdf" H 3550 2450 50  0001 C CNN
	1    3550 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 1950 6700 1950
Wire Wire Line
	6350 3000 6700 3000
Wire Wire Line
	6050 2450 6700 2450
$Comp
L potenciostato-rescue:CP-Device C?
U 1 1 63219BC7
P 6700 2800
F 0 "C?" H 6818 2846 50  0000 L CNN
F 1 "10uF" H 6818 2755 50  0000 L CNN
F 2 "" H 6738 2650 50  0001 C CNN
F 3 "~" H 6700 2800 50  0001 C CNN
	1    6700 2800
	1    0    0    -1  
$EndComp
$Comp
L potenciostato-rescue:CP-Device C?
U 1 1 63219C91
P 6700 2150
F 0 "C?" H 6818 2196 50  0000 L CNN
F 1 "10uF" H 6818 2105 50  0000 L CNN
F 2 "" H 6738 2000 50  0001 C CNN
F 3 "~" H 6700 2150 50  0001 C CNN
	1    6700 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 2300 6700 2450
Connection ~ 6700 2450
Wire Wire Line
	6700 2450 7200 2450
Wire Wire Line
	6700 2650 6700 2450
Wire Wire Line
	6700 2950 6700 3000
Connection ~ 6700 3000
Wire Wire Line
	6700 3000 7250 3000
Wire Wire Line
	6700 2000 6700 1950
Connection ~ 6700 1950
Wire Wire Line
	6700 1950 7200 1950
$Comp
L Device:C C?
U 1 1 6321C4C8
P 5550 2150
F 0 "C?" H 5665 2196 50  0000 L CNN
F 1 "C" H 5665 2105 50  0000 L CNN
F 2 "" H 5588 2000 50  0001 C CNN
F 3 "~" H 5550 2150 50  0001 C CNN
	1    5550 2150
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 6321CAAD
P 5550 2800
F 0 "C?" H 5665 2846 50  0000 L CNN
F 1 "C" H 5665 2755 50  0000 L CNN
F 2 "" H 5588 2650 50  0001 C CNN
F 3 "~" H 5550 2800 50  0001 C CNN
	1    5550 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5550 2650 5550 2450
Connection ~ 5550 2450
Wire Wire Line
	5550 2450 5100 2450
Wire Wire Line
	5550 2450 5550 2300
Wire Wire Line
	5550 2000 5550 1950
Connection ~ 5550 1950
Wire Wire Line
	5550 1950 5100 1950
Wire Wire Line
	5550 2950 5550 3000
Connection ~ 5550 3000
Wire Wire Line
	5550 3000 5100 3000
Wire Wire Line
	5100 2450 4700 2450
Wire Wire Line
	5100 1950 4700 1950
$EndSCHEMATC
