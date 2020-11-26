EESchema Schematic File Version 4
LIBS:RatBoy_bluepill_internals1-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Esquemático do Seguidor de Linha RatBoy"
Date ""
Rev ""
Comp "UFLA"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L RatBoy_bluepill_internals1-rescue:Battery-Device BT1
U 1 1 5CFBEA42
P 5825 2925
F 0 "BT1" H 5933 2971 50  0000 L CNN
F 1 "Battery 7.2V li-ion" H 5933 2880 50  0000 L CNN
F 2 "" V 5825 2985 50  0001 C CNN
F 3 "~" V 5825 2985 50  0001 C CNN
	1    5825 2925
	1    0    0    -1  
$EndComp
Text GLabel 8800 1975 2    50   Input ~ 0
SENS5
Connection ~ 8425 1375
Wire Wire Line
	8800 1975 8700 1975
Wire Wire Line
	8700 1375 8425 1375
Wire Wire Line
	8700 1975 8700 1375
Wire Wire Line
	8425 1775 8425 1850
$Comp
L RatBoy_bluepill_internals1-rescue:+3V3-power #PWR019
U 1 1 5D0169FC
P 8425 1850
F 0 "#PWR019" H 8425 1700 50  0001 C CNN
F 1 "+3V3" H 8440 2023 50  0000 C CNN
F 2 "" H 8425 1850 50  0001 C CNN
F 3 "" H 8425 1850 50  0001 C CNN
	1    8425 1850
	-1   0    0    1   
$EndComp
Wire Wire Line
	8425 1375 8425 1475
Wire Wire Line
	8375 1375 8425 1375
$Comp
L RatBoy_bluepill_internals1-rescue:R-Device R9
U 1 1 5D0169F4
P 8425 1625
F 0 "R9" H 8495 1671 50  0000 L CNN
F 1 "10k" H 8495 1580 50  0000 L CNN
F 2 "" V 8355 1625 50  0001 C CNN
F 3 "~" H 8425 1625 50  0001 C CNN
	1    8425 1625
	1    0    0    -1  
$EndComp
Wire Wire Line
	8400 1175 8375 1175
Wire Wire Line
	8400 1075 8400 1175
$Comp
L RatBoy_bluepill_internals1-rescue:+3V3-power #PWR018
U 1 1 5D0169EC
P 8400 1075
F 0 "#PWR018" H 8400 925 50  0001 C CNN
F 1 "+3V3" H 8415 1248 50  0000 C CNN
F 2 "" H 8400 1075 50  0001 C CNN
F 3 "" H 8400 1075 50  0001 C CNN
	1    8400 1075
	1    0    0    -1  
$EndComp
$Comp
L RatBoy_bluepill_internals1-rescue:+3V3-power #PWR015
U 1 1 5D0169E6
P 7075 1825
F 0 "#PWR015" H 7075 1675 50  0001 C CNN
F 1 "+3V3" H 7090 1998 50  0000 C CNN
F 2 "" H 7075 1825 50  0001 C CNN
F 3 "" H 7075 1825 50  0001 C CNN
	1    7075 1825
	-1   0    0    1   
$EndComp
Wire Wire Line
	7075 1775 7075 1825
Wire Wire Line
	7450 1975 7350 1975
Connection ~ 7075 1375
Wire Wire Line
	7350 1375 7075 1375
Wire Wire Line
	7350 1975 7350 1375
Text GLabel 7450 1975 2    50   Input ~ 0
SENS4
Wire Wire Line
	7075 1375 7075 1475
$Comp
L RatBoy_bluepill_internals1-rescue:R-Device R7
U 1 1 5D0169D9
P 7075 1625
F 0 "R7" H 7145 1671 50  0000 L CNN
F 1 "10k" H 7145 1580 50  0000 L CNN
F 2 "" V 7005 1625 50  0001 C CNN
F 3 "~" H 7075 1625 50  0001 C CNN
	1    7075 1625
	1    0    0    -1  
$EndComp
$Comp
L RatBoy_bluepill_internals1-rescue:GND-power #PWR016
U 1 1 5D0169D3
P 7575 1375
F 0 "#PWR016" H 7575 1125 50  0001 C CNN
F 1 "GND" H 7580 1202 50  0000 C CNN
F 2 "" H 7575 1375 50  0001 C CNN
F 3 "" H 7575 1375 50  0001 C CNN
	1    7575 1375
	1    0    0    -1  
$EndComp
Connection ~ 6275 1175
Wire Wire Line
	6275 1375 6275 1175
$Comp
L TCRT5000:TCRT5000 SENS-5
U 1 1 5D0169CB
P 7975 1275
F 0 "SENS-5" V 8550 1275 50  0000 C CNN
F 1 "TCRT5000" V 7511 1275 50  0000 C BNN
F 2 "5000" H 7975 1275 50  0001 L BNN
F 3 "" H 7975 1275 50  0001 L BNN
F 4 "950 nm 60 mA Through Hole Reflective Optical Sensor with Transistor Output" H 7975 1275 50  0001 L BNN "Field4"
F 5 "TCRT5000" H 7975 1275 50  0001 L BNN "Field5"
F 6 "PCB Mount Vishay" H 7975 1275 50  0001 L BNN "Field6"
F 7 "None" H 7975 1275 50  0001 L BNN "Field7"
F 8 "Unavailable" H 7975 1275 50  0001 L BNN "Field8"
	1    7975 1275
	0    1    -1   0   
$EndComp
$Comp
L TCRT5000:TCRT5000 SENS-4
U 1 1 5D0169C0
P 6675 1275
F 0 "SENS-4" V 7250 1275 50  0000 C CNN
F 1 "TCRT5000" V 6211 1275 50  0000 C BNN
F 2 "5000" H 6675 1275 50  0001 L BNN
F 3 "" H 6675 1275 50  0001 L BNN
F 4 "950 nm 60 mA Through Hole Reflective Optical Sensor with Transistor Output" H 6675 1275 50  0001 L BNN "Field4"
F 5 "TCRT5000" H 6675 1275 50  0001 L BNN "Field5"
F 6 "PCB Mount Vishay" H 6675 1275 50  0001 L BNN "Field6"
F 7 "None" H 6675 1275 50  0001 L BNN "Field7"
F 8 "Unavailable" H 6675 1275 50  0001 L BNN "Field8"
	1    6675 1275
	0    1    -1   0   
$EndComp
Wire Wire Line
	6125 1175 6275 1175
$Comp
L RatBoy_bluepill_internals1-rescue:GND-power #PWR013
U 1 1 5D0169B4
P 6125 1175
F 0 "#PWR013" H 6125 925 50  0001 C CNN
F 1 "GND" H 6130 1002 50  0000 C CNN
F 2 "" H 6125 1175 50  0001 C CNN
F 3 "" H 6125 1175 50  0001 C CNN
	1    6125 1175
	1    0    0    -1  
$EndComp
Wire Wire Line
	7475 1175 7575 1175
Wire Wire Line
	7175 1175 7075 1175
