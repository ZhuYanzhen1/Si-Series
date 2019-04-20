#ifndef _LCD1602_H_
#define _LCD1602_H_
void LCD1602_SendString(unsigned char *s);
void LCD1602_Writecom(unsigned char com);
void LCD1602_Writedat(unsigned char dat);
void LCD1602_Init();
#endif