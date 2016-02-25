/* 
 * File:   main.c
 * Author: Edu
 *
 * Created on 23 de febrero de 2016, 22:44
 */

#include <18F25K80.h>
#device ADC=16

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES WDT128                   //Watch Dog Timer uses 1:128 Postscale
#FUSES NOXINST                  //Extended set extension and Indexed Addressing mode disabled (Legacy mode)
#FUSES NOBROWNOUT               //No brownout reset
#FUSES CANB                     //CANTX and CANRX pins are located on RB2 and RB3

#use delay(internal=64000000)

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

#define ASK_FOR_ID_AD_B      0x201  //ask for AD info from CAN port B

//Variable bus CAN
int32 rx_id;
int rx_len,i,b;
struct rx_stat stat;
unsigned int receive[2];
unsigned int send[2];
unsigned int16 control;



void main ( )
{
    i = 88;
    b = 200;
    send[0] = 0x24;
    send[1] = 0x14;
    
    
    can_init(); // always initialize the can
    while(1) {
       // if ( can_tbe() ) {
            LED2_HIGH;
            LED1_LOW;
            //can_putd(ASK_FOR_ID_AD_B, &i, 1,1,0,0); //put data on transmit buffer
            can_putd(0x100,&send,2,1,FALSE,FALSE);
            delay_ms(500);
            LED1_HIGH;
            LED2_LOW;
            delay_ms(500);
      //  }
    }
}


