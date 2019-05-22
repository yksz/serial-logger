#include <cstdio>
#include <cstdlib>
#include "logger.h"
#include "serialevent.h"

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

    logger_initConsoleLogger(stdout);
    serialevent_set(onSerialDataReceived);

    SerialPort serial = {0};
    if (SerialPort_open(&serial, portname, baudrate) != 0) {
        LOG_ERROR("Could not open");
        return 1;
    }
    serialevent_add(&serial);

    LOG_INFO("start!");
    serialevent_start();

    SerialPort_close(&serial);
    return 0;
}
