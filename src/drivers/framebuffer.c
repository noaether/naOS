#include "framebuffer.h"
#include "../utils/io.h"

/* framebuffer mm io */
char *fb = (char *)0x000B8000;

/**
 * display character c on the position i with color fg and bg.
 *
 * @param i the position, 0 for the first line, first col. 16 for the second line.
 * @param c the displayed character
 * @param fg foreground color
 * @param bg background color
 */
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg)
{
  fb[i] = c;
  fb[i + 1] = ((bg & 0x0F) << 4 | (fg & 0x0F));
}

/** fb_move_cursor:
 *  Moves the cursor of the framebuffer to the given position
 *
 *  @param pos The new position of the cursor
 */
void fb_move_cursor(unsigned short pos)
{
  outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
  outb(FB_DATA_PORT, ((pos >> 8) & 0x00FF));
  outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
  outb(FB_DATA_PORT, pos & 0x00FF);
}

/* write a function that prints a string and moves the cursor to the next available position */
void fb_write(char *buf, unsigned int len)
{
  unsigned int i = 0;
  while (i < len)
  {
    fb_write_cell(i * 2, buf[i], FB_WHITE, FB_BLACK);
    i++;
  }
  fb_move_cursor(i);
}

/* write a function that clears the screen */
void fb_clear()
{
  unsigned int i = 0;
  while (i < 24 * 79)
  {
    fb_write_cell(i * 2, ' ', FB_WHITE, FB_BLACK);
    i++;
  }
  fb_move_cursor(0);
}