EESchema Schematic File Version 4
LIBS:RatBoy-cache
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
L Device:Battery BT1
U 1 1 5CFBEA42
P 2425 3575
F 0 "BT1" H 2533 3621 50  0000 L CNN
F 1 "Battery 7.2V li-ion" H 2533 3530 50  0000 L CNN
F 2 "" V 2425 3635 50  0001 C CNN
F 3 "~" V 2425 3635 50  0001 C CNN
	1    2425 3575
	1    0    0    -1  
$EndComp
$Comp
L bluepill_breakouts:BluePill_STM32F103C U1
U 1 1 5CFBF98B
P 4650 4775
F 0 "U1" H 4675 3302 50  0000 C CNN
F 1 "BluePill_STM32F103C" H 4675 3211 50  0000 C CNN
F 2 "BluePill_breakouts:BluePill_STM32F103C" H 4700 3175 50  0001 C CNN
F 3 "" H 4650 3275 50  0001 C CNN
	1    4650 4775
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
L power:+3V3 #PWR019
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
L Device:R R9
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
L power:+3V3 #PWR018
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
L power:+3V3 #PWR015
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
L Device:R R7
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
L power:GND #PWR016
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
L power:GND #PWR013
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
L Device:R R8
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
L power:+3V3 #PWR012
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
L Device:R R6
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
L power:+3V3 #PWR011
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
L power:+3V3 #PWR08
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
L Device:R R4
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
L power:GND #PWR09
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
L power:GND #PWR07
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
L Device:R R5
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
L power:+3V3 #PWR06
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
L Device:R R3
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
L power:+3V3 #PWR05
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
L power:+3V3 #PWR02
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
L power:+5V #PWR022
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
L power:+3V3 #PWR027
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
L Device:R R2
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
L power:GND #PWR03
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
L power:GND #PWR01
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
L power:GND #PWR026
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
L Device:R R1
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
L Regulator_Linear:AZ1117-3.3 U4
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
P 9000 3275
F 0 "U3" H 8775 2500 60  0000 C CNN
F 1 "L298N" H 8775 2600 60  0000 C CNN
F 2 "digikey-footprints:Multiwatt-15" H 9200 3475 60  0001 L CNN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/82/cc/3f/39/0a/29/4d/f0/CD00000240.pdf/files/CD00000240.pdf/jcr:content/translations/en.CD00000240.pdf" H 9200 3575 60  0001 L CNN
F 4 "497-1395-5-ND" H 9200 3675 60  0001 L CNN "Digi-Key_PN"
F 5 "L298N" H 9200 3775 60  0001 L CNN "MPN"
F 6 "Integrated Circuits (ICs)" H 9200 3875 60  0001 L CNN "Category"
F 7 "PMIC - Full, Half-Bridge Drivers" H 9200 3975 60  0001 L CNN "Family"
F 8 "http://www.st.com/content/ccc/resource/technical/document/datasheet/82/cc/3f/39/0a/29/4d/f0/CD00000240.pdf/files/CD00000240.pdf/jcr:content/translations/en.CD00000240.pdf" H 9200 4075 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/stmicroelectronics/L298N/497-1395-5-ND/585918" H 9200 4175 60  0001 L CNN "DK_Detail_Page"
F 10 "IC BRIDGE DRIVER PAR 15MULTIWATT" H 9200 4275 60  0001 L CNN "Description"
F 11 "STMicroelectronics" H 9200 4375 60  0001 L CNN "Manufacturer"
F 12 "Active" H 9200 4475 60  0001 L CNN "Status"
	1    9000 3275
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x03 J4
U 1 1 5D033E32
P 9950 4725
F 0 "J4" H 10030 4767 50  0000 L CNN
F 1 "Screw_Terminal_01x03" H 10030 4676 50  0000 L CNN
F 2 "" H 9950 4725 50  0001 C CNN
F 3 "~" H 9950 4725 50  0001 C CNN
	1    9950 4725
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x06_Male J1
U 1 1 5D035531
P 7775 3300
F 0 "J1" H 7975 3775 50  0000 C CNN
F 1 "Conn_01x06_Male" H 7950 3675 50  0000 C CNN
F 2 "" H 7775 3300 50  0001 C CNN
F 3 "~" H 7775 3300 50  0001 C CNN
	1    7775 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7975 3100 8075 3100
Wire Wire Line
	7975 3200 8075 3200
Wire Wire Line
	7975 3300 8075 3300
