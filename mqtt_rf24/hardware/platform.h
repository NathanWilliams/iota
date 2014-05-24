/*
 * platform.h
 *
 * Copyright (C) 2014 Nathan Williams
 * License: TODO
 * Purpose: Abstract out platform specific parts
 *          This file should be customised based on the target board
 *          The micro controller used, and the IO pins used for various function
 */

/* The reference platform is based on an AVR micro controller
 * This file needs to be modified if porting to a different platform
 *
 * In future that should probably be controlled by compiler directives
 */
#ifndef __PLATFORM_H_
#define __PLATFORM_H_
#include <stdint.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

//Arduino.h defines these, keeping them here until (if?) I can reasonably replace them
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

//IO control
#define SET_PIN(port, pin, state) if(state) {port |= (1<<pin);} else {port &= ~(1<<pin);}

//Settings for development board

//Chip select for nRF24L01 radio
#define CSN_PORT    PORTB
#define CSN_PIN     PB1

//Chip enable for nRF24L01 radio
#define CE_PORT     PORTB
#define CE_PIN      PB0

//Common
#define CSN(state) SET_PIN(CSN_PORT, CSN_PIN, state)
#define CE(state) SET_PIN(CE_PORT, CE_PIN, state)

void radio_pin_init();
void radio_interrupt_init();

#define HIGH 1
#define LOW  0

//SPI
#define LSB_FIRST 1
#define MSB_FIRST 0

//Taken from the Arduino SPI library
#define SPI_MODE0 0x00
#define SPI_MODE1 0x04
#define SPI_MODE2 0x08
#define SPI_MODE3 0x0C
void set_spi(uint8_t bit_order, uint8_t data_mode);
void spi_init();

uint8_t spi_transfer(uint8_t data);

//not ideal, but not sure how to best take parameters in a platform agnostic way...
void set_spi_rate(); 


#endif //__PLATFORM_H_