$Comp
L RatBoy_bluepill_internals1-rescue:R-Device R8
U 1 1 5D0169AC
P 7325 1175
F 0 "R8" V 7118 1175 50  0000 C CNN
F 1 "100" V 7209 1175 50  0000 C CNN
F 2 "" V 7255 1175 50  0001 C CNN
F 3 "~" H 7325 1175 50  0001 C CNN
	1    7325 1175
	0    1    1    0   
$EndComp
Connection ~ 5775 1375
Wire Wire Line
	6150 1975 6050 1975
Wire Wire Line
	6050 1375 5775 1375
Wire Wire Line
	6050 1975 6050 1375
Text GLabel 6150 1975 2    50   Input ~ 0
SENS3
Wire Wire Line
	5775 1775 5775 1850
$Comp
L RatBoy_bluepill_internals1-rescue:+3V3-power #PWR012
U 1 1 5D001E5B
P 5775 1850
F 0 "#PWR012" H 5775 1700 50  0001 C CNN
F 1 "+3V3" H 5790 2023 50  0000 C CNN
F 2 "" H 5775 1850 50  0001 C CNN
F 3 "" H 5775 1850 50  0001 C CNN
	1    5775 1850
	-1   0    0    1   
$EndComp
Wire Wire Line
	5775 1375 5775 1475
Wire Wire Line
	5725 1375 5775 1375
$Comp
L RatBoy_bluepill_internals1-rescue:R-Device R6
U 1 1 5D001E53
P 5775 1625
F 0 "R6" H 5845 1671 50  0000 L CNN
F 1 "10k" H 5845 1580 50  0000 L CNN
F 2 "" V 5705 1625 50  0001 C CNN
F 3 "~" H 5775 1625 50  0001 C CNN
	1    5775 1625
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 1175 5725 1175
Wire Wire Line
	5750 1075 5750 1175
$Comp
L RatBoy_bluepill_internals1-rescue:+3V3-power #PWR011
U 1 1 5D001E4B
P 5750 1075
F 0 "#PWR011" H 5750 925 50  0001 C CNN
F 1 "+3V3" H 5765 1248 50  0000 C CNN
F 2 "" H 5750 1075 50  0001 C CNN
F 3 "" H 5750 1075 50  0001 C CNN
	1    5750 1075
	1    0    0    -1  
$EndComp
$Comp
L RatBoy_bluepill_internals1-rescue:+3V3-power #PWR08
U 1 1 5D001E45
P 4425 1825
F 0 "#PWR08" H 4425 1675 50  0001 C CNN
F 1 "+3V3" H 4440 1998 50  0000 C CNN
F 2 "" H 4425 1825 50  0001 C CNN
F 3 "" H 4425 1825 50  0001 C CNN
	1    4425 1825
	-1   0    0    1   
$EndComp
Wire Wire Line
	4425 1775 4425 1825
Wire Wire Line
	4800 1975 4700 1975
Connection ~ 4425 1375
Wire Wire Line
	4700 1375 4425 1375
Wire Wire Line
	4700 1975 4700 1375
Text GLabel 4800 1975 2    50   Input ~ 0
SENS2
Wire Wire Line
	4425 1375 4425 1475
$Comp
L RatBoy_bluepill_internals1-rescue:R-Device R4
U 1 1 5D001E2A
P 4425 1625
F 0 "R4" H 4495 1671 50  0000 L CNN
F 1 "10k" H 4495 1580 50  0000 L CNN
F 2 "" V 4355 1625 50  0001 C CNN
F 3 "~" H 4425 1625 50  0001 C CNN
	1    4425 1625
	1    0    0    -1  
$EndComp
$Comp
L RatBoy_bluepill_internals1-rescue:GND-power #PWR09
U 1 1 5D001E24
P 4925 1375
F 0 "#PWR09" H 4925 1125 50  0001 C CNN
F 1 "GND" H 4930 1202 50  0000 C CNN
F 2 "" H 4925 1375 50  0001 C CNN
F 3 "" H 4925 1375 50  0001 C CNN
	1    4925 1375
	1    0    0    -1  
$EndComp
Connection ~ 3625 1175
Wire Wire Line
	3625 1375 3625 1175
$Comp
L TCRT5000:TCRT5000 SENS-3
U 1 1 5D001E1C
P 5325 1275
F 0 "SENS-3" V 5900 1275 50  0000 C CNN
F 1 "TCRT5000" V 4861 1275 50  0000 C BNN
F 2 "5000" H 5325 1275 50  0001 L BNN
F 3 "" H 5325 1275 50  0001 L BNN
F 4 "950 nm 60 mA Through Hole Reflective Optical Sensor with Transistor Output" H 5325 1275 50  0001 L BNN "Field4"
F 5 "TCRT5000" H 5325 1275 50  0001 L BNN "Field5"
F 6 "PCB Mount Vishay" H 5325 1275 50  0001 L BNN "Field6"
F 7 "None" H 5325 1275 50  0001 L BNN "Field7"
F 8 "Unavailable" H 5325 1275 50  0001 L BNN "Field8"
	1    5325 1275
	0    1    -1   0   
$EndComp
$Comp
L TCRT5000:TCRT5000 SENS-2
U 1 1 5D001E11
P 4025 1275
F 0 "SENS-2" V 4600 1275 50  0000 C CNN
F 1 "TCRT5000" V 3561 1275 50  0000 C BNN
F 2 "5000" H 4025 1275 50  0001 L BNN
F 3 "" H 4025 1275 50  0001 L BNN
F 4 "950 nm 60 mA Through Hole Reflective Optical Sensor with Transistor Output" H 4025 1275 50  0001 L BNN "Field4"
F 5 "TCRT5000" H 4025 1275 50  0001 L BNN "Field5"
F 6 "PCB Mount Vishay" H 4025 1275 50  0001 L BNN "Field6"
F 7 "None" H 4025 1275 50  0001 L BNN "Field7"
F 8 "Unavailable" H 4025 1275 50  0001 L BNN "Field8"
	1    4025 1275
	0    1    -1   0   
$EndComp
Wire Wire Line
	3475 1175 3625 1175
$Comp
L RatBoy_bluepill_internals1-rescue:GND-power #PWR07
U 1 1 5D001E05
P 3475 1175
F 0 "#PWR07" H 3475 925 50  0001 C CNN
F 1 "GND" H 3480 1002 50  0000 C CNN
F 2 "" H 3475 1175 50  0001 C CNN
F 3 "" H 3475 1175 50  0001 C CNN
	1    3475 1175
	1    0    0    -1  
$EndComp
Wire Wire Line
	4825 1175 4925 1175
Wire Wire Line
	4525 1175 4425 1175
$Comp
L RatBoy_bluepill_internals1-rescue:R-Device R5
U 1 1 5D001DF7
P 4675 1175
F 0 "R5" V 4468 1175 50  0000 C CNN
F 1 "100" V 4559 1175 50  0000 C CNN
F 2 "" V 4605 1175 50  0001 C CNN
F 3 "~" H 4675 1175 50  0001 C CNN
	1    4675 1175
	0    1    1    0   
