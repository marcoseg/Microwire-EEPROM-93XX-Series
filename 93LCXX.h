#ifndef _93LCXX_H_
#define _93LCXX_H_
#include <Arduino.h>



class Microwire{

    public:
        Microwire();
        ~Microwire();
        void setup(uint8_t cs, uint8_t clk,uint8_t din,uint8_t dout);
        void config(uint8_t number, uint8_t format);
        uint16_t read(uint8_t address);
        void wen();
        void write(uint16_t address, uint16_t data);
        void wrall(uint16_t data);
        void wrdis();
        void erase(uint16_t address);
        void eraseall();
        
        

    private:
// Commands  for 93 Series from 46 to 86 mode 8 or 16 Bits
        uint16_t READ;
        uint16_t WEN;
        uint16_t ERASE;
        uint16_t WRITE;
        uint16_t ERAL;
        uint16_t WRALL;
        uint16_t WDIS;
        

 // Pins used and general register       
        uint8_t _cs_pin;
        uint8_t _clk_pin;
        uint8_t _din_pin;
        uint8_t _dout_pin;
        uint8_t _adrress;
        uint16_t _data;
        uint8_t _data_low;
        uint8_t _bit_number;
        uint8_t _capacity;
        uint8_t _insBit;
        uint8_t _modeBits;
 // shiftOut Modified to send any amount of bits using different MASK       
        void sendBits(uint8_t,uint8_t,uint16_t,uint8_t);
        uint16_t recivedBits(uint8_t,uint8_t,uint8_t);
        uint16_t MASK;
    protected:
    
};


#endif // _93LCXX_H_