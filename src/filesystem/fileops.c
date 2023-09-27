#include "fileops.h"

struct Node root; // The root of your file system

// Initialize the file system
void fs_main()
{
  log("FS  | Initializing RAM filesystem...", LOG_DEBUG);

  memset(&root, 0, sizeof(struct Node));
  root.node.type = FOLDER_TYPE; // The root is a folder
  root.node.parent = NULL;      // The root has no parent

  log("FS  | RAM filesystem initialized!", LOG_DEBUG);
}

// Function to create a file or folder
int createNode(const char *name, uint16_t permissions, enum FileType type)
{
  // Find an empty slot in the children array
  int empty_slot = -1;
  for (int i = 0; i < MAX_CHILDREN; i++)
  {
    if (root.node.children[i] == NULL)
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

  // Initialize node information
  struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
  if (new_node == NULL)
  {
    return -2; // Memory allocation failed
  }

  strncpy(new_node->name, name, MAX_FILENAME_LENGTH);
  new_node->type = type;
  new_node->permissions = permissions;

  // TODO: SET TIMESTAMPS ATTRIBUTES

  new_node->content = NULL; // Initialize content to NULL

  // Initialize children array
  for (int i = 0; i < MAX_CHILDREN; i++)
  {
    new_node->children[i] = NULL;
  }

  // Set the parent directory
  new_node->parent = currentDir;

  // Add the new node to the parent folder (in this case, always root)
  root.node.children[empty_slot] = new_node;

  return 0; // File or folder created successfully
}

// Function to create a file inside the current working directory
int createFile(const char *name, uint16_t permissions)
{
  return createNode(name, permissions, FILE_TYPE);
}

// Function to create a folder inside the current working directory
int createFolder(const char *name, uint16_t permissions)
{
  return createNode(name, permissions, FOLDER_TYPE);
}

// Function to navigate to a folder inside the current working directory
int changeDirectory(const char *folderName)
{
  struct Node **contents = currentDir->node.children;

  // Find the specified folder in the current directory
  for (int i = 0; i < MAX_CHILDREN; i++)
  {
    if (contents[i] != NULL && contents[i]->type == FOLDER_TYPE &&
        strcmp(contents[i]->name, folderName) == 0)
    {
      currentDir = (struct Directory *)contents[i];
      return 0; // Directory changed successfully
    }
  }

  // If folder not found, handle error
  return -1;
}

// Function to navigate up one level in the directory hierarchy
int changeDirectoryUp()
{
  if (currentDir != &root)
  {
    currentDir = (struct Directory *)currentDir->node.parent;
    return 0; // Directory changed successfully
  }
  else
  {
    return -1; // Already at the root directory
  }
}

// Function to list all files and folders recursively from the current directory
struct Node **listFilesAndFolders()
{
  return currentDir->node.children;
}

// Function to return the whole content of a file
char *readFile(const char *name)
{
  // Find the file in the current directory
  struct Node **contents = currentDir->node.children;
  for (int i = 0; i < MAX_CHILDREN; i++)
  {
    if (contents[i] != NULL && contents[i]->type == FILE_TYPE &&
        strcmp(contents[i]->name, name) == 0)
    {
      return contents[i]->content;
    }
  }

  // File not found
  return NULL;
}