$EndComp
Connection ~ 3100 1375
Wire Wire Line
	3475 1975 3375 1975
Wire Wire Line
	3375 1375 3100 1375
Wire Wire Line
	3375 1975 3375 1375
Text GLabel 3475 1975 2    50   Input ~ 0
SENS1
Wire Wire Line
	3100 1775 3100 1850
$Comp
L RatBoy_bluepill_internals1-rescue:+3V3-power #PWR06
U 1 1 5CFE449B
P 3100 1850
F 0 "#PWR06" H 3100 1700 50  0001 C CNN
F 1 "+3V3" H 3115 2023 50  0000 C CNN
F 2 "" H 3100 1850 50  0001 C CNN
F 3 "" H 3100 1850 50  0001 C CNN
	1    3100 1850
	-1   0    0    1   
$EndComp
Wire Wire Line
	3100 1375 3100 1475
Wire Wire Line
	3050 1375 3100 1375
$Comp
L RatBoy_bluepill_internals1-rescue:R-Device R3
U 1 1 5CFE32A2
P 3100 1625
F 0 "R3" H 3170 1671 50  0000 L CNN
F 1 "10k" H 3170 1580 50  0000 L CNN
F 2 "" V 3030 1625 50  0001 C CNN
F 3 "~" H 3100 1625 50  0001 C CNN
	1    3100 1625
	1    0    0    -1  
$EndComp
Wire Wire Line
	3075 1175 3050 1175
Wire Wire Line
	3075 1075 3075 1175
$Comp
L RatBoy_bluepill_internals1-rescue:+3V3-power #PWR05
U 1 1 5CFE1FE5
P 3075 1075
F 0 "#PWR05" H 3075 925 50  0001 C CNN
F 1 "+3V3" H 3090 1248 50  0000 C CNN
F 2 "" H 3075 1075 50  0001 C CNN
F 3 "" H 3075 1075 50  0001 C CNN
	1    3075 1075
	1    0    0    -1  
$EndComp
$Comp
L RatBoy_bluepill_internals1-rescue:+3V3-power #PWR02
U 1 1 5CFE16FF
P 1750 1825
F 0 "#PWR02" H 1750 1675 50  0001 C CNN
F 1 "+3V3" H 1765 1998 50  0000 C CNN
F 2 "" H 1750 1825 50  0001 C CNN
F 3 "" H 1750 1825 50  0001 C CNN
	1    1750 1825
	-1   0    0    1   
$EndComp
Wire Wire Line
	1750 1775 1750 1825
Wire Wire Line
	9375 1175 9300 1175
$Comp
L RatBoy_bluepill_internals1-rescue:+5V-power #PWR022
U 1 1 5CFDD5D6
P 9300 1175
F 0 "#PWR022" H 9300 1025 50  0001 C CNN
F 1 "+5V" H 9315 1348 50  0000 C CNN
F 2 "" H 9300 1175 50  0001 C CNN
F 3 "" H 9300 1175 50  0001 C CNN
	1    9300 1175
	1    0    0    -1  
$EndComp
Wire Wire Line
	10100 1175 9975 1175
$Comp
L RatBoy_bluepill_internals1-rescue:+3V3-power #PWR027
U 1 1 5CFDC6A9
P 10100 1175
F 0 "#PWR027" H 10100 1025 50  0001 C CNN
F 1 "+3V3" H 10115 1348 50  0000 C CNN
F 2 "" H 10100 1175 50  0001 C CNN
F 3 "" H 10100 1175 50  0001 C CNN
	1    10100 1175
	1    0    0    -1  
$EndComp
Wire Wire Line
	2125 1975 2025 1975
Connection ~ 1750 1375
Wire Wire Line
	2025 1375 1750 1375
Wire Wire Line
	2025 1975 2025 1375
Text GLabel 2125 1975 2    50   Input ~ 0
SENS0
Wire Wire Line
	1750 1375 1750 1475
$Comp
L RatBoy_bluepill_internals1-rescue:R-Device R2
U 1 1 5CFD8AF6
P 1750 1625
F 0 "R2" H 1820 1671 50  0000 L CNN
F 1 "10k" H 1820 1580 50  0000 L CNN
F 2 "" V 1680 1625 50  0001 C CNN
F 3 "~" H 1750 1625 50  0001 C CNN
	1    1750 1625
	1    0    0    -1  
$EndComp
$Comp
L RatBoy_bluepill_internals1-rescue:GND-power #PWR03
U 1 1 5CFD87DA
P 2250 1375
F 0 "#PWR03" H 2250 1125 50  0001 C CNN
F 1 "GND" H 2255 1202 50  0000 C CNN
F 2 "" H 2250 1375 50  0001 C CNN
F 3 "" H 2250 1375 50  0001 C CNN
	1    2250 1375
	1    0    0    -1  
$EndComp
Connection ~ 950  1175
Wire Wire Line
	950  1375 950  1175
$Comp
L TCRT5000:TCRT5000 SENS-1
U 1 1 5CFD5957
P 2650 1275
F 0 "SENS-1" V 3225 1275 50  0000 C CNN
F 1 "TCRT5000" V 2186 1275 50  0000 C BNN
F 2 "5000" H 2650 1275 50  0001 L BNN
F 3 "" H 2650 1275 50  0001 L BNN
F 4 "950 nm 60 mA Through Hole Reflective Optical Sensor with Transistor Output" H 2650 1275 50  0001 L BNN "Field4"
F 5 "TCRT5000" H 2650 1275 50  0001 L BNN "Field5"
F 6 "PCB Mount Vishay" H 2650 1275 50  0001 L BNN "Field6"
F 7 "None" H 2650 1275 50  0001 L BNN "Field7"
F 8 "Unavailable" H 2650 1275 50  0001 L BNN "Field8"
	1    2650 1275
	0    1    -1   0   
$EndComp
$Comp
L TCRT5000:TCRT5000 SENS-0
U 1 1 5CFC3CA1
P 1350 1275
F 0 "SENS-0" V 1925 1275 50  0000 C CNN
F 1 "TCRT5000" V 886 1275 50  0000 C BNN
F 2 "5000" H 1350 1275 50  0001 L BNN
F 3 "" H 1350 1275 50  0001 L BNN
F 4 "950 nm 60 mA Through Hole Reflective Optical Sensor with Transistor Output" H 1350 1275 50  0001 L BNN "Field4"
F 5 "TCRT5000" H 1350 1275 50  0001 L BNN "Field5"
F 6 "PCB Mount Vishay" H 1350 1275 50  0001 L BNN "Field6"
F 7 "None" H 1350 1275 50  0001 L BNN "Field7"
F 8 "Unavailable" H 1350 1275 50  0001 L BNN "Field8"
	1    1350 1275
	0    1    -1   0   
$EndComp
Wire Wire Line
	800  1175 950  1175
$Comp
L RatBoy_bluepill_internals1-rescue:GND-power #PWR01
U 1 1 5CFCCED9
P 800 1175
F 0 "#PWR01" H 800 925 50  0001 C CNN
F 1 "GND" H 805 1002 50  0000 C CNN
F 2 "" H 800 1175 50  0001 C CNN
F 3 "" H 800 1175 50  0001 C CNN
	1    800  1175
	1    0    0    -1  
