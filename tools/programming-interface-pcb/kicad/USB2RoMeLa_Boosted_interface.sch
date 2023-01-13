EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr USLetter 11000 8500
encoding utf-8
Sheet 1 1
Title "USB2RoMeLa_Boosted_interface"
Date "2017-09-25"
Rev "1"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Label 3900 2300 0    60   ~ 0
SWCLK
Text Label 3900 2100 0    60   ~ 0
SWDIO
Text Label 3900 2000 0    60   ~ 0
NRST
Text Label 3900 1900 0    60   ~ 0
SWO
$Comp
L USB2RoMeLa_Boosted_interface-rescue:CONN_01X10 P3
U 1 1 59B6CED0
P 3700 1950
F 0 "P3" H 3700 2500 50  0000 C CNN
F 1 "CONN_01X10" V 3800 1950 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x10_Pitch2.54mm" H 3700 1950 50  0001 C CNN
F 3 "" H 3700 1950 50  0001 C CNN
	1    3700 1950
	-1   0    0    1   
$EndComp
$Comp
L USB2RoMeLa_Boosted_interface-rescue:CONN_01X10 P4
U 1 1 59B6DB07
P 1950 2000
F 0 "P4" H 1950 2550 50  0000 C CNN
F 1 "CONN_01X10" V 2050 2000 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x10_Pitch2.54mm" H 1950 2000 50  0001 C CNN
F 3 "" H 1950 2000 50  0001 C CNN
	1    1950 2000
	-1   0    0    1   
$EndComp
Text Label 2150 2450 0    60   ~ 0
PA7
Text Label 2150 2350 0    60   ~ 0
PA6
Text Label 2150 2250 0    60   ~ 0
PA5
Text Label 2150 2150 0    60   ~ 0
PA4
Text Label 2150 1950 0    60   ~ 0
USART1_RX
Text Label 2150 2050 0    60   ~ 0
USART1_TX
Text Label 2150 1850 0    60   ~ 0
USART2_DE
Text Label 2150 1750 0    60   ~ 0
PB7
Text Label 2150 1650 0    60   ~ 0
PB6
Text Label 2150 1550 0    60   ~ 0
LED_R
$Comp
L USB2RoMeLa_Boosted_interface-rescue:CONN_01X10 P2
U 1 1 59C96AD3
P 3350 1950
F 0 "P2" H 3350 2500 50  0000 C CNN
F 1 "CONN_Right" V 3450 1950 50  0000 C CNN
F 2 "footprint_RoMeLa:Spring_Contact_10P" H 3350 1950 50  0001 C CNN
F 3 "" H 3350 1950 50  0001 C CNN
	1    3350 1950
	-1   0    0    1   
$EndComp
Text Label 3900 1500 0    60   ~ 0
LED_G
Text Label 3900 1600 0    60   ~ 0
+5V
Text Label 3900 1700 0    60   ~ 0
GND8
Text Label 3900 1800 0    60   ~ 0
GND7
Text Label 3900 2200 0    60   ~ 0
GND3
Text Label 3900 2400 0    60   ~ 0
VDD
Wire Wire Line
	3550 1500 3900 1500
Wire Wire Line
	3550 1600 3900 1600
Wire Wire Line
	3550 1700 3900 1700
Wire Wire Line
	3900 1800 3550 1800
Wire Wire Line
	3550 1900 3900 1900
Wire Wire Line
	3550 2000 3900 2000
Wire Wire Line
	3550 2100 3900 2100
Wire Wire Line
	3550 2200 3900 2200
Wire Wire Line
	3550 2300 3900 2300
Wire Wire Line
	3550 2400 3900 2400
$Comp
L USB2RoMeLa_Boosted_interface-rescue:CONN_01X10 P1
U 1 1 59C96CC8
P 2850 2000
F 0 "P1" H 2850 2550 50  0000 C CNN
F 1 "CONN_Left" V 2950 2000 50  0000 C CNN
F 2 "footprint_RoMeLa:Spring_Contact_10P" H 2850 2000 50  0001 C CNN
F 3 "" H 2850 2000 50  0001 C CNN
	1    2850 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	2150 1550 2650 1550
Wire Wire Line
	2650 1650 2150 1650
Wire Wire Line
	2150 1750 2650 1750
Wire Wire Line
	2650 1850 2150 1850
Wire Wire Line
	2150 1950 2650 1950
Wire Wire Line
	2650 2050 2150 2050
Wire Wire Line
	2150 2150 2650 2150
Wire Wire Line
	2650 2250 2150 2250
Wire Wire Line
	2150 2350 2650 2350
Wire Wire Line
	2650 2450 2150 2450
$Comp
L USB2RoMeLa_Boosted_interface-rescue:Conn_01x02 J1
U 1 1 59C96F44
P 4600 1600
F 0 "J1" H 4600 1700 50  0000 C CNN
F 1 "Conn_01x02" H 4600 1850 50  0000 C CNN
F 2 "Connectors_Molex:Molex_MiniFit-JR-5556-02A_2x01x4.20mm_Straight" H 4600 1600 50  0001 C CNN
F 3 "" H 4600 1600 50  0001 C CNN
	1    4600 1600
	1    0    0    -1  
$EndComp
Connection ~ 3900 1700
Connection ~ 3900 1600
$Comp
L USB2RoMeLa_Boosted_interface-rescue:Conn_01x06 J2
U 1 1 59C96FCD
P 4350 2200
F 0 "J2" H 4350 2500 50  0000 C CNN
F 1 "Conn_01x06" H 4050 2650 50  0000 C CNN
F 2 "Connectors_JST:JST_SH_SM06B-SRSS-TB_06x1.00mm_Angled" H 4350 2200 50  0001 C CNN
F 3 "" H 4350 2200 50  0001 C CNN
	1    4350 2200
	-1   0    0    1   
$EndComp
Connection ~ 3900 2400
Connection ~ 3900 2300
Connection ~ 3900 2200
Connection ~ 3900 2100
Connection ~ 3900 2000
Connection ~ 3900 1900
Wire Wire Line
	3900 1700 4400 1700
Wire Wire Line
	3900 1600 4400 1600
Wire Wire Line
	3900 2400 4550 2400
Wire Wire Line
	3900 2300 4550 2300
Wire Wire Line
	3900 2200 4550 2200
Wire Wire Line
	3900 2100 4550 2100
Wire Wire Line
	3900 2000 4550 2000
Wire Wire Line
	3900 1900 4550 1900
$EndSCHEMATC
