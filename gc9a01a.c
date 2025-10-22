/**
 *****************************************************************************
 * @file    gc9a01a.c
 * @author  Nabli Hatem
 * @brief   This module contains th implementaion of all gc9a01a functions.
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
#include "gc9a01a.h"
#include <stdint.h>

extern SPI_HandleTypeDef GC9A01A_SPI;

#if USE_DMA
static volatile uint8_t tx_busy = 0;
#endif

#ifndef _swap_int16_t
#    define _swap_int16_t(a, b) \
        {                       \
            int16_t t = a;      \
            a = b;              \
            b = t;              \
        }
#endif

/*Internal GPIO control -----------------------------------------*/

static inline void gc9a01a_chip_select(void) {
    HAL_GPIO_WritePin(GC9A01A_CS_PORT, GC9A01A_CS_PIN, GPIO_PIN_RESET);
}
static inline void gc9a01a_chip_unselect(void) {
    HAL_GPIO_WritePin(GC9A01A_CS_PORT, GC9A01A_CS_PIN, GPIO_PIN_SET);
}
static inline void gc9a01a_dc_set_command(void) {
    HAL_GPIO_WritePin(GC9A01A_DC_PORT, GC9A01A_DC_PIN, GPIO_PIN_RESET);
}
static inline void gc9a01a_dc_set_data(void) {
    HAL_GPIO_WritePin(GC9A01A_DC_PORT, GC9A01A_DC_PIN, GPIO_PIN_SET);
}

void gc9a01a_hw_reset(void) {
    HAL_GPIO_WritePin(GC9A01A_RST_PORT, GC9A01A_RST_PIN, GPIO_PIN_RESET);
    HAL_Delay(20);
    HAL_GPIO_WritePin(GC9A01A_RST_PORT, GC9A01A_RST_PIN, GPIO_PIN_SET);
    HAL_Delay(120);
}

void gc9a01a_write_cmd(uint8_t cmd) {
    gc9a01a_chip_select();
    gc9a01a_dc_set_command();
    HAL_SPI_Transmit(&GC9A01A_SPI, &cmd, 1, GC9A01A_SPI_TIMEOUT);
    gc9a01a_chip_unselect();
}

void gc9a01a_write_data(uint8_t data) {
    gc9a01a_chip_select();
    gc9a01a_dc_set_data();
    HAL_SPI_Transmit(&GC9A01A_SPI, &data, 1, GC9A01A_SPI_TIMEOUT);
    gc9a01a_chip_unselect();
}

void gc9a01a_write_data_buf(uint8_t *data, uint32_t size) {
    gc9a01a_chip_select();
    gc9a01a_dc_set_data();
#if USE_DMA
    tx_busy = 1;
    HAL_SPI_Transmit_DMA(&GC9A01A_SPI, data, size);
#else
    HAL_SPI_Transmit(&GC9A01A_SPI, data, size, GC9A01A_SPI_TIMEOUT);
    gc9a01a_chip_unselect();
#endif
}

// === DMA CALLBACK ===
#if USE_DMA
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi) {
    if (hspi == &GC9A01_SPI)
    {
        GC9A01_Unselect();
        tx_busy = 0;
        GC9A01_FlushReady();
    }
}
#endif

// === OPTIONAL WEAK CALLBACK ===
__weak void gc9a01a_flush_ready(void) {
    // Implement in user code:
}

void gc9a01a_set_address_window(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
    gc9a01a_write_cmd(GC9A01A_CASET);
    uint8_t column_data[] = {x0 >> 8, x0 & 0xFF, x1 >> 8, x1 & 0xFF};
    gc9a01a_write_data_buf(column_data, 4);
    uint8_t row_data[] = {y0 >> 8, y0 & 0xFF, y1 >> 8, y1 & 0xFF};
    gc9a01a_write_cmd(GC9A01A_RAMWR);
}