$EndComp
$Comp
L RatBoy_bluepill_internals1-rescue:GND-power #PWR026
U 1 1 5CFCC9D6
P 9675 1475
F 0 "#PWR026" H 9675 1225 50  0001 C CNN
F 1 "GND" H 9680 1302 50  0000 C CNN
F 2 "" H 9675 1475 50  0001 C CNN
F 3 "" H 9675 1475 50  0001 C CNN
	1    9675 1475
	1    0    0    -1  
$EndComp
Wire Wire Line
	2150 1175 2250 1175
Wire Wire Line
	1850 1175 1750 1175
$Comp
L RatBoy_bluepill_internals1-rescue:R-Device R1
U 1 1 5CFC4A0A
P 2000 1175
F 0 "R1" V 1793 1175 50  0000 C CNN
F 1 "100" V 1884 1175 50  0000 C CNN
F 2 "" V 1930 1175 50  0001 C CNN
F 3 "~" H 2000 1175 50  0001 C CNN
	1    2000 1175
	0    1    1    0   
$EndComp
$Comp
L RatBoy_bluepill_internals1-rescue:AZ1117-3.3-Regulator_Linear U4
U 1 1 5CFC3112
P 9675 1175
F 0 "U4" H 9675 1417 50  0000 C CNN
F 1 "AZ1117-3.3" H 9675 1326 50  0000 C CNN
F 2 "" H 9675 1425 50  0001 C CIN
F 3 "https://www.diodes.com/assets/Datasheets/AZ1117.pdf" H 9675 1175 50  0001 C CNN
	1    9675 1175
	1    0    0    -1  
$EndComp
Wire Notes Line
	10375 2150 625  2150
Wire Notes Line
	625  2150 625  550 
Wire Notes Line
	10375 2150 10375 550 
Wire Notes Line
	10375 550  625  550 
$Comp
L dk_PMIC-Full-Half-Bridge-Drivers:L298N U3
U 1 1 5D02FF97
P 8925 3175
F 0 "U3" H 8700 2400 60  0000 C CNN
F 1 "L298N" H 8700 2500 60  0000 C CNN
F 2 "digikey-footprints:Multiwatt-15" H 9125 3375 60  0001 L CNN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/82/cc/3f/39/0a/29/4d/f0/CD00000240.pdf/files/CD00000240.pdf/jcr:content/translations/en.CD00000240.pdf" H 9125 3475 60  0001 L CNN
F 4 "497-1395-5-ND" H 9125 3575 60  0001 L CNN "Digi-Key_PN"
F 5 "L298N" H 9125 3675 60  0001 L CNN "MPN"
F 6 "Integrated Circuits (ICs)" H 9125 3775 60  0001 L CNN "Category"
F 7 "PMIC - Full, Half-Bridge Drivers" H 9125 3875 60  0001 L CNN "Family"
F 8 "http://www.st.com/content/ccc/resource/technical/document/datasheet/82/cc/3f/39/0a/29/4d/f0/CD00000240.pdf/files/CD00000240.pdf/jcr:content/translations/en.CD00000240.pdf" H 9125 3975 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/stmicroelectronics/L298N/497-1395-5-ND/585918" H 9125 4075 60  0001 L CNN "DK_Detail_Page"
F 10 "IC BRIDGE DRIVER PAR 15MULTIWATT" H 9125 4175 60  0001 L CNN "Description"
F 11 "STMicroelectronics" H 9125 4275 60  0001 L CNN "Manufacturer"
F 12 "Active" H 9125 4375 60  0001 L CNN "Status"
	1    8925 3175
	1    0    0    -1  
$EndComp
$Comp
L RatBoy_bluepill_internals1-rescue:Screw_Terminal_01x03-Connector J4
U 1 1 5D033E32
P 9875 4625
F 0 "J4" H 9955 4667 50  0000 L CNN
F 1 "Screw_Terminal_01x03" H 9955 4576 50  0000 L CNN
F 2 "" H 9875 4625 50  0001 C CNN
F 3 "~" H 9875 4625 50  0001 C CNN
	1    9875 4625
	1    0    0    -1  
$EndComp
$Comp
L RatBoy_bluepill_internals1-rescue:Conn_01x06_Male-Connector J1
U 1 1 5D035531
P 7700 3200
F 0 "J1" H 7900 3675 50  0000 C CNN
F 1 "Conn_01x06_Male" H 7875 3575 50  0000 C CNN
F 2 "" H 7700 3200 50  0001 C CNN
F 3 "~" H 7700 3200 50  0001 C CNN
	1    7700 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	7900 3000 8000 3000
Wire Wire Line
	7900 3100 8000 3100
Wire Wire Line
	7900 3200 8000 3200
Wire Wire Line
	7900 3300 8000 3300
Wire Wire Line
	7900 3400 8000 3400
Wire Wire Line
	7900 3500 8000 3500
Text Label 8275 2975 0    50   ~ 0
IN1
Wire Wire Line
	8275 2975 8425 2975
Text Label 8275 3075 0    50   ~ 0
IN2
Wire Wire Line
	8275 3075 8425 3075
Text Label 8275 3175 0    50   ~ 0
IN3
Wire Wire Line
	8275 3175 8425 3175
Text Label 8275 3275 0    50   ~ 0
IN4
Wire Wire Line
	8275 3275 8425 3275
Text Label 8275 3375 0    50   ~ 0
ENA
Wire Wire Line
	8275 3375 8425 3375
Text Label 8275 3475 0    50   ~ 0
ENB
Wire Wire Line
	8275 3475 8425 3475
$Comp
L RatBoy_bluepill_internals1-rescue:GND-power #PWR021
U 1 1 5D0667C0
P 8925 4050
F 0 "#PWR021" H 8925 3800 50  0001 C CNN
F 1 "GND" H 8930 3877 50  0000 C CNN
F 2 "" H 8925 4050 50  0001 C CNN
F 3 "" H 8925 4050 50  0001 C CNN
	1    8925 4050
	1    0    0    -1  
$EndComp
NoConn ~ 8425 3675
Wire Wire Line
	8925 3975 8925 4025
Wire Wire Line
	8925 4025 8350 4025
Wire Wire Line
	8350 3575 8425 3575
$Comp
L RatBoy_bluepill_internals1-rescue:LM78M05_TO220-Regulator_Linear U2
U 1 1 5D070520
P 8225 4525
F 0 "U2" H 8225 4767 50  0000 C CNN
F 1 "LM78M05_TO220" H 8225 4676 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 8225 4750 50  0001 C CIN
F 3 "http://www.fairchildsemi.com/ds/LM/LM78M05.pdf" H 8225 4475 50  0001 C CNN
	1    8225 4525
	1    0    0    -1  
