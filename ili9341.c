#include "common.h"
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdlib.h>
#include "spi.h"
#include "ili9341.h"

void ILI9341_sendCommand(uint8_t cmd) {
  DC_LOW();
  CS_LOW();
  SPI_transfer(cmd);
  CS_HIGH();
}

void ILI9341_sendData(uint8_t data) {
  DC_HIGH();
  CS_LOW();
  SPI_transfer(data);
  CS_HIGH();
}

void ILI9341_sendData16(uint16_t data) {
  uint8_t h_data = data >> 8;
  uint8_t l_data = data & 0xFF;
  DC_HIGH();
  CS_LOW();
  SPI_transfer(h_data);
  SPI_transfer(l_data);
  CS_HIGH();
}

void ILI9341_Init() {
  LED_OUTPUT();
  LED_ON();
  
  SPI_init();
  CS_HIGH();
  
  DC_OUTPUT();
  DC_HIGH();
  
  RST_OUTPUT();
  RST_ON();
  _delay_ms(10);
  RST_OFF();
  
  ILI9341_setOrientation(PORTRAIT);
  
  ILI9341_sendCommand(ILI9341_CMD_POWER_ON_SEQ_CONTROL);
  ILI9341_sendData(ILI9341_CMD_IDLE_MODE_ON);
  ILI9341_sendData(ILI9341_CMD_MEMORY_WRITE);
  ILI9341_sendData(ILI9341_CMD_NOP);
  ILI9341_sendData(ILI9341_CMD_TEARING_EFFECT_LINE_OFF);
  ILI9341_sendData(0x02);
  
  ILI9341_sendCommand(ILI9341_CMD_POWER_CONTROL_B);
  ILI9341_sendData(ILI9341_CMD_NOP);
  ILI9341_sendData(ILI9341_CMD_POWER_CONTROL_2);
  ILI9341_sendData(ILI9341_CMD_PARTIAL_AREA);
  
  ILI9341_sendCommand(ILI9341_CMD_DRIVER_TIMING_CONTROL_A);
  ILI9341_sendData(0x85);
  ILI9341_sendData(ILI9341_CMD_NOP);
  ILI9341_sendData(0x78);
  
  ILI9341_sendCommand(ILI9341_CMD_DRIVER_TIMING_CONTROL_B);
  ILI9341_sendData(ILI9341_CMD_NOP);
  ILI9341_sendData(ILI9341_CMD_NOP);
  
  ILI9341_sendCommand(0xED);
  ILI9341_sendData(0x64);
  ILI9341_sendData(0x03);
  ILI9341_sendData(ILI9341_CMD_PARTIAL_MODE_ON);
  ILI9341_sendData(0X81);
  
  ILI9341_sendCommand(ILI9341_CMD_PUMP_RATIO_CONTROL);
  ILI9341_sendData(ILI9341_CMD_DISP_INVERSION_OFF);
  
  ILI9341_sendCommand(ILI9341_CMD_POWER_CONTROL_1);
  ILI9341_sendData(0x23);
  
  ILI9341_sendCommand(ILI9341_CMD_POWER_CONTROL_2);
  ILI9341_sendData(ILI9341_CMD_ENTER_SLEEP_MODE);
  
  ILI9341_sendCommand(ILI9341_CMD_VCOM_CONTROL_1);
  ILI9341_sendData(ILI9341_CMD_READ_MEMORY_CONTINUE);
  ILI9341_sendData(ILI9341_CMD_DISPLAY_OFF);
  
  ILI9341_sendCommand(ILI9341_CMD_VCOM_CONTROL_2);
  ILI9341_sendData(0x86);
  
  ILI9341_sendCommand(ILI9341_CMD_MEMORY_ACCESS_CONTROL);
  ILI9341_sendData(0x48);
  
  ILI9341_sendCommand(ILI9341_CMD_COLMOD_PIXEL_FORMAT_SET);
  ILI9341_sendData(ILI9341_CMD_WRITE_CONTENT_ADAPT_BRIGHTNESS);
  
  ILI9341_sendCommand(ILI9341_CMD_FRAME_RATE_CONTROL_NORMAL);
  ILI9341_sendData(ILI9341_CMD_NOP);
  ILI9341_sendData(0x18);
  
  ILI9341_sendCommand(ILI9341_CMD_DISPLAY_FUNCTION_CONTROL);
  ILI9341_sendData(0x08);
  ILI9341_sendData(0x82);
  ILI9341_sendData(0x27);
  
  ILI9341_sendCommand(ILI9341_CMD_ENABLE_3_GAMMA_CONTROL);
  ILI9341_sendData(ILI9341_CMD_NOP);
  
  ILI9341_sendCommand(0x26);
  ILI9341_sendData(ILI9341_CMD_SOFTWARE_RESET);
  
  ILI9341_sendCommand(ILI9341_CMD_POSITIVE_GAMMA_CORRECTION);
  ILI9341_sendData(0x0F);
  ILI9341_sendData(0x31);
  ILI9341_sendData(ILI9341_CMD_PAGE_ADDRESS_SET);
  ILI9341_sendData(ILI9341_CMD_READ_DISP_PIXEL_FORMAT);
  ILI9341_sendData(ILI9341_CMD_READ_DISP_SIGNAL_MODE);
  ILI9341_sendData(0x08);
  ILI9341_sendData(0x4E);
  ILI9341_sendData(0xF1);
  ILI9341_sendData(ILI9341_CMD_VERT_SCROLL_START_ADDRESS);
  ILI9341_sendData(0x07);
  ILI9341_sendData(ILI9341_CMD_ENTER_SLEEP_MODE);
  ILI9341_sendData(0x03);
  ILI9341_sendData(ILI9341_CMD_READ_DISP_SIGNAL_MODE);
  ILI9341_sendData(ILI9341_CMD_READ_DISP_STATUS);
  ILI9341_sendData(ILI9341_CMD_NOP);
  
  ILI9341_sendCommand(ILI9341_CMD_NEGATIVE_GAMMA_CORRECTION);
  ILI9341_sendData(ILI9341_CMD_NOP);
  ILI9341_sendData(ILI9341_CMD_READ_DISP_SIGNAL_MODE);
  ILI9341_sendData(0x14);
  ILI9341_sendData(0x03);
  ILI9341_sendData(ILI9341_CMD_SLEEP_OUT);
  ILI9341_sendData(0x07);
  ILI9341_sendData(0x31);
  ILI9341_sendData(ILI9341_CMD_POWER_CONTROL_2);
  ILI9341_sendData(0x48);
  ILI9341_sendData(0x08);
  ILI9341_sendData(0x0F);
  ILI9341_sendData(ILI9341_CMD_READ_DISP_PIXEL_FORMAT);
  ILI9341_sendData(0x31);
  ILI9341_sendData(ILI9341_CMD_MEMORY_ACCESS_CONTROL);
  ILI9341_sendData(ILI9341_CMD_READ_DISP_SELF_DIAGNOSTIC);
  
  ILI9341_sendCommand(ILI9341_CMD_SLEEP_OUT);
  _delay_ms(120);
  ILI9341_sendCommand(ILI9341_CMD_DISPLAY_ON);
  ILI9341_sendCommand(ILI9341_CMD_MEMORY_WRITE);
  ILI9341_background(COLOR_BLACK);
}

