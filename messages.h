/**
 * @file messages.h
 *
 * Defines interfaces for logging messages at the appropriate error levels.
 *
 * @author Dan Albert <dan@gingerhq.net>
 */
#ifndef MESSAGES_H
#define MESSAGES_H

#include <assert.h>
#include <stdio.h>

/**
 * @def LOGLEVEL_CRITICAL
 *
 * For errors that are too severe for the program to continue.
 */
#define LOGLEVEL_CRITICAL	1

/**
 * @def LOGLEVEL_ERROR
 *
 * For errors that will prevent the current operation from succeeding, but may
 * not necessarily halt the whole system.
 */
#define LOGLEVEL_ERROR		2

/**
 * @def LOGLEVEL_WARNING
 *
 * For errors that will allow the current operation to continue, but may result
 * in undefined behavior or inconsistent data.
 */
#define LOGLEVEL_WARNING	3

/**
 * @def LOGLEVEL_INFO
 *
 * For messages that are simply informational and do not indicate any abnormal
 * state.
 */
#define LOGLEVEL_INFO		4

/**
 * @def LOGLEVEL_DEBUG
 *
 * For messages that provide detailed information about the current state of the
 * system.
 */
#define LOGLEVEL_DEBUG		5

/**
 * @def LOGLEVEL_MIN
 *
 * The most severe log level.
 */
#define LOGLEVEL_MIN LOGLEVEL_CRITICAL

/**
 * @def LOGLEVEL_MAX
 *
 * The least severe log level.
 */
#define LOGLEVEL_MAX LOGLEVEL_DEBUG

/**
 * Returns the current log level used in the program.
 *
 * @return The current log level.
 *
 * @bug This function is not thread safe.
 */
int get_log_level(void);

/**
 * Sets the log level for the program.
 *
 * @bug This function is not thread safe.
 */
void set_log_level(int level);

/**
 * Logs a message at the specified level.
 *
 * Messages are logged to stdout. A new line is automatically printed after the
 * message.
 *
 * @param level The level at which the message is to be logged.
 * @param format The printf style format of the message to be printed.
 * @param ... The variable argument list for message formatting.
 */
void message(int level, const char* format, ...);

/**
 * Logs an message message at the specified level.
 *
 * All behavior is identical to message(), with the following exceptions:
 * - Messages are logged to stderr
 * - Messages are prepended with the log level and line number
 *
 * @param level The level at which the message is to be logged.
 * @param file The name of the file that will be printed along with the message.
 * @param line The line number that will be printed along with the message.
 * @param format The printf style format of the message to be printed.
 * @param ... The variable argument list for message formatting.
 */
void error_message(int level,
                   const char* file,
                   int line,
                   const char* format, ...);

/**
 * @def CRITICAL
 *
 * Logs a critical error messsage.
 *
 * @param format The printf style format for the message.
 * @param ... The variable argument list for message formatting.
 */
#define CRITICAL(format, ...) \
	error_message(LOGLEVEL_CRITICAL, __FILE__, __LINE__, format, ##__VA_ARGS__)

/**
 * @def ERROR
 *
 * Logs a standard error message.
 *
 * @param format The printf style format for the message.
 * @param ... The variable argument list for message formatting.
 */
#define ERROR(format, ...) \
	error_message(LOGLEVEL_ERROR, __FILE__, __LINE__, format, ##__VA_ARGS__)

/**
 * @def WARNING
 *
 * Logs a warning error message.
 *
 * @param format The printf style format for the message.
 * @param ... The variable argument list for message formatting.
 */
#define WARNING(format, ...) \
	error_message(LOGLEVEL_WARNING, __FILE__, __LINE__, format, ##__VA_ARGS__)

/**
 * @def INFO
 *
 * Logs and informational message.
 *
 * @param format The printf style format for the message.
 * @param ... The variable argument list for message formatting.
 */
#define INFO(format, ...) message(LOGLEVEL_INFO, format, ##__VA_ARGS__)

/**
 * @def DEBUG
 *
 * Logs a debug information message.
 *
 * @param format The printf style format for the message.
 * @param ... The variable argument list for message formatting.
 */
#define DEBUG(format, ...) message(LOGLEVEL_DEBUG, format, ##__VA_ARGS__)

#endif // MESSAGES_H