$EndComp
$Comp
L RatBoy_bluepill_internals1-rescue:CP-Device C1
U 1 1 5D072DA9
P 8675 4900
F 0 "C1" H 8793 4946 50  0000 L CNN
F 1 "220uF" H 8793 4855 50  0000 L CNN
F 2 "" H 8713 4750 50  0001 C CNN
F 3 "~" H 8675 4900 50  0001 C CNN
	1    8675 4900
	1    0    0    -1  
$EndComp
$Comp
L RatBoy_bluepill_internals1-rescue:LED-Device D1
U 1 1 5D073E13
P 9150 4700
F 0 "D1" V 9189 4583 50  0000 R CNN
F 1 "LED" V 9098 4583 50  0000 R CNN
F 2 "" H 9150 4700 50  0001 C CNN
F 3 "~" H 9150 4700 50  0001 C CNN
	1    9150 4700
	0    -1   -1   0   
$EndComp
$Comp
L RatBoy_bluepill_internals1-rescue:R-Device R10
U 1 1 5D075262
P 9150 5025
F 0 "R10" H 9220 5071 50  0000 L CNN
F 1 "R" H 9220 4980 50  0000 L CNN
F 2 "" V 9080 5025 50  0001 C CNN
F 3 "~" H 9150 5025 50  0001 C CNN
	1    9150 5025
	1    0    0    -1  
$EndComp
Wire Wire Line
	9150 4850 9150 4875
Wire Wire Line
	8225 4825 8225 5175
$Comp
L RatBoy_bluepill_internals1-rescue:GND-power #PWR017
U 1 1 5D08AB59
P 8225 5175
F 0 "#PWR017" H 8225 4925 50  0001 C CNN
F 1 "GND" H 8230 5002 50  0000 C CNN
F 2 "" H 8225 5175 50  0001 C CNN
F 3 "" H 8225 5175 50  0001 C CNN
	1    8225 5175
	1    0    0    -1  
$EndComp
Connection ~ 9150 4875
Wire Wire Line
	9150 4875 9150 4900
Connection ~ 8225 5175
Wire Wire Line
	8225 5175 8675 5175
Wire Wire Line
	8675 5050 8675 5175
Connection ~ 8675 5175
Wire Wire Line
	8675 5175 9150 5175
Wire Wire Line
	8675 4750 8675 4525
Wire Wire Line
	8675 4525 8525 4525
Wire Wire Line
	8675 4525 9150 4525
Wire Wire Line
	9150 4525 9150 4550
Connection ~ 8675 4525
$Comp
L RatBoy_bluepill_internals1-rescue:+5V-power #PWR025
U 1 1 5D0A9468
P 9575 4525
F 0 "#PWR025" H 9575 4375 50  0001 C CNN
F 1 "+5V" H 9590 4698 50  0000 C CNN
F 2 "" H 9575 4525 50  0001 C CNN
F 3 "" H 9575 4525 50  0001 C CNN
	1    9575 4525
	1    0    0    -1  
$EndComp
Wire Wire Line
	9675 4525 9575 4525
Wire Wire Line
	9150 4525 9575 4525
Connection ~ 9150 4525
Connection ~ 9575 4525
$Comp
L RatBoy_bluepill_internals1-rescue:GND-power #PWR024
U 1 1 5D0B0F46
P 9525 4625
F 0 "#PWR024" H 9525 4375 50  0001 C CNN
F 1 "GND" H 9530 4452 50  0000 C CNN
F 2 "" H 9525 4625 50  0001 C CNN
F 3 "" H 9525 4625 50  0001 C CNN
	1    9525 4625
	1    0    0    -1  
$EndComp
Wire Wire Line
	9675 4625 9525 4625
Wire Wire Line
	7925 4525 7875 4525
Wire Wire Line
	7875 4525 7875 5450
Wire Wire Line
	7875 5450 9675 5450
Wire Wire Line
	9675 5450 9675 5125
$Comp
L RatBoy_bluepill_internals1-rescue:+5V-power #PWR020
U 1 1 5D0CCDEC
P 8925 2675
F 0 "#PWR020" H 8925 2525 50  0001 C CNN
F 1 "+5V" H 8940 2848 50  0000 C CNN
F 2 "" H 8925 2675 50  0001 C CNN
F 3 "" H 8925 2675 50  0001 C CNN
	1    8925 2675
	1    0    0    -1  
$EndComp
$Comp
L RatBoy_bluepill_internals1-rescue:GND-power #PWR023
U 1 1 5D0CD86D
P 9250 2800
F 0 "#PWR023" H 9250 2550 50  0001 C CNN
F 1 "GND" H 9255 2627 50  0000 C CNN
F 2 "" H 9250 2800 50  0001 C CNN
F 3 "" H 9250 2800 50  0001 C CNN
	1    9250 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	9025 2675 9250 2675
Wire Wire Line
	9250 2675 9250 2800
Wire Notes Line
	7175 2275 10950 2275
Wire Notes Line
	10950 2275 10950 5800
Wire Notes Line
	10950 5800 7175 5800
Wire Notes Line
	7175 5800 7175 2275
Text Notes 8125 5750 0    118  ~ 0
L298N Motor Driver
Text Notes 9350 2000 0    118  ~ 0
SENSORES
$Comp
L RatBoy_bluepill_internals1-rescue:SW_DIP_x01-Switch SW1
U 1 1 5D0F64FA
P 6400 2725
F 0 "SW1" H 6400 2992 50  0000 C CNN
F 1 "SWITCH PRINCIPAL" H 6400 2901 50  0000 C CNN
F 2 "" H 6400 2725 50  0001 C CNN
F 3 "~" H 6400 2725 50  0001 C CNN
	1    6400 2725
	1    0    0    -1  
$EndComp
Wire Wire Line
	5825 2725 6100 2725
$Comp
L RatBoy_bluepill_internals1-rescue:GND-power #PWR04
U 1 1 5D1042AF
P 5825 3200
F 0 "#PWR04" H 5825 2950 50  0001 C CNN
F 1 "GND" H 5830 3027 50  0000 C CNN
F 2 "" H 5825 3200 50  0001 C CNN
F 3 "" H 5825 3200 50  0001 C CNN
	1    5825 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5825 3125 5825 3200
Wire Wire Line
	6775 2725 6700 2725
Text GLabel 6775 2725 2    50   Input ~ 0
PSU
Text GLabel 10250 5125 2    50   Input ~ 0
PSU
Wire Wire Line
	10250 5125 9675 5125
Connection ~ 9675 5125
Wire Wire Line
	9675 5125 9675 4725
Text GLabel 3500 5075 2    50   Input ~ 0
SENS5
Wire Wire Line
	3250 5075 3500 5075
Text GLabel 3500 4975 2    50   Input ~ 0
SENS4
Wire Wire Line
	3250 4975 3500 4975
Text GLabel 3500 4875 2    50   Input ~ 0
SENS3
Wire Wire Line
	3250 4875 3500 4875
Text GLabel 3500 4775 2    50   Input ~ 0
SENS2
Wire Wire Line
	3250 4775 3500 4775
Text GLabel 3500 4675 2    50   Input ~ 0
SENS1
Wire Wire Line
	3250 4675 3500 4675
