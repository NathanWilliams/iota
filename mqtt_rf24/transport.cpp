/*
 * transport.cpp
 *
 * Copyright (C) 2014 Nathan Williams
 * License: TODO
 * Purpose: Interface for a class that receives and sends data over a transport layer
 */

#include "transport.h"

ITransport::ITransport() : receiver(NULL) {
};

ITransport::~ITransport() {
}

void ITransport::register_receiver(IReceive *receiver) {
    this->receiver = receiver;
}

void ITransport::dispatch(const uint8_t *data) {
    if(this->receiver != NULL) {
        this->receiver->receive(data);
    }
}
