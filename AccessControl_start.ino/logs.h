#ifndef LOGS_H

#define LOGS_H
#define logBegin 
#define LOG_SIZE 5

struct Log {
    byte card[4];
    byte actionFlag = 0;

    Log(byte* curCard, byte flag);

    Log(uint16_t pos);

    void printFlag();

    void outToSerialPort();

    void writeLog(uint16_t pos);

} typedef Log;

void printLogs();

#endif 
