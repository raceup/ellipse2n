#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "can.h"

void launchControl()
{
    if(start)
    {
        static unsigned long last_interrupt_time = 0;
        unsigned long interrupt_time = millis();
        // If interrupts come faster than 200ms, assume it's a bounce and ignore
        if (interrupt_time - last_interrupt_time > 300)
        {
            Serial.println(String(3));
        }
        last_interrupt_time = interrupt_time;
    }
}

void callbackFrame(CAN_FRAME *frame)
{
    logFrame(*frame);
}

#endif // INTERRUPT_H
