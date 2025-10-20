/**
 *****************************************************************************
 * @file    glcdfont.h
 * @author  Nabli Hatem
 * @brief   This is the classic fixed-space bitmap defined by the glcdfont
 *          structure.
 *          To use a font in your MCU, include the corresponding .h file and
 *          pass adress of glcd_font struct to set_font().
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

/* Define to prevent recursive inclusion ------------------------------------*/
#ifndef GLCD_FONT_H
#define GLCD_FONT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -----------------------------------------------------------------*/
#include <stdint.h>

/**
 * @brief This is the data stored for font.
 * @param width This is the width of the font.
 * @param hight This is the height of the font.
 * @param data  This is the data table.
 */
typedef struct
{
    uint8_t width;
    uint8_t height;
    const uint16_t *data;
} glcd_font_t;
/**
 * @brief This structure define the size of the font.
 * @param height This is the height of the font.
 * @param length This is the length of the font.
 */
typedef struct
{
    uint16_t height;
    uint16_t length;
} glcd_font_size_t;

/**
 * @brief This is a 7 x 10 font size structure
 */
extern glcd_font_t font_7_x_10;
/**
 * @brief This is a 11 x 18 font size structure
 */
extern glcd_font_t font_11_x_18;
/**
 * @brief This is a 16 x 26 font size structure
 */
extern glcd_font_t font_16_x_26;

/**
 * @brief This function calculate string length and height in units of pixels
 *        depending on string and font used
 * @param *str: String to be checked for lenght and height
 * @param *size_struct: Pointer to empty reference of glcd_font_size structure
 * where informations will be saved.
 * @param *font: Pointer to the reference of glcd_font used for calculation
 * @retval Pointer to string used for length and height
 */
char *fonts_get_string_size(char *str, glcd_font_size_t *size_struct, glcd_font_t *font);

#ifdef __cplusplus
}
#endif

#endif /* GLCD_FONT_H */