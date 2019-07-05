#include "common.h"
#include "spi.h"

void SPI_init() {
  ILI9341_SPI_DDR &=~ (1 << ILI9341_MISO);
  ILI9341_SPI_DDR |= (1 << ILI9341_MOSI) | (1 << ILI9341_SCK) | (1 << ILI9341_CS);
  SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR1) | (1 << SPR0);
  SPSR = (1 << SPI2X);
}

uint8_t SPI_transfer(uint8_t data) {
  SPDR = data;
  while ((SPSR & (1 << SPIF)) == 0);
  return SPDR;
}