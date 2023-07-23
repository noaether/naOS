#include "../stdlib/string.h"

#include "../drivers/framebuffer.h"
#include "../drivers/serial.h"

#include "structs.h"
#include "log.h"

struct logConfigStruct defaultConf = {LOG_DEBUG, LOG_SERIAL};

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
    case LOG_SERIAL:
        log_serial(buf);
        break;
    case LOG_FRAMEBUFFER:
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
    case LOG_DEBUG:                 // debug
        strcpy(strbuf, "\n[DEBUG] ");
        strcat(strbuf, append);
        log_to(strbuf, strlen(strbuf));
        break;
    case LOG_INFO: // info
        strcpy(strbuf, "\n[INFO] ");
        strcat(strbuf, append);
        log_to(strbuf, strlen(strbuf));
        break;
    case LOG_WARNING: // warning
        strcpy(strbuf, "\n[WARNING] ");
        strcat(strbuf, append);
        log_to(strbuf, strlen(strbuf));
        break;
    case LOG_ERROR: // error
        strcpy(strbuf, "\n[ERROR] ");
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