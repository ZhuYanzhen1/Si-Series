#ifndef __EEPROM_H__
#define __EEPROM_H__
//STC12C5A60S2的EEPROM有1KB，两个扇区
//第一个扇区起始地址:0x0000~0x01ff<0~511>(共512字节)
//第二个扇区起始地址:0x0200~0x03ff<512~1023>(共512字节)
unsigned char EepromReadByte(unsigned char addr);
void EepromWriteByte(unsigned char addr, unsigned char dat);
#endif
