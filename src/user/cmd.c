#include "../stdlib/stddef.h"
#include "../stdlib/string.h"
#include "../stdlib/types.h"
#include "../memory.h"

#include "../drivers/framebuffer.h"
#include "../utils/log.h"
#include "../drivers/sound.h"

#include "cmd.h"

void interpret(char string[] , size_t len)
{
  const char first_char = string[0];

  reverse(string, len);
  log(string, LOG_DEBUG);

  char args[80];

  memset(args, 0xA1, 80);
  // The first character is the command
  switch (first_char)
  {
  case 'h': // Help
    fb_print_after("Commands: h - help, c - clear, l - log, p - play", 69);
    break;
  case 'c': // Clear
    fb_set_cursor(0);
    fb_clear();
    break;
  case 'l': // e.g. > log hello world
    strncpy(string, args, len - 4);
    log(args, LOG_INFO);
    reverse(args, 80);
    log(args, LOG_INFO);
    break;
  case 'p': // Play
    play_array();
    break;
  default:
    log("Unknown command: ", LOG_INFO);
    log(string, LOG_INFO);
    break;
  }
};