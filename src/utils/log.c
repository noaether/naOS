#include "../stdlib/string.h"

#include "../drivers/framebuffer.h"
#include "../drivers/serial.h"

#include "structs.h"

struct logConfigStruct defaultConf = {0, 0};

void configure_log(struct logConfigStruct lc)
{
    defaultConf.level = lc.level;
    defaultConf.output = lc.output;
}

void log_serial(char *buf)
{
    serial_write(buf);
}

void log_framebuffer(char *buf, unsigned int len)
{
    fb_print_after(buf, len);
}

void log_to(char *buf, unsigned int len)
{

    switch (defaultConf.output)
    {
    case 0:
        log_serial(buf);
        break;
    case 1:
        log_framebuffer(buf, len);
        break;
    default:
        break;
    }
}

void log_with_type(char *append, unsigned char logtype)
{
    char strbuf[256];
    switch (logtype)
    {
    case 0:                 // debug
        strcpy(strbuf, "[DEBUG]");
        strcat(strbuf, append);
        log_to(strbuf, strlen(strbuf));
        break;
    case 1: // info
        strcpy(strbuf, "[INFO]");
        strcat(strbuf, append);
        log_to(strbuf, strlen(strbuf));
        break;
    case 2: // warning
        strcpy(strbuf, "[WARNING]");
        strcat(strbuf, append);
        log_to(strbuf, strlen(strbuf));
        break;
    case 3: // error
        strcpy(strbuf, "[ERROR]");
        strcat(strbuf, append);
        log_to(strbuf, strlen(strbuf));
        break;
    default:
        break;
    }
}

void log(char *buf, unsigned char logtype)
{
    if (logtype >= defaultConf.level)
    {
        log_with_type(buf, logtype);
    }
    else
    {
        return;
    }
}