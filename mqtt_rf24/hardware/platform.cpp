/*
 * platform.cpp
 *
 * Copyright (C) 2014 Nathan Williams
 * License: TODO
 * Purpose: Abstract out platform specific parts
 *          This file should be customised based on the target board
 *          The micro controller used, and the IO pins used for various function
 */

#include "platform.h"


void radio_pin_init() {
    DDRB |= (1<<PB0) | (1<<PB1); //PB0 and PB1 as output pins
}

void radio_interrupt_init() {
    //IRQ on PD2
    //INT0, in future might move this to a PCINT..

    //External Interrupt Control Register A
    EICRA |= (1<<ISC11) | (0<<ISC10); //Falling
    EIMSK |= (1<<INT0); //Enable INT0 interrupt
}

void set_spi(uint8_t bit_order, uint8_t data_mode) {
    SPCR |= (bit_order<<DORD) | data_mode; 
}

void spi_init() {
    //SPI enable, SPI master mode
    SPCR |= (1<<SPE) | (1<<MSTR);
}

uint8_t spi_transfer(uint8_t data) {
    SPDR = data;
    while( !(SPSR & (1<<SPIF)) ); //wait for transfer to complete
    return SPDR; //return received data
}

void set_spi_rate() {
    //AVR @ 16Mhz
    //Radio SPI max: 10Mhz
    //Faster xfer lets AVR do other work
    //makes better use of radio buffers
    SPSR |= (1<<SPI2X);
    SPCR |= (0<<SPR1) | (0<<SPR0); //nop, here to state intent
}
