#ifndef FILEOPS_H
#define FILEOPS_H

int createFile(const char *name, uint16_t permissions);
int writeFile(const char *name, const char *data, uint32_t size);
int readFile(const char *name, char *buffer, uint32_t size);
int deleteFile(const char *name);

#endif // FILEOPS_H