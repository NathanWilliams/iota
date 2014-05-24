/*
 * nrf24l01.h
 *
 * Copyright (C) Nathan Williams
 * License: TODO
 *
 * Purpose: Use an NRF24L01+ radio for communications
 */

#ifndef __NRF24L01_H_ 
#define __NRF24L01_H_ 

#include <stdint.h>
#include "transport.h"
#include "receive.h"
#include "hardware/RF24.h"

#define MAX_BUFFER_SIZE 66 //Defined in MQTT-SN spec
#define PIPE 0xE8E8F0F0E1LL //Temporary hardcoded pipe

class NRF24L01 : public ITransport {
public:
    NRF24L01();
    virtual ~NRF24L01();

    virtual void send(const uint8_t *msg, size_t length);
    void listen();
    void receive(); //called by an interrupt

private:
    uint8_t send_buffer[MAX_BUFFER_SIZE];
    uint8_t receive_buffer[MAX_BUFFER_SIZE];
    RF24    radio;
};

#endif //__NRF24L01_H_
