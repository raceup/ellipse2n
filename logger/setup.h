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


void setupDisplay() {
    display.init();
    display.setLogo();
}

void setupSD() {
    Serial.print("Initializing SD card...");
    // see if the card is present and can be initialized:
    if (!SD.begin(chipSelect)) {
        Serial.println("Card failed, or not present");
        // don't do anything more:
        return;
    }

    while (nr != 0)
    {
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

void setupTasks()
{

    runner.init();
    Serial.println("Initialized scheduler");

    runner.addTask(tRefreshScreen);
    Serial.println("added t1");

    // runner.addTask(tChangePage);

    runner.addTask(tWriteToSD);
    Serial.println("added t2");

    runner.addTask(tSaveToSD);
    Serial.println("added t3");
    tSaveToSD.enable();
    tWriteToSD.enable();
    tRefreshScreen.enable();
    // tChangePage.enable();
}

void setupButtonInterrupts()
{

    // pinMode(BTN1, INPUT_PULLUP);
    // attachInterrupt(digitalPinToInterrupt(BTN1), launchControl, RISING);

    // pinMode(BTN2, INPUT_PULLUP);
    // attachInterrupt(digitalPinToInterrupt(BTN2), menuBack, RISING);

    pinMode(BTN3, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(BTN3), R2D, RISING);

    // pinMode(BTN4, INPUT_PULLUP);
    // attachInterrupt(digitalPinToInterrupt(BTN4), menuForward, RISING);
}

void setupCAN()
{
    Can0.begin(CAN_COMMUNICATION_FREQUENCY);
    // Can0.setBigEndian(true);   // operate in big endian

    Can0.setNumTXBoxes(1);   // use 1 mailbox (out of 8 on the Arduino Due) for transmission

    // set up the remaining 7 CAN mailboxes to receive messages from the slaves

    int MB_0 = Can0.setRXFilter(0x0, 0x0, false);  // fault messages (ID 0x00)
    /*
    int MB_1 = Can0.setRXFilter(0x0, 0x0, false);  // messages from BMSs 1, 7, 13 and 19
    int MB_2 = Can0.setRXFilter(0x0, 0x0, false);  // messages from BMSs 2, 8, 14 and 20
    int MB_3 = Can0.setRXFilter(0x0, 0x0, false);  // messages from BMSs 3, 9, 15 and 21
    int MB_4 = Can0.setRXFilter(0x0, 0x0, false);  // messages from BMSs 4, 10, 16 and 22
    int MB_5 = Can0.setRXFilter(0x0, 0x0, false);  // messages from BMSs 5, 11, 17 and 23
    int MB_6 = Can0.setRXFilter(0x0, 0x0, false);  // messages from BMSs 6, 12, 18 and 24
    */

    Can0.setCallback(MB_0, callBackTest);
    /*
    Can0.setCallback(MB_1, gotFrameFromSlave);
    Can0.setCallback(MB_2, gotFrameFromSlave);
    Can0.setCallback(MB_3, gotFrameFromSlave);
    Can0.setCallback(MB_4, gotFrameFromSlave);
    Can0.setCallback(MB_5, gotFrameFromSlave);
    Can0.setCallback(MB_6, gotFrameFromSlave);
    */

    // int MB_0 = Can0.setRXFilter(0x20, 0x7FF, true);  // fault messages (ID 0x00)
    // Can0.setCallback(MB_0, callBackTest);

    /*
    for (int filter = 0; filter < 6; filter++) {
      Can0.setRXFilter(filter, 0, 0, false);
      Can1.setRXFilter(filter, 0, 0, false);

      // Can0.setCallback(MB_0, callBackTest);
    }
    */
}

#endif // SETUP_H
