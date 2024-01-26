/*
 * eth_udp.h
 *
 *  Created on: Jan 19, 2024
 *      Author: Kurus
 */

#ifndef INC_ETH_UDP_H_
#define INC_ETH_UDP_H_

#include "lwip.h"
#include "udp.h"

extern volatile int newDataAvailable;  // Declare the flag as external
extern char rx_buffer[];  // Declare the rx_buffer variable

void UDP_Init(void);
void UDP_SendMessage(const char *msg);
void UDP_ReceiveCallback(void *arg, struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, u16_t port);

#endif /* INC_ETH_UDP_H_ */
