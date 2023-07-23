#ifndef LOG_H
#define LOG_H

#include "structs.h"

#define LOG_DEBUG 0
#define LOG_INFO 1
#define LOG_WARNING 2
#define LOG_ERROR 3

#define LOG_SERIAL 0
#define LOG_FRAMEBUFFER 1

void configure_log(struct logConfigStruct lc);

void log(char *buf, unsigned char logtype);
void log_with_type(char *append, unsigned char logtype);
void log_to(char* buf, unsigned int len);
void log_serial(char* buf);
void log_framebuffer(char* buf, unsigned int len);

#endif  // LOG_H