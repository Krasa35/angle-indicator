/*
 * eth_udp.h
 *
 *  Created on: Jan 19, 2024
 *      Author: Kurus
 */

#ifndef INC_ETH_UDP_H_
#define INC_ETH_UDP_H_

// Define maximum message size
#define MAX_MSG_SIZE 	100

// Include necessary libraries and header files
#include "lwip.h"
#include "udp.h"
#include "init.h"

// Structure for Ethernet buffer handle
typedef struct{
	  int8_t active;
	  Menu_States state;
	  MenuComs com;
	  MenuStrings compStrings;
	  char rx_buffer[MAX_MSG_SIZE];
	  char tx_message[MAX_MSG_SIZE];
	  ip_addr_t dst_ip;
	  volatile int newDataAvailable;
} _BUFFER_ETHHandle;

void UDP_Init(void);
void UDP_SendMessage(const char *msg);
void UDP_ReceiveCallback(void *arg, struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, u16_t port);

#endif /* INC_ETH_UDP_H_ */
