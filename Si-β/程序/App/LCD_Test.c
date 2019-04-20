#include "lcd.h"
#include "stm32f10x_it.h"
#include "gui.h"
#include "LCD_Test.h"
#include "Picture.h"
//========================variable==========================//
u16 ColorTab[5]={BRED,YELLOW,RED,GREEN,BLUE};//∂®“Â—’…´ ˝◊È
//=====================end of variable======================//
void DrawTestPage(u8 *str)
{
	LCD_Fill(0,0,lcddev.width,20,BLUE);
	LCD_Fill(0,lcddev.height-20,lcddev.width,lcddev.height,BLUE);
	POINT_COLOR=WHITE;
	Gui_StrCenter(0,2,WHITE,BLUE,str,16,1);//æ”÷–œ‘ æ
	Gui_StrCenter(0,lcddev.height-18,WHITE,BLUE,"Si∞Ê»®À˘”–",16,1);//æ”÷–œ‘ æ
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,BLACK);
}
void main_test(void)
{
	DrawTestPage("LCD◊€∫œ≤‚ ‘≥Ã–Ú");
	Gui_StrCenter(0,60,RED,BLUE,"◊€∫œ≤‚ ‘≥Ã–Ú",16,1);//æ”÷–œ‘ æ	
	Gui_StrCenter(0,90,YELLOW,BLUE,"3.5' ILI9486 320X480",16,1);//æ”÷–œ‘ æ
	Gui_StrCenter(0,120,BLUE,BLUE,"ZYZ Tech 2018-08-22",24,1);//æ”÷–œ‘ æ
	Delayms(1500);
}
void Test_Color(void)
{
	DrawTestPage("≤‚ ‘1:¥ø…´ÃÓ≥‰≤‚ ‘");
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
	Show_Str(lcddev.width-50,30,BLUE,YELLOW,"White",16,1);Delayms(500);
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,BLACK);
	Show_Str(lcddev.width-50,30,BLUE,YELLOW,"Black",16,1);Delayms(500);
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,RED);
	Show_Str(lcddev.width-50,30,BLUE,YELLOW,"Red",16,1); Delayms(500);
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,GREEN);
	Show_Str(lcddev.width-50,30,BLUE,YELLOW,"Green",16,1);Delayms(500);
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,BLUE);
	Show_Str(lcddev.width-50,30,WHITE,YELLOW,"Blue",16,1);Delayms(500);

}
void Test_FillRec(void)
{
	u8 i=0;
	DrawTestPage("≤‚ ‘2:GUIæÿ–ŒÃÓ≥‰≤‚ ‘");
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
	for (i=0; i<5; i++) 
	{
		LCD_DrawRectangle(lcddev.width/2-80+(i*15),lcddev.height/2-80+(i*15),lcddev.width/2-80+(i*15)+60,lcddev.height/2-80+(i*15)+60); 
		POINT_COLOR=ColorTab[i];
	}
	Delayms(1500);	
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE); 
	for (i=0; i<5; i++) 
	{
		LCD_Fill(lcddev.width/2-80+(i*15),lcddev.height/2-80+(i*15),lcddev.width/2-80+(i*15)+60,lcddev.height/2-80+(i*15)+60,POINT_COLOR); 
		POINT_COLOR=ColorTab[i];
	}
	Delayms(1500);
}
void Test_Circle(void)
{
	u8 i=0;
	DrawTestPage("≤‚ ‘3:GUIª≠‘≤ÃÓ≥‰≤‚ ‘");
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
	for (i=0; i<5; i++)  
		gui_circle(lcddev.width/2-80+(i*25),lcddev.height/2-50+(i*25),ColorTab[i],30,0);
	Delayms(1500);	
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE); 
	for (i=0; i<5; i++) 
	  	gui_circle(lcddev.width/2-80+(i*25),lcddev.height/2-50+(i*25),ColorTab[i],30,1);
	Delayms(1500);
}
void English_Font_test(void)
{
	DrawTestPage("≤‚ ‘4:”¢Œƒœ‘ æ≤‚ ‘");
	POINT_COLOR=RED;
	BACK_COLOR=BLUE;
	LCD_ShowString(10,30,12,"6X12:abcdefghijklmnopqrstuvwxyz0123456789",0);
	LCD_ShowString(10,45,12,"6X12:ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789",1);
	LCD_ShowString(10,60,12,"6X12:~!@#$%^&*()_+{}:<>?/|-+.",0);
	LCD_ShowString(10,80,16,"8X16:abcdefghijklmnopqrstuvwxyz0123456789",0);
	LCD_ShowString(10,100,16,"8X16:ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789",1);
	LCD_ShowString(10,120,16,"8X16:~!@#$%^&*()_+{}:<>?/|-+.",0); 
	Show_Str(50,200,WHITE,WHITE,"Test",12,1);
	Delayms(1200);
}
void Chinese_Font_test(void)
{	
	DrawTestPage("≤‚ ‘5:÷–Œƒœ‘ æ≤‚ ‘");
	Show_Str(75,50,BLUE,YELLOW," ±”Ø“∞",32,1);
	Show_Str(50,100,BLUE,YELLOW,"÷Ï—Â’È÷∆◊˜",32,1);
	Delayms(1000);
	Delayms(1000);
}
void Pic_test(void)
{
	DrawTestPage("≤‚ ‘6:Õº∆¨œ‘ æ≤‚ ‘");
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
	Gui_Drawbmp16(30,50,gImage_Develope,200,200);
	Delayms(1000);
	Delayms(1000);
}
