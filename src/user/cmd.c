#include "../stdlib/stddef.h"
#include "../stdlib/string.h"
#include "../stdlib/types.h"
#include "../memory.h"

#include "../drivers/framebuffer.h"
#include "../utils/log.h"
#include "../drivers/sound.h"

#include "../filesystem/fileops.h"

#include "cmd.h"

int since_enter = 0;

void interpret(char string[], size_t len)
{
  const char first_char = string[0];

  char *del = " ";
  char *argslist = strtok(string, del);

  char endbuffer[1024];

  // The first character is the command
  switch (first_char)
  {
  case 'w': // write file writefile
    argslist = strtok(NULL, del); // move to arg1

    createFile(argslist, 0x06);

    reverse(string, len);
    strncpy(endbuffer, string, len - 11 - strlen(argslist));
    reverse(endbuffer, strlen(endbuffer));

    writeFile(argslist, endbuffer, 1024);

    break;
  case 'r': // read file readfile
    argslist = strtok(NULL, del); // arg1
    readFile(argslist, endbuffer, sizeof(endbuffer));

    fb_println(endbuffer, strlen(endbuffer));
    break;
  case 't':
    log("test args", LOG_DEBUG);

    while (argslist != NULL)
    {
      log(argslist, LOG_DEBUG);
      argslist = strtok(NULL, del);
    }
    break;
  case 'h': // Help
    fb_println("Commands: h - help, c - clear, l - log, e - echo, p - play, q - quit", 69);
    break;
  case 'c': // Clear
    fb_set_cursor(0);
    fb_clear();
    break;
  case 'l': // e.g. > log hello world
    strncpy(endbuffer, string, len - 4);
    reverse(endbuffer, len - 4);
    log("CMD | Log", LOG_DEBUG);
    log(endbuffer, LOG_DEBUG);
    break;
  case 'e': // e.g. > echo hello world
    strncpy(endbuffer, string, len - 5);
    reverse(endbuffer, len - 5);
    log("CMD | Echo", LOG_DEBUG);
    log(endbuffer, LOG_DEBUG);
    fb_println(endbuffer, len - 5);
    break;
  case 'p': // Play
    play_array();
    break;
  case 'q':
    log("CMD | Quit", LOG_DEBUG);
    log("Quitting...", LOG_DEBUG);
    asm volatile("hlt");
    break;
  default:
    log("Unknown command: ", LOG_DEBUG);
    log(string, LOG_DEBUG);
    break;
  }
};