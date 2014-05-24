/*
 * Test harness
 */

#include <avr/interrupt.h>
#include <util/delay.h>
#include "nrf24l01.h"
#include "mqttsn/mqttsn-messages.h"

#define TRANSMIT
//#define RECEIVE

#ifdef RECEIVE
#include "receive.h"
#include "transport.h"
#include "mqttsn/mqttsn.h"

class DummyMQ : public virtual IReceive {
public:
    DummyMQ(ITransport *delegate) : delegate(delegate) {}
    void receive(const uint8_t *data) {
        message_header *msg = (message_header*)data;
        
        if(msg->type == CONNECT) {
            const msg_connect *con = reinterpret_cast<const msg_connect*>(data);
            PORTD |= (1<<PD3);                  //stage 1 LED lit
            if(con->flags == FLAG_CLEAN) {
                PORTD |= (1<<PD4);              //stage 2 LED lit
            }
            _delay_ms(500);                     //hold on
            PORTD &= ~( (1<<PD3) | (1<<PD4) );  //turn them off
        }
        else {
            //Error case, flash LED on PD4
            for(uint8_t i=0;i<10;++i) {
                PORTD ^= (1<<PD4);
                _delay_ms(100);
                PORTD ^= (1<<PD4);
            }
        } 
    }
private:
    ITransport *delegate;
};
#endif //RECEIVE

NRF24L01 radio_link;

int main(void) {
#ifdef TRANSMIT
    MQTTSN mq(&radio_link);
    sei();
    for(;;) {
       mq.connect(FLAG_CLEAN, 300, "client-1");
      _delay_ms(2000); 
    }
#endif //TRANSMIT


#ifdef RECEIVE
    DummyMQ dmq(&radio_link);
    radio_link.listen();
    sei();
    for(;;){} //Interrupts from here on

#endif //RECEIVE

    return 0;
}

/*
int main(void) {
    MQTTSN protocol(&radio_link);
    sei(); //enable interrupts globally
    protocol.connect(FLAG_CLEAN, 300, "clientid-1");

    //when waiting for messages from base station
    radio_link.listen();

    return 0;
}
*/


ISR(INT0_vect) {
    radio_link.receive();
}

