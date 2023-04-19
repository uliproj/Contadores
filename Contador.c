/*
 * MICROCONTROLADORES.c
 * Author: Ulisses Teixeira
 *
 * Created on 02 de Novembro de 2021, 18:09
 */


#include <xc.h>
#include <pic16f628a.h>
#include <stdlib.h>
#include <stdio.h>
#include "configdobonus1.h"
#include <stdint.h>

//                                                 > Numeros em Hexadecimal! <

uint8_t N[16] = {0xEE, 0x28, 0xCD, 0x6D, 0x2B, 0x67, 0xE7, 0x2C, 0xEF, 0x6F, 0xAF, 0xE3, 0xC6, 0xE9, 0xC7, 0x87}; 

//                                                 > Numeros em binário! <

//uint8_t N[16] = {0b11101110, 0b00101000 , 0b11001101, 0b01101101, 0b00101011, 0b01100111, 0b11100111, 0b00101100, 0b11101111, 0b01101111, 0b10101111, 0b11100011, 0b11000110, 0b11101001, 0b11000111, 0b10000111};

//                                                 > Contador <

int i = 0;

void main(void){

//                                                 > Definir LEDs e botões como entradas ou sa�das <
     TRISB = 0x00;
     PORTB = 0x00;
     TRISA = 0xFF;
     PORTA = 0xFF;

     while(1){
        PORTB = N[i];
//                                                 > Com o acionamento do botão R1 ou R2, o contador irá começar a contar <
        if(!PORTAbits.RA1){

            __delay_ms(80);
           
//                                                 > Pressionar o botão, irá aumentar o contador <
            while(!PORTAbits.RA1){

                i++;

                if(i>15){ 
                    i=0;
                }
//                                                 > Se contador igual for maior que 15, o valor vai ser reiniciado <
                PORTB = N[i];

                __delay_ms(250);
                
            }
            
        }

        if(!PORTAbits.RA2){

            __delay_ms(80); 
            
//                                                 > Ao precionar o botão R2 o contador irá diminuir <
            while(!PORTAbits.RA2){

                i--;

//                                                 > Se contador menor que 0, seu valor chegará ao máximo, no caso F no display <
                if(i<0){
                    i=15;
                    }
                PORTB = N[i];

                __delay_ms(250);
               
            }
            
        }
//                                                 > Reset para o contador, porque sim :v <
        if(!PORTAbits.RA3){                       
            
            __delay_ms(80);

            i = 0;
            
            PORTB = N[i];
               
        }

    }
     
    return;
}
