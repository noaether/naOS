#include "../lib/naOS/string.h"

#include "../drivers/framebuffer.h"
#include "../drivers/serial.h"

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
        strcpy(strbuf, "\n[DBG] ");
        strcat(strbuf, append);
        log_to(strbuf, strlen(strbuf));
        break;
    case LOG_INFO: // info
        strcpy(strbuf, "\n[INF] ");
        strcat(strbuf, append);
        log_to(strbuf, strlen(strbuf));
        break;
    case LOG_WARNING: // warning
        strcpy(strbuf, "\n[WRN] ");
        strcat(strbuf, append);
        log_to(strbuf, strlen(strbuf));
        break;
    case LOG_ERROR: // error
        strcpy(strbuf, "\n[ERR] ");
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