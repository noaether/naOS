#ifndef FILEOPS_H
#define FILEOPS_H

#include "__constants.h"
#include "../memory.h"
#include "../utils/log.h"

void fs_main();

int createFile(const char *name, uint16_t permissions);
int writeFile(const char *name, const char *data, uint32_t size);
int readFile(const char *name, char *buffer, uint32_t size);
int deleteFile(const char *name);

#endif // FILEOPS_H