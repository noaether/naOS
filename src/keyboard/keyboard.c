#include "keyboard.h"
#include "keyboard_map.h"

#include "../drivers/irq.h"

#include "../drivers.h"
#include "../utils/io.h"

bool shift_pressed = false; // Global flag to track Shift key state
bool alt_pressed = false;   // Global flag to track Alt key state
bool ctrl_pressed = false;  // Global flag to track Ctrl key state

void kb_init()
{
  asm volatile("cli");
  // ioport_out(PIC1_DATA_PORT, 0xFD); <- this disabled everything but the keyboard
  ioport_out(PIC1_DATA_PORT, 0x00);
  asm volatile("sti");
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
      char logup[] = "KBD | UP ";
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
      } else if (keycode == -99) {
        // CTRL
        ctrl_pressed = false;
      }
      return;
    }
    else
    {
      char logdown[] = "KBD | DOWN ";
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
      } else if (keycode == 58) {
        // Caps lock
        shift_pressed = !shift_pressed;
      } else if (keycode == 29) {
        // CTRL
        ctrl_pressed = true;
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
      else if (ctrl_pressed)
      {
        ascii[0] = keyboard_map[keycode];
        ctrlkey_handler(keycode);
        return;
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
        special_key_handler(keycode);
        return;
      }

      log(ascii, LOG_INFO); // Pass ascii char to the log function

      fb_print_after(ascii, 1);
    }
  }
  else
  {
    log("KBD | No data", LOG_DEBUG);
  }
}

void special_key_handler(int keycode)
{

  char keycode_str[10];
  citoa(keycode, keycode_str, 10);
  if ((57 - keycode) == 0)
  {

    char ascii[2];
    ascii[0] = ' ';
    ascii[1] = '\0';
    log(ascii, LOG_ERROR);
    fb_print_after(ascii, 1);
  }
  else if ((14 - keycode) == 0)
  {
    fb_backspace();
  } else if /* enter key */ ((28 - keycode) == 0)
  {
    char enter[] = "\n";
    fb_write(enter, -1);
  }
  else
  {
    log(keycode_str, LOG_INFO);
  }
}

void ctrlkey_handler(int keycode) {
  if(keycode == 46) {
    fb_write("\n", -1);
    fb_print_after("naOS> ", 6);
  }
}
