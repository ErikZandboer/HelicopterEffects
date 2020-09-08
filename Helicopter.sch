EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Helicopter schematic diagram"
Date "2020-09-08"
Rev "1.0"
Comp "XHD"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Device:LED D8
U 1 1 5F453DBF
P 5550 3950
F 0 "D8" V 5589 3832 50  0000 R CNN
F 1 "GREEN" V 5498 3832 50  0000 R CNN
F 2 "" H 5550 3950 50  0001 C CNN
F 3 "~" H 5550 3950 50  0001 C CNN
	1    5550 3950
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R7
U 1 1 5F456EB1
P 5550 3350
F 0 "R7" H 5620 3396 50  0000 L CNN
F 1 "560" H 5620 3305 50  0000 L CNN
F 2 "" V 5480 3350 50  0001 C CNN
F 3 "~" H 5550 3350 50  0001 C CNN
	1    5550 3350
	1    0    0    -1  
$EndComp
$Comp
L Transistor_BJT:BC547 Q2
U 1 1 5F45F9C7
P 5450 4800
F 0 "Q2" H 5640 4846 50  0000 L CNN
F 1 "2N2222" H 5640 4755 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 5650 4725 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BC/BC547.pdf" H 5450 4800 50  0001 L CNN
	1    5450 4800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R6
U 1 1 5F4627DC
P 5000 4800
F 0 "R6" V 4793 4800 50  0000 C CNN
F 1 "10K" V 4884 4800 50  0000 C CNN
F 2 "" V 4930 4800 50  0001 C CNN
F 3 "~" H 5000 4800 50  0001 C CNN
	1    5000 4800
	0    1    1    0   
$EndComp
Wire Wire Line
	5150 4800 5250 4800
$Comp
L Device:LED D7
U 1 1 5F466EB5
P 5550 3650
F 0 "D7" V 5589 3532 50  0000 R CNN
F 1 "RED" V 5498 3532 50  0000 R CNN
F 2 "" H 5550 3650 50  0001 C CNN
F 3 "~" H 5550 3650 50  0001 C CNN
	1    5550 3650
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R10
U 1 1 5F4FD6A0
P 7350 2950
F 0 "R10" V 7143 2950 50  0000 C CNN
F 1 "10K" V 7234 2950 50  0000 C CNN
F 2 "" V 7280 2950 50  0001 C CNN
F 3 "~" H 7350 2950 50  0001 C CNN
	1    7350 2950
	0    1    1    0   
$EndComp
$Comp
L Transistor_BJT:BC547 Q4
U 1 1 5F4FDBDE
P 7850 2950
F 0 "Q4" H 8040 2996 50  0000 L CNN
F 1 "2N2222" H 8040 2905 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 8050 2875 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BC/BC547.pdf" H 7850 2950 50  0001 L CNN
	1    7850 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	7500 2950 7650 2950
$Comp
L Motor:Motor_DC M1
U 1 1 5F503615
P 7950 2200
F 0 "M1" H 8108 2196 50  0000 L CNN
F 1 "Motor_DC" H 8108 2105 50  0000 L CNN
F 2 "" H 7950 2110 50  0001 C CNN
F 3 "~" H 7950 2110 50  0001 C CNN
	1    7950 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	7950 2500 7950 2550
Wire Wire Line
	7950 1750 7950 1950
$Comp
L Diode:1N4004 D11
U 1 1 5F505AF8
P 7550 2250
F 0 "D11" V 7550 1950 50  0000 L CNN
F 1 "1N4004" V 7650 1900 50  0000 L CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 7550 2075 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 7550 2250 50  0001 C CNN
	1    7550 2250
	0    1    1    0   
$EndComp
Wire Wire Line
	7550 2100 7550 1950
Wire Wire Line
	7550 1950 7950 1950
Connection ~ 7950 1950
Wire Wire Line
	7950 1950 7950 2000
Wire Wire Line
	7550 2400 7550 2550
Wire Wire Line
	7550 2550 7950 2550
