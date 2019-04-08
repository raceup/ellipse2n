#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "can.h"

void menuBack()
{
    /*
    Serial.print(String(page));
    */
    if(start)
    {
        static unsigned long last_interrupt_time = 0;
        unsigned long interrupt_time = millis();
        // If interrupts come faster than 200ms, assume it's a bounce and ignore
        if (interrupt_time - last_interrupt_time > 300)
        {
            if(page > 0)
            {
                // page = display.getPage();
                Serial.println("Page Before: " + String(page));
                page--;
                Serial.println("Page After: " + String(page));
                display.setPage(page);
            }
            Serial.println(String(1));
        }
        last_interrupt_time = interrupt_time;
    }
}

void menuForward()
{
    /*
    Serial.print(String(page));
    */
    if(start)
    {
        static unsigned long last_interrupt_time = 0;
        unsigned long interrupt_time = millis();
        // If interrupts come faster than 200ms, assume it's a bounce and ignore
        if (interrupt_time - last_interrupt_time > 300)
        {
            if(page < 2)
            {
                // page = display.getPage();
                Serial.println("Page Before: " + String(page));

                page++;
                page = page%3;
                display.setPage(page);
                Serial.println("Page After: " + String(page));
            }
            Serial.println(String(2));
        }
        last_interrupt_time = interrupt_time;
    }
}

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

void R2D()
{
    detachInterrupt(BTN3);
    Serial.print("premuto_R2D\n");
    static unsigned long last_interrupt_time = 0;
    unsigned long interrupt_time = millis();
    // If interrupts come faster than 200ms, assume it's a bounce and ignore
    if (interrupt_time - last_interrupt_time > 300)
    {
        CAN_FRAME outgoing;
        outgoing.id = 0x20;
        outgoing.extended = false;
        outgoing.priority = 0; // 0-15 lower is higher priority
        outgoing.length = 1;
        outgoing.data.byte[0] = 0x01;
        Can0.sendFrame(outgoing);
        Serial.println("Send R2D");
        if(!start)
        {
            start = true;
            display.setPage(page);
            previousMillis = millis();
        }

    }
    last_interrupt_time = interrupt_time;
}

void btn3() {

    unsigned long currentMillis = millis(); // Ottengo il tempo di lavoro
    // Controllo che sia passato un tempo idoneo per la lettura di un nuovo input
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        Serial.print("premuto_3\n");
    }
}

void callBackTest(CAN_FRAME *frame)
{
    // Serial.println("ricevuto AMK");
    printFrame(*frame);
}

void gotFrameFromSlave(CAN_FRAME *frame)
{

}

#endif // INTERRUPT_H
