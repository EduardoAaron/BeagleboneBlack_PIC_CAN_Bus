/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 * 
 * CAN FILTER EXAMPLES: CAN_bus::filter(canid_t id, canid_t mask)
 * struct can_filter rfilter[4];
 * rfilter[0].can_id   = 0x80001234;    Exactly this EFF frame 
 * rfilter[0].can_mask = CAN_EFF_MASK; /* 0x1FFFFFFFU all bits valid 
 * rfilter[1].can_id   = 0x123;        /* Exactly this SFF frame 
 * rfilter[1].can_mask = CAN_SFF_MASK; /* 0x7FFU all bits valid 
 * rfilter[2].can_id   = 0x200 | CAN_INV_FILTER; /* all, but 0x200-0x2FF 
 * rfilter[2].can_mask = 0xF00;        /* (CAN_INV_FILTER set in can_id) 
 * rfilter[3].can_id   = 0;            /* don't care 
 * rfilter[3].can_mask = 0;            /* ALL frames will pass this filter 
 * setsockopt(s, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter));
 */

/* 
 * File:   CAN_bus.cpp
 * Author: Edu
 * 
 * Created on 3 de diciembre de 2015, 13:51
 */

#include "CAN_bus.h"

using namespace std;

int CAN_bus::init() {
    
    /* particular protocols of the protocol family PF_CAN */
        /*-- RAW sockets */
    if((sock = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
	cout << "Error while opening socket" << endl;
	return -1;
    }
    
    //char *ifname = "can0";
    //char *ifname =can_bus_name;
    
    strcpy(ifr.ifr_name, can_bus_name);
    ioctl(sock, SIOCGIFINDEX, &ifr);
	
    addr.can_family  = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex; 

    printf("%s at index %d\n", ifr.ifr_name, ifr.ifr_ifindex);

    if(bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("Error in socket bind");
        return -2;
    }
    return sock;
}

int CAN_bus::send_bus() {
    int nbytes;
    if ( nbytes = write(sock, &frame, sizeof(struct can_frame)) < 0) {
        cout << "Error while write socket" << endl;
	return -1;
    }
    return nbytes;
}

int CAN_bus::read_bus() {
    int nbytes;
    nbytes = read(sock, &frame_read, sizeof(frame_read));
    return nbytes;
}

void CAN_bus::filter(canid_t id, canid_t mask) {
    //rfilter.can_id   = 0x202; /* SFF frame */
    rfilter.can_id   = id; /* SFF frame */
    rfilter.can_mask = mask;
    setsockopt(sock, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter));  
}


CAN_bus::~CAN_bus() {
    close(sock);
}

