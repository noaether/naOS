#include "../stdlib/types.h"

// Define constants
#define MAX_FILES 100
#define MAX_FILENAME_LENGTH 255
#define MAX_FILE_SIZE 1024

// Struct to represent file information
struct FileInformation
{
  char name[MAX_FILENAME_LENGTH + 1];
  uint32_t size;
  uint16_t permissions;
  uint32_t creation_time;
  uint32_t modified_time;
  char *content;
};

// Array to store file entries
struct FileInformation file_table[MAX_FILES];
