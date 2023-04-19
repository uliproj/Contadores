/*
 * File:   MICROCONTROLADORES
 * Author: Ulisses T.
 *
 * Created on 11 de Outubro de 2021, 10:25
 */

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <pic16f628a.h>
#include "config.h"
#include <stdint.h>

void main(void) {
    TRISB = 0b11100000;
    TRISAbits.TRISA1 = 1;
    TRISAbits.TRISA2 = 1;
    TRISAbits.TRISA3 = 1; //{11111000,11101100,11100110,11100011}{11110001,11101010,11100100,11101110}{11111011,11110001,11101010,11111011}
    uint8_t pad[3][4] = {{0xF8, 0xEC, 0xE6, 0xE3},{0xF1, 0xEA, 0xE4, 0xEE},{0xFB, 0xF1, 0xEA, 0xFB}};
    int contpad=0,i=0;
    while(1){
        if(!PORTAbits.RA1){  //Nada burocrático, o botão pressionado irá orientar o padrão a ser ligado no display
            __delay_ms(50);
            contpad=0;
            while(!PORTAbits.RA1){
                PORTB = 0xFF;
                __delay_ms(25);
            }
        }        
        if(PORTAbits.RA2 == 0){
            __delay_ms(50);
            contpad=1;
            while(!PORTAbits.RA2){
                PORTB = 0xFF;
                __delay_ms(25);
            }
        }
        if(PORTAbits.RA3 == 0){
            __delay_ms(50);
            contpad=2;
            while(!PORTAbits.RA3){
                PORTB = 0xFF;
                __delay_ms(25);
            }
        }
        for(i=0;i<4;i++){
            __delay_ms(300);
            PORTB = pad[contpad][i];
        }
    }
}