Connection ~ 7950 2550
Wire Wire Line
	7950 2550 7950 2750
$Comp
L MCU_Module:Arduino_UNO_R3 A1
U 1 1 5F520893
P 2350 3050
F 0 "A1" H 1900 4100 50  0000 C CNN
F 1 "Arduino_UNO_R3" H 1650 4000 50  0000 C CNN
F 2 "Module:Arduino_UNO_R3" H 2350 3050 50  0001 C CIN
F 3 "https://www.arduino.cc/en/Main/arduinoBoardUno" H 2350 3050 50  0001 C CNN
	1    2350 3050
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R11
U 1 1 5F52546A
P 8750 2950
F 0 "R11" V 8543 2950 50  0000 C CNN
F 1 "10K" V 8634 2950 50  0000 C CNN
F 2 "" V 8680 2950 50  0001 C CNN
F 3 "~" H 8750 2950 50  0001 C CNN
	1    8750 2950
	0    1    1    0   
$EndComp
$Comp
L Transistor_BJT:BC547 Q5
U 1 1 5F525474
P 9250 2950
F 0 "Q5" H 9440 2996 50  0000 L CNN
F 1 "2N2222" H 9440 2905 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 9450 2875 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BC/BC547.pdf" H 9250 2950 50  0001 L CNN
	1    9250 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	8900 2950 9050 2950
$Comp
L Motor:Motor_DC M2
U 1 1 5F52548B
P 9350 2200
F 0 "M2" H 9508 2196 50  0000 L CNN
F 1 "Motor_DC" H 9508 2105 50  0000 L CNN
F 2 "" H 9350 2110 50  0001 C CNN
F 3 "~" H 9350 2110 50  0001 C CNN
	1    9350 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	9350 2500 9350 2550
Wire Wire Line
	9350 1750 9350 1950
$Comp
L Diode:1N4004 D12
U 1 1 5F525497
P 8950 2250
F 0 "D12" V 8950 1950 50  0000 L CNN
F 1 "1N4004" V 9050 1900 50  0000 L CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 8950 2075 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 8950 2250 50  0001 C CNN
	1    8950 2250
	0    1    1    0   
$EndComp
Wire Wire Line
	8950 2100 8950 1950
Wire Wire Line
	8950 1950 9350 1950
Connection ~ 9350 1950
Wire Wire Line
	9350 1950 9350 2000
Wire Wire Line
	8950 2400 8950 2550
Wire Wire Line
	8950 2550 9350 2550
Connection ~ 9350 2550
Wire Wire Line
	9350 2550 9350 2750
Wire Wire Line
	8600 2950 8600 3200
Wire Wire Line
	7200 2950 2850 2950
Wire Wire Line
	2850 3050 7300 3050
Wire Wire Line
	7950 1750 9350 1750
$Comp
L Transistor_BJT:BC547 Q3
U 1 1 5F5513D4
P 6350 5250
F 0 "Q3" H 6540 5296 50  0000 L CNN
F 1 "2N2222" H 6540 5205 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 6550 5175 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BC/BC547.pdf" H 6350 5250 50  0001 L CNN
	1    6350 5250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R8
U 1 1 5F5513DE
P 5900 5250
F 0 "R8" V 5693 5250 50  0000 C CNN
F 1 "10K" V 5784 5250 50  0000 C CNN
F 2 "" V 5830 5250 50  0001 C CNN
F 3 "~" H 5900 5250 50  0001 C CNN
	1    5900 5250
	0    1    1    0   
$EndComp
Wire Wire Line
	6050 5250 6150 5250
