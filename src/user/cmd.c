#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <naOS/string.h>

#include <naOS/mem.h>
#include <drivers/framebuffer.h>
#include <utils/log.h>
#include <drivers/sound.h>

#include <filesystem/fileops.h>

#include "cmd.h"

int since_enter = 0;

char *del = " ";

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

/*
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
/**
 * @brief Handles the writefile command by creating a file with the given name and writing the given string to it.
 *
 * @param string The string to write to the file.
 * @param len The length of the string.
 * @param args The arguments passed to the command.
 */
void handleWriteFile(char *string, size_t len, char *args);

/**
 * @brief Handles the cat command by reading the contents of the given file and printing it to the screen.
 *
 * @param string The string to write to the file.
 * @param len The length of the string.
 * @param args The arguments passed to the command.
 */
void handleReadFile(char *string, size_t len, char *args);

/**
 * @brief Handles the help command by printing the help message to the screen.
 *
 * @param string The string to write to the file.
 * @param len The length of the string.
 * @param args The arguments passed to the command.
 */
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
  const char *desc;
  const char *usage;
  void (*handler)(char *, size_t, char *);
  int numArgs;
  const char *args[10];
} __attribute__((packed));

struct Command commands[] = {
    {"writefile", "Writes a file to the filesystem", "writefile <name> <data>", handleWriteFile, 2, {"name", "data"}},
    {"cat", "Reads a file from the filesystem", "cat <name>", handleReadFile, 1, {"name"}},
    {"help", "Prints this help message", "help", handleHelp, 0, {}},
    {"clear", "Clears the screen", "clear", handleClear, 0, {}},
    {"log", "Logs a message to the kernel log", "log <data>", handleLog, 1, {"data"}},
    {"echo", "Prints a message to the screen", "echo <data>", handleEcho, 1, {"data"}},
    {"play", "Plays a song", "play", handlePlay, 0, {}},
    {"quit", "Quits the kernel", "quit", handleQuit, 0, {}},
    {"cd", "Changes the current directory", "cd <path>", handleChangeDirectory, 1, {"path"}}};

int numCommands = sizeof(commands) / sizeof(commands[0]);

// Function to interpret a command
void interpret(char *string, size_t len)
{
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
      commands[i].handler(string, len, command);
      return;
    }
  }

  handleUnknown(string, len, NULL);
}

void handleWriteFile(char *string, size_t len, char *args)
{
  char endbuffer[256];
  // Implementation for writefile command
  args = strtok(NULL, del); // move to arg1

  createFile(args, 0x06);

  reverse(string, len);
  strncpy(endbuffer, string, len - strlen("writefile  ") - strlen(args));
  reverse(endbuffer, strlen(endbuffer));

  writeFile(args, endbuffer, strlen(endbuffer));

  fb_println("File written succesfully !", 27);

  clear(string, sizeof(string));
  clear(endbuffer, sizeof(endbuffer));
  clear(args, sizeof(args));

  (void)len;
}

void handleReadFile(char *string, size_t len, char *args)
{
  char endbuffer[256];

  args = strtok(NULL, del); // arg1
  readFile(args, endbuffer, sizeof(endbuffer));

  fb_println(endbuffer, strlen(endbuffer));

  clear(string, sizeof(string));
  clear(endbuffer, sizeof(endbuffer));
  clear(args, sizeof(args));

  (void)len;
}

void handleHelp(char *string, size_t len, char *args)
{
  char endbuffer[256];

  for (int i = 0; i < numCommands; i++)
  {
    sprintf(endbuffer, "%s - %s : %s", commands[i].name, commands[i].desc, commands[i].usage);
    fb_println(endbuffer, strlen(endbuffer));
    memset(endbuffer, 0, sizeof(endbuffer));
  }
  clear(string, sizeof(string));
  clear(endbuffer, sizeof(endbuffer));
  clear(args, sizeof(args));

  (void)len;
}

void handleClear(char *string, size_t len, char *args)
{
  char endbuffer[256];

  fb_set_cursor(0);
  fb_clear();

  clear(string, sizeof(string));
  clear(endbuffer, sizeof(endbuffer));
  clear(args, sizeof(args));

  (void)len;
}

void handleLog(char *string, size_t len, char *args)
{
  char endbuffer[256];

  char *toBeLogged = chopN(string, strlen("log "));
  sprintf(endbuffer, "CMD | Log: %s", toBeLogged);
  log(endbuffer, LOG_DEBUG);

  clear(string, sizeof(string));
  clear(endbuffer, sizeof(endbuffer));
  clear(args, sizeof(args));

  (void)len;
}

void handleEcho(char *string, size_t len, char *args)
{
  char *endbuffer = chopN(string, strlen("echo "));
  fb_println(endbuffer, strlen(endbuffer));

  clear(string, sizeof(string));
  clear(endbuffer, sizeof(endbuffer));
  clear(args, sizeof(args));

  (void)len;
}

void handlePlay(char *string, size_t len, char *args)
{
  char endbuffer[256];

  play_array(mary_had_a_little_lamb, 38);

  clear(string, sizeof(string));
  clear(endbuffer, sizeof(endbuffer));
  clear(args, sizeof(args));

  (void)len;
}

void handleQuit(char *string, size_t len, char *args)
{
  char endbuffer[256];

  log("CMD | Quit", LOG_DEBUG);
  asm volatile("hlt");

  clear(string, sizeof(string));
  clear(endbuffer, sizeof(endbuffer));
  clear(args, sizeof(args));

  (void)len;
}

void handleUnknown(char *string, size_t len, char *args)
{
  char endbuffer[256];

  // sprintf(endbuffer, "Unknown command: %s", string);
  fb_println("Unknown command.", 17);

  // memset(endbuffer, 0, sizeof(endbuffer));

  clear(string, sizeof(string));
  clear(endbuffer, sizeof(endbuffer));
  clear(args, sizeof(args));

  (void)len;
}

void handleChangeDirectory(char *string, size_t len, char *args)
{
  char endbuffer[256];

  clear(string, sizeof(string));
  clear(endbuffer, sizeof(endbuffer));
  clear(args, sizeof(args));

  (void)len;
}