/*
 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)
*/

#include <UTFT.h>
#include <SPI.h>
#include <SD.h>
#include <TaskScheduler.h>

#include "display.h"
#include "setup.h"
#include "callBacks.h"
#include "data.h"

void setup()
{
    setupDisplay();
    setupSerial();
    setupCAN();
    setupTasks();
    setupButtonInterrupts();
    setupSD();
}

void loop()
{
    runner.execute();

    if(start)
    {
        int val_1 = 9 - (analogRead(analogInPin1)/110);
        display.setRigenerativeLvl(val_1);

        val_1 = 9 - (analogRead(analogInPin2)/110);
        display.setTractionControl(val_1);

        val_1 = 9 - (analogRead(analogInPin3)/110);
        display.setTorqueVectoring(val_1);
    }

    if (Can0.available() > 0)
    {
        Can0.read(incoming);
        printFrame(incoming);
    }
}
