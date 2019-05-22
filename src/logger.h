#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

/**
 * Initialize the logger as a console logger.
 * If the file pointer is NULL, stdout will be used.
 *
 * @param[in] output A file pointer. Make sure to set stdout or stderr.
 * @return Non-zero value upon success or 0 on error
 */
int logger_initConsoleLogger(FILE* output);

/**
 * Initialize the logger as a file logger.
 * If the filename is NULL, return without doing anything.
 *
 * @param[in] filename The name of the output file
 * @param[in] maxFileSize The maximum number of bytes to write to any one file
 * @param[in] maxBackupFiles The maximum number of files for backup
 * @return Non-zero value upon success or 0 on error
 */
int logger_initFileLogger(const char* filename, long maxFileSize, unsigned char maxBackupFiles);

/**
 * Flush automatically.
 * Auto flush is off in default.
 *
 * @param[in] interval A fulsh interval in milliseconds. Switch off if 0 or a negative integer.
 */
void logger_autoFlush(long interval);

/**
 * Flush buffered log messages.
 */
void logger_flush(void);

/**
 * Log a message.
 * Make sure to call one of the following initialize functions before starting logging.
 * - logger_initConsoleLogger()
 * - logger_initFileLogger()
 *
 * @param[in] fmt A format string
 * @param[in] ... Additional arguments
 */
void logger_log(const char* fmt, ...);

#endif /* LOGGER_H */
