#include "../memory.h"
#include "__constants.h"

#include "fileops.h"

#include "../lib.h"

void initializeFileSystem() {
    for (int i = 0; i < 99; i++) {
        memset(&file_table[i], 0, sizeof(struct FileInformation));
    }
}

void fs_main() {
    log("Initializing RAM filesystem...", LOG_INFO);
    initializeFileSystem();
    log("RAM filesystem initialized!", LOG_INFO);

    /*// Example usage
    createFile("example.txt", 0x06); // Create a file with read and write permissions
    log("Created file!", LOG_INFO);

    writeFile("example.txt", "Hello, RAM filesystem!", 23);
    log("Wrote to file!", LOG_INFO);


    char buffer[100];
    int bytesRead = readFile("example.txt", buffer, sizeof(buffer));
    log("Read file!", LOG_INFO);

    if (bytesRead >= 0) {
        log("Read file contents !", LOG_INFO);
        log(buffer, LOG_INFO);
    }

    deleteFile("example.txt");
    log("Deleted file!", LOG_INFO);*/
}