void gc9a01a_configure() {
    uint8_t params[15];
    gc9a01a_chip_select();

    gc9a01a_write_cmd(GC9A01A_INREG_ON_1);  ///< Inter register enable 1
    gc9a01a_write_cmd(GC9A01A_INREG_ON_2);  ///< Inter register enable 2

    params[0] = 0x14;
    gc9a01a_write_cmd(0xEB);
    gc9a01a_write_data_buf(params, 1);

    params[0] = 0x60;
    gc9a01a_write_cmd(0x84);
    gc9a01a_write_data_buf(params, 1);

    params[0] = 0xFF;
    gc9a01a_write_cmd(0x85);
    gc9a01a_write_data_buf(params, 1);

    params[0] = 0xFF;
    gc9a01a_write_cmd(0x86);
    gc9a01a_write_data_buf(params, 1);

    params[0] = 0xFF;
    gc9a01a_write_cmd(0x87);
    gc9a01a_write_data_buf(params, 1);

    params[0] = 0xFF;
    gc9a01a_write_cmd(0x8E);
    gc9a01a_write_data_buf(params, 1);

    params[0] = 0xFF;
    gc9a01a_write_cmd(0x8F);
    gc9a01a_write_data_buf(params, 1);

    params[0] = 0x0A;
    gc9a01a_write_cmd(0x88);
    gc9a01a_write_data_buf(params, 1);

    params[0] = 0x21;
    gc9a01a_write_cmd(0x89);
    gc9a01a_write_data_buf(params, 1);

    params[0] = 0x00;
    gc9a01a_write_cmd(0x8A);
    gc9a01a_write_data_buf(params, 1);

    params[0] = 0x80;
    gc9a01a_write_cmd(0x8B);
    gc9a01a_write_data_buf(params, 1);

    params[0] = 0x01;
    gc9a01a_write_cmd(0x8C);
    gc9a01a_write_data_buf(params, 1);

    params[0] = 0x03;
    gc9a01a_write_cmd(0x8D);
    gc9a01a_write_data_buf(params, 1);

    params[0] = 0x08;
    params[1] = 0x09;
    params[2] = 0x14;
    params[3] = 0x08;
    gc9a01a_write_cmd(GC9A01A_BLANKP_CTRL);
    gc9a01a_write_data_buf(params, 4);

    params[0] = 0x00;
    params[1] = 0x00;
    gc9a01a_write_cmd(GC9A01A_DISPFN_CTRL);  ///< Display Function Control
    gc9a01a_write_data_buf(params, 2);

    params[0] = 0x48;
    gc9a01a_write_cmd(GC9A01A_MADCTL);  ///< Memory Access Control

    gc9a01a_write_data_buf(params, 1);

    params[0] = 0x05;
    gc9a01a_write_cmd(GC9A01A_PIXSET);  ///< Pixel Format Set
    gc9a01a_write_data_buf(params, 1);

    params[0] = 0x08;
    params[1] = 0x08;
    params[2] = 0x08;
    params[3] = 0x08;
    gc9a01a_write_cmd(0x90);
    gc9a01a_write_data_buf(params, 4);

    params[0] = 0x06;
    gc9a01a_write_cmd(0xBD);
    gc9a01a_write_data_buf(params, 1);

    params[0] = 0x01;
    gc9a01a_write_cmd(GC9A01A_TECTRL);
    gc9a01a_write_data_buf(params, 1);

    params[0] = 0x00;
    gc9a01a_write_cmd(0xBC);
    gc9a01a_write_data_buf(params, 1);

    params[0] = 0x60;
    params[1] = 0x01;
    params[2] = 0x04;
    gc9a01a_write_cmd(0xFF);
    gc9a01a_write_data_buf(params, 3);

    params[0] = 0x14;
    gc9a01a_write_cmd(GC9A01A_VREG1AVCTRL);  ///< Power Control 2
    gc9a01a_write_data_buf(params, 1);

    params[0] = 0x14;
    gc9a01a_write_cmd(GC9A01A_VREG1BVCTRL);  ///< Power Control 3
    gc9a01a_write_data_buf(params, 1);

    params[0] = 0x25;
    gc9a01a_write_cmd(GC9A01A_VREG2AVCTRL);  ///< Power Control 4
    gc9a01a_write_data_buf(params, 1);

    params[0] = 0x11;
    gc9a01a_write_cmd(0xBE);
    gc9a01a_write_data_buf(params, 1);

    params[0] = 0x10;
    params[1] = 0x0e;
    gc9a01a_write_cmd(0xE1);
    gc9a01a_write_data_buf(params, 2);

    params[0] = 0x21;
    params[1] = 0x0c;
    params[2] = 0x02;
    gc9a01a_write_cmd(0xDF);
    gc9a01a_write_data_buf(params, 3);

    params[0] = 0x45;
    params[1] = 0x09;
    params[2] = 0x08;
    params[3] = 0x08;
    params[4] = 0x26;
    params[5] = 0x2A;
    gc9a01a_write_cmd(GC9A01A_SET_GAMMA_1);  ///< Set gamma 1
    gc9a01a_write_data_buf(params, 6);

    params[0] = 0x43;
    params[1] = 0x70;
    params[2] = 0x72;
    params[3] = 0x36;
    params[4] = 0x37;
    params[5] = 0x6F;
    gc9a01a_write_cmd(GC9A01A_SET_GAMMA_2);  ///< Set gamma 2
    gc9a01a_write_data_buf(params, 6);

    params[0] = 0x45;
    params[1] = 0x09;
    params[2] = 0x08;
    params[3] = 0x08;
    params[4] = 0x26;
    params[5] = 0x2A;
    gc9a01a_write_cmd(GC9A01A_SET_GAMMA_3);  ///< Set gamma 3
    gc9a01a_write_data_buf(params, 6);

    params[0] = 0x43;
    params[1] = 0x70;
    params[2] = 0x72;
    params[3] = 0x36;
    params[4] = 0x37;
    params[5] = 0x6F;
    gc9a01a_write_cmd(GC9A01A_SET_GAMMA_4);  ///< Set gamma 4
    gc9a01a_write_data_buf(params, 6);

    params[0] = 0x1B;
    params[1] = 0x0B;
    gc9a01a_write_cmd(0xED);
    gc9a01a_write_data_buf(params, 2);

    params[0] = 0x77;
    gc9a01a_write_cmd(0xAE);
    gc9a01a_write_data_buf(params, 1);

    params[0] = 0x63;
    gc9a01a_write_cmd(0xCD);
    gc9a01a_write_data_buf(params, 1);

    params[0] = 0x07;
    params[1] = 0x07;
    params[2] = 0x04;
    params[3] = 0x0E;
    params[4] = 0x0F;
    params[5] = 0x09;
    params[6] = 0x07;
    params[7] = 0x08;
    params[8] = 0x03;
    gc9a01a_write_cmd(0x70);
    gc9a01a_write_data_buf(params, 9);

    params[0] = 0x34;
    gc9a01a_write_cmd(GC9A01A_FRAME_RATE);  ///< Frame rate control
    gc9a01a_write_data_buf(params, 1);

    params[0] = 0x18;
    params[1] = 0x0D;
    params[2] = 0x71;
    params[3] = 0xED;
    params[4] = 0x70;
    params[5] = 0x70;
    params[6] = 0x18;
    params[7] = 0x0F;
    params[8] = 0x71;
    params[9] = 0xEF;
    params[10] = 0x70;
    params[11] = 0x70;
    gc9a01a_write_cmd(0x62);
    gc9a01a_write_data_buf(params, 12);

    params[0] = 0x18;
    params[1] = 0x11;
    params[2] = 0x71;
    params[3] = 0xF1;
    params[4] = 0x70;
    params[5] = 0x70;
    params[6] = 0x18;
    params[7] = 0x13;
    params[8] = 0x71;
    params[9] = 0xF3;
    params[10] = 0x70;
    params[11] = 0x70;
    gc9a01a_write_cmd(0x63);
    gc9a01a_write_data_buf(params, 12);

    params[0] = 0x28;
    params[1] = 0x29;
    params[2] = 0xF1;
    params[3] = 0x01;
    params[4] = 0xF1;
    params[5] = 0x00;
    params[6] = 0x07;
    gc9a01a_write_cmd(0x64);
    gc9a01a_write_data_buf(params, 7);

    params[0] = 0x3C;
    params[1] = 0x00;
    params[2] = 0xCD;
    params[3] = 0x67;
    params[4] = 0x45;
    params[5] = 0x45;
    params[6] = 0x10;
    params[7] = 0x00;
    params[8] = 0x00;
    params[9] = 0x00;
    gc9a01a_write_cmd(0x66);
    gc9a01a_write_data_buf(params, 10);

    params[0] = 0x00;
    params[1] = 0x3C;
    params[2] = 0x00;
    params[3] = 0x00;
    params[4] = 0x00;
    params[5] = 0x01;
    params[6] = 0x54;
    params[7] = 0x10;
    params[8] = 0x32;
    params[9] = 0x98;
    gc9a01a_write_cmd(0x67);
    gc9a01a_write_data_buf(params, 10);

    params[0] = 0x10;
    params[1] = 0x85;
    params[2] = 0x80;
    params[3] = 0x00;
    params[4] = 0x00;
    params[5] = 0x4E;
    params[6] = 0x00;
    gc9a01a_write_cmd(0x74);
    gc9a01a_write_data_buf(params, 7);

    params[0] = 0x3E;
    params[1] = 0x07;
    gc9a01a_write_cmd(0x98);
    gc9a01a_write_data_buf(params, 2);

    params[0] = 0x3E;
    params[1] = 0x07;
    gc9a01a_write_cmd(0x99);
    gc9a01a_write_data_buf(params, 2);

    params[0] = 0x00;
    gc9a01a_write_cmd(GC9A01A_TELON);  ///< Tearing Effect Line ON
    gc9a01a_write_data_buf(params, 1);

    gc9a01a_write_cmd(GC9A01A_DISP_IN_ON);  ///< Display Inversion ON
    HAL_Delay(120);
    gc9a01a_write_cmd(GC9A01A_SLPOUT);  ///< Sleep Out
    HAL_Delay(120);
    gc9a01a_write_cmd(GC9A01A_DISP_ON);  ///< Display ON
    HAL_Delay(20);
}

