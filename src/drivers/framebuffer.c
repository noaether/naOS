#include "framebuffer.h"
#include "../utils/io.h"

#include "../stdlib/types.h"

/* framebuffer mm io */
char *fb = (char *)0x000B8000;

/* parameters and memory */
int cursor = 0;
unsigned char def_fg = FB_WHITE;
unsigned char def_bg = FB_BLACK;

/* PRIMITIVE FUNCTIONS */

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
void fb_set_cursor(unsigned short pos)
{
  cursor = pos;

  outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
  outb(FB_DATA_PORT, ((pos >> 8) & 0x00FF));
  outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
  outb(FB_DATA_PORT, pos & 0x00FF);
}

/* high-level functions */
void fb_write(char *buf, unsigned int len)
{
  unsigned int i = 0;
  while (i < len)
  {
    fb_write_cell(i * 2, buf[i], def_fg, def_bg);
    i++;
  }
  fb_set_cursor(i);
}

void fb_print_after(char *buf, unsigned int len)
{
  unsigned int i = 0;
  while (i < len)
  {
    fb_write_cell(cursor * 2, buf[i], def_fg, def_bg);
    i++;
    cursor++;
  }
  fb_set_cursor(cursor);
}

void fb_clear()
{
  unsigned int i = 0;
  while (i < 24 * 79)
  {
    fb_write_cell(i * 2, ' ', def_fg, def_bg);
    i++;
  }
  fb_set_cursor(0);
}

void fb_backspace()
{
  if (cursor > 0)
  {
    cursor--;
    fb_write_cell(cursor * 2, ' ', def_fg, def_bg);
    fb_set_cursor(cursor);
  }
}