$Comp
L Device:LED D10
U 1 1 5F555FE7
P 6450 3950
F 0 "D10" V 6489 3832 50  0000 R CNN
F 1 "GREEN" V 6398 3832 50  0000 R CNN
F 2 "" H 6450 3950 50  0001 C CNN
F 3 "~" H 6450 3950 50  0001 C CNN
	1    6450 3950
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R9
U 1 1 5F555FF1
P 6450 3350
F 0 "R9" H 6520 3396 50  0000 L CNN
F 1 "560" H 6520 3305 50  0000 L CNN
F 2 "" V 6380 3350 50  0001 C CNN
F 3 "~" H 6450 3350 50  0001 C CNN
	1    6450 3350
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D9
U 1 1 5F555FFB
P 6450 3650
F 0 "D9" V 6489 3532 50  0000 R CNN
F 1 "RED" V 6398 3532 50  0000 R CNN
F 2 "" H 6450 3650 50  0001 C CNN
F 3 "~" H 6450 3650 50  0001 C CNN
	1    6450 3650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6450 4100 6450 5050
Wire Wire Line
	5750 5250 3400 5250
Wire Wire Line
	3400 5250 3400 3750
Wire Wire Line
	3400 3750 2850 3750
$Comp
L Device:Battery_Cell BT1
U 1 1 5F55E4CD
P 1200 3600
F 0 "BT1" H 950 3700 50  0000 L CNN
F 1 "3.6V 18650 cell" H 500 3600 50  0000 L CNN
F 2 "" V 1200 3660 50  0001 C CNN
F 3 "~" V 1200 3660 50  0001 C CNN
	1    1200 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6450 3200 5550 3200
Wire Wire Line
	3500 4800 4850 4800
$Comp
L Transistor_BJT:BC547 Q1
U 1 1 5F59612F
P 4400 4350
F 0 "Q1" H 4590 4396 50  0000 L CNN
F 1 "2N2222" H 4590 4305 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 4600 4275 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BC/BC547.pdf" H 4400 4350 50  0001 L CNN
	1    4400 4350
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 5F596139
P 4000 4350
F 0 "R4" V 3793 4350 50  0000 C CNN
F 1 "10K" V 3884 4350 50  0000 C CNN
F 2 "" V 3930 4350 50  0001 C CNN
F 3 "~" H 4000 4350 50  0001 C CNN
	1    4000 4350
	0    1    1    0   
$EndComp
Wire Wire Line
	4150 4350 4200 4350
Text Label 2950 3750 0    50   ~ 0
SOLIDLED
Text Label 2950 3450 0    50   ~ 0
BLINK1
Text Label 2950 3350 0    50   ~ 0
BLINK2
$Comp
L Device:LED D6
U 1 1 5F5A0F78
P 4500 3950
F 0 "D6" V 4539 3832 50  0000 R CNN
F 1 "WHITE" V 4448 3832 50  0000 R CNN
F 2 "" H 4500 3950 50  0001 C CNN
F 3 "~" H 4500 3950 50  0001 C CNN
	1    4500 3950
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R5
U 1 1 5F5A0F7E
P 4500 3350
F 0 "R5" H 4570 3396 50  0000 L CNN
F 1 "390" H 4570 3305 50  0000 L CNN
F 2 "" V 4430 3350 50  0001 C CNN
F 3 "~" H 4500 3350 50  0001 C CNN
	1    4500 3350
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D5
U 1 1 5F5A0F84
P 4500 3650
F 0 "D5" V 4539 3532 50  0000 R CNN
F 1 "RED" V 4448 3532 50  0000 R CNN
F 2 "" H 4500 3650 50  0001 C CNN
F 3 "~" H 4500 3650 50  0001 C CNN
	1    4500 3650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4500 4100 4500 4150
Wire Wire Line
	5550 4100 5550 4600
Wire Wire Line
	4500 3200 5550 3200
Connection ~ 5550 3200
Text Label 2950 2950 0    50   ~ 0
MAINROTOR
Text Label 2950 3050 0    50   ~ 0
REARROTOR
$Comp
L Device:Battery_Cell BT2
U 1 1 5F577CA2
P 1200 4000
F 0 "BT2" H 950 4050 50  0000 L CNN
F 1 "3.6V 18650 cell" H 500 3950 50  0000 L CNN
F 2 "" V 1200 4060 50  0001 C CNN
F 3 "~" V 1200 4060 50  0001 C CNN
	1    1200 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	1200 3700 1200 3800
Wire Wire Line
	1200 4100 1200 5700
