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

char *del = " ";
char endbuffer[1024];

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

/*void interpret(char string[], size_t len)
{
  const char first_char = string[0];


  char *argslist = strtok(string, del);


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
};*/

// Function prototypes for command handlers
void handleWriteFile(char *string, size_t len, char *args);
void handleReadFile(char *string, size_t len, char *args);
void handleHelp(char *string, size_t len, char *args);
void handleClear(char *string, size_t len, char *args);
void handleLog(char *string, size_t len, char *args);
void handleEcho(char *string, size_t len, char *args);
void handlePlay(char *string, size_t len, char *args);
void handleQuit(char *string, size_t len, char *args);
void handleUnknown(char *string, size_t len, char *args);
void handleChangeDirectory(char *string, size_t len, char *args);

// Define a command table
struct Command
{
  const char *name;
  void (*handler)(char *, size_t, char *);
  uint8_t numArgs;
};

// Command handlers
struct Command commands[] = {
    {"writefile", handleWriteFile, 2},
    {"cat", handleReadFile, 1},
    {"help", handleHelp, 0},
    {"clear", handleClear, 0},
    {"log", handleLog, 1},
    {"echo", handleEcho, 1},
    {"play", handlePlay, 0},
    {"quit", handleQuit, 0},
    {"cd", handleChangeDirectory, 1}};

int numCommands = sizeof(commands) / sizeof(commands[0]);

// Function to interpret a command
void interpret(char *string, size_t len)
{
  char *del = " ";
  char *command = strtok(string, del);

  if (command == NULL)
  {
    return; // Empty input
  }

  // Find the corresponding command handler
  for (int i = 0; i < numCommands; i++)
  {
    if (strcmp(command, commands[i].name) == 0)
    {
      char *args = strtok(NULL, "");
      commands[i].handler(string, len, args);
      return;
    }
  }

  handleUnknown(string, len, NULL);
}

// Command handlers
void handleWriteFile(char *string, size_t len, char *args)
{
  // Implementation for writefile command
  args = strtok(NULL, del); // move to arg1

  createFile(args, 0x06);

  reverse(string, len);
  strncpy(endbuffer, string, len - 11 - strlen(args));
  reverse(endbuffer, strlen(endbuffer));

  writeFile(args, endbuffer, 1024);

  fb_println("File written succesfully !", 27);
}

void handleReadFile(char *string, size_t len, char *args)
{
  (void)len, (void)args, (void)string;
}

void handleHelp(char *string, size_t len, char *args)
{
  (void)len, (void)args, (void)string;
}

void handleClear(char *string, size_t len, char *args)
{
  (void)len, (void)args, (void)string;
}

void handleLog(char *string, size_t len, char *args)
{
  (void)len, (void)args, (void)string;
}

void handleEcho(char *string, size_t len, char *args)
{
  (void)len, (void)args, (void)string;
}

void handlePlay(char *string, size_t len, char *args)
{
  (void)len, (void)args, (void)string;
}

void handleQuit(char *string, size_t len, char *args)
{
  (void)len, (void)args, (void)string;
}

void handleUnknown(char *string, size_t len, char *args)
{
  (void)len, (void)args, (void)string;
}

void handleChangeDirectory(char *string, size_t len, char *args)
{
  (void)len, (void)args, (void)string;
}
