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

struct note mary_had_a_little_lamb[] = {
    {OCTAVE_4, NOTE_E, 4},
    {OCTAVE_4, NOTE_D, 4},
    {OCTAVE_4, NOTE_C, 4},
    {OCTAVE_4, NOTE_D, 4},
    {OCTAVE_4, NOTE_E, 4},
    {OCTAVE_4, NOTE_E, 4},
    {OCTAVE_4, NOTE_E, 2},
    {OCTAVE_4, NOTE_D, 4},
    {OCTAVE_4, NOTE_D, 4},
    {OCTAVE_4, NOTE_E, 4},
    {OCTAVE_4, NOTE_G, 4},
    {OCTAVE_4, NOTE_G, 4},
    {OCTAVE_4, NOTE_E, 4},
    {OCTAVE_4, NOTE_D, 4},
    {OCTAVE_4, NOTE_C, 4},
    {OCTAVE_4, NOTE_D, 4},
    {OCTAVE_4, NOTE_E, 4},
    {OCTAVE_4, NOTE_E, 4},
    {OCTAVE_4, NOTE_E, 4},
    {OCTAVE_4, NOTE_D, 4},
    {OCTAVE_4, NOTE_D, 4},
    {OCTAVE_4, NOTE_E, 4},
    {OCTAVE_4, NOTE_D, 4},
    {OCTAVE_4, NOTE_D, 4},
    {OCTAVE_4, NOTE_D, 4},
    {OCTAVE_4, NOTE_D, 4},
    {OCTAVE_4, NOTE_E, 4},
    {OCTAVE_4, NOTE_E, 4},
    {OCTAVE_4, NOTE_E, 2},
    {OCTAVE_4, NOTE_D, 4},
    {OCTAVE_4, NOTE_D, 4},
    {OCTAVE_4, NOTE_E, 4},
    {OCTAVE_4, NOTE_G, 4},
    {OCTAVE_4, NOTE_G, 4},
    {OCTAVE_4, NOTE_E, 4},
    {OCTAVE_4, NOTE_D, 4},
    {OCTAVE_4, NOTE_C, 4},
    {0, 0, 0} // End of array
};

struct note note_to_play[] = {{OCTAVE_4, NOTE_A, 10}};

void interpret(char string[], size_t len)
{
  const char first_char = string[0];

  char *del = " ";
  char *argslist = strtok(string, del);

  char endbuffer[1024];

  // The first character is the command
  switch (first_char)
  {
  case 'w':                       // write file writefile
                                  // TODO : ADD ERROR HANDLING
    argslist = strtok(NULL, del); // move to arg1

    createFile(argslist, 0x06);

    reverse(string, len);
    strncpy(endbuffer, string, len - 11 - strlen(argslist));
    reverse(endbuffer, strlen(endbuffer));

    writeFile(argslist, endbuffer, 1024);

    fb_println("File written succesfully !", 27);

    break;
  case 'r':                       // read file readfile
                                  // TODO : ADD ERROR HANDLING
    argslist = strtok(NULL, del); // arg1
    readFile(argslist, endbuffer, sizeof(endbuffer));

    fb_println(endbuffer, strlen(endbuffer));
    break;
  case 't':
    while (argslist != NULL)
    {
      log(argslist, LOG_DEBUG);
      argslist = strtok(NULL, del);
    }
    break;
  case 'i': // pi
    argslist = strtok(NULL, del);

    sprintf(endbuffer, "The %dth digit of Pi is: %.15f\n", argslist[0] - '0', calculateNthDigitOfPi(argslist[0] - '0'));

    fb_println(endbuffer, strlen(endbuffer));

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
    play_array(mary_had_a_little_lamb, 38);
    break;
  case '2':
    play_array(note_to_play, 1);
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