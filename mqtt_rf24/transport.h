/*
 * transport.h
 *
 * Copyright (C) 2014 Nathan Williams
 * License: TODO
 * Purpose: Interface for a class that receives and sends data over a transport layer
 */

#ifndef __TRANSPORT_H_
#define __TRANSPORT_H_

#include <stdint.h>
#include <stdlib.h>
#include "receive.h"
#include "new.h"

class ITransport {
public:
    ITransport();
    virtual ~ITransport() ;
    void register_receiver(IReceive *receiver);
    virtual void send(const uint8_t *msg, size_t length) = 0;

protected:
    void dispatch(const uint8_t *data);
private:
    IReceive *receiver;
};

#endif //__TRANSPORT_H_
