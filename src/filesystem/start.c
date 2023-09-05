#include "../memory.h"
#include "__constants.h"

#include "../lib.h"

void initializeFileSystem() {
    for (int i = 0; i < MAX_FILES; i++) {
        memset(&file_table[i], 0, sizeof(struct FileInformation));
    }
}

int fs_main() {
    initializeFileSystem();

    // Example usage
    createFile("example.txt", 0x06); // Create a file with read and write permissions
    writeFile("example.txt", "Hello, RAM filesystem!", 23);

    char buffer[100];
    int bytesRead = readFile("example.txt", buffer, sizeof(buffer));
    if (bytesRead >= 0) {
        log("Read file contents !", LOG_INFO);
    }

    deleteFile("example.txt");

    return 0;
}