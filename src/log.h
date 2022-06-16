#ifndef _NTR_LOG_H_
#define _NTR_LOG_H_ 1

#include "loglevels.h"
#include <stdbool.h>
#include <stdio.h>
struct Logger {
	enum LogLevel level;
	char *file;
};

struct Logger loginit(enum LogLevel ll, const char *fname);
#define log(L,LL, M) __log(L, LL, M, __FILE__, __func__, __LINE__);
void __log(struct Logger log, enum LogLevel ll, const char *message, 
		const char *file, const char *func, int line);
void logdump(struct Logger log, bool doPrint);
void logfree(struct Logger *log);

#define warn(L,M) log(L, LOG_WARN, M)
#define err(L,M) log(L, LOG_ERR, M)
#define debug(L,M) log(L, LOG_DEBUG, M)
void note(const char *message);

#endif //_NTR_LOG_H_
