#include "messages.h"

#include <stdarg.h>
#include <string.h>

#define LOGLEVEL_STR_LEN (strlen("CRITICAL") + 1)

int log_level = 3;

void log_level_to_str(int level, char* buf, int len);

int get_log_level(void)
{
	return log_level;
}

void set_log_level(int level)
{
	assert(level >= LOGLEVEL_CRITICAL);
	assert(level <= LOGLEVEL_DEBUG);

	log_level = level;
}

void log_level_to_str(int level, char* buf, int len)
{
	assert(level >= LOGLEVEL_CRITICAL);
	assert(level <= LOGLEVEL_DEBUG);
	
	const char* str = NULL;
	switch (level)
	{
	case LOGLEVEL_CRITICAL:
		str = "CRITICAL";
		break;
	case LOGLEVEL_ERROR:
		str = "ERROR";
		break;
	case LOGLEVEL_WARNING:
		str = "WARNING";
		break;
	case LOGLEVEL_INFO:
		str = "INFO";
		break;
	case LOGLEVEL_DEBUG:
		str = "DEBUG";
		break;
	default:
		fprintf(stderr, "%s:%s:%d:%s\n", "ERROR", __FILE__, __LINE__,
			   	"invalid log level");
		str = "";
	}

	assert(str);
	snprintf(buf, len, "%s", str);
}

void message(int level, const char* format, ...)
{
	assert(format);
	assert(level >= LOGLEVEL_CRITICAL);
	assert(level <= LOGLEVEL_DEBUG);

	if (level > log_level)
		return;

	va_list args;
	va_start(args, format);
	
	char level_str[LOGLEVEL_STR_LEN];
	log_level_to_str(level, level_str, sizeof(level_str));

	fprintf(stderr, "%s:", level_str);
	vfprintf(stderr, format, args);
	putc('\n', stderr);

	va_end(args);
}

void error_message(int level,
                   const char* file,
                   int line,
                   const char* format, ...)
{
	assert(format);
	assert(level >= LOGLEVEL_CRITICAL);
	assert(level <= LOGLEVEL_DEBUG);

	if (level > log_level)
		return;

	va_list args;
	va_start(args, format);
	
	char level_str[LOGLEVEL_STR_LEN];
	log_level_to_str(level, level_str, sizeof(level_str));

	fprintf(stderr, "%s:%s:%d:", level_str, file, line);
	vfprintf(stderr, format, args);
	putc('\n', stderr);

	va_end(args);
}

