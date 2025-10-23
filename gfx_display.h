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
#include <stddef.h>
#include <stdint.h>

/**
 *
 */
typedef enum
{
    PORTRAIT = 0,
    LANDSCAPE = 1
} display_orientation;

typedef struct
{
    void (*init)(void);
    void (*write_string)(int16_t x, int16_t y, const char *str, glcd_font_t font, uint16_t color,
                         uint16_t background_color);
    void (*write_char)(int16_t x, int16_t y, const char ch, glcd_font_t font, uint16_t color,
                       uint16_t background_color);

    void (*write_pixel)(int16_t x, int16_t y, uint16_t color);
    void (*draw_image)(int16_t x, int16_t y, int16_t width, int16_t height, const uint16_t *image);
    void (*draw_fast_vertical_line)(int16_t x, int16_t y, int16_t height, uint16_t color);
    void (*draw_fast_horizental_line)(int16_t x, int16_t y, int16_t width, uint16_t color);
    void (*draw_line)(int16_t x_0, int16_t y_0, int16_t x_1, int16_t y_1, uint16_t color);
    void (*draw_rectangle)(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t color);
    void (*fill_rectangle)(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t color);
    void (*draw_circle)(int16_t x, int16_t y, int16_t radius, uint16_t color);
    void (*fill_circle)(int16_t x, int16_t y, int16_t radius, uint16_t color);
    void (*draw_ellipse)(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t color);
    void (*fill_ellipse)(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t color);
    void (*draw_triangle)(int16_t x_0, int16_t y_0, int16_t x_1, int16_t y_1, int16_t x_2,
                          int16_t y_2, uint16_t color);
    void (*fill_triangle)(int16_t x_0, int16_t y_0, int16_t x_1, int16_t y_1, int16_t x_2,
                          int16_t y_2, int16_t color);
    void (*draw_round_rectangle)(int16_t x_0, int16_t y_0, int16_t width, int16_t height,
                                 int16_t radius, uint16_t color);
    void (*fill_round_rectangle)(int16_t x_0, int16_t y_0, int16_t width, int16_t height,
                                 int16_t radius, uint16_t color);
    void (*fill_screen)(uint16_t color);
    void (*orientation)(display_orientation orientation);
} gfx_display_driver_t;

/**
 * @brief Initialize the TFT display module.
 * @retval None.
 */
void gfx_display_init(void);

/**
 * @brief Write a string on the display at a specific position, font and color.
 * @param x x-cordinate in pixels.
 * @param y y-cordinate in pixels.
 * @param str pointer to the string to be displayed.
 * @param font font definition of the string.
 * @param color color in RGB565 format.
 * @param background_color in RGB565 format.
 * @retval None.
 */
void gfx_display_write_string(int16_t x, int16_t y, const char *str, glcd_font_t font,
                              uint16_t color, uint16_t background_color);

/**
 * @brief Write a character on the display at a specific position, font and color.
 * @param x x-cordinate in pixels.
 * @param y y-cordinate in pixels.
 * @param char character to be displayed.
 * @param font font definition of the character.
 * @param color color in RGB565 format.
 * @param background_color in RGB565 format.
 * @retval None.
 */
void gfx_display_write_char(int16_t x, int16_t y, const char ch, glcd_font_t font, uint16_t color,
                            uint16_t background_color);

/**
 * @brief Write a pixel on the display at a specific position and color.
 * @param x x-cordinate in pixels.
 * @param y y-cordinate in pixels.
 * @param color color in RGB565 format.
 * @retval None.
 */
void gfx_display_write_pixel(int16_t x, int16_t y, uint16_t color);

/**
 * @brief Draw an image on the display at a specific position, width and height.
 * @param x x-cordinate in pixels.
 * @param y y-cordinate in pixels.
 * @param width the width of the image on th display.
 * @param height the height of the image on the display.
 * @param image pointer to the image to be displayed.
 * @retval None.
 */
void gfx_display_draw_image(int16_t x, int16_t y, int16_t width, int16_t height,
                            const uint16_t *image);

/**
 * @brief Draw a vertical line at a specific position, height and color.
 * @param x x-cordinate in pixels.
 * @param y y-cordinate in pixels.
 * @param height the height of the line.
 * @param color the color in RGB565 format.
 * @retval None.
 */
void gfx_display_draw_fast_vertical_line(int16_t x, int16_t y, int16_t height, uint16_t color);

/**
 * @brief Draw an horizental line at a specific position, width and color.
 * @param x x-cordinate in pixels.
 * @param y y-cordinate in pixels.
 * @param width the width of the line.
 * @param color the color in RGB565 format.
 * @retval None.
 */
void gfx_display_draw_fast_horizental_line(int16_t x, int16_t y, int16_t width, uint16_t color);

/**
 * @brief Draw a line between two pixels width a specific color.
 * @param x_0 x-cordinate of the first pixel.
 * @param y_0 y-cordinate of the first pixel.
 * @param x_1 x-cordinate of the second pixel.
 * @param y_1 y-cordinate of the second pixel.
 * @param color the color in RGB565 format.
 * @retval None.
 */
void gfx_display_darw_line(int16_t x_0, int16_t y_0, int16_t x_1, int16_t y_1, uint16_t color);

