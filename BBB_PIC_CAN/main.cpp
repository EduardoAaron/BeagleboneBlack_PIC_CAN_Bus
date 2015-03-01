/* 
 * File:   main.cpp
 * Author: Eduardo Aarón Feránadez Orallo
 * Created on 24 de febrero de 2016, 21:49
 * * *************************************************
 * - This program only receives data from the CAN bus and displays them on screen.
 */

#include <cstdlib>
#include <signal.h>
#include <iostream>

using namespace std;

#include "CAN_bus.h"

CAN_bus* PIC_CAN = new CAN_bus();

void my_handler(int s){
        printf(" Control+C. Caught signal %d\n",s);
        delete PIC_CAN;
        exit(1); 
}


/*
 * 
 */
int main(int argc, char** argv) {

    /* Control+C signal */
    struct sigaction sigIntHandler;

    sigIntHandler.sa_handler = my_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;

    sigaction(SIGINT, &sigIntHandler, NULL);
    
    int i;
    
    PIC_CAN->init();
    PIC_CAN->filter(0x100, CAN_SFF_MASK);
    
    cout << "INICIANDO....." << endl;
    
    while(true) {
        if (PIC_CAN->read_bus() > 0) {
            cout << "\nData received. ID: " << hex << PIC_CAN->frame_read.can_id << endl;

            printf("DLC: [%d] ", PIC_CAN->frame_read.can_dlc);
                
            for (i = 0; i < PIC_CAN->frame_read.can_dlc; i++) {
                printf(" Data %d: %04X",i ,PIC_CAN->frame_read.data[i]);
            }
        }
    }
    
    return 0;
}
