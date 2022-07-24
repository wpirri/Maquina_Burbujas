/***************************************************************************
    Copyright (C) 2018   Walter Pirri

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 ***************************************************************************/

/* *****************************************************************************
 * Controlador para máquina de burbujas
 * 
 * *****************************************************************************
 * PIC12F629
 * Pines:
 *  1 - Vdd (2.0 a 5.5)     Vdd   PU
 *  2 - GP5                 i/o - y - Boton 1   - Vent+
 *  3 - GP4                 i/o - y - Boton 2   - Vent-
 *  4 - GP3 / MCLR / Vpp    i   - n - Boton 3   - Rueda+
 *  5 - GP2 / INT           i/o - y - Boton 4   - Rueda-
 *  6 - GP1 / ICSP CLK      i/o - n - Ventilador
 *  7 - GP0 / ICSP DAT      i/o - n - Servo 0,5ms - 1,5ms - 2,5ms c/20ms
 *  8 - Vss                 Vss
 * Clock:
 *  Interno 4 MHz
 * ************************************************************************** */
#pragma config CPD = ON
#pragma config CP = ON
#pragma config BOREN = OFF
#pragma config MCLRE = OFF
#pragma config PWRTE = ON
#pragma config WDTE = ON
#pragma config FOSC = INTRCIO
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>

#include <xc.h>

#include "config.h"
#include "perif.h"
#include "bitmacro.h"

typedef enum
{
    INIT = 0,
    STOP,
    START,
    RUNNING,
    ERROR
} stm_t;

/* *************************************************************************** *
 * Globales
 */
stm_t STM;

unsigned char flag_pulso_servo_1;
unsigned char cont_pulso_servo_1;
unsigned char cont_off_servo_1;
unsigned char val_off_servo_1;

unsigned char flag_pulso_servo_2;
unsigned char cont_pulso_servo_2;
unsigned char cont_off_servo_2;
unsigned char val_off_servo_2;

unsigned char btn_status;

unsigned int off_counter;

unsigned char gShadow;

/* Interrupción cada 256us */
void Timer0Int()
{
    if(cont_off_servo_1)
    {
        cont_off_servo_1--;
        if(cont_off_servo_1 == 0)
        {
            ResetBit(SHADOW_REG, SERVO1_OUT);
        }
    }
    cont_pulso_servo_1++;
    if(cont_pulso_servo_1 == 78)
    {
        cont_pulso_servo_1 = 0;
        cont_off_servo_1 = val_off_servo_1;
        if(cont_off_servo_1 > 0)
        {
            SetBit(SHADOW_REG, SERVO1_OUT);
        }
    }
    
    if(cont_off_servo_2)
    {
        cont_off_servo_2--;
        if(cont_off_servo_2 == 0)
        {
            ResetBit(SHADOW_REG, SERVO2_OUT);
        }
    }
    cont_pulso_servo_2++;
    if(cont_pulso_servo_2 == 78)
    {
        cont_pulso_servo_2 = 0;
        cont_off_servo_2 = val_off_servo_2;
        if(cont_off_servo_2 > 0)
        {
            SetBit(SHADOW_REG, SERVO2_OUT);
        }
    }

    if(IS_BTN1(btn_status))
    {
        off_counter++;
        if(off_counter >= 10000)
        {
            STM = STOP;
        }
    }
    else
    {
        off_counter = 0;
    }
    
    
}

//void ExternalInt()
//{
//
//}

/* *************************************************************************** *
 * Punto de interrupcion
 */
void interrupt isr(void)
{
    /* GIE = 0;  << NO SE DEBE HACER */
    /* Si se usa % dentro de interrupcion da overflow el stack */
    /* <<< Interrupcion de TIMER0 - 250 us >>> */
    if(T0IF)   { T0IF = 0; if( !T0IE) return; Timer0Int(); }
    //if(TMR1IF) { TMR1IF = 0; if( !TMR1IE) Timer1Int(); }
    //if(INTF)   { INTF = 0; if( !INTE) return; ExternalInt(); }
    /* GIE = 1;  << NO SE DEBE HACER >> */
}

/* *************************************************************************** *
 * MAIN
 */
