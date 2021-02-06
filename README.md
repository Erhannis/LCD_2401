Controller code for the WD-C2401P-1GNN, and probably similar models.  Bought a small pile of them for $0.50 each from https://www.allelectronics.com/item/lcd-111/24-x-1-lcd-incredible-price/1.html  
  
![lcd connected to arduino](https://github.com/Erhannis/LCD_2401/blob/master/images/20210205_122543.jpg)  
  
Code is a slightly modified version of dirty_valentine's post at https://forum.arduino.cc/index.php?topic=78002.msg705823#msg705823  
  
Here are basically all the relevant links I know:  
https://web.archive.org/web/20111020231316/http://www.serialwombat.com/parts/lcd111.htm  
https://web.archive.org/web/20120310103945/http://www.serialwombat.com/channel_mode_lcd111.htm  
https://forum.arduino.cc/index.php?topic=78002  
https://forum.arduino.cc/index.php?topic=206577.0  
  
The first of those links suggests that to connect to the pins, you bend them out alternating directions, to make them easier to connect to.  Then tin your wires, tin the pins, and solder them together.  
  
As described in the header, plug GND and VCC to GND and 5v, then the rest to gpio 13 and down.  
  
Notes, things that tripped me up, to the best of my knowledge:  
Pins are 5v.  (ESP8266 and Raspberry Pi emit 3.3v ; ATMEGA2560 (maybe arduinos in general?) emit 5v.)  
RESET needs to be pulled low for a few ms, then pulled high and left there.  (The code does this in Initialize().)  (At least, I think it's important.  Getting conflicting evidence.)  
R/W needs to be pulled low.  (Presumably if you wanted to read you'd pull it high?)  (The code does this in Initialize().)  
See images/ for pictures of the setup.  
  
The original author didn't mention a license, so I'm going to make an assumption and release this under Apache 2.0 - except for the PDF, that probably belongs to a company.  
  
-Erhannis