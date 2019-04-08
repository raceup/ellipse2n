#ifndef SETUP_H
#define SETUP_H

#include "data.h"
#include "interrupts.h"


void setupSerial() {
    while (!Serial) {
        delay(100);
    }

    Serial.begin(SERIAL_COMMUNICATION_FREQUENCY);
}


void setupSD() {
    Serial.print("Initializing SD card...");
    // see if the card is present and can be initialized:
    if (!SD.begin(chipSelect)) {
        Serial.println("Card failed, or not present");
        // don't do anything more:
        return;
    }

    while (nr != 0) {
        sprintf(fileName, "log_%03d.txt", nr);
        if (SD.exists(fileName) == false) break;
        Serial.print(fileName);
        Serial.println(" exists.");
        nr++;
    }

    Serial.print(fileName);
    Serial.println( " created.");
    
    dataFile = SD.open(fileName, FILE_WRITE);
    dataFile.print(header);
    dataFile.print("\r\n");
}

void setupTasks() {
    runner.init();
    Serial.println("Initialized scheduler");

    runner.addTask(tWrite2SD);
    Serial.println("added 2SD writer");

    runner.addTask(tSave2SD);
    Serial.println("added 2SD saver");

    tSave2SD.enable();
    tWrite2SD.enable();
}


void setupCAN()
{
    Can0.begin(CAN_COMMUNICATION_FREQUENCY);
    // Can0.setBigEndian(true);   // operate in big endian

    Can0.setNumTXBoxes(1);   // use 1 mailbox (out of 8 on the Arduino Due) for transmission

    // set up the remaining 7 CAN mailboxes to receive messages from the slaves
    int MB_0 = Can0.setRXFilter(0x0, 0x0, false);  // fault messages (ID 0x00)

    Can0.setCallback(MB_0, callbackFrame);
}

#endif // SETUP_H
