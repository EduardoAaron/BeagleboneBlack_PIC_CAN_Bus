# **README** #

This is a simple example to comunicate the BBB to a PIC micro through CAN bus.

## **PIC program:** ##
   This programama is a simple example of sending data via CAN bus.

   * Compiler: CCS C COMPILER
   * Microcontroller: PIC18F25K80
   * CAN bus transceiver: MCP551
   * CAN bus speed: 1 MBs

## **BBB program:** ##
  This program only receives data from the CAN bus and displays them on screen.

* Use SocketCAN in C++
* CAN bus transceiver: SN65HVD230 (RS485 CAN CAPE Features RS485 CAN Interfaces for BB Black Expansion Connection)
http://www.ebay.es/itm/RS485-CAN-CAPE-Features-RS485-CAN-Interfaces-for-BB-Black-Expansion-Connection-/261694039969
* CAN bus speed: 1 MBs


### Folders ###

* PIC_program: PIC program
* BBB_program: BBB program