void ILI9341_setX(uint16_t x0, uint16_t x1) {
  ILI9341_sendCommand(ILI9341_CMD_COLUMN_ADDRESS_SET);
  ILI9341_sendData16(x0);
  ILI9341_sendData16(x1);
}

void ILI9341_setY(uint16_t y0, uint16_t y1) {
  ILI9341_sendCommand(ILI9341_CMD_PAGE_ADDRESS_SET);
  ILI9341_sendData16(y0);
  ILI9341_sendData16(y1);
}

void ILI9341_setOrientation(uint8_t orientation) {
  setOrientation = orientation;
  if (setOrientation == PORTRAIT) {
    maxX = 240;
    maxY = 320;
  } else if (setOrientation == LANDSCAPE) {
    maxX = 320;
    maxY = 240;
  }
}

void ILI9341_setXY(uint16_t x0, uint16_t y0) {
  ILI9341_setX(x0, x0);
  ILI9341_setY(y0, y0);
  ILI9341_sendCommand(ILI9341_CMD_MEMORY_WRITE);
}

void ILI9341_pixel(uint16_t x0, uint16_t y0, uint16_t color) {
  if (setOrientation == PORTRAIT) {
    ILI9341_setXY(x0, y0);
    ILI9341_sendData16(color);
  } else if (setOrientation == LANDSCAPE) {
    ILI9341_setXY(y0, maxX - x0);
    ILI9341_sendData16(color);
  }
}

