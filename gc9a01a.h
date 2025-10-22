/**
 *****************************************************************************
 * @file    gc9a01a.h
 * @author  Nabli Hatem
 * @brief   This module contains all functions prototypes for the gc9a01a.c
 *          driver.
 *****************************************************************************
 * @attention
 *
 * Copyright © 2025 Nabli Hatem
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

/* Definition to prevent recursive inclusion -------------------------------*/

#ifndef GC9A01A_H
#define GC9A01A_H

/* Includes --------------------------------------------------------------- */
#include <stdint.h>
#include <stddef.h>
#include "gfx_display.h"

#define GC9A01A_TFTWIDTH 240   ///< Display width in pixels
#define GC9A01A_TFTHEIGHT 240  ///< Display hight in pixels

#define GC9A01A_SWRESET 0x01  ///< Software Reset (not documented)
#define GC9A01A_RDDID 0x04    ///< Read display identification information
#define GC9A01A_RDDST 0x09    ///< Read display status

#define GC9A01A_SLPIN 0x10   ///< Enter Sleep Mode
#define GC9A01A_SLPOUT 0x11  ///< Sleep Out
#define GC9A01A_PTLON 0x12   ///< Partial Mode ON
#define GC9A01A_NORON 0x13   ///< Normal Display Mode ON

#define GC9A01A_DISP_IN_OFF 0x20  ///< Display Inversion OFF
#define GC9A01A_DISP_IN_ON 0x21   ///< Display Inversion ON
#define GC9A01A_DISP_OFF 0x28     ///< Display OFF
#define GC9A01A_DISP_ON 0x29      ///< Display ON

#define GC9A01A_CASET 0x2A  ///< Column Address Set
#define GC9A01A_RASET 0x2B  ///< Row Address Set
#define GC9A01A_RAMWR 0x2C  ///< Memory Write

#define GC9A01A_PTLAR 0x30    ///< Partial Area
#define GC9A01A_VSCRDEF 0x33  ///< Vertical Scrolling Definition
#define GC9A01A_TELOFF 0x34   ///< Tearing Effect Line OFF
#define GC9A01A_TELON 0x35    ///< Tearing Effect Line ON

#define GC9A01A_MADCTL 0x36   ///< Memory Access Control
#define GC9A01A_VSSADD 0x37   ///< Vertical Scrolling Start Address
#define GC9A01A_IDLEOFF 0x38  ///< Idle Mode OFF
#define GC9A01A_IDLEON 0x39   ///< Idle Mode ON

#define GC9A01A_PIXSET 0x3A    ///< Pixel Format Set
#define GC9A01A_WMEMC 0x3C     ///< Write Memory Continue
#define GC9A01A_SETTSCAN 0x44  ///< Set Tear Scanline

#define GC9A01A_GETSCAN 0x45    ///< Get Scanline
#define GC9A01A_WDISBRIGH 0x51  ///< Write Display Brightness
#define GC9A01A_WCTRLDISP 0x53  ///< Write CTRL Display

#define GC9A01A_READ_ID1 0xDA  ///< Read ID1
#define GC9A01A_READ_ID2 0xDB  ///< Read ID2
#define GC9A01A_READ_ID3 0xDC  ///< Read ID3

#define GC9A01A_RGBSIG_CTRL 0xB0  ///< RGB Signal Control
#define GC9A01A_BLANKP_CTRL 0xB5  ///< Blanking Porch Control
#define GC9A01A_DISPFN_CTRL 0xB6  ///< Display Function Control

#define GC9A01A_TECTRL 0xBA          ///< TE Control
#define GC9A01A_INTERFACE_CTRL 0xF6  ///< Interface Control

#define GC9A01A_POWCRICTRL 0xC1   ///< Power Criterion Control
#define GC9A01A_VREG1AVCTRL 0xC3  ///< VReg1a voltage Control
#define GC9A01A_VREG1BVCTRL 0xC4  ///< VReg1b voltage Control
#define GC9A01A_VREG2AVCTRL 0xC9  ///< VReg2a voltage Control
#define GC9A01A_VCOREVCTRL 0xA7   ///< Vcore voltage Control
#define GC9A01A_FRAME_RATE 0xE8   ///< Frame Rate
#define GC9A01A_SPI2D_CTRL 0xE9   ///< SPI2 Data Control
#define GC9A01A_CHPFR_CTRL 0xEC   ///< Charge Pump Frequent Control
#define GC9A01A_INREG_ON_1 0xFE   ///< Inner Register Enable 1
#define GC9A01A_INREG_ON_2 0xEF   ///< Inner Register Enable 2
#define GC9A01A_SET_GAMMA_1 0xF0  ///< SET GAMMA 1
#define GC9A01A_SET_GAMMA_2 0xF1  ///< SET GAMMA 2
#define GC9A01A_SET_GAMMA_3 0xF2  ///< SET GAMMA 3
#define GC9A01A_SET_GAMMA_4 0xF3  ///< SET GAMMA 4

