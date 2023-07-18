#ifndef LOG_H
#define LOG_H

#include "structs.h"

void configure_log(struct logConfigStruct lc);

void log(char *buf, unsigned char logtype);
void log_with_type(char *append, unsigned char logtype);
void log_to(char* buf, unsigned int len);
void log_serial(char* buf);
void log_framebuffer(char* buf, unsigned int len);

#endif  // LOG_H