Wire Wire Line
	7975 3400 8075 3400
Wire Wire Line
	7975 3500 8075 3500
Wire Wire Line
	7975 3600 8075 3600
Text Label 8350 3075 0    50   ~ 0
IN1
Wire Wire Line
	8350 3075 8500 3075
Text Label 8350 3175 0    50   ~ 0
IN2
Wire Wire Line
	8350 3175 8500 3175
Text Label 8350 3275 0    50   ~ 0
IN3
Wire Wire Line
	8350 3275 8500 3275
Text Label 8350 3375 0    50   ~ 0
IN4
Wire Wire Line
	8350 3375 8500 3375
Text Label 8350 3475 0    50   ~ 0
ENA
Wire Wire Line
	8350 3475 8500 3475
Text Label 8350 3575 0    50   ~ 0
ENB
Wire Wire Line
	8350 3575 8500 3575
$Comp
L power:GND #PWR021
U 1 1 5D0667C0
P 9000 4150
F 0 "#PWR021" H 9000 3900 50  0001 C CNN
F 1 "GND" H 9005 3977 50  0000 C CNN
F 2 "" H 9000 4150 50  0001 C CNN
F 3 "" H 9000 4150 50  0001 C CNN
	1    9000 4150
	1    0    0    -1  
$EndComp
NoConn ~ 8500 3775
Wire Wire Line
	9000 4075 9000 4125
Wire Wire Line
	9000 4125 8425 4125
Wire Wire Line
	8425 3675 8500 3675
$Comp
L Regulator_Linear:LM78M05_TO220 U2
U 1 1 5D070520
P 8300 4625
F 0 "U2" H 8300 4867 50  0000 C CNN
F 1 "LM78M05_TO220" H 8300 4776 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 8300 4850 50  0001 C CIN
F 3 "http://www.fairchildsemi.com/ds/LM/LM78M05.pdf" H 8300 4575 50  0001 C CNN
	1    8300 4625
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C1
U 1 1 5D072DA9
P 8750 5000
F 0 "C1" H 8868 5046 50  0000 L CNN
F 1 "220uF" H 8868 4955 50  0000 L CNN
F 2 "" H 8788 4850 50  0001 C CNN
F 3 "~" H 8750 5000 50  0001 C CNN
	1    8750 5000
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D1
U 1 1 5D073E13
P 9225 4800
F 0 "D1" V 9264 4683 50  0000 R CNN
F 1 "LED" V 9173 4683 50  0000 R CNN
F 2 "" H 9225 4800 50  0001 C CNN
F 3 "~" H 9225 4800 50  0001 C CNN
	1    9225 4800
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R10
U 1 1 5D075262
P 9225 5125
F 0 "R10" H 9295 5171 50  0000 L CNN
F 1 "R" H 9295 5080 50  0000 L CNN
F 2 "" V 9155 5125 50  0001 C CNN
F 3 "~" H 9225 5125 50  0001 C CNN
	1    9225 5125
	1    0    0    -1  
$EndComp
Wire Wire Line
	9225 4950 9225 4975
Wire Wire Line
	8300 4925 8300 5275
$Comp
L power:GND #PWR017
U 1 1 5D08AB59
P 8300 5275
F 0 "#PWR017" H 8300 5025 50  0001 C CNN
F 1 "GND" H 8305 5102 50  0000 C CNN
F 2 "" H 8300 5275 50  0001 C CNN
F 3 "" H 8300 5275 50  0001 C CNN
	1    8300 5275
	1    0    0    -1  
$EndComp
Connection ~ 9225 4975
Wire Wire Line
	9225 4975 9225 5000
Connection ~ 8300 5275
Wire Wire Line
	8300 5275 8750 5275
Wire Wire Line
	8750 5150 8750 5275
Connection ~ 8750 5275
Wire Wire Line
	8750 5275 9225 5275
Wire Wire Line
	8750 4850 8750 4625
Wire Wire Line
	8750 4625 8600 4625
Wire Wire Line
	8750 4625 9225 4625
Wire Wire Line
	9225 4625 9225 4650
Connection ~ 8750 4625
$Comp
L power:+5V #PWR025
U 1 1 5D0A9468
P 9650 4625
F 0 "#PWR025" H 9650 4475 50  0001 C CNN
F 1 "+5V" H 9665 4798 50  0000 C CNN
F 2 "" H 9650 4625 50  0001 C CNN
F 3 "" H 9650 4625 50  0001 C CNN
	1    9650 4625
	1    0    0    -1  
