/*
 Autor: José Amezcua
 Repositorio - Control de leds por Dip Protolink EX
 
 * Pines Leds: PIN_B0,PIN_B1,PIN_E5,PIN_E4
 * Pines Dip: PIN_F0, PIN_F1, PIN_F2, PIN_F3
 * Pines serial: PIN_E2, PIN_E3
 
 * Mapeo realizado por excore.h
 
 UART
 #define TX_5        PIN_E2
 #define RX_5        PIN_E3

 DIP
 #define ADDR0       PIN_F0
 #define ADDR1       PIN_F1
 #define ADDR2       PIN_F2
 #define ADDR3       PIN_F3

 Leds
 #define GPIO_1      PIN_B0
 #define GPIO_2      PIN_B1
 #define GPIO_3      PIN_E5
 #define GPIO_4      PIN_E4
 */

#include "../protolink/excore.h"
#include <bootloader.h>
#include <stdio.h>
#include <stdlib.h>

int dip;
int8 bin[4];

/*
 
 El "~" se usa para negar el comportamiento del Switch (NOT).
 
 El uso de 0x0F (binario 00001111) funciona como una máscara de bits que filtra
 el puerto para obtener únicamente los 4 bits menos significativos
 */

void lectura(){
      dip = (input_f()) & 0x0F;
 //   dip = (~input_f()) & 0x0F;
}

void control_leds(){
    switch (dip){
      case 1:  
       output_high(GPIO_1);
       output_low(GPIO_2);
       output_low(GPIO_3);
       output_low(GPIO_4);
       break;  

      case 2:  
       output_low(GPIO_1);
       output_high(GPIO_2);
       output_low(GPIO_3);
       output_low(GPIO_4);
       break;  

      case 3:  
       output_high(GPIO_1);
       output_high(GPIO_2);
       output_low(GPIO_3);
       output_low(GPIO_4);
       break;  

      case 4:  
       output_low(GPIO_1);
       output_low(GPIO_2);
       output_high(GPIO_3);
       output_low(GPIO_4);
       break;  

      case 5:  
       output_high(GPIO_1);
       output_low(GPIO_2);
       output_high(GPIO_3);
       output_low(GPIO_4);
       break;  

      case 6:  
       output_low(GPIO_1);
       output_high(GPIO_2);
       output_high(GPIO_3);
       output_low(GPIO_4);
       break;  

      case 7:  
       output_high(GPIO_1);
       output_high(GPIO_2);
       output_high(GPIO_3);
       output_low(GPIO_4);
       break;  

      case 8:  
       output_low(GPIO_1);
       output_low(GPIO_2);
       output_low(GPIO_3);
       output_high(GPIO_4);
       break;  

      case 9:  
       output_high(GPIO_1);
       output_low(GPIO_2);
       output_low(GPIO_3);
       output_high(GPIO_4);
       break;  

      case 10:  
       output_low(GPIO_1);
       output_high(GPIO_2);
       output_low(GPIO_3);
       output_high(GPIO_4);
       break;  

      case 11:  
       output_high(GPIO_1);
       output_high(GPIO_2);
       output_low(GPIO_3);
       output_high(GPIO_4);
       break;  

      case 12:  
       output_low(GPIO_1);
       output_low(GPIO_2);
       output_high(GPIO_3);
       output_high(GPIO_4);
       break;  

      case 13:  
       output_high(GPIO_1);
       output_low(GPIO_2);
       output_high(GPIO_3);
       output_high(GPIO_4);
       break;  

      case 14:  
       output_low(GPIO_1);
       output_high(GPIO_2);
       output_high(GPIO_3);
       output_high(GPIO_4);
       break;  

      case 15:  
       output_high(GPIO_1);
       output_high(GPIO_2);
       output_high(GPIO_3);
       output_high(GPIO_4);
       break;         
       
      default:
         output_low(GPIO_1);
         output_low(GPIO_2);
         output_low(GPIO_3);
         output_low(GPIO_4);
         break;
         
    }
}

void binario() {
    int x = dip;
    for(int i = 0; i < 4; i++) {
        bin[i] = x % 2;  
        x = x / 2;       
    }
}

void main (void){
int lectura_ant = 0;
while(1){
    lectura();
    if(dip!= lectura_ant){
    control_leds();
    binario();
        protolink_debug_data("Valor DIP: %u \r\n", dip);
        protolink_debug_msg("Valor binario: ");
        for(int z = 4; z > 0; z--){
            protolink_debug_data("%u", bin[z-1]);
            delay_ms(5);
        }
        
        protolink_debug_msg(" \r\n");
        lectura_ant = dip;
    }
    
    delay_ms(250);
}
}