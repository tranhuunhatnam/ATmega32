#ifndef COMMON_H_
#define COMMON_H_

#define F_CPU 16000000ul
#include <avr/io.h>

#define ILI9341_SPI_DDR     DDRB
#define ILI9341_SPI_PORT    PORTB
#define ILI9341_CS          4
#define ILI9341_MOSI        5
#define ILI9341_MISO        6
#define ILI9341_SCK         7

#define ILI9341_DC_DDR      DDRB
#define ILI9341_DC_PORT     PORTB
#define ILI9341_DC          1

#define ILI9341_RST_DDR     DDRB
#define ILI9341_RST_PORT    PORTB
#define ILI9341_RST         2

#define ILI9341_LED_DDR     DDRB
#define ILI9341_LED_PORT    PORTB
#define ILI9341_LED         0

#define CS_OUTPUT() {ILI9341_SPI_DDR |= (1 << ILI9341_CS);}
#define CS_LOW() {ILI9341_SPI_PORT &= ~(1 << ILI9341_CS);}
#define CS_HIGH() {ILI9341_SPI_PORT |= (1 << ILI9341_CS);}

#define DC_OUTPUT() {ILI9341_DC_DDR |= (1 << ILI9341_DC);}
#define DC_LOW() {ILI9341_DC_PORT &= ~(1 << ILI9341_DC);}
#define DC_HIGH() {ILI9341_DC_PORT |= (1 << ILI9341_DC);}

#define RST_OUTPUT() {ILI9341_RST_DDR |= (1 << ILI9341_RST);}
#define RST_ON()  {ILI9341_RST_PORT &= ~(1 << ILI9341_RST);}
#define RST_OFF() {ILI9341_RST_PORT |= (1 << ILI9341_RST);}

#define LED_OUTPUT() {ILI9341_LED_DDR |= (1 << ILI9341_LED);}
#define LED_OFF() {ILI9341_LED_PORT &= ~(1 << ILI9341_LED);}
#define LED_ON() {ILI9341_LED_PORT |= (1 << ILI9341_LED);}

#endif