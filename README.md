# Microwire-EEPORM-93XX-Series
A complete library to use Microwire™  93XX EEPROM memories from  93X46 to 93X86 in 8 or 16 bit data mode
# 93CXX Library for Arduino

 Read / Wirte Library for 16-Kbit, 8-Kbit, 4-Kbit, 2-Kbit and 1-Kbit (8-bit or 16-bit wide) MICROWIRE™
 ST M93C46-x 
[Product overview](https://www.st.com/en/memories/m93c86-r.html#overview)

## Introduction

"The 93CXX series are 16-Kbit(86), 8-Kbit(76), 4-Kbit(66), 2-Kbit(56) and 1-Kbit(46)  electrically
erasable programmable memory (EEPROM) devices accessed through the MICROWIRE™ bus protocol. The
memory array can be configured either in bytes (x8b) or in words (x16b)."


## Methods

| Method |  Description |
| ------ | ------ |
| `Microwire name` | Constructor / Instance |
| `setup(cs_clk,di,do)` |  Select the interface pins |
| `wen()` | Enables Write, Erase and (Erase all) commands|
| `wdis()`| Disables Write, Erase and (Erase all) commands  |
| `eraseall()` | Erase all memory locations, all memory bits are set to  `1` |
| `writeall(word value)` | Write all memory locations to the provided value |
| `write(word address, word value)` | Write in specific location the value given  |
| `erase(word address)` | Change memory location to `0xFFFF`|
| `read(word address)` | Returns the value of the provided memory location|