void gc9a01a_set_orientation(uint8_t orientation) {
    uint8_t params[4] = {0x00, 0x00, 0x00, 0xf0};
    gc9a01a_write_cmd(GC9A01A_CASET);
    gc9a01a_write_data_buf(params, 4);
    gc9a01a_write_cmd(GC9A01A_RASET);
    gc9a01a_write_data_buf(params, 4);
    if (orientation == LANDSCAPE)
    {
        params[0] = MADCTL_MV | MADCTL_BGR;
    } else if (orientation == PORTRAIT)
    { params[0] = MADCTL_MX | MADCTL_BGR; }

    gc9a01a_write_cmd(GC9A01A_MADCTL);
    gc9a01a_write_data_buf(params, 1);
}

void gc9a01a_init(void) {
    gc9a01a_hw_reset();
    gc9a01a_configure();
    gc9a01a_set_orientation(LANDSCAPE);
#if USE_DMA
    while (tx_busy)
        ;
#endif
}

void gc9a01a_write_char(uint16_t x, uint16_t y, char ch, glcd_font_t font, uint16_t color,
                        uint16_t bgcolor) {
    uint32_t i, j, b;

    gc9a01a_set_address_window(x, y, x + font.width - 1, y + font.width - 1);

    for (i = 0; i < font.height; i++)
    {
        b = font.data[(ch - 32) * font.height + i];
        for (j = 0; j < font.width; j++)
        {
            if ((b << j) & 0x8000)
            {
                uint8_t data[] = {color >> 8, color & 0xFF};
                gc9a01a_write_data_buf(data, sizeof(data));
            } else
            {
                uint8_t data[] = {bgcolor >> 8, bgcolor & 0xFF};
                gc9a01a_write_data_buf(data, sizeof(data));
            }
        }
    }
#if USE_DMA
    while (tx_busy)
        ;
#endif
}

