#ifndef _NTR_LOG_LEV_H_
#define _NTR_LOG_LEV_H_ 1

enum LogLevel {
	LOG_DEBUG = 0,
	LOG_WARN,
	LOG_ERR,
	LOG_NONE
};
#define LOG_ALL 0
const char *lltostr(enum LogLevel ll);

#endif //_NTR_LOG_LEV_H_