$EndComp
Wire Wire Line
	9750 4625 9650 4625
Wire Wire Line
	9225 4625 9650 4625
Connection ~ 9225 4625
Connection ~ 9650 4625
$Comp
L power:GND #PWR024
U 1 1 5D0B0F46
P 9600 4725
F 0 "#PWR024" H 9600 4475 50  0001 C CNN
F 1 "GND" H 9605 4552 50  0000 C CNN
F 2 "" H 9600 4725 50  0001 C CNN
F 3 "" H 9600 4725 50  0001 C CNN
	1    9600 4725
	1    0    0    -1  
$EndComp
Wire Wire Line
	9750 4725 9600 4725
Wire Wire Line
	8000 4625 7950 4625
Wire Wire Line
	7950 4625 7950 5550
Wire Wire Line
	7950 5550 9750 5550
Wire Wire Line
	9750 5550 9750 5225
$Comp
L power:+5V #PWR020
U 1 1 5D0CCDEC
P 9000 2775
F 0 "#PWR020" H 9000 2625 50  0001 C CNN
F 1 "+5V" H 9015 2948 50  0000 C CNN
F 2 "" H 9000 2775 50  0001 C CNN
F 3 "" H 9000 2775 50  0001 C CNN
	1    9000 2775
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR023
U 1 1 5D0CD86D
P 9325 2900
F 0 "#PWR023" H 9325 2650 50  0001 C CNN
F 1 "GND" H 9330 2727 50  0000 C CNN
F 2 "" H 9325 2900 50  0001 C CNN
F 3 "" H 9325 2900 50  0001 C CNN
	1    9325 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	9100 2775 9325 2775
Wire Wire Line
	9325 2775 9325 2900
Wire Notes Line
	7250 2375 11025 2375
Wire Notes Line
	11025 2375 11025 5900
Wire Notes Line
	11025 5900 7250 5900
Wire Notes Line
	7250 5900 7250 2375
Text Notes 8200 5850 0    118  ~ 0
L298N Motor Driver
Text Notes 9350 2000 0    118  ~ 0
SENSORES
$Comp
L power:GND #PWR010
U 1 1 5D0E1CC1
P 5675 4175
F 0 "#PWR010" H 5675 3925 50  0001 C CNN
F 1 "GND" V 5680 4047 50  0000 R CNN
F 2 "" H 5675 4175 50  0001 C CNN
F 3 "" H 5675 4175 50  0001 C CNN
	1    5675 4175
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5675 4175 5550 4175
$Comp
L power:+5V #PWR014
U 1 1 5D0EF581
P 6125 4250
F 0 "#PWR014" H 6125 4100 50  0001 C CNN
F 1 "+5V" H 6140 4423 50  0000 C CNN
F 2 "" H 6125 4250 50  0001 C CNN
F 3 "" H 6125 4250 50  0001 C CNN
	1    6125 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	5550 4275 6125 4275
Wire Wire Line
	6125 4275 6125 4250
$Comp
L Switch:SW_DIP_x01 SW1
U 1 1 5D0F64FA
P 3000 3375
F 0 "SW1" H 3000 3642 50  0000 C CNN
F 1 "SWITCH PRINCIPAL" H 3000 3551 50  0000 C CNN
F 2 "" H 3000 3375 50  0001 C CNN
F 3 "~" H 3000 3375 50  0001 C CNN
	1    3000 3375
	1    0    0    -1  
$EndComp
Wire Wire Line
	2425 3375 2700 3375
$Comp
L power:GND #PWR04
U 1 1 5D1042AF
P 2425 3850
F 0 "#PWR04" H 2425 3600 50  0001 C CNN
F 1 "GND" H 2430 3677 50  0000 C CNN
F 2 "" H 2425 3850 50  0001 C CNN
F 3 "" H 2425 3850 50  0001 C CNN
	1    2425 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2425 3775 2425 3850
Wire Wire Line
	3375 3375 3300 3375
Text GLabel 3375 3375 2    50   Input ~ 0
PSU
Text GLabel 10325 5225 2    50   Input ~ 0
PSU
Wire Wire Line
	10325 5225 9750 5225
Connection ~ 9750 5225
Wire Wire Line
	9750 5225 9750 4825
Text GLabel 3550 5175 0    50   Input ~ 0
SENS5
Wire Wire Line
	3800 5175 3550 5175
