/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

/**
 * Based on pingpair_irq.iro from RF24 arduino examples
 *
 */

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

#define LED_PIN     4 //PD4
#define BUTTON_PIN  3 //PD3

RF24 radio(8,9);

#define ROLE_PIN 7

// Single radio pipe address for the 2 nodes to communicate.
#define PIPE 0xE8E8F0F0E1LL

// The various roles supported by this sketch
typedef enum { role_sender = 1, role_receiver } role_e;

// The role of the current running sketch
role_e role;

// Interrupt handler, check the radio because we got an IRQ
void check_radio(void);

//Button interrupt for sending data
void send_data(void);

void flash_led(uint8_t count);

void setup(void)
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  digitalWrite(BUTTON_PIN, HIGH); //Enable the internal pull-up resistor

  // set up the role pin
  pinMode(ROLE_PIN, INPUT);
  digitalWrite(ROLE_PIN,HIGH);
  delay(20); // Just to get a solid reading on the role pin

  // read the address pin, establish our role
  if ( digitalRead(ROLE_PIN) )
    role = role_sender;
  else
    role = role_receiver;

  radio.begin();

  radio.enableAckPayload();

  if ( role == role_sender ) {
    radio.openWritingPipe(PIPE);
  }
  else {
    radio.openReadingPipe(1,PIPE);
  }

  if ( role == role_receiver )
    radio.startListening();

  //INT0 - PD2 (digital pin 2) interupt
  attachInterrupt(0, check_radio, FALLING);

  //INT1 - PD3 (digital pin 3) interrupt (TX button)
  attachInterrupt(1, send_data, FALLING);
}

static uint32_t message_count = 0;

void loop(void) { } //all interrupt driven


void send_data(void) {
  if(role == role_sender) {
    uint8_t flashes = 2;
    radio.startWrite( &flashes, sizeof(uint8_t));
  }
}

void check_radio(void)
{
  // What happened?
  bool tx,fail,rx;
  radio.whatHappened(tx,fail,rx);

  // Have we successfully transmitted?
  if ( tx ) {
    if ( role == role_sender ) Serial.println("Send:OK");
    if ( role == role_receiver ) Serial.println("Ack Payload:Sent");
  }

  // Have we failed to transmit?
  if ( fail ) {
    if ( role == role_sender ) Serial.println("Send:Failed");
    if ( role == role_receiver ) Serial.println("Ack Payload:Failed");
  }

  // Transmitter can power down for now, because
  // the transmission is done.
  if ( ( tx || fail ) && ( role == role_sender ) )
    radio.powerDown();

  // Did we receive a message?
  if ( rx ) {
    // If we're the sender, we've received an ack payload
    if ( role == role_sender ) {
      radio.read(&message_count,sizeof(message_count)); //ignoring response for now
    }

    // If we're the receiver, we've received a time message
    if ( role == role_receiver )
    {
      // Get this payload and dump it
      uint8_t count;
      radio.read( &count, sizeof(count) );

      flash_led(count);

      // Add an ack packet for the next time around.  This is a simple
      // packet counter
      radio.writeAckPayload( 1, &message_count, sizeof(message_count) );
      ++message_count;
    }
  }
}

void flash_led(uint8_t count) {
  for(uint8_t i=0; i<count;i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(200);
    digitalWrite(LED_PIN, LOW);
    delay(200);
  }
}
