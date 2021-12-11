#include <16F877A.h>
#device ADC=10


#FUSES NOWDT                  //No Watch Dog Timer
#FUSES HS                     //High speed Osc (> 4mhz for PCM/PCH) (>10mhz for PCD)
#FUSES NOPUT                  //No Power Up Timer
#FUSES NOPROTECT              //Code not protected from reading
#FUSES NODEBUG                //No Debug mode for ICD
#FUSES NOBROWNOUT             //No brownout reset
#FUSES NOLVP                  //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                  //No EE protection
#FUSES NOWRT                  //Program memory not write protected

#use delay(crystal=20000000)

#ifndef lcd_enable
   #define lcd_enable     pin_e1      // pino enable do LCD
   #define lcd_rs         pin_e2      // pino rs do LCD
   //#define lcd_rw       pin_e2      // pino rw do LCD
   #define lcd_d4         pin_d4      // pino de dados d4 do LCD
   #define lcd_d5         pin_d5      // pino de dados d5 do LCD
   #define lcd_d6         pin_d6      // pino de dados d6 do LCD
   #define lcd_d7         pin_d7      // pino de dados d7 do LCD
#endif





/*    Pinagem

Heater = Resistencia
Cooler = Ventoinha

A porta CCP1 é a mesma porta do C2
A porta CCP2 é a mesma porta do C1

C1 = Resistencia no PicSimLab para utilizar o PWM 
C2 = Ventoinha
C5 = Resistencia


ANA0 = Potenciometro 1
ANA1 = Potenciometro 2
ANA2 = LM-35 leitura da temperatura


*/

