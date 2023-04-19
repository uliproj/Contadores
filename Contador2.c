/*
 * File:   MICROCONTROLADORES
 * Author: Ulisses T.
 *
 * Created on 3 de Novembro de 2021, 20:38
 */


#include <xc.h>
#include <pic16f628a.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "configatividade2.h"

uint8_t disp1[10] = {0xEE, 0x28, 0xCD, 0x6D, 0x2B, 0x67, 0xE7, 0x2C, 0xEF, 0x6F}; //Declarando display 1
uint8_t disp2[10] = {0xFE, 0x38, 0xDD, 0x7D, 0x3B, 0x77, 0xF7, 0x3C, 0xFF, 0x7F}; //Declarando display 2

int i1 = 0, i2 = 0;
//i1 é o contador do display esquerdo
//i2 é o contador do display direito

void mult_disp(){//funcão pra chamar as PORTAS caso ocorra alguma alteracão durante o programa, bem como o delay
    
    PORTB = disp1[i1];
    __delay_ms(25);
    
    PORTB = disp2[i2];
    __delay_ms(30);
}

void main(void) {
    int dig = 1;//se dig for 1, ele irá alterar as unidades, caso seja 0, vai alterar as dezenas, achei sugestivo deixar ele como 1 mesmo
    TRISB = 0x00;
    PORTB = 0x00;
    TRISA = 0xFF;
    PORTA = 0xFF;
    while(1){
        mult_disp();
        if(!PORTAbits.RA1){
            mult_disp();
            if(dig == 0){
                dig = 1;
            }else 
            {
                dig = 0;
            }
        }
        
        if(!PORTAbits.RA2){
            if(dig == 0){
                i1++;
                mult_disp();
                if(i1>9)
                    i1=0;
            }
            if(dig == 1){
                i2++;
                mult_disp();
                if(i2>9){
                    i2=0;
                }
            }
        }    
        if(!PORTAbits.RA3){//cá temos o decremento do programa, eu usei do/while e o escambal pra fazer automático
            //daí lembrei que bastava essa droga de while(1)
            while(1){
                for(int t = 0;t < 15;t++){ //um delayzin
                mult_disp();
                }
                i2--;
                    if(i2<0){
                        i1--;
                        i2 = 9;
                    }
                        if(i1 < 0)
                        {
                            i2 = 9;
                            for(int t = 0;t < 15;t++){//outro delayzin
                                mult_disp();
                            }
                        }
                if(i1 == 0 && i2 == 0){
                        for(int t = 0;t < 30;t++)//mais outro delayzin
                        mult_disp();
                        i1 = 0;
                        i2 = 0;
                    break;
                }
                }
        }
    }

    return;
}