Text GLabel 3500 4575 2    50   Input ~ 0
SENS0
Wire Wire Line
	3250 4575 3500 4575
Text Label 1750 4375 0    50   ~ 0
IN1
Wire Wire Line
	1950 4375 1750 4375
Text Label 1750 4475 0    50   ~ 0
IN2
Wire Wire Line
	1950 4475 1750 4475
$Comp
L RatBoy_bluepill_internals1-rescue:D-Device D3
U 1 1 5D1443D6
P 9450 3750
F 0 "D3" V 9404 3829 50  0000 L CNN
F 1 "D" V 9495 3829 50  0000 L CNN
F 2 "" H 9450 3750 50  0001 C CNN
F 3 "~" H 9450 3750 50  0001 C CNN
	1    9450 3750
	0    1    1    0   
$EndComp
$Comp
L RatBoy_bluepill_internals1-rescue:D-Device D5
U 1 1 5D146251
P 9675 3750
F 0 "D5" V 9629 3829 50  0000 L CNN
F 1 "D" V 9720 3829 50  0000 L CNN
F 2 "" H 9675 3750 50  0001 C CNN
F 3 "~" H 9675 3750 50  0001 C CNN
	1    9675 3750
	0    1    1    0   
$EndComp
$Comp
L RatBoy_bluepill_internals1-rescue:Screw_Terminal_01x02-Connector J3
U 1 1 5D0BD45A
P 10350 3400
F 0 "J3" H 10430 3392 50  0000 L CNN
F 1 "Screw_01x02" H 10430 3301 50  0000 L CNN
F 2 "" H 10350 3400 50  0001 C CNN
F 3 "~" H 10350 3400 50  0001 C CNN
	1    10350 3400
	1    0    0    -1  
$EndComp
$Comp
L RatBoy_bluepill_internals1-rescue:Screw_Terminal_01x02-Connector J2
U 1 1 5D03481F
P 10350 3175
F 0 "J2" H 10430 3167 50  0000 L CNN
F 1 "Screw_01x02" H 10430 3076 50  0000 L CNN
F 2 "" H 10350 3175 50  0001 C CNN
F 3 "~" H 10350 3175 50  0001 C CNN
	1    10350 3175
	1    0    0    -1  
$EndComp
Wire Wire Line
	8925 4025 9450 4025
Connection ~ 8925 4025
Wire Wire Line
	8925 4025 8925 4050
Wire Wire Line
	9450 3900 9450 4025
Connection ~ 9450 4025
$Comp
L RatBoy_bluepill_internals1-rescue:D-Device D7
U 1 1 5D1763C9
P 9900 3750
F 0 "D7" V 9854 3829 50  0000 L CNN
F 1 "D" V 9945 3829 50  0000 L CNN
F 2 "" H 9900 3750 50  0001 C CNN
F 3 "~" H 9900 3750 50  0001 C CNN
	1    9900 3750
	0    1    1    0   
$EndComp
$Comp
L RatBoy_bluepill_internals1-rescue:D-Device D9
U 1 1 5D1763CF
P 10125 3750
F 0 "D9" V 10079 3829 50  0000 L CNN
F 1 "D" V 10170 3829 50  0000 L CNN
F 2 "" H 10125 3750 50  0001 C CNN
F 3 "~" H 10125 3750 50  0001 C CNN
	1    10125 3750
	0    1    1    0   
$EndComp
Wire Wire Line
	10125 3600 10125 3500
Connection ~ 10125 3500
Wire Wire Line
	10125 3500 10150 3500
Wire Wire Line
	10125 4025 10125 3900
Wire Wire Line
	9900 3900 9900 4025
Connection ~ 9900 4025
Wire Wire Line
	9900 4025 10125 4025
Connection ~ 9900 3400
Wire Wire Line
	9900 3400 10150 3400
Wire Wire Line
	9450 4025 9675 4025
Wire Wire Line
	9675 3900 9675 4025
Connection ~ 9675 4025
Wire Wire Line
	9675 4025 9900 4025
Wire Wire Line
	9325 3275 9675 3275
Wire Wire Line
	9325 3175 9450 3175
Connection ~ 9675 3275
Wire Wire Line
	9675 3275 10150 3275
Wire Wire Line
	9450 3600 9450 3175
Connection ~ 9450 3175
Wire Wire Line
	9450 3175 10150 3175
Wire Wire Line
	9375 3400 9375 3375
Wire Wire Line
	9375 3375 9325 3375
Wire Wire Line
	9375 3400 9900 3400
Wire Wire Line
	9375 3500 9375 3475
Wire Wire Line
	9375 3475 9325 3475
Wire Wire Line
	9375 3500 10125 3500
$Comp
L RatBoy_bluepill_internals1-rescue:D-Device D2
U 1 1 5D1C96C9
P 9450 2825
F 0 "D2" V 9404 2904 50  0000 L CNN
F 1 "D" V 9495 2904 50  0000 L CNN
F 2 "" H 9450 2825 50  0001 C CNN
F 3 "~" H 9450 2825 50  0001 C CNN
	1    9450 2825
	0    1    1    0   
$EndComp
$Comp
L RatBoy_bluepill_internals1-rescue:D-Device D4
U 1 1 5D1C96CF
P 9675 2825
F 0 "D4" V 9629 2904 50  0000 L CNN
F 1 "D" V 9720 2904 50  0000 L CNN
F 2 "" H 9675 2825 50  0001 C CNN
F 3 "~" H 9675 2825 50  0001 C CNN
	1    9675 2825
	0    1    1    0   
$EndComp
$Comp
L RatBoy_bluepill_internals1-rescue:D-Device D6
U 1 1 5D1C96D5
P 9900 2825
F 0 "D6" V 9854 2904 50  0000 L CNN
F 1 "D" V 9945 2904 50  0000 L CNN
F 2 "" H 9900 2825 50  0001 C CNN
F 3 "~" H 9900 2825 50  0001 C CNN
	1    9900 2825
	0    1    1    0   
$EndComp
$Comp
L RatBoy_bluepill_internals1-rescue:D-Device D8
U 1 1 5D1C96DB
P 10125 2825
F 0 "D8" V 10079 2904 50  0000 L CNN
F 1 "D" V 10170 2904 50  0000 L CNN
F 2 "" H 10125 2825 50  0001 C CNN
F 3 "~" H 10125 2825 50  0001 C CNN
	1    10125 2825
	0    1    1    0   
$EndComp
Wire Wire Line
	9450 2975 9450 3175
Wire Wire Line
	9675 3600 9675 3275
Wire Wire Line
	9675 2975 9675 3275
Wire Wire Line
	9900 3600 9900 3400
Wire Wire Line
	9900 2975 9900 3400
Wire Wire Line
	10125 2975 10125 3500
Wire Wire Line
	10125 2675 10125 2600
Wire Wire Line
	10125 2600 9900 2600
Wire Wire Line
	9450 2600 9450 2675
Text GLabel 10375 2600 2    50   Input ~ 0
PSU
Wire Wire Line
	10125 2600 10375 2600
