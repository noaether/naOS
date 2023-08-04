#ifndef KEYBOARD_H
#define KEYBOARD_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "../lib.h"
#include "../utils/io.h"
#include "../drivers/irq.h"

// IO Ports for Keyboard
#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

#define COMMAND_BUFFER_SIZE 100

  // ----- External functions -----

  void handle_keyboard_interrupt();

  void kb_init();

  void special_key_handler(int keycode);
  void ctrlkey_handler(int keycode);
#ifdef __cplusplus
}
#endif

#endif // KEYBOARD_H