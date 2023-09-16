#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "../utils/log.h"
#include "../keyboard/keyboard.h"
#include "../user/cmd.h"

#include "../stdlib/types.h"

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

int cursor;

void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg);
void fb_set_cursor(unsigned short pos);
void fb_write(char *buf, signed int len);
void fb_print_after(char *buf, size_t len);
void fb_println(char *buf, size_t len);
void fb_backspace();
void fb_clear();
void printf(char *buf, const char *format, ...);

#endif // FRAMEBUFFER_H
