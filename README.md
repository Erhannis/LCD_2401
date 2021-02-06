Controller code for the WD-C2401P-1GNN, and probably similar models.  Bought a small pile of them for $0.50 each from https://www.allelectronics.com/item/lcd-111/24-x-1-lcd-incredible-price/1.html

Code is a slightly modified version of dirty_valentine's post at https://forum.arduino.cc/index.php?topic=78002.msg705823#msg705823

As described in the header, plug GND and VCC to GND and 5v, then the rest to gpio 13 and down.

Notes, things that tripped me up, to the best of my knowledge:
Pins are 5v.  (ESP8266 and Raspberry Pi emit 3.3v ; ATMEGA2560 (maybe arduinos in general?) emit 5v.)
RESET needs to be pulled low for a few ms, then pulled high and left there.  (The code does this in Initialize().)  (At least, I think it's important.  Getting conflicting evidence.)
R/W needs to be pulled low.  (Presumably if you wanted to read you'd pull it high?)  (The code does this in Initialize().)

The original author didn't mention a license, so I'm going to make an assumption and release this under Apache 2.0 - except for the PDF, that probably belongs to a company.

-Erhannis