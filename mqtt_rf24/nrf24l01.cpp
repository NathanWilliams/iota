/*
 * nrf24l01.cpp
 *
 * Copyright (C) Nathan Williams
 * License: TODO
 *
 * Purpose: Use an NRF24L01+ radio for communications
 */

#include "nrf24l01.h"
#include <string.h> //memset

NRF24L01::NRF24L01() {
    memset(send_buffer, 0, MAX_BUFFER_SIZE);
    radio.begin();
    radio.enableAckPayload();
}

NRF24L01::~NRF24L01() {

}

void NRF24L01::send(const uint8_t *msg, size_t length) {
    memcpy(&send_buffer, msg, length);
    radio.openWritingPipe(PIPE);
    radio.startWrite(msg, length);
} 

void NRF24L01::listen() {
    radio.openReadingPipe(1,PIPE);
    radio.startListening();
}


//Called by the radio's IRQ
void NRF24L01::receive() {
    //grab data from radio...
    radio.read(receive_buffer, MAX_BUFFER_SIZE);
    //and pass to receiver
    dispatch(const_cast<const uint8_t*>(receive_buffer));
}
