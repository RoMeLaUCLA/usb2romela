# USB2RoMeLa RS-485 USB Adapter

USB2RoMeLa Boosted is a low latency USB to RS-485 adapter. FT232H is used for USB to serial conversion. STM32 intercepts data packets and signals FT232H whenever a complete data packet is received, lowering roundtrip communication latency.
Packet acceleration is designed around Dynamixel communication protocols. 

# Usage

## Baudrate setting

<img src="/docs/baud_setting.jpg" height="200">

## Terminal resistor setting

<img src="/docs/terminal_resistor_setting.jpg" height="200">

## Startup code
 - Flash 2 times: 8Mbps
 - Flash 3 times: 3Mbps
## Error code 
 - Flash 1 time: Packet Timeout
 - Flash 2 times: Checksum Error
 - Flash 3 times: UART Error

# PCB reference

<img src="/docs/pcb_reference.jpg" height="500">

[Link to schematics](/pcb/USB2RoMeLa_Boosted_rev2_1.pdf)

# Latency test

<img src="/docs/usb_latency.jpg" height="350">

# Folder structure

cad: 3D CAD files and render.

firmware: STM32 firmware with STM32CubeIDE project. \
firmware\Bin: binary file of compiled firmware.

pcb: PCB design files(KiCAD) and schematics. \
pcb\BOM: Bill of Materials. \
pcb\Gerber: PCB mfg files.

tools\ftdi-template: template to use when programing FT232H using FT_Prog.

tools\programming-interface-pcb: PCB design files for interface board with castellation. 

