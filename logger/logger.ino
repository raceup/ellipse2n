#include <SPI.h>
#include <SD.h>
#include <TaskScheduler.h>

#include "setup.h"
#include "callBacks.h"
#include "data.h"

void setup()
{
    setupSerial();
    setupCAN();
    setupTasks();
    setupButtonInterrupts();
    setupSD();
}

void loop()
{
    runner.execute();

    if (Can0.available() > 0) {
        Can0.read(incoming);
        logFrame(incoming);  // todo needed?? already `Can0.setCallback(MB_0, callbackFrame);` ...
    }
}
