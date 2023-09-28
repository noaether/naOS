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

/*
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
};

struct Command commands[] = {
    {"writefile", "Writes a file to the filesystem", "writefile <name> <data>", handleWriteFile, 2, {"name", "data"}},
    {"cat", "Reads a file from the filesystem", "cat <name>", handleReadFile, 1, {"name"}},
    {"help", "Prints this help message", "help", handleHelp, 0, {}},
    {"clear", "Clears the screen", "clear", handleClear, 0, {}},
    {"log", "Logs a message to the kernel log", "log <data>", handleLog, 1, {"data"}},
    {"echo", "Prints a message to the screen", "echo <data>", handleEcho, 1, {"data"}},
    {"play", "Plays a song", "play", handlePlay, 0, {}},
    {"quit", "Quits the kernel", "quit", handleQuit, 0, {}},
    {"cd", "Changes the current directory", "cd <path>", handleChangeDirectory, 1, {"path"}}
  };

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
      char *args = strtok(NULL, del);
      commands[i].handler(string, len, args);
      return;
    }
  }

  handleUnknown(string, len, NULL);
}

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

  (void)len, (void)args, (void)string;
}

void handleReadFile(char *string, size_t len, char *args)
{
  args = strtok(NULL, del); // arg1
  readFile(args, endbuffer, sizeof(endbuffer));

  fb_println(endbuffer, strlen(endbuffer));

  (void)len, (void)args, (void)string;
}

void handleHelp(char *string, size_t len, char *args)
{
  for (int i = 0; i < numCommands; i++)
  {
    sprintf(endbuffer, "%s - %s : %s", commands[i].name, commands[i].desc, commands[i].usage);
    fb_println(endbuffer, strlen(endbuffer));
    memset(endbuffer, 0, sizeof(endbuffer));
  }
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