void main(void)
{
    /*
    bit 7 GPPU: GPIO Pull-up Enable bit
        1 = GPIO pull-ups are disabled
        0 = GPIO pull-ups are enabled by individual port latch values
    bit 6 INTEDG: Interrupt Edge Select bit
        1 = Interrupt on rising edge of GP2/INT pin
        0 = Interrupt on falling edge of GP2/INT pin
    bit 5 T0CS: TMR0 Clock Source Select bit
        1 = Transition on GP2/T0CKI pin
        0 = Internal instruction cycle clock (CLKOUT)
    bit 4 T0SE: TMR0 Source Edge Select bit
        1 = Increment on high-to-low transition on GP2/T0CKI pin
        0 = Increment on low-to-high transition on GP2/T0CKI pin
    bit 3 PSA: Prescaler Assignment bit
        1 = Prescaler is assigned to the WDT
        0 = Prescaler is assigned to the TIMER0 module
    bit 2-0 PS2:PS0: Prescaler Rate Select bits
        Bit Value   TMR0 Rate WDT Rate
        000         1:2         1:1
        001         1:4         1:2
        010         1:8         1:4
        011         1:16        1:8
        100         1:32        1:16
        101         1:64        1:32
        110         1:128       1:64
        111         1:256       1:128
     */
    OPTION_REG = 0b00001111;
    /* Control del comparador */
    CMCON = 0b00000000;     /* Solamente necesario para el 675 */
    GPIO = 0x00;
    TRISIO = 0b11111100;
    /* Pull-Up */
    WPU = 0b00110100;
    /*
    bit 7 GIE: Global Interrupt Enable bit
        1 = Enables all unmasked interrupts
        0 = Disables all interrupts
    bit 6 PEIE: Peripheral Interrupt Enable bit
        1 = Enables all unmasked peripheral interrupts
        0 = Disables all peripheral interrupts
    bit 5 T0IE: TMR0 Overflow Interrupt Enable bit
        1 = Enables the TMR0 interrupt
        0 = Disables the TMR0 interrupt
    bit 4 INTE: GP2/INT External Interrupt Enable bit
        1 = Enables the GP2/INT external interrupt
        0 = Disables the GP2/INT external interrupt
    bit 3 GPIE: Port Change Interrupt Enable bit (1)
        1 = Enables the GPIO port change interrupt
        0 = Disables the GPIO port change interrupt
    bit 2 T0IF: TMR0 Overflow Interrupt Flag bit (2)
        1 = TMR0 register has overflowed (must be cleared in software)
        0 = TMR0 register did not overflow
    bit 1 INTF: GP2/INT External Interrupt Flag bit
        1 = The GP2/INT external interrupt occurred (must be cleared in software)
        0 = The GP2/INT external interrupt did not occur
    bit 0 GPIF: Port Change Interrupt Flag bit
        1 = When at least one of the GP5:GP0 pins changed state (must be cleared in software)
        0 = None of the GP5:GP0 pins have changed state
     */
    INTCON = 0b00100000;
    /* Interrupt on change */
    IOC = 0b00000000;

    STM=INIT;
    off_counter = 0;

    GIE = 1;    /* Habilito las interrupciones */
    while(1)
    {
        CLRWDT();
        
        /* Traslado los imput al shadow */
        SHADOW_REG |= (INPUT_PORT & TRISIO);
        SHADOW_REG &= (INPUT_PORT | (TRISIO ^ 0xFF));
        /* Traslado el shadow a los output */
        OUTPUT_PORT = SHADOW_REG;
        
        switch(STM)
        {
            case INIT:
                flag_pulso_servo_1 = 0;
                cont_pulso_servo_1 = 0;
                cont_off_servo_1 = 0;

                flag_pulso_servo_2 = 0;
                cont_pulso_servo_2 = 0;
                cont_off_servo_2 = 0;
                
                InitPerif();
                
                STM++;
                break;
            case STOP:
                val_off_servo_1 = 0;  /*  <6 giro a la izquierda - >6 giro a la derecha */
                val_off_servo_2 = 0;  /* 0= STOP .. 78= MAXIMO */
                if( IS_BTN1(CheckBtn()) )
                {
                    while(CheckBtn()) CLRWDT();
                    STM++;
                }
                break;
            case START:
                val_off_servo_1 = SERVO1_INIT;
                val_off_servo_2 = SERVO2_INIT;
                STM++;
                break;
            case RUNNING:
                if((btn_status = CheckBtn()) != 0)
                {
                    if(IS_BTN1(btn_status))
                    {
                        while(CheckBtn()) CLRWDT();
                        if(val_off_servo_2 < SERVO2_MAX)
                        {
                            val_off_servo_2 += SERVO2_STEP;
                        }
                    }
                    else if(IS_BTN2(btn_status))
                    {
                        while(CheckBtn()) CLRWDT();
                        if(val_off_servo_2 > SERVO2_MIN)
                        {
                            val_off_servo_2 -= SERVO2_STEP;
                        }
                    }
                    else if(IS_BTN3(btn_status))
                    {
                        while(CheckBtn()) CLRWDT();
                        if(val_off_servo_1 < SERVO1_MAX)
                        {
                            val_off_servo_1 += SERVO1_STEP;
                        }
                    }
                    else if(IS_BTN4(btn_status))
                    {
                        while(CheckBtn()) CLRWDT();
                        if(val_off_servo_1 > SERVO1_MIN)
                        {
                            val_off_servo_1 -= SERVO1_STEP;
                        }
                    }
                }
                break;
            case ERROR:
                break;
        }
    }
}
