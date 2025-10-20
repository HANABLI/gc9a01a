/**
 *****************************************************************************
 * @file    gfx_display.c
 * @author  Nabli Hatem
 * @brief   This is the gfx_display generic module that handle diferrent
 *          drawing function.
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

#include "gfx_display.h"

static const gfx_display_driver_t *lcd_driver = NULL;

void gfx_display_register_driver(const gfx_display_driver_t *driver) {
    lcd_driver = driver;
}

void gfx_display_init(void) {
    if (lcd_driver && lcd_driver->init)
    { lcd_driver->init(); }
}

void gfx_display_write_string(int16_t x, int16_t y, const char *str, glcd_font_t font,
                              uint16_t color, uint16_t background_color) {
    if (lcd_driver && lcd_driver->write_string)
    { lcd_driver->write_string(x, y, str, font, color); }
}

void gfx_display_write_char(int16_t x, int16_t y, const char ch, glcd_font_t font, uint16_t color,
                            uint16_t background_color) {
    if (lcd_driver && lcd_driver->write_char)
    { lcd_driver->write_char(x, y, ch, font, color, background_color); }
}

void gfx_display_write_pixel(int16_t x, int16_t y, uint16_t color) {
    if (lcd_driver && lcd_driver->write_pixel)
    { lcd_driver->write_pixel(x, y, color); }
}

void gfx_display_draw_image(int16_t x, int16_t y, int16_t width, int16_t height,
                            const uint16_t *image) {
    if (lcd_driver && lcd_driver->draw_image)
    { lcd_driver->draw_image(x, y, width, height, image); }
}

void gfx_display_draw_fast_vertical_line(int16_t x, int16_t y, int16_t height, uint16_t color) {
    if (lcd_driver && lcd_driver->draw_fast_vertical_line)
    { lcd_driver->draw_fast_vertical_line(x, y, height, color); }
}

void gfx_display_draw_fast_horizental_line(int16_t x, int16_t y, int16_t width, uint16_t color) {
    if (lcd_driver && lcd_driver->draw_fast_horizental_line)
    { lcd_driver->draw_fast_horizental_line(x, y, width, color); }
}

void gfx_display_darw_line(int16_t x_0, int16_t y_0, int16_t x_1, int16_t y_1, uint16_t color) {
    if (lcd_driver && lcd_driver->draw_line)
    { lcd_driver->draw_line(x_0, y_0, x_1, y_1, color); }
}

void gfx_display_draw_rectangle(int16_t x, int16_t y, int16_t width, int16_t height,
                                uint16_t color) {
    if (lcd_driver && lcd_driver->draw_rectangle)
    { lcd_driver->draw_rectangle(x, y, width, height, color); }
}

void gfx_display_fill_rectangle(int16_t x, int16_t y, int16_t width, int16_t height,
                                uint16_t color) {
    if (lcd_driver && lcd_driver->fill_rectangle)
    { lcd_driver->fill_rectangle(x, y, width, height, color); }
}

void gfx_display_draw_circle(int16_t x, int16_t y, int16_t radius, uint16_t color) {
    if (lcd_driver && lcd_driver->draw_circle)
    { lcd_driver->draw_circle(x, y, radius, color); }
}

void gfx_display_fill_circle(int16_t x, int16_t y, int16_t radius, uint16_t color) {
    if (lcd_driver && lcd_driver->fill_circle)
    { lcd_driver->draw_circle(x, y, radius, color); }
}

void gfx_display_draw_ellipse(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t color) {
    if (lcd_driver && lcd_driver->draw_ellipse)
    { lcd_driver->draw_ellipse(x, y, width, height, color); }
}

void gfx_display_fill_ellipse(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t color) {
    if (lcd_driver && lcd_driver->fill_ellipse)
    { lcd_driver->fill_ellipse(x, y, width, height, color); }
}

void gfx_display_draw_triangle(int16_t x_0, int16_t y_0, int16_t x_1, int16_t y_1, int16_t x_2,
                               int16_t y_2, uint16_t color) {
    if (lcd_driver && lcd_driver->draw_triangle)
    { lcd_driver->draw_triangle(x_0, y_0, x_1, y_1, x_2, y_2, color); }
}

void gfx_display_fill_triangle(int16_t x_0, int16_t y_0, int16_t x_1, int16_t y_1, int16_t x_2,
                               int16_t y_2, int16_t color) {
    if (lcd_driver && lcd_driver->fill_triangle)
    { lcd_driver->fill_triangle(x_0, y_0, x_1, y_1, x_2, y_2, color); }
}

void gfx_display_draw_round_rectangle(int16_t x_0, int16_t y_0, int16_t width, int16_t height,
                                      int16_t radius, uint16_t color) {
    if (lcd_driver && lcd_driver->draw_round_rectangle)
    { lcd_driver->draw_round_rectangle(x_0, y_0, width, height, radius, color); }
}

void gfx_display_fill_round_rectangle(int16_t x_0, int16_t y_0, int16_t width, int16_t height,
                                      int16_t radius, uint16_t color) {
    if (lcd_driver && lcd_driver->fill_round_rectangle)
    { lcd_driver->fill_round_rectangle(x_0, y_0, width, height, radius, color); }
}

void gfx_display_fill_screen(uint16_t color) {
    if (lcd_driver && lcd_driver->fill_screen)
    { lcd_driver->fill_screen(color); }
}

void gfx_display_set_orientation(display_orientation orientation) {
    if (lcd_driver && lcd_driver->orientation)
    { lcd_driver->orientation(orientation); }
}