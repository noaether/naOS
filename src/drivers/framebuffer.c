#include "framebuffer.h"

/* framebuffer mm io */
char *fb = (char *)0x000B8000;

/* parameters and memory */
int cursor = 0;
unsigned char def_fg = FB_WHITE;
unsigned char def_bg = FB_BLACK;

char input_buffer[256];

/* PRIMITIVE FUNCTIONS */

void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg)
{
  fb[i] = c;
  fb[i + 1] = ((bg & 0x0F) << 4 | (fg & 0x0F));
}

void fb_set_cursor(unsigned short pos)
{
  cursor = pos;

  outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
  outb(FB_DATA_PORT, ((pos >> 8) & 0x00FF));
  outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
  outb(FB_DATA_PORT, pos & 0x00FF);
}


void fb_write(char *buf, signed int len)
{

  if (len == -1) // escaped char
  {
    log("KBD | Escaped Character", LOG_DEBUG);

    char since_enter_str[10];

    switch (buf[0])
    {
    case '\n':
      if (since_enter == 0)
      {
        if (cursor > (80 * 24))
        {
          fb_clear();
          fb_set_cursor(0);
          fb_clear();
          break;
        }
        else
        {
          cursor = (cursor / 80 + 1) * 80;
          fb_set_cursor(cursor);
        }
      }
      else
      {
        // get since_enter amount of characters from the buffer
        for (uint8_t i = 0; i < since_enter; i++)
        {
          input_buffer[i] = fb[(cursor - since_enter + i) * 2];
        }

        input_buffer[since_enter] = '\0'; // Null-terminate the buffer
        log(input_buffer, LOG_INFO);

        if (cursor > (80 * 24))
        {
          fb_clear();
          fb_write("naOS> ", 6);
        }

        cursor = (cursor / 80 + 1) * 80;
        fb_set_cursor(cursor);

        citoa(since_enter, since_enter_str, 10);

        interpret(input_buffer, since_enter);

        log(since_enter_str, LOG_DEBUG);

        since_enter = 0;
        clear(since_enter_str, 10);
        clear(input_buffer, 80);
      }

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
    if (buf[i] == '\n')
    {
      since_enter = 0;
      fb_write("\n", -1);
    }
    else
    {
      fb_write_cell(cursor * 2, buf[i], def_fg, def_bg);
      cursor++;
    }
    i++;
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
  while (i < 25 * 80)
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

void _putchar(char c)
{
  fb_write_cell(cursor * 2, c, def_fg, def_bg);
  cursor++;
  fb_set_cursor(cursor);
}

void sprintf(char *buf, const char *format, ...)
{
  char *p = buf;
  char c;
  char str_buf[sizeof(size_t)]; // Adjust the size as needed

  // Pointer to the first argument after 'format'
  void *arg = (void *)(&format + 1);

  while ((c = *format++) != '\0')
  {
    if (c != '%')
    {
      *p++ = c;
    }
    else
    {
      c = *format++;
      if (c == 's')
      {
        char *arg_str = *(char **)arg;
        while (*arg_str)
        {
          *p++ = *arg_str++;
        }
        arg += sizeof(char *);
      }
      else if (c == 'd')
      {
        int arg_int = *(int *)arg;
        // void itoa(int n, char *buf, int buf_size);
        itoa(arg_int, str_buf, 20);
        char *arg_str = str_buf;
        while (*arg_str)
        {
          *p++ = *arg_str++;
        }
        arg += sizeof(int);
      }
      else if (c == 'c')
      {
        char arg_char = *(char *)arg;
        *p++ = arg_char;
        arg += sizeof(char);
      }
      else if (c == 'x')
      {
        int arg_int = *(int *)arg;
        // void itoa(int n, char *buf, int buf_size);
        itoa(arg_int, str_buf, 20);
        char *arg_str = str_buf;
        while (*arg_str)
        {
          *p++ = *arg_str++;
        }
        arg += sizeof(int);
      }
      else if (c == 'f')
      {
        double arg_double = *(double *)arg;
        // void itoa(int n, char *buf, int buf_size);
        (void)itoa(arg_double, str_buf, 20);
        char *arg_str = str_buf;
        while (*arg_str)
        {
          *p++ = *arg_str++;
        }
        arg += sizeof(double);
      }
      // Add support for more format specifiers as needed
    }
  }

  *p = '\0';
}

void arrow_key_handler(int keycode)
{
  if ((72 - keycode) == 0)
  {
    fb_set_cursor(cursor - 80);
  }
  else if ((80 - keycode) == 0)
  {
    fb_set_cursor(cursor + 80);
  }
  else if ((75 - keycode) == 0)
  {
    // avoid access to 5 first chars of line
    if (fb[cursor] != '>') /* '>' */
    {
      fb_set_cursor(cursor - 1);
    }
  }
  else if ((77 - keycode) == 0)
  {
    if (fb[cursor] != '>') /* '>' */
    {
      fb_set_cursor(cursor + 1);
    }
  }
}
