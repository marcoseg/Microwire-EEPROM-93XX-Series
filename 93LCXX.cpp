#include <93LCXX.h>


Microwire::Microwire()
{
     
}

Microwire::~Microwire()
{
    
}


void Microwire::setup(uint8_t cs, uint8_t clk,uint8_t din,uint8_t dout)
{
    _cs_pin = cs;
    _clk_pin = clk;
    _din_pin = din;
    _dout_pin = dout;
    pinMode(_cs_pin,OUTPUT);
    pinMode(_clk_pin,OUTPUT);
    pinMode(_din_pin,OUTPUT);   // data input on chip
    pinMode(_dout_pin,INPUT);   // data output on chip
    digitalWrite(_cs_pin,LOW);

}

void Microwire::config(uint8_t number, uint8_t format)
{
    _bit_number=number;
    _capacity=format;

    switch (number)
    {
    case 46:
        switch (format)
        {
        case 8:
        READ = 0x300;     
        WEN = 0x260; 
        ERASE = 0x380; 
        WRITE = 0x280;
        ERAL = 0x240; 
        WRALL = 0x220; 
        WDIS = 0x200;
            _insBit=10;
            _modeBits=8;
            break;
        case 16:
        READ = 0x180;     
        WEN = 0x130; 
        ERASE = 0x1C0; 
        WRITE = 0x140;
        ERAL = 0x120; 
        WRALL = 0x110; 
        WDIS = 0x100;
        _insBit = 9;
        _modeBits=16;
            break;
        }
        break;
    case 56:  
    case 66:
        switch (format)
        {
        case 8:
        READ = 0xC00;     
        WEN = 0x980; 
        ERASE = 0xE00;
        WRITE = 0xA00;
        ERAL = 0x900;
        WRALL = 0x880; 
        WDIS = 0x800;
            _insBit=12;
            _modeBits=8;
            break;
        case 16:
        READ = 0x600;     
        WEN = 0x4C0; 
        ERASE = 0x700;
        WRITE = 0x500;
        ERAL = 0x480; 
        WRALL = 0x440; 
        WDIS = 0x400;
            _insBit=12;
            _modeBits=16;
            break;
        }
        break;
    case 76:
    case 86:
        switch (format)
        {
        case 8:
        READ = 0x3000;    
        WEN = 0x2600; 
        ERASE = 0x3800; 
        WRITE = 0x2800;
        ERAL = 0x2400; 
        WRALL = 0x2200; 
        WDIS = 0x2000;
            _insBit=14;
            _modeBits=8;
            break;
        case 16:
        READ = 0x1800;     
        WEN = 0x1300;
        ERASE = 0x1C00;
        WRITE = 0x1400;
        ERAL = 0x1200; 
        WRALL = 0x1100; 
        WDIS = 0x1000;
            _insBit=13;
            _modeBits=16;
            break;
        }
        break;
    default:
        break;
    }
}


uint16_t Microwire::read(uint8_t address)
{ 
    
    digitalWrite(_cs_pin,HIGH);
    delayMicroseconds(5);
    sendBits(_din_pin,_clk_pin,(READ + address),_insBit);
    _data = recivedBits(_dout_pin,_clk_pin,_modeBits);
    digitalWrite(_cs_pin,LOW);  
    return _data;  
}

void Microwire::wen()
{
    digitalWrite(_cs_pin,HIGH);
    delayMicroseconds(5);
    sendBits(_din_pin,_clk_pin,WEN,_insBit);
    digitalWrite(_cs_pin,LOW);

}

void Microwire::write(uint16_t address, uint16_t data)
{
    digitalWrite(_cs_pin,HIGH);
    delayMicroseconds(5);
    sendBits(_din_pin,_clk_pin,(WRITE + address),_insBit);
    sendBits(_din_pin,_clk_pin,data,_modeBits);
    digitalWrite(_cs_pin,LOW);
    delay(30);
}

void Microwire::wrall(uint16_t data)
{
    digitalWrite(_cs_pin,HIGH);
    delayMicroseconds(5);
    sendBits(_din_pin,_clk_pin,WRALL,_insBit);
    sendBits(_din_pin,_clk_pin,data,_modeBits);
    digitalWrite(_cs_pin,LOW);
    delay(40);
}

void Microwire::wrdis()
{
    digitalWrite(_cs_pin,HIGH);
    delayMicroseconds(5);
    sendBits(_din_pin,_clk_pin,WDIS,_insBit);
    digitalWrite(_cs_pin,LOW);
}

void Microwire::erase(uint16_t address)
{
    digitalWrite(_cs_pin,HIGH);
    delayMicroseconds(5);
    sendBits(_din_pin,_clk_pin,(ERASE + address),_insBit);
    digitalWrite(_cs_pin,LOW);
    delay(15);
}

void Microwire::eraseall()
{
    digitalWrite(_cs_pin,HIGH);
    delayMicroseconds(5);
    sendBits(_din_pin,_clk_pin,ERAL,_insBit);
    digitalWrite(_cs_pin,LOW);
    delay(25);
}


void Microwire::sendBits(uint8_t dataPin,uint8_t clk,uint16_t value,uint8_t nbits)
{ // Sending n Bits dependig size with variable MASK
    digitalWrite(_clk_pin,LOW);
switch (nbits)
{
    case 8:
        MASK=0x0080;
    break;
    case 9:
        MASK=0x0100;
    break;
     case 10:
        MASK=0x0200;
    break;
     case 11:
        MASK=0x0400;
    break;
     case 12:
        MASK=0x0800;
    break;
    case 16:
        MASK=0x8000;
    break;
}

     for (int i = 0; i < nbits; i++){
        digitalWrite(dataPin, (value & MASK) !=0);
        value<<=1;
        digitalWrite(clk,HIGH);
        digitalWrite(clk,LOW);
    } 
    
}

uint16_t Microwire::recivedBits(uint8_t dataPin,uint8_t clk,uint8_t nbits)
{   uint16_t value = 0x0000;   
        for(int i = 1; i <= nbits; i++ ){
            digitalWrite(clk,HIGH);
            value |= digitalRead(dataPin) << (nbits - i);
            digitalWrite(clk,LOW);
        }
        
    return value;
}
