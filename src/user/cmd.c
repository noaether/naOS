#include "../stdlib/stddef.h"
#include "../stdlib/string.h"
#include "../stdlib/types.h"
#include "../memory.h"

#include "../drivers/framebuffer.h"
#include "../utils/log.h"
#include "../drivers/sound.h"

#include "cmd.h"

void interpret(char string[], size_t len)
{
  const char first_char = string[0];

  reverse(string, len);
  log(string, LOG_DEBUG);

  char args[len];

  // The first character is the command
  switch (first_char)
  {
  case 'h': // Help
    fb_println("Commands: h - help, c - clear, l - log, e - echo, p - play, q - quit", 59);
    break;
  case 'c': // Clear
    fb_set_cursor(0);
    fb_clear();
    break;
  case 'l': // e.g. > log hello world
    strncpy(args, string, len - 4);
    reverse(args, len - 4);
    log("CMD | Log", LOG_INFO);
    log(args, LOG_INFO);
    break;
  case 'e': // e.g. > echo hello world
    strncpy(args, string, len - 5);
    reverse(args, len - 5);
    log("CMD | Echo", LOG_INFO);
    log(args, LOG_INFO);
    fb_println(args, len - 5);
    break;
  case 'p': // Play
    play_array();
    break;
  case 'q':
    log("CMD | Quit", LOG_INFO);
    log("Quitting...", LOG_INFO);
    asm volatile("hlt");
    break;
  default:
    log("Unknown command: ", LOG_INFO);
    log(string, LOG_INFO);
    break;
  }
};