void ILI9341_line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color) {
  int x = x1 - x0;
  int y = y1 - y0;
  int dx = abs(x), sx = x0 < x1 ? 1 : -1;
  int dy = -abs(y), sy = y0 < y1 ? 1 : -1;
  int err = dx + dy, e2;
  for (;;) {
    ILI9341_pixel(x0, y0, color);
    e2 = 2 * err;
    if (e2 >= dy) {
      if (x0 == x1)
        break;
      err += dy;
      x0 += sx;
    }
    if (e2 <= dx) {
      if (y0 == y1) break;
      err += dx;
      y0 += sy;
    }
  }
}

void ILI9341_hLine(uint16_t x0, uint16_t y0, uint16_t length, uint16_t color) {
  if (setOrientation == PORTRAIT) {
    ILI9341_setX(x0, x0 + length);
    ILI9341_setY(y0, y0);
    ILI9341_sendCommand(ILI9341_CMD_MEMORY_WRITE);
    int i = 0;
    for (i = 0; i < length; i++)
      ILI9341_sendData16(color);
  } else if (setOrientation ==  LANDSCAPE) {
    ILI9341_setX(y0, y0);
    ILI9341_setY(maxX - x0 - length, maxY - x0);
    ILI9341_sendCommand(ILI9341_CMD_MEMORY_WRITE);
    int i = 0;
    for (i = 0; i < length; i++)
      ILI9341_sendData16(color);
  }
}

void ILI9341_vLine(uint16_t x0, uint16_t y0, uint16_t length, uint16_t color) {
  if (setOrientation == PORTRAIT) {
    ILI9341_setX(x0, x0);
    ILI9341_setY(y0, y0 + length);
    ILI9341_sendCommand(ILI9341_CMD_MEMORY_WRITE);
    int i = 0;
    for (i = 0; i < length; i++)
      ILI9341_sendData16(color);
  } else if (setOrientation ==  LANDSCAPE) {
    ILI9341_setX(y0, y0 + length);
    ILI9341_setY(maxX - x0, maxX - x0);
    ILI9341_sendCommand(ILI9341_CMD_MEMORY_WRITE);
    int i = 0;
    for (i = 0; i < length; i++)
      ILI9341_sendData16(color);
  }
}

void ILI9341_rectangle(uint16_t x0, uint16_t y0, uint16_t length, uint16_t width, uint16_t color) {
  ILI9341_hLine(x0, y0, length, color);
  ILI9341_hLine(x0, y0 + width, length, color);
  ILI9341_vLine(x0, y0, width, color);
  ILI9341_vLine(x0 + length, y0, width, color);
}

void ILI9341_fillRectangle(uint16_t x0, uint16_t y0, uint16_t length, uint16_t width, uint16_t color) {
  for (int i = 0; i < width; i++)
    ILI9341_hLine(x0, y0 + i, length, color);
}

void ILI9341_circle(int x0, int y0, int r, uint16_t color) {
  int x = -r, y = 0, err = 2 - 2 * r, e2;
  do {
    ILI9341_pixel(x0 - x, y0 + y, color);
    ILI9341_pixel(x0 + x, y0 + y, color);
    ILI9341_pixel(x0 + x, y0 - y, color);
    ILI9341_pixel(x0 - x, y0 - y, color);
    e2 = err;
    if (e2 <= y) {
      err += ++y * 2 + 1;
      if (-x == y && e2 <= x)
        e2 = 0;
    }
    if (e2 > x)
      err += ++x * 2 + 1;
  } while (x <= 0);
}

void ILI9341_fillCircle(int x0, int y0, int r, uint16_t color) {
  int x = -r, y = 0, err = 2 - 2 * r, e2;
  do {
    ILI9341_vLine(x0 - x, y0 - y, 2 * y, color);
    ILI9341_vLine(x0 + x, y0 - y, 2 * y, color);
    e2 = err;
    if (e2 <= y) {
      err += ++y * 2 + 1;
      if (-x == y && e2 <= x) e2 = 0;
    }
    if (e2 > x)
      err += ++x * 2 + 1;
  } while (x <= 0);
}

void ILI9341_char(uint8_t ascii, uint16_t x0, uint16_t y0, uint16_t size, uint16_t fgColor) {
  if ((ascii >= 32) && (ascii <= 127)) {
  } else {
    ascii = '?' - 32;
  }
  int i;
  for (i = 0; i < FONT_X; i++ ) {
    uint8_t temp = pgm_read_byte(&fonts[ascii - 32][i]);
    uint8_t f = 0;
    for (f = 0; f < 8; f++) {
      if ((temp >> f) & 0x01)
        ILI9341_fillRectangle(x0 + i * size, y0 + f * size, size, size, fgColor);
    }
  }
}

