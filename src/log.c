#include "log.h"
#include <locale.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_LOGS 16
char *logs[MAX_LOGS];
unsigned used = 0;

struct Logger loginit(enum LogLevel ll, const char *fname) {
	struct Logger ret = { ll, NULL };
	ret.file = malloc(64);
	strncpy(ret.file, fname, 64);
	for(int i = 0; i < MAX_LOGS; i++) {
		logs[i] = malloc(128);
		if(logs[i] == NULL) {
			fprintf(stderr, "Couldn't allocate logs\n\t"
					"errno: %d - %s\n",
					errno, strerror(errno));
			exit(-1);
		}
	}
	return ret;
}

void __log(struct Logger log, enum LogLevel ll, const char *message, 
		const char *file, const char *func, int line) {
	if(log.level == LOG_NONE || ll == LOG_NONE || used+1>=MAX_LOGS)
		return;
	char buff[128];
	char timeString[32];
	{
		setlocale(LC_ALL, NULL);
		time_t current_time;
		struct tm *time_info;
		time(&current_time);
		time_info = localtime(&current_time);
		strftime(timeString, sizeof(timeString), "%c", time_info);
	}
	sprintf(buff, "%s: %s\n\tmessage: %s\n\tin file: %s\n\tin function: %s"
			"\n\tat line: %d\n\terrno: %d - %s\n", 
			timeString, lltostr(ll), message, file, func, line, 
			errno, strerror(errno));
	if(ll >= log.level)
		fprintf(stderr, "%s", buff);
	strncpy(logs[used], buff, 128);
	used++;
}

void logdump(struct Logger log, bool doPrint) {
	FILE *file = fopen(log.file, "a");
	if(!file) {
		fprintf(stderr, "Couldn't open log file: %s\n", strerror(errno));
		return;
	}
	for(int i = 0; i < used; i++) {
		if(doPrint)
			fprintf(stderr, "%s", logs[i]);
		fprintf(file, "%128s", logs[i]);
		strncpy(logs[i], "", 1);
	}
	used = 0;
}

void note(const char *message) {
	if(used+1 >= MAX_LOGS)
		return;
	strncpy(logs[used], message, 128);
	used++;
	return;
}

void logfree(struct Logger *log) {
	free(log->file);
	log->file = NULL;
	for(int i = 0; i < MAX_LOGS; i++) {
		free(logs[i]);
		logs[i] = NULL;
	}
}

