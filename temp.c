#include <temp.h>
#include "biblioteca\mod_lcd.c"


char grau = 223;                           //  Pega o simbolo "º", grau

float temperatura_Atual = 0.0,
      temperatura_Antiga = 0.0,
      Disturbio = 0;
      
double ref,                                // Referencia desejada
       error,                              // Diferenca entre temperatura desejada e temperatura atual
       kP = 70,
       kI = 2,
       kD = 0,
       P, I, D,
       pid;
      
       
       
       
double process(){
// Implementação PID
//Proporcional
P = error * kP;
//Integrador
I = I + (error * kI);
//Derivador
D = (temperatura_Antiga - temperatura_Atual) * kD;
temperatura_Antiga = temperatura_Atual;
// Soma tudo
pid = P + I + D;

return pid;
}

void main(){

   setup_adc(ADC_CLOCK_DIV_16);                       // ADC Module uses its internal oscillator
   setup_adc_ports(AN0_AN1_AN2_AN3_AN4);              // Configuracao de portas analogicas
   
   enable_interrupts(INT_RTCC);
   enable_interrupts(GLOBAL);

   setup_timer_2(T2_DIV_BY_16,255,1);      //819 us overflow, 819 us interrupt 255+1 = 256 *4 = 1024

   setup_ccp1(CCP_PWM);                    // Configura a porta CCP1 como PWM
   setup_ccp2(CCP_PWM);                    // Configura a porta CCP2 como PWM
      
   lcd_ini();        // Inicializa LCD
   delay_ms(10);

  
   while(TRUE) {

      set_adc_channel(0);                                    // Seleciona o canal ANA0
      delay_ms(10);                                          // Tempo para ativacao
      ref = read_adc() * 0.0489 + 20;                        // Pega a leitura do ANA0
      
      set_adc_channel(2);
      delay_ms(10);
      temperatura_Atual = ((read_adc() * 5)/1023.0)/0.010;
      if (temperatura_Atual >=1) {
      
      error = ref - temperatura_Atual;

      process();

      if(pid>1023) { pid=1023; } else if (pid<=0) { pid=0; }
      if (error >0) { set_pwm2_duty((int16)pid); }
      
      else if (error <=0) { set_pwm2_duty(0); }
           
      set_adc_channel(1);
      delay_ms(10);
      disturbio = read_adc();

      SET_PWM1_DUTY((int16) disturbio);    
                                                                            // Escreve na Tela
      printf (lcd_escreve,"\fTemp= %f %cC",temperatura_Atual, grau);        // Temperatura
      printf (lcd_escreve,"\n\rRef= %f %cC",ref, grau);                     // Referencia
      delay_ms(1000);
      
      
      }
   } // While

} // Main