Connection ~ 10125 2600
Wire Wire Line
	9900 2675 9900 2600
Connection ~ 9900 2600
Wire Wire Line
	9900 2600 9675 2600
Wire Wire Line
	9675 2675 9675 2600
Connection ~ 9675 2600
Wire Wire Line
	9675 2600 9450 2600
Wire Wire Line
	8350 4025 8350 3575
Text Notes 10300 3950 0    50   ~ 0
Diodos Rápidos\nFR107
Text Label 8000 3000 0    50   ~ 0
ENB
Text Label 8000 3100 0    50   ~ 0
IN4
Text Label 8000 3200 0    50   ~ 0
IN3
Text Label 8000 3300 0    50   ~ 0
IN2
Text Label 8000 3400 0    50   ~ 0
IN1
Text Label 8000 3500 0    50   ~ 0
ENA
Text Label 1750 5375 0    50   ~ 0
ENA
Wire Wire Line
	1950 5375 1750 5375
Text Label 1750 5475 0    50   ~ 0
ENB
Wire Wire Line
	1950 5475 1750 5475
$Comp
L RatBoy_bluepill_internals1-rescue:STM32F103C8Tx-MCU_ST_STM32F1 U1
U 1 1 5CFF0796
P 2650 4575
F 0 "U1" H 2600 2986 50  0000 C CNN
F 1 "STM32F103C8T6" H 2600 2895 50  0000 C CNN
F 2 "Package_QFP:LQFP-48_7x7mm_P0.5mm" H 2050 3175 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/CD00161566.pdf" H 2650 4575 50  0001 C CNN
	1    2650 4575
	1    0    0    -1  
$EndComp
$Comp
L RT9193-33GB:RT9193-33GB U5
U 1 1 5D00671E
P 4100 3650
F 0 "U5" H 4100 4017 50  0000 C CNN
F 1 "RT9193-33GB" H 4100 3926 50  0000 C CNN
F 2 "SOT94P279X129-5N" H 4100 3650 50  0001 L BNN
F 3 "" H 4100 3650 50  0001 L BNN
F 4 "Richtek USA" H 4100 3650 50  0001 L BNN "Field4"
F 5 "Unavailable" H 4100 3650 50  0001 L BNN "Field5"
F 6 "SOT-23-5 Richtek" H 4100 3650 50  0001 L BNN "Field6"
F 7 "None" H 4100 3650 50  0001 L BNN "Field7"
F 8 "RT9193-33GB" H 4100 3650 50  0001 L BNN "Field8"
	1    4100 3650
	1    0    0    -1  
$EndComp
$Comp
L RatBoy_bluepill_internals1-rescue:Crystal-Device Y1
U 1 1 5CFF3BB1
P 1225 3800
F 0 "Y1" H 1250 3550 50  0000 R CNN
F 1 "8M0 Quartz Resonator" H 1575 3625 50  0000 R CNN
F 2 "" H 1225 3800 50  0001 C CNN
F 3 "~" H 1225 3800 50  0001 C CNN
	1    1225 3800
	-1   0    0    1   
$EndComp
$Comp
L RatBoy_bluepill_internals1-rescue:C_Small-Device C3
U 1 1 5D00809E
P 1450 3925
F 0 "C3" H 1542 3971 50  0000 L CNN
F 1 "12p" H 1542 3880 50  0000 L CNN
F 2 "" H 1450 3925 50  0001 C CNN
F 3 "~" H 1450 3925 50  0001 C CNN
	1    1450 3925
	1    0    0    -1  
$EndComp
$Comp
L RatBoy_bluepill_internals1-rescue:C_Small-Device C2
U 1 1 5D009773
P 1000 3925
F 0 "C2" H 908 3971 50  0000 R CNN
F 1 "12p" H 908 3880 50  0000 R CNN
F 2 "" H 1000 3925 50  0001 C CNN
F 3 "~" H 1000 3925 50  0001 C CNN
	1    1000 3925
	1    0    0    -1  
$EndComp
Wire Wire Line
	1075 3800 1000 3800
Wire Wire Line
	1000 3800 1000 3825
Wire Wire Line
	1375 3800 1450 3800
Wire Wire Line
	1450 3800 1450 3825
$Comp
L RatBoy_bluepill_internals1-rescue:GND-power #PWR010
U 1 1 5D02843C
P 1225 4050
F 0 "#PWR010" H 1225 3800 50  0001 C CNN
F 1 "GND" H 1230 3877 50  0000 C CNN
F 2 "" H 1225 4050 50  0001 C CNN
F 3 "" H 1225 4050 50  0001 C CNN
	1    1225 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1000 4025 1225 4025
Wire Wire Line
	1225 4050 1225 4025
Connection ~ 1225 4025
Wire Wire Line
	1225 4025 1450 4025
Text Label 1750 3975 0    50   ~ 0
IN3
Wire Wire Line
	1950 3975 1750 3975
Text Label 1750 4075 0    50   ~ 0
IN4
Wire Wire Line
	1950 4075 1750 4075
Wire Wire Line
	1950 3675 1000 3675
Wire Wire Line
	1000 3675 1000 3800
Connection ~ 1000 3800
Wire Wire Line
	1450 3800 1450 3775
Wire Wire Line
	1450 3775 1950 3775
Connection ~ 1450 3800
$Comp
L RatBoy_bluepill_internals1-rescue:+3.3V-power #PWR014
U 1 1 5D069EAC
P 2700 2950
F 0 "#PWR014" H 2700 2800 50  0001 C CNN
F 1 "+3.3V" H 2715 3123 50  0000 C CNN
F 2 "" H 2700 2950 50  0001 C CNN
F 3 "" H 2700 2950 50  0001 C CNN
	1    2700 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	2850 3075 2750 3075
Wire Wire Line
	2750 3075 2700 3075
Wire Wire Line
	2650 3075 2550 3075
Connection ~ 2750 3075
Connection ~ 2650 3075
Wire Wire Line
	2700 2950 2700 3075
Connection ~ 2700 3075
Wire Wire Line
	2700 3075 2650 3075
$Comp
L RatBoy_bluepill_internals1-rescue:+5V-power #PWR029
U 1 1 5D089F98
P 3525 3550
F 0 "#PWR029" H 3525 3400 50  0001 C CNN
F 1 "+5V" H 3540 3723 50  0000 C CNN
F 2 "" H 3525 3550 50  0001 C CNN
F 3 "" H 3525 3550 50  0001 C CNN
	1    3525 3550
	1    0    0    -1  
$EndComp
$Comp
L RatBoy_bluepill_internals1-rescue:CP-Device C4
U 1 1 5D092B12
P 3300 3725
F 0 "C4" H 3418 3771 50  0000 L CNN
F 1 "10uF" H 3418 3680 50  0000 L CNN
F 2 "" H 3338 3575 50  0001 C CNN
F 3 "~" H 3300 3725 50  0001 C CNN
	1    3300 3725
	1    0    0    -1  
