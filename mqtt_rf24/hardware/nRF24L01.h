/*
    Copyright (c) 2007 Stefan Engelke <mbox@stefanengelke.de>

    Permission is hereby granted, free of charge, to any person 
    obtaining a copy of this software and associated documentation 
    files (the "Software"), to deal in the Software without 
    restriction, including without limitation the rights to use, copy, 
    modify, merge, publish, distribute, sublicense, and/or sell copies 
    of the Software, and to permit persons to whom the Software is 
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be 
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
    DEALINGS IN THE SOFTWARE.
*/

/* Memory Map */
#define CONFIG      0x00
#define EN_AA       0x01
#define EN_RXADDR   0x02
#define SETUP_AW    0x03
#define SETUP_RETR  0x04
#define RF_CH       0x05
#define RF_SETUP    0x06
#define STATUS      0x07
#define OBSERVE_TX  0x08
#define CD          0x09
#define RX_ADDR_P0  0x0A
#define RX_ADDR_P1  0x0B
#define RX_ADDR_P2  0x0C
#define RX_ADDR_P3  0x0D
#define RX_ADDR_P4  0x0E
#define RX_ADDR_P5  0x0F
#define TX_ADDR     0x10
#define RX_PW_P0    0x11
#define RX_PW_P1    0x12
#define RX_PW_P2    0x13
#define RX_PW_P3    0x14
#define RX_PW_P4    0x15
#define RX_PW_P5    0x16
#define FIFO_STATUS 0x17
#define DYNPD	    0x1C
#define FEATURE	    0x1D

/* Bit Mnemonics */
#define MASK_RX_DR  6
#define MASK_TX_DS  5
#define MASK_MAX_RT 4
#define EN_CRC      3
#define CRCO        2
#define PWR_UP      1
#define PRIM_RX     0
#define ENAA_P5     5
#define ENAA_P4     4
#define ENAA_P3     3
#define ENAA_P2     2
#define ENAA_P1     1
#define ENAA_P0     0
#define ERX_P5      5
#define ERX_P4      4
#define ERX_P3      3
#define ERX_P2      2
#define ERX_P1      1
#define ERX_P0      0
#define AW          0
#define ARD         4
#define ARC         0
#define PLL_LOCK    4
#define RF_DR       3
#define RF_PWR      6
#define RX_DR       6
#define TX_DS       5
#define MAX_RT      4
#define RX_P_NO     1
#define TX_FULL     0
#define PLOS_CNT    4
#define ARC_CNT     0
#define TX_REUSE    6
#define FIFO_FULL   5
#define TX_EMPTY    4
#define RX_FULL     1
#define RX_EMPTY    0
#define DPL_P5	    5
#define DPL_P4	    4
#define DPL_P3	    3
#define DPL_P2	    2
#define DPL_P1	    1
#define DPL_P0	    0
#define EN_DPL	    2
#define EN_ACK_PAY  1
#define EN_DYN_ACK  0

/* Instruction Mnemonics */
#define R_REGISTER    0x00
#define W_REGISTER    0x20
#define REGISTER_MASK 0x1F
#define ACTIVATE      0x50
#define R_RX_PL_WID   0x60
#define R_RX_PAYLOAD  0x61
#define W_TX_PAYLOAD  0xA0
#define W_ACK_PAYLOAD 0xA8
#define FLUSH_TX      0xE1
#define FLUSH_RX      0xE2
#define REUSE_TX_PL   0xE3
#define NOP           0xFF

/* Non-P omissions */
#define LNA_HCURR   0

/* P model memory Map */
#define RPD         0x09

/* P model bit Mnemonics */
#define RF_DR_LOW   5
#define RF_DR_HIGH  3
#define RF_PWR_LOW  1
#define RF_PWR_HIGH 2

/* NOTE
 *
 * From the datasheet:
 * Please take care when setting this parameter. 
 * If the ACK payload is more than 15 byte in 2Mbps 
 * mode the ARD must be 500μS or more, if the ACK 
 * payload is more than 5byte in 1Mbps mode the 
 * ARD must be 500μS or more. 
 *
 * In 250kbps mode (even when the payload is not in 
 * ACK) the ARD must be 500μS or more.
 *
 */

/* Auto Retransmit Delay values */
#define ARD_250uS  (0x0 << ARD)
#define ARD_500uS  (0x1 << ARD)
#define ARD_750uS  (0x2 << ARD)
#define ARD_1000uS (0x3 << ARD)
#define ARD_1250uS (0x4 << ARD)
#define ARD_1500uS (0x5 << ARD)
#define ARD_1750uS (0x6 << ARD)
#define ARD_2000uS (0x7 << ARD)
#define ARD_2250uS (0x8 << ARD)
#define ARD_2500uS (0x9 << ARD)
#define ARD_2750uS (0xA << ARD)
#define ARD_3000uS (0xB << ARD)
#define ARD_3250uS (0xC << ARD)
#define ARD_3500uS (0xD << ARD)
#define ARD_3750uS (0xE << ARD)
#define ARD_4000uS (0xF << ARD)

/* Auto Retransmit Count */
#define ARC_0   0x0
#define ARC_1   0x1
#define ARC_2   0x2
#define ARC_3   0x3
#define ARC_4   0x4
#define ARC_5   0x5
#define ARC_6   0x6
#define ARC_7   0x7
#define ARC_8   0x8
#define ARC_9   0x9
#define ARC_10  0xA
#define ARC_11  0xB
#define ARC_12  0xC
#define ARC_13  0xD
#define ARC_14  0xE
#define ARC_15  0xF

/* Enable Auto Acknowledgment */
/* Additional */
#define ENAA_ALL (ENAA_P5 | ENAA_P4 | ENAA_P3 | ENAA_P2 | ENAA_P1 | ENAA_P0)
#define ENAA_DISABLE 0




/* Misc */
/* get the pipe number from the status */
#define PIPE_MASK 0x7
#define PIPE_NUM(status) (status >> RX_P_NO) & PIPE_MASK

