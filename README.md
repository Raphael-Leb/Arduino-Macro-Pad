# Arduino Macro Pad
 A small macropad programmed using arduino featuring programmable key sets, a knob and an oled screed

## Features
- Xiao rp2040 microcontroller
- Cherry mx keys
- An oled screen displaying the shortcuts set
- A clickable rotary encoder knob

  ![20230922_190033](https://github.com/Raphael-Leb/Arduino-Macro-Pad/assets/62116334/0a234013-a7b2-4195-a0a8-cbfd1a02daa2)

![20230922_190054](https://github.com/Raphael-Leb/Arduino-Macro-Pad/assets/62116334/3b6c9ba4-99dc-485f-8493-ff87f12477cb)

## Design
### PCB
The pcb was made using kicad, the design files are in Mainpad/PCBfiles.
 *The keys are not organised properly, they need to be rearanged to match with the schematic. The keys are also not spaced enough for regular keycaps*
The gerber files are in Mainpad/ProdFiles, these should be all you need to produce more copies if you are unexperienced with pcb software
![image](https://github.com/Raphael-Leb/Arduino-Macro-Pad/assets/62116334/0b677f26-b157-48f2-9d50-37d034ec1afd)
![image](https://github.com/Raphael-Leb/Arduino-Macro-Pad/assets/62116334/75c25d1b-7260-46d9-bd6b-c0ee0f1ee455)

### Software
The entire software is made with arduino, the firmware_2040.ino contains the logic and the pins.h contains the configuration for configuring layout as well as shortcuts.
I tried to make this with a xiao esp32c3, but couldn't get the bluetooth keyboard and bluetooth mouse library working at simultanuously, so let me know if you find a fix. For now this will only work as a wired keypad.
*I will be making a frontend for configuring the pins.h in the near future.*

### Casing
The casing was made in solidworks with several models I found on grabcad. 
I had to make custom keycaps because the keys were too close together to fit standard caps, I followed the footprint's spacing but should've double checked if it was correct.
I first modeled a casing with the pcb tilted upward to fit the angle of my keyboard, but then decided on making it flat instead. The files are still there if that's what you prefer, but they are incomplete.
Initialy tried to make a press fit casing, but spacing proved to be quite a pain to nail down considering how 3d printed plastic warps. I used 6 m3 screws to secure everything.
![image](https://github.com/Raphael-Leb/Arduino-Macro-Pad/assets/62116334/5a00618b-a451-4685-b815-9650acbdede7)

### Parts
| Part   | Link | Amount |
| -------- | ------- | ------- |
| Cherry switch  | https://www.digikey.ca/en/products/detail/cherry-americas-llc/MX1A-E1NW/20180    | 8 |
| Rotary encoder | https://www.digikey.ca/en/products/detail/bourns-inc/PEC11R-4215K-S0024/4499662     | 1 |
| Diodes    | https://www.digikey.ca/en/products/detail/smc-diode-solutions/1N4148/6022448    | 8 |
| rp2040    | https://www.digikey.ca/en/products/detail/seeed-technology-co-ltd/102010428/14672129   | 1 |
| screen    | https://www.amazon.ca/GeeekPi-SSD1306-Display-Arduino-Raspberry/dp/B0833PF7ML/ref=sr_1_2?crid=A12OUYH5RILN&keywords=ssd1306&qid=1695136173&sprefix=ssd130%2Caps%2C130&sr=8-2   | 1 |
