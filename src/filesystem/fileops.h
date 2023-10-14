#ifndef FILEOPS_H
#define FILEOPS_H

#include "__constants.h"
#include "../memory.h"
#include "../utils/log.h"

#include <stdint.h>
#include <naOS/stdreturn.h>

int fs_main();

naOSReturnCode createFile(const char *name, uint16_t permissions);
naOSReturnCode writeFile(const char *name, const char *data, uint32_t size);
naOSReturnCode readFile(const char *name, char *buffer, uint32_t size);
int deleteFile(const char *name);

#endif // FILEOPS_H