#include <cstdio>
#include <cstdlib>
#include <map>
#include <string>
#include <vector>
#include "getopty.h"
#include "logger.h"
#include "serialevent.h"

const uint32_t kDefaultBaudRate = 9600;

static void showUsage(const std::string& name) {
    printf("Usage: %s [option] <portname[:baudrate]>\n"
           "\n"
           "option:\n"
           "    -h        Show this help message\n"
           "    -o        Output the logs to a specified file\n"
           "    -c        Configure the log settings using a specified setting file\n"
           ""
           , name.c_str());
}

static std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> result;
    std::stringstream stream(s);
    std::string item;
    while (std::getline(stream, item, delim)) {
        result.push_back(item);
    }
    return result;
}

static void onSerialDataReceived(SerialPort* serial) {
    char buf[8192] = {0};
    int nbytes;

    nbytes = SerialPort_read(serial, buf, sizeof(buf) - 1);
    if (nbytes > 0) {
        LOG_INFO("%s", buf);
    }
}

int main(int argc, char** argv) {
    char* portname = "/dev/ttyUSB0";
    int baudrate = 115200;

    struct opty opty = {0};
    int opt;
    while ((opt = getopty(argc, argv, "hc:o:", &opty)) != -1) {
        switch (opt) {
            case 'h':
                showUsage(argv[0]);
                break;

            case 'c':
                printf("opt: c=%s\n", opty.arg);
                break;

            case 'o':
                printf("opt: o=%s\n", opty.arg);
                break;

            default:
                break;
        }
    }

    for (int i = opty.ind; i < argc; i++) {
        printf("arg: %s\n", argv[i]);
    }



//    logger_initConsoleLogger(stdout);
//    serialevent_set(onSerialDataReceived);
//
//    SerialPort serial = {0};
//    if (SerialPort_open(&serial, portname, baudrate) != 0) {
//        LOG_ERROR("Could not open");
//        return 1;
//    }
//    serialevent_add(&serial);
//
//    LOG_INFO("start!");
//    serialevent_start();
//
//    SerialPort_close(&serial);
    return 0;
}
