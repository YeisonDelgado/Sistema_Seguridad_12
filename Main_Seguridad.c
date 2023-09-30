/*!
\file   Main_Seguridad.c
\date   2023-09-27
\author Yeison Delgado <yeisondelgado@unicauca.edu.co>
\brief  Security House.

\par Copyright
Information contained herein is proprietary to and constitutes valuable
confidential trade secrets of unicauca, and
is subject to restrictions on use and disclosure.

\par
Copyright (c) unicauca 2023. All rights reserved.

\par
The copyright notices above do not evidence any actual or
intended publication of this material.
******************************************************************************
*/
#include <xc.h>
#include <pic16f887.h>  /*Header file PIC16f887 definitions*/
#include <stdio.h>
#include <string.h>
#include "fuses.h"
#include "lcd.h"
#include "keypad.h"

#define IN  1
#define OFF 0
#define LED_GREEN RE0 
#define LED_RED   RE1
#define LED_BLUE  RE2

const char password[5] ={'2','0','2','3',0};
char pass_user[5];
unsigned char idx = 0;
unsigned char system_lock = 0;

void main() {

    char key = '0';
    //Configura Fosc = 8Mhz interno, Fuente de Fosc del sistema = interno
    OSCCON = 0x71; //Configura oscilador interno (FOSC = 8Mhz)
    TRISE = 0;
    PORTE = 0;
     
    LCD_Init();    //Inicializa el LCD
    keypad_init(); //Inicializa el keypad

    while (1) {
        LCD_String_xy(0,0,"Press a Key");
        LCD_Command(0xC0); 
        do{
            key = keypad_getkey();
            if(key != 0){
                LCD_Char('*');/* display pressed key on LCD16x2 */
                // LCD_Char(key);/* display pressed key on LCD16x2 */
                pass_user[idx++] = key;
            }
            __delay_ms(100);
        }while(idx < 5);
       
        if(strncmp(pass_user,password,4)==0){
            LCD_Clear();
            LCD_String_xy(0,0,"Clave Correcta");
            LED_GREEN = IN;
            idx = 0;
            
        }else{
            
            LCD_Clear();
            LCD_String_xy(0,0,"Clave Incorrecta");
            LED_BLUE = IN;
            
            if(system_lock == 3){
                LCD_String_xy(0,0,"Sisteama Bloqueado");
                LED_RED= IN;
                 
            }else{
                
                system_lock++;
                 idx = 6;
            }  
        }
        __delay_ms(2000);
        LCD_Clear();
       
    }
}