#define MADCTL_MY 0x80   ///< Bottom to top
#define MADCTL_MX 0x40   ///< Right to left
#define MADCTL_MV 0x20   ///< Reverse Mode
#define MADCTL_ML 0x10   ///< LCD refresh Bottom to top
#define MADCTL_RGB 0x00  ///< Red-Green-Blue pixel order
#define MADCTL_BGR 0x08  ///< Blue-Green-Red pixel order
#define MADCTL_MH 0x04   ///< LCD refresh right to left

// Color definitions
#define GC9A01A_BLACK 0x0000        ///<   0,   0,   0
#define GC9A01A_NAVY 0x000F         ///<   0,   0, 123
#define GC9A01A_DARKGREEN 0x03E0    ///<   0, 125,   0
#define GC9A01A_DARKCYAN 0x03EF     ///<   0, 125, 123
#define GC9A01A_MAROON 0x7800       ///< 123,   0,   0
#define GC9A01A_PURPLE 0x780F       ///< 123,   0, 123
#define GC9A01A_OLIVE 0x7BE0        ///< 123, 125,   0
#define GC9A01A_LIGHTGREY 0xC618    ///< 198, 195, 198
#define GC9A01A_DARKGREY 0x7BEF     ///< 123, 125, 123
#define GC9A01A_BLUE 0x001F         ///<   0,   0, 255
#define GC9A01A_GREEN 0x07E0        ///<   0, 255,   0
#define GC9A01A_CYAN 0x07FF         ///<   0, 255, 255
#define GC9A01A_RED 0xF800          ///< 255,   0,   0
#define GC9A01A_MAGENTA 0xF81F      ///< 255,   0, 255
#define GC9A01A_YELLOW 0xFFE0       ///< 255, 255,   0
#define GC9A01A_WHITE 0xFFFF        ///< 255, 255, 255
#define GC9A01A_ORANGE 0xFD20       ///< 255, 165,   0
#define GC9A01A_GREENYELLOW 0xAFE5  ///< 173, 255,  41
#define GC9A01A_PINK 0xFC18         ///< 255, 130, 198

#define GC9A01A_SPI hspi2
#define GC9A01A_SPI_TIMEOUT 100
#define USE_DMA 0

#define GC9A01A_CS_PORT GPIOB
#define GC9A01A_CS_PIN LCD_CS_Pin

#define GC9A01A_DC_PORT GPIOB
#define GC9A01A_DC_PIN LCD_DC_Pin

#define GC9A01A_RST_PORT GPIOB
#define GC9A01A_RST_PIN LCD_RST_Pin

void gc9a01a_hw_reset(void);
void gc9a01a_configure(void);
void gc9a01a_init(void);
void gc9a01a_write_cmd(uint8_t cmd);
void gc9a01a_write_data(uint8_t data);
void gc9a01a_write_data_buf(uint8_t *data, uint32_t size);
void gc9a01a_set_address_window(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
void gc9a01a_set_orientation(uint8_t orientation);
void gc9a01a_write_char(uint16_t x, uint16_t y, char ch, glcd_font_t font, uint16_t color,
                        uint16_t bgcolor);
void gc9a01a_write_string(int16_t x, int16_t y, const char *str, glcd_font_t font, uint16_t color,
                          uint16_t background_color);
void gc9a01a_write_pixel(int16_t x, int16_t y, uint16_t color);
void gc9a01a_draw_image(int16_t x, int16_t y, int16_t width, int16_t height, const uint16_t *image);
void gc9a01a_draw_fast_vertical_line(int16_t x, int16_t y, int16_t height, uint16_t color);
void gc9a01a_draw_fast_horizental_line(int16_t x, int16_t y, int16_t width, uint16_t color);
void gc9a01a_draw_line(int16_t x_0, int16_t y_0, int16_t x_1, int16_t y_1, uint16_t color);
void gc9a01a_draw_rectangle(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t color);
void gc9a01a_fill_rectangle(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t color);
void gc9a01a_draw_circle(int16_t x, int16_t y, int16_t radius, uint16_t color);
void gc9a01a_fill_circle(int16_t x, int16_t y, int16_t radius, uint16_t color);
void gc9a01a_draw_ellipse(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t color);
void gc9a01a_fill_ellipse(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t color);
void gc9a01a_draw_triangle(int16_t x_0, int16_t y_0, int16_t x_1, int16_t y_1, int16_t x_2,
                           int16_t y_2, uint16_t color);
void gc9a01a_fill_triangle(int16_t x_0, int16_t y_0, int16_t x_1, int16_t y_1, int16_t x_2,
                           int16_t y_2, int16_t color);
void gc9a01a_draw_round_corner(int16_t x, int16_t y, int16_t r, uint8_t cornername, uint16_t color);
void gc9a01a_fill_round_corner(int16_t x0, int16_t y0, int16_t r, uint8_t corners, int16_t delta,
                               uint16_t color);
void gc9a01a_draw_round_rectangle(int16_t x_0, int16_t y_0, int16_t width, int16_t height,
                                  int16_t radius, uint16_t color);
void gc9a01a_fill_round_rectangle(int16_t x_0, int16_t y_0, int16_t width, int16_t height,
                                  int16_t radius, uint16_t color);
void gc9a01a_fill_screen(uint16_t color);

#endif /* GC9A01_H */