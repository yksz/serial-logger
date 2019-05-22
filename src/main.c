#include <stdio.h>
#include <stdlib.h>
#include "getopty.h"
#include "logger.h"
#include "serialevent.h"

const int kDefaultBaudRate = 9600;
const long kDefaultMaxFileSize = 10000000L; /* 10MB */
const int kDefaultMaxBackupFiles = 10;
const int kAutoFlashIntervalMilliseconds = 1000;

static char* s_output;

static void showUsage(const char* name)
{
    printf("Usage: %s [option] <portname> [baudrate]\n"
           "\n"
           "option:\n"
           "    -h        Show this help message\n"
           "    -o        Output the logs to a specified file\n"
           ""
           , name);
}

static int parse(int argc, char** argv, char** portname, int* baudrate)
{
    struct opty opty = {0};
    int opt;
    while ((opt = getopty(argc, argv, "ho:", &opty)) != -1) {
        switch (opt) {
            case 'h':
                showUsage(argv[0]);
                return 0; /* false */
            case 'o':
                s_output= opty.arg;
                break;
            default:
                break;
        }
    }

    if (argc - opty.ind < 2) {
        showUsage(argv[0]);
        return 0; /* false */
    }
    *portname = argv[opty.ind + 0];
    *baudrate = atoi(argv[opty.ind + 1]);
    return 1; /* true */
}

static void onSerialDataReceived(SerialPort* serial)
{
    static char line[8192];
    static int pos;

    int nbytes = SerialPort_read(serial, &line[pos], 1);
    if (nbytes <= 0) {
        return;
    }
    if (line[pos] == '\n') {
        line[pos] = '\0'; /* overwrite */
        logger_log("%s", line);
        pos = 0;
        return;
    }
    pos += nbytes;
    if (pos + 1 >= sizeof(line)) { /* full */
        line[pos] = '\0';
        logger_log("%s", line);
        pos = 0;
        return;
    }
}

int main(int argc, char** argv)
{
    char* portname = NULL;
    int baudrate = 0;
    int ok = parse(argc, argv, &portname, &baudrate);
    if (!ok) {
        return 1;
    }
    if (baudrate <= 0) {
        baudrate = kDefaultBaudRate;
    }
    if (s_output == NULL) {
        logger_initConsoleLogger(stdout);
    } else {
        logger_initFileLogger(s_output, kDefaultMaxFileSize, kDefaultMaxBackupFiles);
    }
    logger_autoFlush(kAutoFlashIntervalMilliseconds);

    SerialPort serial = {0};
    if (SerialPort_open(&serial, portname, baudrate) != 0) {
        fprintf(stderr, "ERROR: Failed to open serial port: `%s:%d`\n", portname, baudrate);
        return 1;
    }
    serialevent_add(&serial);
    serialevent_set(onSerialDataReceived);
    serialevent_start();
    SerialPort_close(&serial);
    return 0;
}
