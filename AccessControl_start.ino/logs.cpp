#include "logs.h"

#define MAGICAL_NUMBER 143                  // EEPROM address 1 should hold magical number which is '143'

Log::Log(byte* curCard, byte flag) {

    for (uint8_t i = 0; i < 4; i++) {

        card[i] = curCard[i];

    }

    actionFlag = flag;
}

Log::Log(uint16_t pos) {

    for (uint8_t i = 0; i < 4; i++) {

        card[i] = EEPROM.read(pos + i);

    }

    actionFlag = EEPROM.read(pos + 4);
}

void Log::printFlag() {
    switch (actionFlag) {

    case 0:
        Serial.print("Access granted");
        break;

    case 1:
        Serial.print("Access denied");
        break;

    case 2:
        Serial.print("Add card");
        break;

    case 3:
        Serial.print("Delete card");
        break;

    case 4:
        Serial.print("Entry program mode");
        break;

    case 5:
        Serial.print("Exiting program mode");
        break;

    case 6:
        Serial.print("Add mater card");
        break;
    }
}

void Log::outToSerialPort() {
    
    for (uint8_t i = 0; i < 4; i++) {

        Serial.print(card[i]);

    }

    Serial.print(" ");

    printFlag();
    
    Serial.println();
}

void Log::writeLog(uint16_t pos) {

    for (int i = 0; i < 4; i++) {

        EEPROM.write(pos + i, card[i]);

    }

    EEPROM.write(pos + 4, actionFlag);
}

void Log::writeLog() {

    uint16_t i;

    for (i = LOG_BEGIN; i < 1000 && EEPROM.read(i) != MAGICAL_NUMBER; i += LOG_SIZE);

    writeLog(i);

    EEPROM.write(i + LOG_SIZE, MAGICAL_NUMBER);

}

void printLogs() {
    Serial.println("Log is begin");
    bool flag = true;
    uint16_t i;
    if (EEPROM.read(LOG_BEGIN) == MAGICAL_NUMBER) {
        Serial.println("Log is out");
        return;
    }
    for (i = LOG_BEGIN; i < 1000 && EEPROM.read(i) != MAGICAL_NUMBER; i += LOG_SIZE);
    if (EEPROM.read(++i) == 0) {
        i = LOG_BEGIN;
        flag = false;
    }
    for (i; i < 1000 && EEPROM.read(i) != MAGICAL_NUMBER; i += LOG_SIZE) {
        Log logg(i);
        logg.outToSerialPort();
    }
    if (flag) {
        for (uint16_t j = LOG_BEGIN; EEPROM.read(j) != MAGICAL_NUMBER; j += LOG_SIZE) {
            Log logg(j);
            logg.outToSerialPort();
        }
    }
    Serial.println("Log is out");
}

void cleanEEPROM(){
  for (uint16_t i = LOG_BEGIN; i < 1024; i++){
    EEPROM.write(i, 0);
  }
}
