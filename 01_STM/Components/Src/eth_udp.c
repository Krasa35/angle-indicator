/*
 * eth_udp.c
 *
 *  Created on: Jan 19, 2024
 *      Author: Kurus
 */

#include "eth_udp.h"
#include <stdio.h>
#include <string.h>

#define MAX_MSG_SIZE 100

static struct pbuf *p;
static struct udp_pcb *pUDP_tx_pcb;
static struct udp_pcb *pUDP_rx_pcb;

_BUFFER_ETHHandle hudp = {
		.active = 0,
		.compStrings = {
				  ._DEBUG = "DEBUG",
				  ._REMOTE = "REMOTE",
				  ._MANUAL = "MANUAL",
				  ._IDLE = "IDLE",
				},
		.state = _IDLE,
		.newDataAvailable = 0
};

void UDP_SendMessage(const char *msg)
{
    MX_LWIP_Process();

    // Dynamic part of the message
    int length = snprintf(hudp.tx_message, MAX_MSG_SIZE, "%s;", msg);

    if (length < 0 || length >= MAX_MSG_SIZE)
    {
        // Handle error, e.g., by toggling an error LED
        return;
    }

    p = pbuf_alloc(PBUF_TRANSPORT, (uint16_t)length, PBUF_RAM);

    if (p == NULL)
    {
        // Handle error, e.g., by toggling an error LED
        return;
    }

    memcpy(p->payload, hudp.tx_message, (size_t)length);

    udp_sendto(pUDP_tx_pcb, p, &hudp.dst_ip, 25565); // Use the desired destination port

    pbuf_free(p);
}

void UDP_ReceiveCallback(void *arg, struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, u16_t port)
{
    // Process received UDP packet
    if (p != NULL)
    {
        // Copy received data to buffer
        if (p->tot_len < MAX_MSG_SIZE)
        {
            pbuf_copy_partial(p, hudp.rx_buffer, p->tot_len, 0);
            hudp.rx_buffer[p->tot_len] = '\0'; // Null-terminate the string

            // Handle the received data, for example, print it
            printf("Received UDP packet from %s:%d: %s\n", ip4addr_ntoa(addr), port, hudp.rx_buffer);
        }

        hudp.newDataAvailable = 1;

        // Free the pbuf
        pbuf_free(p);
    }
}

void UDP_Init(void)
{
    pUDP_tx_pcb = udp_new();
    udp_bind(pUDP_tx_pcb, IP4_ADDR_ANY, 1000);

    pUDP_rx_pcb = udp_new();
    udp_bind(pUDP_rx_pcb, IP4_ADDR_ANY, 25565); // Set the port to the one you want to listen on
    udp_recv(pUDP_rx_pcb, UDP_ReceiveCallback, NULL);

    IP4_ADDR(&hudp.dst_ip, 192, 168, 113, 4);
}
