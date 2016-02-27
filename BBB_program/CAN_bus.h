/* 
 * File:   CAN_bus.h
 * Author: Eduardo Aarón Feránadez Orallo
 *
 * Created on 3 de diciembre de 2015, 13:51
 */

#ifndef CAN_BUS_H
#define CAN_BUS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#include <iostream>
using namespace std;

#include <cstring>

class CAN_bus {
public:
    CAN_bus(char *bus_name) : can_bus_name(bus_name){};
    CAN_bus() : can_bus_name("can0"){};
    
    virtual int init();
    struct can_frame frame;
    struct can_frame frame_read;
    virtual int send_bus();
    virtual int read_bus();
    virtual void filter(canid_t id, canid_t mask);
    virtual ~CAN_bus();
    
private:
    int sock;
    char *can_bus_name;
    struct sockaddr_can addr;
    struct ifreq ifr;
    struct can_filter rfilter;

};

#endif /* CAN_BUS_H */

