#include "fileops.h"

#include <naOS/string.h>
#include <naOS/stdreturn.h>

/**
 * PERMISSION DOCUMENTATION
 *
 * READ | WRITE | EXECUTE | DELETE
 *  0   |   0   |    0    |    0   = 0x00 = 0
 *  0   |   0   |    0    |    1   = 0x01 = 1
 *  0   |   0   |    1    |    0   = 0x02 = 2
 *  0   |   0   |    1    |    1   = 0x03 = 3
 *  0   |   1   |    0    |    0   = 0x04 = 4
 *  0   |   1   |    0    |    1   = 0x05 = 5
 *  0   |   1   |    1    |    0   = 0x06 = 6
 *  0   |   1   |    1    |    1   = 0x07 = 7
 *  1   |   0   |    0    |    0   = 0x08 = 8
 *  1   |   0   |    0    |    1   = 0x09 = 9
 *  1   |   0   |    1    |    0   = 0x0A = 10
 *  1   |   0   |    1    |    1   = 0x0B = 11
 *  1   |   1   |    0    |    0   = 0x0C = 12
 *  1   |   1   |    0    |    1   = 0x0D = 13
 *  1   |   1   |    1    |    0   = 0x0E = 14
 *  1   |   1   |    1    |    1   = 0x0F = 15
 */

/**
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
} __attribute__((packed));

struct FileInformation file_table[MAX_FILES];

int fs_main()
{
  log("FS  | Initializing RAM filesystem...", LOG_DEBUG);

  for (int i = 0; i < MAX_FILES - 1; i++)
  {
    memset(&file_table[i], 0, sizeof(struct FileInformation));
  };

  log("FS  | RAM filesystem initialized!", LOG_DEBUG);

  return SUCCESS;
}

/**
 * Creates a new file with the given name and permissions.
 *
 * @param name The name of the file to be created.
 * @param permissions The permissions to be set for the file.
 *
 * @return SUCCESS if the file was created successfully, ERROR_OUT_OF_MEMORY if there is no available slot or memory allocation failed, ERROR_INVALID_ARGUMENT if the name or permissions is invalid.
 *
 * @note The function searches for an empty slot in the file table and initializes the file information with the given name, size 0, and the provided permissions. It also allocates memory for the file content.
 */
naOSReturnCode createFile(const char *name, uint16_t permissions)
{
  if (strlen(name) == 0 || strlen(name) > MAX_FILENAME_LENGTH || permissions > 0x0F)
  {
    return RETURN_WITH_PTR(ERROR_INVALID_ARGUMENT, &name);
  }

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
    return RETURN_WITH_PTR(ERROR_OUT_OF_MEMORY, &file_table); // No available slots
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
    return RETURN_WITH_PTR(ERROR_OUT_OF_MEMORY, &name); // Memory allocation failed
  }

  return RETURN_WITH_PTR(SUCCESS, &name); // File created successfully
}

// Function to write data to a file
/**
 * Writes data to a file with the given name.
 *
 * @param name The name of the file to write to.
 * @param data The data to write to the file.
 * @param size The size of the data to write.
 *
 * @return SUCCESS if the write was successful, ERROR_INVALID_ARGUMENT if the size or data is invalid, ERROR_OUT_OF_MEMORY if the file size exceeds the limit, ERROR_PERMISSION_DENIED if the file does not have write permissions, or ERROR_FILE_NOT_FOUND if the file was not found.
 */
