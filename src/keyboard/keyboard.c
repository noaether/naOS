#include "keyboard.h"
#include "keyboard_map.h"

#include "../drivers/irq.h"

#include "../drivers.h"
#include "../utils/io.h"

bool shift_pressed = false; // Global flag to track Shift key state
bool alt_pressed = false;   // Global flag to track Alt key state

void kb_init()
{
  // 0xFD = 1111 1101 in binary. enables only IRQ1
  // Why IRQ1? Remember, IRQ0 exists, it's 0-based
  ioport_out(PIC1_DATA_PORT, 0xFD);
}

void handle_keyboard_interrupt()
{
  ioport_out(0x20, 0x20);

  unsigned char status = ioport_in(KEYBOARD_STATUS_PORT);
  // Lowest bit of status will be set if buffer not empty
  // (thanks mkeykernel)
  /* Lowest bit of status will be set if buffer is not empty */
  if (status & 0x01)
  {
    int keycode = ioport_in(KEYBOARD_DATA_PORT);

    char keycode_str[10];
    citoa(keycode, keycode_str, 10);

    if (keycode < 0)
    {
      char logup[] = "KBD INT UP: ";
      strcat(logup, keycode_str);
      log(logup, LOG_DEBUG);

      if (keycode == -86 || keycode == -74)
      {
        // Shift key released
        shift_pressed = false;
      }
      else if (keycode == -72)
      {
        // Alt key released
        alt_pressed = false;
      }
      return;
    }
    else
    {
      char logdown[] = "KBD INT DOWN: ";
      strcat(logdown, keycode_str);
      log(logdown, LOG_DEBUG);

      if (keycode == 42 || keycode == 54)
      {
        // Shift key pressed
        shift_pressed = true;
      }
      else if (keycode == 56)
      {
        // Alt key pressed
        alt_pressed = true;
      }
    }

    // Check if it's a key press event (the most significant bit is clear)
    if (!(keycode & 0x80))
    {
      char ascii[2];

      if (alt_pressed)
      {
        ascii[0] = keyboard_map3[keycode];
      }
      else if (shift_pressed)
      {
        ascii[0] = keyboard_map2[keycode];
      }
      else
      {
        ascii[0] = keyboard_map[keycode];
      }

      if (ascii[0] < 0)
      {
        // Special cases, will be handled later
        return;
      }

      ascii[1] = '\0'; // Ensure null-terminated string

      if (ascii[0] == 0)
      {
        special_key_handler(keycode_str);
      }

      log(ascii, LOG_INFO); // Pass ascii char to the log function

      fb_print_after(ascii, 1);
    }
  }
}

void special_key_handler(char keycode_str[])
{
  char space[] = "57";
  if (strcmp(keycode_str, space) == 0)
  {
    nosound();
    fb_print_after("_", 0);
  }
}
