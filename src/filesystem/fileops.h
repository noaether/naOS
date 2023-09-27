#ifndef FILEOPS_H
#define FILEOPS_H

#include "__constants.h"
#include "../memory.h"
#include "../utils/log.h"

#define MAX_FILENAME_LENGTH 255
#define MAX_PATH_LENGTH 1024
#define MAX_CHILDREN 128

// Enumeration for file types
enum FileType
{
    FILE_TYPE,
    FOLDER_TYPE
};

// Structure to represent a file or folder node
struct Node
{
    char name[MAX_FILENAME_LENGTH + 1];
    enum FileType type;
    uint16_t permissions;
    uint32_t creation_time;
    uint32_t modified_time;
    uint32_t size; // Added field to represent file size
    char *content;
    struct Node *children[MAX_CHILDREN];
    struct Node *parent; // Pointer to the parent directory
};

// Structure to represent a directory
struct Directory
{
    struct Node node; // Inherits the attributes of a node
    struct Node *contents[MAX_CHILDREN];
};

// Initialize the root directory
struct Directory root;

// Pointer to the current working directory
struct Directory *currentDir;

// Initialize the file system
void fs_main();

// Function to create a file or folder
int createNode(const char *name, uint16_t permissions, enum FileType type);

// Function to create a file inside the current working directory
int createFile(const char *name, uint16_t permissions);

// Function to create a folder inside the current working directory
int createFolder(const char *name, uint16_t permissions);

// Function to navigate to a folder inside the current working directory
int changeDirectory(const char *folderName);

// Function to navigate up one level in the directory hierarchy
int changeDirectoryUp();

// Function to list all files and folders recursively from the current directory
struct Node **listFilesAndFolders();

// Function to return the whole content of a file
char *readFile(const char *name);

#endif // FILEOPS_H