Text GLabel 3550 5075 0    50   Input ~ 0
SENS4
Wire Wire Line
	3800 5075 3550 5075
Text GLabel 3550 4975 0    50   Input ~ 0
SENS3
Wire Wire Line
	3800 4975 3550 4975
Text GLabel 3550 4875 0    50   Input ~ 0
SENS2
Wire Wire Line
	3800 4875 3550 4875
Text GLabel 3550 4775 0    50   Input ~ 0
SENS1
Wire Wire Line
	3800 4775 3550 4775
Text GLabel 3550 4675 0    50   Input ~ 0
SENS0
Wire Wire Line
	3800 4675 3550 4675
Text Label 3600 5275 0    50   ~ 0
IN1
Wire Wire Line
	3800 5275 3600 5275
Text Label 3600 5375 0    50   ~ 0
IN2
Wire Wire Line
	3800 5375 3600 5375
$Comp
L Device:D D3
U 1 1 5D1443D6
P 9525 3850
F 0 "D3" V 9479 3929 50  0000 L CNN
F 1 "D" V 9570 3929 50  0000 L CNN
F 2 "" H 9525 3850 50  0001 C CNN
F 3 "~" H 9525 3850 50  0001 C CNN
	1    9525 3850
	0    1    1    0   
$EndComp
$Comp
L Device:D D5
U 1 1 5D146251
P 9750 3850
F 0 "D5" V 9704 3929 50  0000 L CNN
F 1 "D" V 9795 3929 50  0000 L CNN
F 2 "" H 9750 3850 50  0001 C CNN
F 3 "~" H 9750 3850 50  0001 C CNN
	1    9750 3850
	0    1    1    0   
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J3
U 1 1 5D0BD45A
P 10425 3500
F 0 "J3" H 10505 3492 50  0000 L CNN
F 1 "Screw_01x02" H 10505 3401 50  0000 L CNN
F 2 "" H 10425 3500 50  0001 C CNN
F 3 "~" H 10425 3500 50  0001 C CNN
	1    10425 3500
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J2
U 1 1 5D03481F
P 10425 3275
F 0 "J2" H 10505 3267 50  0000 L CNN
F 1 "Screw_01x02" H 10505 3176 50  0000 L CNN
F 2 "" H 10425 3275 50  0001 C CNN
F 3 "~" H 10425 3275 50  0001 C CNN
	1    10425 3275
	1    0    0    -1  
$EndComp
Wire Wire Line
	9000 4125 9525 4125
Connection ~ 9000 4125
Wire Wire Line
	9000 4125 9000 4150
Wire Wire Line
	9525 4000 9525 4125
Connection ~ 9525 4125
$Comp
L Device:D D7
U 1 1 5D1763C9
P 9975 3850
F 0 "D7" V 9929 3929 50  0000 L CNN
F 1 "D" V 10020 3929 50  0000 L CNN
F 2 "" H 9975 3850 50  0001 C CNN
F 3 "~" H 9975 3850 50  0001 C CNN
	1    9975 3850
	0    1    1    0   
$EndComp
$Comp
L Device:D D9
U 1 1 5D1763CF
P 10200 3850
F 0 "D9" V 10154 3929 50  0000 L CNN
F 1 "D" V 10245 3929 50  0000 L CNN
F 2 "" H 10200 3850 50  0001 C CNN
F 3 "~" H 10200 3850 50  0001 C CNN
	1    10200 3850
	0    1    1    0   
$EndComp
Wire Wire Line
	10200 3700 10200 3600
Connection ~ 10200 3600
Wire Wire Line
	10200 3600 10225 3600
Wire Wire Line
	10200 4125 10200 4000
Wire Wire Line
	9975 4000 9975 4125
Connection ~ 9975 4125
Wire Wire Line
	9975 4125 10200 4125
Connection ~ 9975 3500
Wire Wire Line
	9975 3500 10225 3500
Wire Wire Line
	9525 4125 9750 4125
Wire Wire Line
	9750 4000 9750 4125
Connection ~ 9750 4125
Wire Wire Line
	9750 4125 9975 4125
Wire Wire Line
	9400 3375 9750 3375
Wire Wire Line
	9400 3275 9525 3275
Connection ~ 9750 3375
Wire Wire Line
	9750 3375 10225 3375
Wire Wire Line
	9525 3700 9525 3275
Connection ~ 9525 3275
Wire Wire Line
	9525 3275 10225 3275
