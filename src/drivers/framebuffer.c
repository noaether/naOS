#include "framebuffer.h"
#include "../utils/io.h"

#include "../stdlib/types.h"
#include "../user/cmd.h"

/* framebuffer mm io */
char *fb = (char *)0x000B8000;

/* parameters and memory */
int cursor = 0;
unsigned char def_fg = FB_WHITE;
unsigned char def_bg = FB_BLACK;

int since_enter = 0;

char input_buffer[80];

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
void fb_write(char *buf, signed int len)
{

  if (len == -1) // escaped char
  {
    char since_enter_str[10];

    log("KBD | Escaped Character", LOG_DEBUG);
    switch (buf[0])
    {
    case '\n':
      // get since_enter amount of characters from the buffer
      for (uint8_t i = 0; i < since_enter; i++)
      {
        input_buffer[i] = fb[(cursor - since_enter + i) * 2];
      }

      if (cursor > (79 * 24))
      {
        fb_clear();
        fb_write("naOS> ", 6);
      }

      input_buffer[since_enter] = '\0'; // Null-terminate the buffer
      log(input_buffer, LOG_INFO);

      cursor = (cursor / 80 + 1) * 80;
      fb_set_cursor(cursor);

      citoa(since_enter, since_enter_str, 10);

      interpret(input_buffer, since_enter);

      log(since_enter_str, LOG_DEBUG);

      since_enter = 0;
      clear(since_enter_str, 10);
      clear(input_buffer, 80);

      break;
    }
  }
  else
  {
    int i = 0;
    while (i < len)
    {
      fb_write_cell(i * 2, buf[i], def_fg, def_bg);
      i++;
    }
    fb_set_cursor(i);
  }
}

void fb_print_after(char *buf, size_t len)
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

void fb_println(char *buf, size_t len)
{
  since_enter = 0;
  fb_print_after(buf, len);
  fb_write("\n", -1);
}

void fb_clear()
{
  unsigned int i = 0;
  while (i < 24 * 79)
  {
    fb_write_cell(i * 2, 0x00, def_fg, def_bg);
    i++;
  }
  fb_set_cursor(0);
}

void fb_backspace()
{
  if (cursor > 0 && since_enter > 0)
  {
    since_enter--;
    cursor--;
    fb_write_cell(cursor * 2, 0x00, def_fg, def_bg);
    fb_set_cursor(cursor);
  }
}
