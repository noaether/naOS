#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "../utils/log.h"
#include "../keyboard/keyboard.h"
#include "../user/cmd.h"

#include <stddef.h>
#include <stdint.h>

/* colors */
#define FB_BLACK 0
#define FB_BLUE 1
#define FB_GREEN 2
#define FB_CYAN 3
#define FB_RED 4
#define FB_MAGENTA 5
#define FB_BROWN 6
#define FB_LIGHT_GREY 7
#define FB_DARK_GREY 8
#define FB_LIGHT_BLUE 9
#define FB_LIGHT_GREEN 10
#define FB_LIGHT_CYAN 11
#define FB_LIGHT_RED 12
#define FB_LIGHT_MAGENTA 13
#define FB_LIGHT_BROWN 14
#define FB_WHITE 15

/* The I/O ports */
#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT 0x3D5

/* The I/O port commands */
#define FB_HIGH_BYTE_COMMAND 14
#define FB_LOW_BYTE_COMMAND 15

/**
 * display character c on the position i with color fg and bg.
 *
 * @param i the position, 0 for the first line, first col. 16 for the second line.
 * @param c the displayed character
 * @param fg foreground color
 * @param bg background color
 */
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg);

/** fb_move_cursor:
 *  Moves the cursor of the framebuffer to the given position
 *
 *  @param pos The new position of the cursor
 */
void fb_set_cursor(unsigned short pos);

/**
 * Writes a buffer to the framebuffer.
 *
 * @param buf The buffer to write.
 * @param len The length of the buffer.
 */
void fb_write(char *buf, signed int len);

/**
 * Prints a buffer of characters to the framebuffer, starting from the current cursor position.
 * If a newline character is encountered, the cursor is moved to the beginning of the next line.
 *
 * @param buf Pointer to the buffer of characters to print.
 * @param len The length of the buffer.
 */
void fb_print_after(char *buf, size_t len);

/**
 * Prints a string followed by a newline character to the framebuffer.
 *
 * @param buf The string to print.
 * @param len The length of the string.
 */
void fb_println(char *buf, size_t len);

/**
 * Clears the framebuffer by writing empty cells to all positions.
 *
 * @param None
 *
 * @return None
 */
void fb_clear();

/**
 * @brief Deletes the character before the cursor position in the framebuffer.
 *
 * If the cursor is not at the beginning of the line and the user has typed since the last enter,
 * the function deletes the character before the cursor position, updates the cursor position and
 * the since_enter counter, and updates the framebuffer accordingly.
 *
 * @return void
 */
void fb_backspace();

/**
 * @brief Formats and stores a series of characters and values in a buffer.
 *
 * This function formats and stores a series of characters and values in a buffer.
 * It supports the following format specifiers: %s (string), %d (integer), %c (character), %x (hexadecimal), %f (double).
 *
 * @param buf Pointer to the buffer where the formatted string will be stored.
 * @param format Pointer to the format string.
 * @param ... Optional arguments to be formatted according to the format string.
 */
void sprintf(char *buf, const char *format, ...);

/**
 * Handles arrow key events and moves the cursor accordingly.
 * @param keycode The keycode of the arrow key pressed.
 */
void arrow_key_handler(int keycode);

#endif // FRAMEBUFFER_H