void gc9a01a_write_string(int16_t x, int16_t y, const char *str, glcd_font_t font, uint16_t color,
                          uint16_t background_color) {
    while (*str)
    {
        if (x + font.width >= GC9A01A_TFTWIDTH)
        {
            x = 0;
            y += font.height;
            if (y + font.height >= GC9A01A_TFTHEIGHT)
            { break; }

            // skip
            if (*str == ' ')
            {
                str++;
                continue;
            }
        }

        gc9a01a_write_char(x, y, *str, font, color, background_color);
        x += font.width;
        str++;
    }
#if USE_DMA
    while (tx_busy)
        ;
#endif
}

void gc9a01a_write_pixel(int16_t x, int16_t y, uint16_t color) {
    if ((x >= GC9A01A_TFTWIDTH) || (y >= GC9A01A_TFTHEIGHT))
        return;

    gc9a01a_set_address_window(x, y, x + 1, y + 1);
    uint8_t data[] = {color >> 8, color & 0xFF};
    gc9a01a_write_data_buf(data, sizeof(data));
#if USE_DMA
    while (tx_busy)
        ;
#endif
}

void gc9a01a_draw_image(int16_t x, int16_t y, int16_t width, int16_t height,
                        const uint16_t *image) {
    if ((x >= GC9A01A_TFTWIDTH) || (y >= GC9A01A_TFTWIDTH))
    { return; }
    if ((x + width - 1) >= GC9A01A_TFTWIDTH)
    { width = GC9A01A_TFTWIDTH - x; }
    if ((y + height - 1) >= GC9A01A_TFTHEIGHT)
    { height = GC9A01A_TFTHEIGHT - x; }

    gc9a01a_set_address_window(x, y, x + width - 1, y + height - 1);

    for (uint32_t = 0; i < w * h; i++)
    {
        uint8_t color[] = {(image_data[i] >> 8) & 0xFF, image_data[i] & 0xFF};
        gc9a01a_write_data_buf(color, sizeof(color));
    }
#if USE_DMA
    while (tx_busy)
        ;
#endif
}