$EndComp
$Comp
L RatBoy_bluepill_internals1-rescue:CP-Device C6
U 1 1 5D093BF8
P 5100 3725
F 0 "C6" H 5218 3771 50  0000 L CNN
F 1 "10uF" H 5218 3680 50  0000 L CNN
F 2 "" H 5138 3575 50  0001 C CNN
F 3 "~" H 5100 3725 50  0001 C CNN
	1    5100 3725
	1    0    0    -1  
$EndComp
$Comp
L RatBoy_bluepill_internals1-rescue:GND-power #PWR030
U 1 1 5D09E812
P 4625 3925
F 0 "#PWR030" H 4625 3675 50  0001 C CNN
F 1 "GND" V 4630 3797 50  0000 R CNN
F 2 "" H 4625 3925 50  0001 C CNN
F 3 "" H 4625 3925 50  0001 C CNN
	1    4625 3925
	1    0    0    -1  
$EndComp
Wire Wire Line
	4625 3875 4625 3775
Wire Wire Line
	4625 3775 4600 3750
Wire Wire Line
	3600 3550 3525 3550
Wire Wire Line
	3600 3750 3600 3550
Connection ~ 3600 3550
Wire Wire Line
	3300 3575 3525 3575
Wire Wire Line
	3525 3575 3525 3550
Connection ~ 3525 3550
Wire Wire Line
	3300 3875 4625 3875
Wire Wire Line
	4625 3875 4625 3925
Connection ~ 4625 3875
Wire Wire Line
	4750 3875 5100 3875
Wire Wire Line
	4625 3875 4750 3875
Connection ~ 4750 3875
$Comp
L RatBoy_bluepill_internals1-rescue:C_Small-Device C5
U 1 1 5D0947B2
P 4750 3775
F 0 "C5" H 4842 3821 50  0000 L CNN
F 1 "100n" H 4842 3730 50  0000 L CNN
F 2 "" H 4750 3775 50  0001 C CNN
F 3 "~" H 4750 3775 50  0001 C CNN
	1    4750 3775
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 3650 4750 3650
Wire Wire Line
	4750 3650 4750 3675
Wire Wire Line
	5100 3575 5100 3550
Wire Wire Line
	5100 3550 4825 3550
$Comp
L RatBoy_bluepill_internals1-rescue:+3.3V-power #PWR031
U 1 1 5D12CB67
P 4825 3550
F 0 "#PWR031" H 4825 3400 50  0001 C CNN
F 1 "+3.3V" H 4840 3723 50  0000 C CNN
F 2 "" H 4825 3550 50  0001 C CNN
F 3 "" H 4825 3550 50  0001 C CNN
	1    4825 3550
	1    0    0    -1  
$EndComp
Connection ~ 4825 3550
Wire Wire Line
	4825 3550 4600 3550
Wire Wire Line
	2450 6075 2550 6075
Connection ~ 2550 6075
Wire Wire Line
	2550 6075 2650 6075
Connection ~ 2650 6075
Wire Wire Line
	2650 6075 2750 6075
$Comp
L RatBoy_bluepill_internals1-rescue:GND-power #PWR028
U 1 1 5D156262
P 3150 6100
F 0 "#PWR028" H 3150 5850 50  0001 C CNN
F 1 "GND" H 3155 5927 50  0000 C CNN
F 2 "" H 3150 6100 50  0001 C CNN
F 3 "" H 3150 6100 50  0001 C CNN
	1    3150 6100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 6100 2650 6100
Wire Wire Line
	2650 6100 2650 6075
$Comp
L RatBoy_bluepill_internals1-rescue:R-Device R11
U 1 1 5D160C0D
P 1575 3000
F 0 "R11" H 1645 3046 50  0000 L CNN
F 1 "10k" H 1645 2955 50  0000 L CNN
F 2 "" V 1505 3000 50  0001 C CNN
F 3 "~" H 1575 3000 50  0001 C CNN
	1    1575 3000
	1    0    0    -1  
$EndComp
$Comp
L RatBoy_bluepill_internals1-rescue:+3V3-power #PWR033
U 1 1 5D161146
P 1575 2775
F 0 "#PWR033" H 1575 2625 50  0001 C CNN
F 1 "+3V3" H 1590 2948 50  0000 C CNN
F 2 "" H 1575 2775 50  0001 C CNN
F 3 "" H 1575 2775 50  0001 C CNN
	1    1575 2775
	1    0    0    -1  
$EndComp
Wire Wire Line
	1575 2775 1575 2850
$Comp
L RatBoy_bluepill_internals1-rescue:C_Small-Device C7
U 1 1 5D174D10
P 1575 3250
F 0 "C7" H 1667 3296 50  0000 L CNN
F 1 "100n" H 1667 3205 50  0000 L CNN
F 2 "" H 1575 3250 50  0001 C CNN
F 3 "~" H 1575 3250 50  0001 C CNN
	1    1575 3250
	1    0    0    -1  
$EndComp
Connection ~ 1575 3150
Wire Wire Line
	1950 3275 1950 3150
Wire Wire Line
	1575 3150 1950 3150
$Comp
L RatBoy_bluepill_internals1-rescue:GND-power #PWR034
U 1 1 5D18C481
P 1575 3350
F 0 "#PWR034" H 1575 3100 50  0001 C CNN
F 1 "GND" H 1580 3177 50  0000 C CNN
F 2 "" H 1575 3350 50  0001 C CNN
F 3 "" H 1575 3350 50  0001 C CNN
	1    1575 3350
	1    0    0    -1  
$EndComp
$Comp
L RatBoy_bluepill_internals1-rescue:SW_Push-Switch SW2
U 1 1 5D18CF04
P 1275 3150
F 0 "SW2" H 1275 3435 50  0000 C CNN
F 1 "SW_Push" H 1275 3344 50  0000 C CNN
F 2 "" H 1275 3350 50  0001 C CNN
F 3 "~" H 1275 3350 50  0001 C CNN
	1    1275 3150
	-1   0    0    -1  
$EndComp
$Comp
L RatBoy_bluepill_internals1-rescue:GND-power #PWR032
U 1 1 5D197F13
P 1075 3250
F 0 "#PWR032" H 1075 3000 50  0001 C CNN
F 1 "GND" H 1080 3077 50  0000 C CNN
F 2 "" H 1075 3250 50  0001 C CNN
F 3 "" H 1075 3250 50  0001 C CNN
	1    1075 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	1075 3150 1075 3250
Wire Wire Line
	1475 3150 1575 3150
Wire Notes Line
	625  2275 5475 2275
Wire Notes Line
	5475 2275 5475 6450
Wire Notes Line
	5475 6450 625  6450
Wire Notes Line
	625  6450 625  2275
Text Notes 3350 6225 0    118  ~ 0
Dev Board STM32F103
Wire Notes Line
	5600 2275 5600 3475
Wire Notes Line
	5600 3475 7050 3475
Wire Notes Line
	7050 3475 7050 2275
Wire Notes Line
	7050 2275 5600 2275
Text Notes 6100 3425 0    118  ~ 0
SWITCH\nPRINCIPAL
$EndSCHEMATC