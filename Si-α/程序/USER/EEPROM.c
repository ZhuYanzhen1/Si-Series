#include "intrins.h"
#include "EEPROM.h"
#include "STC12.h"

#define   CMD_IDLE      0                 //Stand-By
#define   CMD_READ      1                 //Byte-Read
#define   CMD_PROGRAM   2                 //Byte-Program
#define   CMD_ERASE     3                 //Sector-Erase
#define   ENABLE_IAP    0x82              //if SYSCLK<20MHz
#define   IAP_ADDRESS   0x0000
#define      USING_CHAR_NUM   40

void IapIdle();
unsigned char IapReadunsigned (unsigned int addr);
void IapProgramunsigned(unsigned int addr, unsigned char dat);
void IapEraseSector(unsigned int addr);

unsigned char EepromReadByte(unsigned char addr)
{
    return(IapReadunsigned(addr));
}

void EepromWriteByte(unsigned char addr, unsigned char dat)
{
    unsigned char eepromBUF[USING_CHAR_NUM];
    unsigned char i;
    for(i=0; i< USING_CHAR_NUM; i++)
    {
        eepromBUF[IAP_ADDRESS+i] = IapReadunsigned(IAP_ADDRESS+i);   
    }
    if(addr < USING_CHAR_NUM)
    {
        eepromBUF[IAP_ADDRESS+addr] = dat;
        IapEraseSector(IAP_ADDRESS);

        for(i=0; i< USING_CHAR_NUM; i++)
        {
            IapProgramunsigned(IAP_ADDRESS+i, eepromBUF[IAP_ADDRESS+i]);   
        }
    }
}
void IapIdle()
{
      IAP_CONTR = 0;      //Close IAP function
      IAP_CMD = 0;            //Clear command to standby
      IAP_TRIG = 0;                      //Clear trigger register
      IAP_ADDRH = 0x80;                 //Data ptr point to non-EEPROM area
      IAP_ADDRL = 0;                     //Clear IAP address to prevent misuse
}

unsigned char IapReadunsigned(unsigned int addr)
{
      unsigned char dat;                          //Data buffer
      IAP_CONTR = ENABLE_IAP;   //Open IAP function, and set wait time
      IAP_CMD = CMD_READ;        //Set ISP/IAP/EEPROM READ command
      IAP_ADDRL = addr;                 //Set ISP/IAP/EEPROM address low
      IAP_ADDRH = addr >> 8;      //Set ISP/IAP/EEPROM address high
      IAP_TRIG = 0x5a;                //Send trigger command1 (0x5a)
      IAP_TRIG = 0xa5;                  //Send trigger command2 (0xa5)
      _nop_();  _nop_();                          //MCU will hold here until ISP/IAP/EEPROM
      dat = IAP_DATA;            //Read ISP/IAP/EEPROM data
      IapIdle();                         //Close ISP/IAP/EEPROM function
      return dat;                        //Return Flash data
}

void IapProgramunsigned(unsigned int addr, unsigned char dat)
{
      IAP_CONTR = ENABLE_IAP;         //Open IAP function, and set wait time
      IAP_CMD = CMD_PROGRAM;     //Set ISP/IAP/EEPROM PROGRAM command
      IAP_ADDRL = addr;                 //Set ISP/IAP/EEPROM address low
      IAP_ADDRH = addr >> 8;            //Set ISP/IAP/EEPROM address high
      IAP_DATA = dat;                  //Write ISP/IAP/EEPROM data
      IAP_TRIG = 0x5a;                   //Send trigger command1 (0x5a)
      IAP_TRIG = 0xa5;                   //Send trigger command2 (0xa5)
      _nop_();   _nop_();                        //MCU will hold here until ISP/IAP/EEPROM
      IapIdle();
}
void IapEraseSector(unsigned int addr)
{
      IAP_CONTR = ENABLE_IAP;  //Open IAP function, and set wait time
      IAP_CMD = CMD_ERASE;      //Set ISP/IAP/EEPROM ERASE command
      IAP_ADDRL = addr;                //Set ISP/IAP/EEPROM address low
      IAP_ADDRH = addr >> 8;         //Set ISP/IAP/EEPROM address high
      IAP_TRIG = 0x5a;                   //Send trigger command1 (0x5a)
      IAP_TRIG = 0xa5;                   //Send trigger command2 (0xa5)
      _nop_();  _nop_();                         //MCU will hold here until ISP/IAP/EEPROM
      IapIdle();
}