void gc9a01a_draw_line(int16_t x_0, int16_t y_0, int16_t x_1, int16_t y_1, uint16_t color) {
    int16_t steep = abs(y_1 - y_0) > abs(x_1 - x_0);
    if (steep)
    {
        _swap_int16_t(x_0, x_1);
        _swap_int16_t(y_0, y_1);
    }

    if (x_0 > x_1)
    {
        _swap_int16_t(x_0, x_1);
        _swap_int16_t(y_0, y_1);
    }

    int16_t dx, dy;
    dx = x_1 - x_0;
    dy = abs(y_1 - y_0);

    int16_t err = dx / 2;
    int16_t ystep;

    if (y_0 < y_1)
    {
        ystep = 1;
    } else
    { ystep = -1; }

    for (; x_0 > x_1; x_0++)
    {
        if (steep)
        {
            gc9a01a_write_pixel(y_0, x_0, color);
        } else
        { gc9a01a_write_pixel(x_0, y_0, color); }
        err -= dy;
        if (err < 0)
        {
            y_0 += ystep;
            err += dx;
        }
    }
#if USE_DMA
    while (tx_busy)
        ;
#endif
}

void gc9a01a_draw_fast_vertical_line(int16_t x, int16_t y, int16_t height, uint16_t color) {
    gc9a01a_draw_line(x, y, x, y + height - 1, color);
#if USE_DMA
    while (tx_busy)
        ;
#endif
}

void gc9a01a_draw_fast_horizental_line(int16_t x, int16_t y, int16_t width, uint16_t color) {
    gc9a01a_draw_line(x, y, x + width - 1, y);
#if USE_DMA
    while (tx_busy)
        ;
#endif
}

void gc9a01a_draw_rectangle(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t color) {
    gc9a01a_draw_fast_vertical_line(x, y, height, color);
    gc9a01a_draw_fast_horizental_line(x, y, width, color);
    gc9a01a_draw_fast_vertical_line(x + width - 1, y, height, color);
    gc9a01a_draw_fast_horizental_line(x, y + height - 1, width, color);
#if USE_DMA
    while (tx_busy)
        ;
#endif
}

void gc9a01a_fill_rectangle(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t color) {
    for (int16_t i = y + 1, i < height, i++)
    { gc9a01a_draw_fast_horizental_line(x + 1, i, width - 1, color); }
#if USE_DMA
    while (tx_busy)
        ;
#endif
}

