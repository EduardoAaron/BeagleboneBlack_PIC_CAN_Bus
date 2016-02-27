/* 
 * File:   main.c
 * Author: Eduardo Aarón Fernández Orallo
 * Created on 23 de febrero de 2016, 22:44
 * *************************************************
 * - This programama is a simple example of sending data via CAN bus.
 */

#include <18F25K80.h>
#device ADC=16

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES WDT128                   //Watch Dog Timer uses 1:128 Postscale
#FUSES NOXINST                  //Extended set extension and Indexed Addressing mode disabled (Legacy mode)
#FUSES NOBROWNOUT               //No brownout reset
#FUSES CANB                     //CANTX and CANRX pins are located on RB2 and RB3

#use delay(internal=64000000)

//Configure CAN bus speed for 1Mbs
#define CAN_USE_EXTENDED_ID FALSE
#define CAN_BRG_SEG_2_PHASE_TS TRUE  
#define CAN_BRG_PRESCALAR 1 
#define CAN_BRG_SYNCH_JUMP_WIDTH 0 
#define CAN_BRG_PROPAGATION_TIME 7 
#define CAN_BRG_PHASE_SEGMENT_1 0 
#define CAN_BRG_PHASE_SEGMENT_2 5 
#define CAN_BRG_WAKE_FILTER TRUE 
#define CAN_BRG_SAM FALSE

#include <can-18F4580.c>

#define PIN_LED1  PIN_A2
#define PIN_LED2  PIN_A1

#define LED1_LOW  output_low(PIN_LED1)
#define LED1_HIGH output_high(PIN_LED1)
#define LED2_LOW  output_low(PIN_LED2)
#define LED2_HIGH output_high(PIN_LED2)

#define WRITE_REGISTER_D_ID      0x100  //CAN bus ID.

struct rx_stat stat;
unsigned int buf[2];

void main ( )
{

    //Send data.
    buf[0] = 0x24;
    buf[1] = 0x14;
    
    can_init(); // Initialize the can
    
    while(1) {
        LED2_HIGH;
        LED1_LOW;
        can_putd(WRITE_REGISTER_D_ID,&buf,sizeof(buf),1,FALSE,FALSE); 
        /*  - Identifier: 0x100
            - Data pointer: buf
            - Number of data bytes: sizeof(buf) = 2
            - Priority (0-3) determines the order messages are sent
            - Flag to indicate 29 bit identifier
            - Flag to indicate if this is a data frame
    (       FALSE) or request for frame (TRUE)
        */
        delay_ms(500);
        LED1_HIGH;
        LED2_LOW;
        delay_ms(500);
    }
}


