/**
 *****************************************************************************
 * @file    gfx_display.h
 * @author  Nabli Hatem
 * @brief   This is a generic module that handle different drawing functions.
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
#ifndef GFX_DISPLAY_H
#define GFX_DISPLAY_H

#include "glcdfont.h"

#include <stdint.h>

/**
 *
 */
typedef enum
{
    PORTRAIT = 0,
    LANDSCAPE
} display_orientation;

typedef struct
{
    void *init(void);
    void *write_string(int16_t x, int16_t y, const char *str, glcd_font_t font, uint16_t color,
                       uint16_t background_color);
    void *write_char(int16_t x, int16_t y, const char ch, glcd_font_t font, uint16_t color,
                     uint16_t background_color);

    void *write_pixel(int16_t x, int16_t y, uint16_t color);
    void *draw_image(int16_t x, int16_t y, int16_t width, int16_t height, const uint16_t *image);
    void *draw_fast_vertical_line(int16_t x, int16_t y, int16_t height, uint16_t color);
    void *draw_fast_horizental_line(int16_t x, int16_t y, int16_t width, uint16_t color);
    void *draw_line(int16_t x_0, int16_t y_0, int16_t x_1, int16_t y_1, uint16_t color);
    void *draw_rectangle(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t color);
    void *fill_rectangle(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t color);
    void *draw_circle(int16_t x, int16_t y, int16_t radius, uint16_t color);
    void *fill_circle(int16_t x, int16_t y, int16_t radius, uint16_t color);
    void *draw_ellipse(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t color);
    void *fill_ellipse(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t color);
    void *draw_triangle(int16_t x_0, int16_t y_0, int16_t x_1, int16_t y_1, int16_t x_2,
                        int16_t y_2, uint16_t color);
    void *fill_triangle(int16_t x_0, int16_t y_0, int16_t x_1, int16_t y_1, int16_t x_2,
                        int16_t y_2, int16_t color);
    void *draw_round_rectangle(int16_t x_0, int16_t y_0, int16_t width, int16_t height,
                               int16_t radius, uint16_t color);
    void *fill_round_rectangle(int16_t x_0, int16_t y_0, int16_t width, int16_t height,
                               int16_t radius, uint16_t color);
    void *fill_screen(uint16_t color);
    void *orientation(display_orientation orientation);
} gfx_display_driver_t;

void gfx_display_init(void);
void gfx_display_write_string(int16_t x, int16_t y, const char *str, glcd_font_t font,
                              uint16_t color, uint16_t background_color);
void gfx_display_write_char(int16_t x, int16_t y, const char ch, glcd_font_t font, uint16_t color,
                            uint16_t background_color);

void gfx_display_write_pixel(int16_t x, int16_t y, uint16_t color);
void gfx_display_draw_image(int16_t x, int16_t y, int16_t width, int16_t height,
                            const uint16_t *image);
void gfx_display_draw_fast_vertical_line(int16_t x, int16_t y, int16_t height, uint16_t color);
void gfx_display_draw_fast_horizental_line(int16_t x, int16_t y, int16_t width, uint16_t color);
void gfx_display_darw_line(int16_t x_0, int16_t y_0, int16_t x_1, int16_t y_1, uint16_t color);
void gfx_display_draw_rectangle(int16_t x, int16_t y, int16_t width, int16_t height,
                                uint16_t color);
void gfx_display_fill_rectangle(int16_t x, int16_t y, int16_t width, int16_t height,
                                uint16_t color);
void gfx_display_draw_circle(int16_t x, int16_t y, int16_t radius, uint16_t color);
void gfx_display_fill_circle(int16_t x, int16_t y, int16_t radius, uint16_t color);
void gfx_display_draw_ellipse(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t color);
void gfx_display_fill_ellipse(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t color);
void gfx_display_draw_triangle(int16_t x_0, int16_t y_0, int16_t x_1, int16_t y_1, int16_t x_2,
                               int16_t y_2, uint16_t color);
void gfx_display_fill_triangle(int16_t x_0, int16_t y_0, int16_t x_1, int16_t y_1, int16_t x_2,
                               int16_t y_2, int16_t color);
void gfx_display_draw_round_rectangle(int16_t x_0, int16_t y_0, int16_t width, int16_t height,
                                      int16_t radius, uint16_t color);
void gfx_display_fill_round_rectangle(int16_t x_0, int16_t y_0, int16_t width, int16_t height,
                                      int16_t radius, uint16_t color);
void gfx_display_fill_screen(uint16_t color);
void gfx_display_set_orientation(display_orientation orientation);
void gfx_display_register_driver(const gfx_display_driver_t *driver);

#endif /* GFX_DISPLAY_H */