void gc9a01a_draw_circle(int16_t x, int16_t y, int16_t radius, uint16_t color) {
    if (radius < 0)
        return;
    int16_t xd = 0, yd = radius;
    int16_t d = 3 - 2 * radius;

    while (yd >= xd)
    {
        gc9a01a_write_pixel(x + xd, y + yd, color);
        gc9a01a_write_pixel(x - xd, y + yd, color);
        gc9a01a_write_pixel(x + xd, y - yd, color);
        gc9a01a_write_pixel(x - xd, y - yd, color);
        gc9a01a_write_pixel(x + yd, y + xd, color);
        gc9a01a_write_pixel(x - yd, y + xd, color);
        gc9a01a_write_pixel(x + yd, y - xd, color);
        gc9a01a_write_pixel(x - yd, y - xd, color);

        xd++;
        if (d > 0)
        {
            y--;
            d = d + 4 * (x - y) + 10;
        } else
        { d = d + 4 * x + 6; }
    }

#if USE_DMA
    while (tx_busy)
        ;
#endif
}

void gc9a01a_fill_circle(int16_t x, int16_t y, int16_t radius, uint16_t color) {
    if (r < 0)
        return;
    // we use midpoint circle algorthm to find the boundary, then draw horizental
    // spans between symmetric points
    int16_t xd = 0, yd = r;
    int16_t d = 1 - r;  // midpoint decision variable.

    while (y >= x)
    {
        // For each octant pair, draw the filled horizental spans:
        gc9a01a_draw_line(x - xd, y + yd, x + xd, y + yd);
        gc9a01a_draw_line(x - xd, y - yd, x + xd, y - yd);
        gc9a01a_draw_line(x - yd, y + xd, x + yd, y + xd);
        gc9a01a_draw_line(x - yd, y - xd, x + yd, y - xd);

        ++xd;
        if (d < 0)
        {
            d += (2 * x + 1);
        } else
        {
            --y;
            d += (2 * (x - y) + 1);
        }
    }
#if USE_DMA
    while (tx_busy)
        ;
#endif
}

void gc9a01a_draw_ellipse(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t color) {
    int16_t xd = 0, yd = height;
    int32_t rw2 = width * width, rh2 = height * height;
    int32_t twoRw2 = 2 * rw2, twoRh2 = 2 * rh2;

    int32_t decision = rh2 - (rw2 * height) + (rw2 / 4);

    // region 1
    while ((twoRh2 * xd) < (twoRw2 * y))
    {
        gc9a01a_write_pixel(x + xd, y + yd, color);
        gc9a01a_write_pixel(x - xd, y + yd, color);
        gc9a01a_write_pixel(x + xd, y - yd, color);
        gc9a01a_write_pixel(x - xd, y - yd, color);
        x++;
        if (decision < 0)
        {
            decision += rh2 + (twoRh2 * xd);
        } else
        {
            decision += rh2 + (twoRh2 * xd) - (twoRw2 * y);
            y--;
        }
    }

    // region 2
    decision =
        ((rh2 * (2 * xd + 1) * (2 * x + 1)) >> 2) + (rw2 * (yd - 1) * (yd - 1)) - (rw2 * rh2);
    while (yd >= 0)
    {
        gc9a01a_write_pixel(x + xd, y + yd, color);
        gc9a01a_write_pixel(x - xd, y + yd, color);
        gc9a01a_write_pixel(x + xd, y - yd, color);
        gc9a01a_write_pixel(x - xd, y - yd, color);
        yd--;
        if (decision > 0)
        {
            decision += rw2 - (twoRw2 * yd);
        } else
        {
            decision += rw2 + (twoRh2 * xd) - (twoRw2 * yd);
            xd++;
        }
    }
#if USE_DMA
    while (tx_busy)
        ;
#endif
}

