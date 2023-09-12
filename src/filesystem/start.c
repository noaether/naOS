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
    log("FS  | Initializing RAM filesystem...", LOG_DEBUG);
    initializeFileSystem();
    log("FS  | RAM filesystem initialized!", LOG_DEBUG);
}