naOSReturnCode writeFile(const char *name, const char *data, uint32_t size)
{
  if (
    size < 1 || strlen(data) < 1 || strlen(name) < 1 ||
    size > MAX_FILE_SIZE || strlen(data) > MAX_FILE_SIZE || strlen(name) > MAX_FILENAME_LENGTH)
  {
    return RETURN_WITH_PTR(ERROR_INVALID_ARGUMENT, &name);
  }
  // Find the file in the file table
  for (int i = 0; i < MAX_FILES; i++)
  {
    if (strcmp(file_table[i].name, name) == 0)
    {
      // Check if the file has write permissions
      if (file_table[i].permissions & 0b0100)
      {
        // Check if the file content can hold the new data
        if (size > MAX_FILE_SIZE)
        {
          return RETURN_WITH_PTR(ERROR_OUT_OF_MEMORY, &size); // File size exceeds limit
        }

        // Update file size and content
        struct FileInformation *file = &file_table[i];
        file->size = size;
        strncpy(file->content, data, size);

        // Update the modified timestamp here

        return RETURN_WITH_PTR(SUCCESS, &name); // Write successful
      }
      else
      {
        return RETURN_WITH_PTR(ERROR_PERMISSION_DENIED, &(file_table[i].permissions)); // Permission denied
      }
    }
  }

  return RETURN_WITH_PTR(ERROR_FILE_NOT_FOUND, &name); // File not found
}

// Function to read data from a file
naOSReturnCode readFile(const char *name, char *buffer, uint32_t size)
{
  if(strlen(name) == 0 || strlen(name) > MAX_FILENAME_LENGTH)
  {
    return RETURN_WITH_PTR(ERROR_INVALID_ARGUMENT, &name);
  } else if(size == 0)
  {
    return RETURN_WITH_PTR(ERROR_INVALID_ARGUMENT, &size);
  } else if(buffer == NULL)
  {
    return RETURN_WITH_PTR(ERROR_INVALID_ARGUMENT, &buffer);
  }

  // Find the file in the file table
  for (int i = 0; i < MAX_FILES; i++)
  {
    if (strcmp(file_table[i].name, name) == 0)
    {
      // Check if the file has read permissions
      if (file_table[i].permissions & 0b1000)
      {
        // Check if the buffer can hold the file content
        if (size < file_table[i].size)
        {
          return RETURN_WITH_PTR(ERROR_BUFFER_SIZE_TOO_SMALL, &buffer); // Buffer size is too small
        }

        // Copy file content to the buffer
        struct FileInformation *file = &file_table[i];
        strncpy(buffer, file->content, file->size);

        return RETURN_WITH_PTR(SUCCESS, &(file->size));
      }
      else
      {
        return RETURN_WITH_PTR(ERROR_PERMISSION_DENIED, &name); // Permission denied
      }
    }
  }

  return RETURN_WITH_PTR(ERROR_FILE_NOT_FOUND, &name); // File not found
}

// Function to delete a file
naOSReturnCode deleteFile(const char *name)
{
  // Find the file in the file table
  for (int i = 0; i < MAX_FILES; i++)
  {
    if (strcmp(file_table[i].name, name) == 0)
    {
      // Check if the file has delete permissions
      if (file_table[i].permissions & 0b0001)
      {
        // Free memory used by file content
        free(file_table[i].content);

        // Clear file information
        memset(&file_table[i], 0, sizeof(struct FileInformation));

        return RETURN_WITH_PTR(SUCCESS, NULL); // File deleted successfully
      }
      else
      {
        return RETURN_WITH_PTR(ERROR_PERMISSION_DENIED, &name); // Permission denied
      }
    }
  }

  return RETURN_WITH_PTR(ERROR_FILE_NOT_FOUND, &name); // File not found
}

naOSReturnCode editPermissions(const char *name, uint16_t permissions)
{
  if (strlen(name) == 0 || strlen(name) > MAX_FILENAME_LENGTH || permissions > 0x10)
  {
    return RETURN_WITH_PTR(ERROR_INVALID_ARGUMENT, &name);
  }

  // Find the file in the file table
  for (int i = 0; i < MAX_FILES; i++)
  {
    if (strcmp(file_table[i].name, name) == 0)
    {
      // Check if the file has edit permissions
      if (file_table[i].permissions & 0b0100)
      {
        // Update file permissions
        file_table[i].permissions = permissions;

        return RETURN_WITH_PTR(SUCCESS, &name); // Permissions updated successfully
      }
      else
      {
        return RETURN_WITH_PTR(ERROR_PERMISSION_DENIED, &name); // Permission denied
      }
    }
  }

  return RETURN_WITH_PTR(ERROR_FILE_NOT_FOUND, &name); // File not found
}

// Function to list all files
struct FileInformation *listfiles()
{
  return file_table;
}