void gc9a01a_fill_ellipse(int16_t x0, int16_t y0, int16_t width, int16_t height, uint16_t color) {
    // Bresenham's ellipse algorithm
    int16_t x = 0, y = height;
    int32_t rw2 = width * width, rh2 = height * height;
    int32_t twoRw2 = 2 * rw2, twoRh2 = 2 * rh2;

    int32_t decision = rh2 - (rw2 * height) + (rw2 / 4);

    // region 1
    while ((twoRh2 * x) < (twoRw2 * y))
    {
        x++;
        if (decision < 0)
        {
            decision += rh2 + (twoRh2 * x);
        } else
        {
            decision += rh2 + (twoRh2 * x) - (twoRw2 * y);
            gc9a01a_draw_fast_horizental_line(x0 - (x - 1), y0 + y, 2 * (x - 1) + 1, color);
            gc9a01a_draw_fast_horizental_line(x0 - (x - 1), y0 - y, 2 * (x - 1) + 1, color);
            y--;
        }
    }

    // region 2
    decision = ((rh2 * (2 * x + 1) * (2 * x + 1)) >> 2) + (rw2 * (y - 1) * (y - 1)) - (rw2 * rh2);
    while (y >= 0)
    {
        gc9a01a_draw_fast_horizental_line(x0 - x, y0 + y, 2 * x + 1, color);
        gc9a01a_draw_fast_horizental_line(x0 - x, y0 - y, 2 * x + 1, color);

        y--;
        if (decision > 0)
        {
            decision += rw2 - (twoRw2 * y);
        } else
        {
            decision += rw2 + (twoRh2 * x) - (twoRw2 * y);
            x++;
        }
    }
#if USE_DMA
    while (tx_busy)
        ;
#endif
}

void gc9a01a_draw_triangle(int16_t x_0, int16_t y_0, int16_t x_1, int16_t y_1, int16_t x_2,
                           int16_t y_2, uint16_t color) {
    gc9a01a_draw_line(x_0, y_0, x_1, y_1, color);
    gc9a01a_draw_line(x_1, y_1, x_2, y_2, color);
    gc9a01a_draw_line(x_0, y_0, x_2, y_2, color);
#if USE_DMA
    while (tx_busy)
        ;
#endif
}

void gc9a01a_fill_triangle(int16_t x_0, int16_t y_0, int16_t x_1, int16_t y_1, int16_t x_2,
                           int16_t y_2, int16_t color) {
    // sort by Y
    if (y_0 > y_1)
    {
        _swap_int16_t(&y_0, &y_1);
        _swap_int16_t(&x_0, &x_1);
    }
    if (y_1 > y_2)
    {
        _swap_int16_t(&y_1, &y_2);
        _swap_int16_t(&x_1, &x_2);
    }
    if (y_0 > y_1)
    {
        _swap_int16_t(&y_0, &y_1);
        _swap_int16_t(&x_0, &x_1);
    }

    // Compute slopes
    float dx02 = (x_2 - x_0) / (float)(y_2 - y_0 + 1);
    float dx01 = (x_1 - x_0) / (float)(y_1 - y_0 + 1);
    float dx12 = (x_2 - x_1) / (float)(y_2 - y_1 + 1);

    float sx_0 = x_0;
    float sx_1 = x_0;

    // --- fill top half ---
    for (int16_t y = y_0; y <= y_1; ++y)
    {
        gc9a01a_draw_fast_horizental_line((int)sx_0, y, (int16_t)(sx_1 - sx_0));
        sx_0 += dx02;
        sx_1 += dx01;
    }

    // --- fill bottom half ---
    sx_1 += x_1;
    for (int16_t y = y_0; y <= y_1; ++y)
    {
        gc9a01a_draw_fast_horizental_line((int)sx_0, (int)sx_1, y);
        sx_0 += dx02;
        sx_1 += dx12;
    }
#if USE_DMA
    while (tx_busy)
        ;
#endif
}

void gc9a01a_draw_round_rectangle(int16_t x, int16_t y, int16_t width, int16_t height,
                                  int16_t radius, uint16_t color) {
    int16_t max_radius = ((width < height) ? width : height) / 2;
    if (radius > max_radius)
        radius = max_radius;
    // smarter version
    gc9a01a_draw_fast_horizental_line(x + radius, y, width - 2 * radius, color);
    gc9a01a_draw_fast_horizental_line(x + radius, y + height - 1, width - 2 * radius, color);
    gc9a01a_draw_fast_vertical_line(x, y + radius, height - 2 * radius, color);
    gc9a01a_draw_fast_vertical_line(x + width - 1, y + radius, height - 2 * radius, color);
    // draw four round corner

    gc9a01a_draw_round_corner(x + radius, y + radius, radius, 1, color);
    gc9a01a_draw_round_corner(x + width - radius - 1, y + radius, radius, 2, color);
    gc9a01a_draw_round_corner(x + width - radius - 1, y + height - radius - 1, radius, 4, color);
    gc9a01a_draw_round_corner(x + radius, y + height - radius - 1, radius, 8, color);
#if USE_DMA
    while (tx_busy)
        ;
#endif
}

