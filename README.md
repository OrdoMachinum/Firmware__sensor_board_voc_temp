Firmware for the VOC, Humidity and Temperature Sensor board
![image](https://github.com/user-attachments/assets/d9b4a7d3-f43b-4157-8e6d-75f16bc7cfdf)


# Current usage:
After initial, and heat-up state, the device accept a '?' character on uart, after this it should return 2x2x2 byte information in the format below. Full zero bytes mean that the relevant device is not available. 

From th SHT4x sensor:  
+ Temperature Tick MSB
+ Temperature Tick LSB
+ Relative Humidity MSB
+ Relative Humidity LSB

From the SGP41 sensor:  
+ VOC Tick MSB
+ VOC Tick LSB
+ NOx Tick MSB
+ NOx Tick LSB  

# Current UART communication parameters:
+ speed: 9600
+ data bits: 8
+ stop bits: 1
+ parity: none
