/*
 * receive.h
 *
 * Copyright (C) 2014 Nathan Williams
 * License: TODO
 * Purpose: Interface for a class that receives data for processing / dispatch
 */

#ifndef __RECEIVE_H_
#define __RECEIVE_H_

#include <stdint.h>
#include "new.h"

class IReceive {
public:
    IReceive();
    virtual ~IReceive();
    virtual void receive(const uint8_t *data)=0;
};

#endif //__RECEIVE_H_