Wire Wire Line
	9450 3500 9450 3475
Wire Wire Line
	9450 3475 9400 3475
Wire Wire Line
	9450 3500 9975 3500
Wire Wire Line
	9450 3600 9450 3575
Wire Wire Line
	9450 3575 9400 3575
Wire Wire Line
	9450 3600 10200 3600
$Comp
L Device:D D2
U 1 1 5D1C96C9
P 9525 2925
F 0 "D2" V 9479 3004 50  0000 L CNN
F 1 "D" V 9570 3004 50  0000 L CNN
F 2 "" H 9525 2925 50  0001 C CNN
F 3 "~" H 9525 2925 50  0001 C CNN
	1    9525 2925
	0    1    1    0   
$EndComp
$Comp
L Device:D D4
U 1 1 5D1C96CF
P 9750 2925
F 0 "D4" V 9704 3004 50  0000 L CNN
F 1 "D" V 9795 3004 50  0000 L CNN
F 2 "" H 9750 2925 50  0001 C CNN
F 3 "~" H 9750 2925 50  0001 C CNN
	1    9750 2925
	0    1    1    0   
$EndComp
$Comp
L Device:D D6
U 1 1 5D1C96D5
P 9975 2925
F 0 "D6" V 9929 3004 50  0000 L CNN
F 1 "D" V 10020 3004 50  0000 L CNN
F 2 "" H 9975 2925 50  0001 C CNN
F 3 "~" H 9975 2925 50  0001 C CNN
	1    9975 2925
	0    1    1    0   
$EndComp
$Comp
L Device:D D8
U 1 1 5D1C96DB
P 10200 2925
F 0 "D8" V 10154 3004 50  0000 L CNN
F 1 "D" V 10245 3004 50  0000 L CNN
F 2 "" H 10200 2925 50  0001 C CNN
F 3 "~" H 10200 2925 50  0001 C CNN
	1    10200 2925
	0    1    1    0   
$EndComp
Wire Wire Line
	9525 3075 9525 3275
Wire Wire Line
	9750 3700 9750 3375
Wire Wire Line
	9750 3075 9750 3375
Wire Wire Line
	9975 3700 9975 3500
Wire Wire Line
	9975 3075 9975 3500
Wire Wire Line
	10200 3075 10200 3600
Wire Wire Line
	10200 2775 10200 2700
Wire Wire Line
	10200 2700 9975 2700
Wire Wire Line
	9525 2700 9525 2775
Text GLabel 10450 2700 2    50   Input ~ 0
PSU
Wire Wire Line
	10200 2700 10450 2700
Connection ~ 10200 2700
Wire Wire Line
	9975 2775 9975 2700
Connection ~ 9975 2700
Wire Wire Line
	9975 2700 9750 2700
Wire Wire Line
	9750 2775 9750 2700
Connection ~ 9750 2700
Wire Wire Line
	9750 2700 9525 2700
Wire Wire Line
	8425 4125 8425 3675
Text Notes 10375 4050 0    50   ~ 0
Diodos Rápidos\nFR107
Text Label 8075 3100 0    50   ~ 0
ENB
Text Label 8075 3200 0    50   ~ 0
IN4
Text Label 8075 3300 0    50   ~ 0
IN3
Text Label 8075 3400 0    50   ~ 0
IN2
Text Label 8075 3500 0    50   ~ 0
IN1
Text Label 8075 3600 0    50   ~ 0
ENA
Text Label 3600 4275 0    50   ~ 0
IN3
Wire Wire Line
	3800 4275 3600 4275
Text Label 3600 4375 0    50   ~ 0
IN4
Wire Wire Line
	3800 4375 3600 4375
Text Label 3600 5475 0    50   ~ 0
ENA
Wire Wire Line
	3800 5475 3600 5475
Text Label 3600 5575 0    50   ~ 0
ENB
Wire Wire Line
	3800 5575 3600 5575
$Comp
L MCU_ST_STM32F1:STM32F103C8Tx U?
U 1 1 5CFF0796
P 1475 4625
F 0 "U?" H 1425 3036 50  0000 C CNN
F 1 "STM32F103C8Tx" H 1425 2945 50  0000 C CNN
F 2 "Package_QFP:LQFP-48_7x7mm_P0.5mm" H 875 3225 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/CD00161566.pdf" H 1475 4625 50  0001 C CNN
	1    1475 4625
	1    0    0    -1  
$EndComp
$EndSCHEMATC