/**
 * @brief Draw a rectangle at a specific position using width and height.
 * @param x x-cordinate of the rectangle position.
 * @param y y-cordiante of the rectangle position.
 * @param width the width of the rectangle to be displayed.
 * @param height the height of the rectangle to be displayed.
 * @param color the color of the rectangle's perimeter in RGB56 format.
 * @retval None.
 */
void gfx_display_draw_rectangle(int16_t x, int16_t y, int16_t width, int16_t height,
                                uint16_t color);
/**
 * @brief Fill the rectangle with a spectific color.
 * @param x x-cordinate of the rectangle's position.
 * @param y y-cordinate of the rectangle's position.
 * @param width the width of the rectangle to fill.
 * @param height the height of the rectangle to fill.
 * @param color the color in RGB565 format.
 * @retval None.
 */
void gfx_display_fill_rectangle(int16_t x, int16_t y, int16_t width, int16_t height,
                                uint16_t color);
/**
 * @brief Draw a circle in a specific position using a radius and color.
 * @param x x-cordinate of the circle's position.
 * @param y y-cordinate of the circle's position.
 * @param radius the radius of the circle to draw.
 * @param color the color in RGB565 format.
 * @retval None.
 */
void gfx_display_draw_circle(int16_t x, int16_t y, int16_t radius, uint16_t color);

/**
 * @brief Fill a circle with a specific color.
 * @param x x-cordinate of the circle's position.
 * @param y y-cordinate of the circle's position.
 * @param radius the radius of the circle to fill.
 * @param color the color in RGB565 format.
 * @retval None
 */
void gfx_display_fill_circle(int16_t x, int16_t y, int16_t radius, uint16_t color);

/**
 * @brief Draw an ellipse at a specific position.
 * @param x x-cordinate of the ellipse's position.
 * @param y y-cordinate of the ellipse's position.
 * @param width the width of the ellipse to draw.
 * @param height the height of the ellipse to draw.
 * @param color the color in RGB565 format.
 * @retval None.
 */
void gfx_display_draw_ellipse(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t color);

/**
 * @brief Fill an ellipse with a specific color.
 * @param x x-cordinate of the ellipse to fill.
 * @param y y-cordinate of the ellipse to fill.
 * @param width the width of the ellipse to draw.
 * @param heidht the height of the ellipse to fill.
 * @param color the color in RGB565 format.
 * @retval None.
 */
void gfx_display_fill_ellipse(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t color);

/**
 * @brief Draw a triangle using three pixels positions.
 * @param x_0 x-cordinate of the first pixel.
 * @param y_0 y-cordinate of the first pixel.
 * @param x_1 x-cordinate of the second pixel.
 * @param y_1 y-cordinate of the second pixel.
 * @param x_2 x-cordinate of the third pixel.
 * @param x_2 y-cordinate of the third pixel.
 * @param color the color in RGB565 format.
 * @retval None.
 */
void gfx_display_draw_triangle(int16_t x_0, int16_t y_0, int16_t x_1, int16_t y_1, int16_t x_2,
                               int16_t y_2, uint16_t color);
/**
 * @brief Fill a triangle with a specific color.
 * @param x_0 x-cordinate of the first pixel.
 * @param y_0 y-cordinate of the first pixel.
 * @param x_1 x-cordinate of the second pixel.
 * @param y_1 y-cordinate of the second pixel.
 * @param x_2 x-cordinate of the third pixel.
 * @param x_2 y-cordinate of the third pixel.
 * @param color the color in RGB565 format.
 * @retval None.
 */
void gfx_display_fill_triangle(int16_t x_0, int16_t y_0, int16_t x_1, int16_t y_1, int16_t x_2,
                               int16_t y_2, int16_t color);
/**
 * @brief Draw a round rectangle at a specific position.
 * @param x_0 x-cordinate of the rectangle position.
 * @param y_0 y-cordinate of the rectangle position.
 * @param width the width of the rectangle to draw.
 * @param height the height of the rectangle to draw.
 * @param radius the radius of the rectangle to draw.
 * @param color the color of the rectangle to draw in RGB565 format.
 * @retval None.
 */
void gfx_display_draw_round_rectangle(int16_t x_0, int16_t y_0, int16_t width, int16_t height,
                                      int16_t radius, uint16_t color);
/**
 * @brief Fill a round rectangle with a specific color.
 * @param x_0 x-cordinate of the rectangle to fill.
 * @param y_0 y-cordinate of the rectangle to fill.
 * @param width the width of the rectangle to fill.
 * @param height the height of the rectangle to fill.
 * @param radius the radius of the rectangle to fill.
 * @param color the color in RGB565 foramt.
 */
void gfx_display_fill_round_rectangle(int16_t x_0, int16_t y_0, int16_t width, int16_t height,
                                      int16_t radius, uint16_t color);
/**
 * @brief Fill a screen with a specific color
 * @param color the color in RGB565 format.
 */
void gfx_display_fill_screen(uint16_t color);
/**
 * @brief Set the oriantation of the display.
 * @param orientation PORTRAIT / LANDSCAPE
 */
void gfx_display_set_orientation(display_orientation orientation);
/**
 * @brief register the driver to the display
 */
void gfx_display_register_driver(const gfx_display_driver_t *driver);

#endif /* GFX_DISPLAY_H */