void ILI9341_string(char *string, uint16_t x0, uint16_t y0, uint16_t size, uint16_t fgColor) {
  while (*string) {
    ILI9341_char(*string, x0, y0, size, fgColor);
    string++;
    if (x0 < MAX_X)
      x0 += FONT_SPACE * size;
  }
}

uint8_t ILI9341_number(uint16_t longNumber, uint16_t x0, uint16_t y0, uint16_t size, uint16_t fgColor) {
  uint8_t char_buffer[10] = "";
  uint8_t i = 0;
  uint8_t f = 0;
  if (longNumber < 0) {
    f = 1;
    ILI9341_char('-', x0, y0, size, fgColor);
    longNumber = -longNumber;
    if (x0 < MAX_X)
      x0 += FONT_SPACE * size;
  } else if (longNumber == 0) {
    f = 1;
    ILI9341_char('0', x0, y0, size, fgColor);
    return f;
    if (x0 < MAX_X)
      x0 += FONT_SPACE * size;
  }
  while (longNumber > 0) {
    char_buffer[i++] = longNumber % 10;
    longNumber /= 10;
  }
  f = f + i;
  for (; i > 0; i--) {
    ILI9341_char('0' + char_buffer[i - 1], x0, y0, size, fgColor);
    if (x0 < MAX_X)
      x0 += FONT_SPACE * size;
  }
  return f;
}

uint8_t ILI9341_float(float floatNumber, uint16_t x0, uint16_t y0, uint16_t size, uint16_t fgColor) {
  uint8_t decimal = 1;
  uint16_t temp = 0;
  float decy = 0.0;
  float rounding = 0.5;
  uint8_t f = 0;
  if (floatNumber < 0.0) {
    ILI9341_char('-', x0, y0, size, fgColor);
    floatNumber = -floatNumber;
    if (x0 < MAX_X)
      x0 += FONT_SPACE * size;
    f = 1;
  }
  for (uint8_t i = 0; i < decimal; ++i)
    rounding /= 10.0;
  floatNumber += rounding;
  temp = (uint16_t)floatNumber;
  uint8_t howlong = ILI9341_number(temp, x0, y0, size, fgColor);
  f += howlong;
  if ((x0 + 8 * size * howlong) < MAX_X)
    x0 += FONT_SPACE * size * howlong;
  if (decimal > 0) {
    ILI9341_char('.', x0, y0, size, fgColor);
    if (x0 < MAX_X)
      x0 += FONT_SPACE * size;
    f += 1;
  }
  decy = floatNumber - temp;
  for (uint8_t i = 0; i < decimal; i++) {
    decy *= 10;
    temp = decy;
    ILI9341_number(temp, x0, y0, size, fgColor);
    floatNumber = -floatNumber;
    if (x0 < MAX_X)
      x0 += FONT_SPACE * size;
    decy -= temp;
  }
  f += decimal;
  return f;
}

void ILI9341_clr(uint16_t x0, uint16_t y0, uint16_t size) {
  ILI9341_fillRectangle(x0, y0, size * 10, size * 10, COLOR_YELLOW);
}

void ILI9341_clrLine(uint16_t y0, uint16_t size) {
  ILI9341_fillRectangle(0, y0 - size, maxX, size * 10, COLOR_BLACK);
}

void ILI9341_background(uint16_t color) {
  ILI9341_fillRectangle(0, 0, maxX, maxY, color);
}

void ILI9341_arc(int x, int y, int r, int startAngle, int endAngle, int thickness, uint16_t color) {
  int rDelta = -(thickness / 2);
  int px, py, cx, cy;
  startAngle -= 90;
  endAngle   -= 90;
  if (startAngle != endAngle) {
    for (int i = 0; i < thickness; i++) {
      px = x + cos((startAngle * 3.14) / 180) * (r + rDelta + i);
      py = y + sin((startAngle * 3.14) / 180) * (r + rDelta + i);
      for (int d = startAngle + 1; d < endAngle + 1; d++) {
        cx = x + cos((d * 3.14) / 180) * (r + rDelta + i);
        cy = y + sin((d * 3.14) / 180) * (r + rDelta + i);
        ILI9341_line(px, py, cx, cy, color);
        px = cx;
        py = cy;
      }
    }
    } else {
    px = x + cos((startAngle * 3.14) / 180) * (r + rDelta);
    py = y + sin((startAngle * 3.14) / 180) * (r + rDelta);
    cx = x + cos((startAngle * 3.14) / 180) * (r - rDelta);
    cy = y + sin((startAngle * 3.14) / 180) * (r - rDelta);
    ILI9341_line(px, py, cx, cy, color);
  }
}
