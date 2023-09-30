#include "fileops.h"

/*
 * 1. Find an empty slot in the file table
 * 2. Check if there is an available slot
 * 3. Initialize file information
 * 4. Allocate memory for file content
 */
struct FileInformation
{
  char name[MAX_FILENAME_LENGTH + 1];
  uint32_t size;
  uint16_t permissions;
  uint32_t creation_time;
  uint32_t modified_time;
  char *content;
}__attribute__((packed));

struct FileInformation file_table[MAX_FILES];


void fs_main() {
    log("FS  | Initializing RAM filesystem...", LOG_DEBUG);

    for (int i = 0; i < MAX_FILES - 1; i++) {
        memset(&file_table[i], 0, sizeof(struct FileInformation));
    };

    log("FS  | RAM filesystem initialized!", LOG_DEBUG);
}

int createFile(const char *name, uint16_t permissions)
{
  // TODO : WRITE DOCUMENTATION FOR PERMISSIONS

  // Find an empty slot in the file table
  int empty_slot = -1;
  for (int i = 0; i < MAX_FILES; i++)
  {
    if (file_table[i].size == 0)
    {
      empty_slot = i;
      break;
    }
  }

  // Check if there is an available slot
  if (empty_slot < 0)
  {
    return empty_slot; // No available slots
  }

  // Initialize file information
  struct FileInformation *new_file = &file_table[empty_slot];
  strncpy(new_file->name, name, MAX_FILENAME_LENGTH);
  new_file->size = 0;
  new_file->permissions = permissions;

  // TODO: SET TIMESTAMPS ATTRIBUTES

  // Allocate memory for file content
  new_file->content = (char *)malloc(MAX_FILE_SIZE);

  if (new_file->content == NULL)
  {
    return -2; // Memory allocation failed
  }

  return 0; // File created successfully
}

// Function to write data to a file
int writeFile(const char *name, const char *data, uint32_t size)
{
  // Find the file in the file table
  for (int i = 0; i < MAX_FILES; i++)
  {
    if (strcmp(file_table[i].name, name) == 0)
    {
      // Check if the file has write permissions
      if (file_table[i].permissions & 0x02)
      {
        // Check if the file content can hold the new data
        if (size > MAX_FILE_SIZE)
        {
          return -1; // File size exceeds limit
        }

        // Update file size and content
        struct FileInformation *file = &file_table[i];
        file->size = size;
        strncpy(file->content, data, size);

        // Update the modified timestamp here

        return 0; // Write successful
      }
      else
      {
        return -2; // Permission denied
      }
    }
  }

  return -3; // File not found
}

int editFile(const char *name, const char *data, uint32_t size)
{
  // Find the file in the file table
  for (int i = 0; i < MAX_FILES; i++)
  {
    if (strcmp(file_table[i].name, name) == 0)
    {
      // Check if the file has write permissions
      if (file_table[i].permissions & 0x02)
      {
        // Check if the file content can hold the new data
        if (size > MAX_FILE_SIZE)
        {
          return -1; // File size exceeds limit
        }

        // Update file size and content
        struct FileInformation *file = &file_table[i];
        file->size = size;
        strncpy(file->content, data, size);

        // Update the modified timestamp here

        return 0; // Write successful
      }
      else
      {
        return -2; // Permission denied
      }
    }
  }

  return -3; // File not found
}

// Function to read data from a file
int readFile(const char *name, char *buffer, uint32_t size)
{
  // Find the file in the file table
  for (int i = 0; i < MAX_FILES; i++)
  {
    if (strcmp(file_table[i].name, name) == 0)
    {
      // Check if the file has read permissions
      if (file_table[i].permissions & 0x04)
      {
        // Check if the buffer can hold the file content
        if (size < file_table[i].size)
        {
          return -1; // Buffer size is too small
        }

        // Copy file content to the buffer
        struct FileInformation *file = &file_table[i];
        strncpy(buffer, file->content, file->size);

        return file->size; // Return the number of bytes read
      }
      else
      {
        return -2; // Permission denied
      }
    }
  }

  return -3; // File not found
}

// Function to delete a file
int deleteFile(const char *name)
{
  // Find the file in the file table
  for (int i = 0; i < MAX_FILES; i++)
  {
    if (strcmp(file_table[i].name, name) == 0)
    {
      // Check if the file has delete permissions
      if (file_table[i].permissions & 0x08)
      {
        // Free memory used by file content
        free(file_table[i].content);

        // Clear file information
        memset(&file_table[i], 0, sizeof(struct FileInformation));

        return 0; // File deleted successfully
      }
      else
      {
        return -1; // Permission denied
      }
    }
  }

  return -2; // File not found
}

// Function to list all files
struct FileInformation* listfiles()
{
  return file_table;
}