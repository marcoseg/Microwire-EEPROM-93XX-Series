/*
 * Read / Wirte Library for 16-Kbit, 8-Kbit, 4-Kbit, 2-Kbit and 1-Kbit (8-bit or 16-bit wide) MICROWIRE™
 * serial access EEPROM 93 Series
 * This sketch wirtes a string and show the content into the memory
 * The Circuit:
 * Pin 2 Chip Select CS
 * Pin 3 Clock       CLK  
 * Pin 4 Data Input  DI on chip
 * Pin 5 Data Output DO on chip
 * Written by Marcos Guardia 04/24/2023
 */
#include <93LCXX.h>


Microwire Mem1;

void setup() {
  Serial.begin(9600);
  Mem1.setup(2,3,4,5);    // pins to be used where cs = 2,clk = 3, di 4 (on chip), dout 5 (on chip)
  Mem1.config(46,16);    // Memory model 46 and Mode 16 bits
  Mem1.wen();  
  Mem1.eraseall();
String TestMemory = "Is working silky smooth";

for(int i =0; i< 64;i++){
  Mem1.write(i,TestMemory[i]);
}
Serial.println ("\t\t\tMemory Values");

 for(int base = 0;base < 64;base +=16){
    uint16_t MemLoc[16];
    for(int offset = 0; offset <=15; offset++){
      MemLoc[offset]= Mem1.read(base + offset );
    }
    char buff[80];
    sprintf(buff,"%02x:  %02x %02x %02x %02x %02x %02x %02x %02x   %02x %02x %02x %02x %02x %02x %02x %02x",
            base, MemLoc[0], MemLoc[1], MemLoc[2], MemLoc[3], MemLoc[4], MemLoc[5], MemLoc[6], MemLoc[7],
            MemLoc[8], MemLoc[9], MemLoc[10], MemLoc[11], MemLoc[12], MemLoc[13], MemLoc[14], MemLoc[15]);
  
   Serial.println(buff);
  }
 
}


void loop() {
  // put your main code here, to run repeatedly:
}
