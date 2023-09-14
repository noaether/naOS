#include "start.h"

void fs_main() {
    log("FS  | Initializing RAM filesystem...", LOG_DEBUG);

    for (int i = 0; i < MAX_FILES - 1; i++) {
        memset(&file_table[i], 0, sizeof(struct FileInformation));
    };

    log("FS  | RAM filesystem initialized!", LOG_DEBUG);
}