$Comp
L Device:Battery_Cell BT3
U 1 1 5F587003
P 10250 3400
F 0 "BT3" H 10368 3496 50  0000 L CNN
F 1 "3.6V 18650 cell" H 10368 3405 50  0000 L CNN
F 2 "" V 10250 3460 50  0001 C CNN
F 3 "~" V 10250 3460 50  0001 C CNN
	1    10250 3400
	1    0    0    -1  
$EndComp
$Comp
L Device:Battery_Cell BT4
U 1 1 5F587018
P 10250 3800
F 0 "BT4" H 10368 3896 50  0000 L CNN
F 1 "3.6V 18650 cell" H 10368 3805 50  0000 L CNN
F 2 "" V 10250 3860 50  0001 C CNN
F 3 "~" V 10250 3860 50  0001 C CNN
	1    10250 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	10250 3500 10250 3600
Wire Wire Line
	9350 1750 10250 1750
Wire Wire Line
	10250 1750 10250 3200
Connection ~ 9350 1750
Wire Wire Line
	10250 5700 9350 5700
Wire Wire Line
	2450 4150 2450 5700
Wire Wire Line
	10250 3900 10250 5700
Wire Wire Line
	4500 4550 4500 5700
Connection ~ 4500 5700
Wire Wire Line
	5550 5000 5550 5700
Connection ~ 5550 5700
Wire Wire Line
	5550 5700 4500 5700
Wire Wire Line
	6450 5450 6450 5700
Connection ~ 6450 5700
Wire Wire Line
	6450 5700 5550 5700
Wire Wire Line
	7950 3150 7950 5700
Connection ~ 7950 5700
Wire Wire Line
	9350 3150 9350 5700
Connection ~ 9350 5700
Wire Wire Line
	9350 5700 7950 5700
Wire Wire Line
	6450 5700 7950 5700
Wire Wire Line
	2450 5700 1200 5700
Connection ~ 2450 5700
Wire Wire Line
	1200 1700 2450 1700
Wire Wire Line
	1200 1700 1200 3400
Wire Wire Line
	2450 2050 2450 1700
Connection ~ 2450 1700
Wire Wire Line
	3600 3350 2850 3350
Wire Wire Line
	3500 4800 3500 3450
Wire Wire Line
	3500 3450 2850 3450
$Comp
L Connector_Generic:Conn_01x04 J1
U 1 1 5F5ABB3F
P 4350 2300
F 0 "J1" H 4430 2292 50  0000 L CNN
F 1 "RedMP3 player" H 4430 2201 50  0000 L CNN
F 2 "" H 4350 2300 50  0001 C CNN
F 3 "~" H 4350 2300 50  0001 C CNN
	1    4350 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 2200 3850 2200
Wire Wire Line
	3850 2200 3850 1850
Wire Wire Line
	3850 1850 2150 1850
Wire Wire Line
	2150 1850 2150 2050
Wire Wire Line
	4500 5700 3750 5700
Wire Wire Line
	3600 3350 3600 4350
Wire Wire Line
	3600 4350 3850 4350
Wire Wire Line
	6450 1700 6450 3200
Wire Wire Line
	2450 1700 6450 1700
Connection ~ 6450 3200
Wire Wire Line
	4150 2500 3750 2500
Wire Wire Line
	3750 2500 3750 5700
Connection ~ 3750 5700
Wire Wire Line
	3750 5700 2450 5700
Wire Wire Line
	4150 2400 3600 2400
Wire Wire Line
	3600 2400 3600 3250
Wire Wire Line
	3600 3250 2850 3250
Wire Wire Line
	4150 2300 3500 2300
Wire Wire Line
	3500 2300 3500 3150
Wire Wire Line
	3500 3150 2850 3150
Text Label 2950 3250 0    50   ~ 0
MP3_RX
Text Label 2950 3150 0    50   ~ 0
MP3_TX
Wire Wire Line
	7300 3200 8600 3200
Wire Wire Line
	7300 3200 7300 3050
$EndSCHEMATC