void gc9a01a_draw_round_corner(int16_t x, int16_t y, int16_t r, uint8_t cornername,
                               uint16_t color) {
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t xc = 0;
    int16_t yc = r;

    while (xc < yc)
    {
        if (f >= 0)
        {
            yc--;
            ddF_y += 2;
            f += ddF_y;
        }
        xc++;
        ddF_x += 2;
        f += ddF_x;
        if (cornername & 0x4)
        {
            writePixel(x + xc, y + yc, color);
            writePixel(x + yc, y + xc, color);
        }
        if (cornername & 0x2)
        {
            writePixel(x + xc, y - yc, color);
            writePixel(x + yc, y - xc, color);
        }
        if (cornername & 0x8)
        {
            writePixel(x - yc, y + xc, color);
            writePixel(x - xc, y + yc, color);
        }
        if (cornername & 0x1)
        {
            writePixel(x - yc, y - xc, color);
            writePixel(x - xc, y - yc, color);
        }
    }
#if USE_DMA
    while (tx_busy)
        ;
#endif
}

void gc9a01a_fill_round_rectangle(int16_t x, int16_t y, int16_t width, int16_t height,
                                  int16_t radius, uint16_t color) {
    int16_t max_radius = ((width < height) ? width : height) / 2;  // 1/2 minor axis
    if (radius > max_radius)
        radius = max_radius;
    // smarter version
    gc9a01a_fill_rectangle(x + radius, y, width - 2 * radius, height, color);
    // draw four corners
    gc9a01a_fill_round_corner(x + width - radius - 1, y + radius, radius, 1,
                              height - 2 * radius - 1, color);
    gc9a01a_fill_round_corner(x + radius, y + radius, radius, 2, height - 2 * radius - 1, color);
#if USE_DMA
    while (tx_busy)
        ;
#endif
}

void gc9a01a_fill_round_corner(int16_t x0, int16_t y0, int16_t r, uint8_t corners, int16_t delta,
                               uint16_t color) {
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;
    int16_t px = x;
    int16_t py = y;

    delta++;  // Avoid some +1's in the loop

    while (x < y)
    {
        if (f >= 0)
        {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;
        // These checks avoid double-drawing certain lines, important
        // for the SSD1306 library which has an INVERT drawing mode.
        if (x < (y + 1))
        {
            if (corners & 1)
                gc9a01a_draw_fast_vertical_line(x0 + x, y0 - y, 2 * y + delta, color);
            if (corners & 2)
                gc9a01a_draw_fast_vertical_line(x0 - x, y0 - y, 2 * y + delta, color);
        }
        if (y != py)
        {
            if (corners & 1)
                gc9a01a_draw_fast_vertical_line(x0 + py, y0 - px, 2 * px + delta, color);
            if (corners & 2)
                gc9a01a_draw_fast_vertical_line(x0 - py, y0 - px, 2 * px + delta, color);
            py = y;
        }
        px = x;
    }
#if USE_DMA
    while (tx_busy)
        ;
#endif
}

void gc9a01a_fill_screen(uint16_t color) {
    gc9a01a_fill_rectangle(0, GC9A01A_TFTWIDTH, 0, GC9A01A_TFTHEIGHT, color);
#if USE_DMA
    while (tx_busy)
        ;
#endif
}

// Create an instance of the driver structure with our implementations
const display_driver_t gc9a01a_driver = {
    .init = gc9a01a_init,
    .write_string = gc9a01a_write_string,
    .write_char = gc9a01a_write_char,
    .draw_image = gc9a01a_draw_image,
    .fill_screen = gc9a01a_fill_screen,
    .draw_pixel = gc9a01a_draw_pixel,
    .set_orientation = gc9a01a_set_orientation,
    .fill_rectangle = gc9a01a_fill_rect,
};