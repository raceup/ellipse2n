#ifndef UTILS_H
#define UTILS_H


void displayMainPage() {
    int m = 0, s = 0, ms = 0;

    /*
    unsigned long over;
    int elapsed = millis();
    over = elapsed%3600000;
    m = int(over/60000);
    over = over%60000;
    s = int(over/1000);
    ms=over%1000;
    */

    display.setNumLap(0);
    display.setSpeed(velocity);
    display.setBestTimeLap(m,s,ms/10);
    display.setTimeLap(m,s,ms/10);

    int val = (int)(totalVoltage - 426000) / 1704; // map(totalVoltage, 426000, 596400, 0, 100);
    Serial.println(totalVoltage);

    if(val<0 || val>100)
        val = 0;
    Serial.println(val);

    display.barEnergy(val);
}


void displayMotorsPage() {
    display.updateMotor(0, 15000, 20.3, 0, 25.3 );
    display.updateMotor(1, 15000, 20.3, 0, 25.3 );
    display.updateMotor(2, 15000, 20.3, 0, 25.3 );
    display.updateMotor(3, 15000, 20.3, 0, 25.3 );
    /*
    display.updateMotor(0, 15000 + random(5000), 20.3 + random(30) * 0.1 , 0, 25.3 + random(30) * 0.1);
    display.updateMotor(1, 15000 + random(5000), 20.3 + random(30) * 0.1 , 0, 25.3 + random(30) * 0.1);
    display.updateMotor(2, 15000 + random(5000), 20.3 + random(30) * 0.1 , 0, 25.3 + random(30) * 0.1);
    display.updateMotor(3, 15000 + random(5000), 20.3 + random(30) * 0.1 , 0, 25.3 + random(30) * 0.1);
    */
}


void displayInfoPage() {
    display.updateSusp(random(100),random(100),random(100),random(100));
    display.updateTemp(20 + random(30) * 0.1, 20 + random(30) * 0.1, 20 + random(30) * 0.1, 20 + random(30) * 0.1);
    display.updateThrottle(random(100));
    display.updateBrake(random(100));
    display.updatePower(random(800) * 0.1);
}


void logToFile(double value)
{
    dataFile.print(value);
    dataFile.print(",");  // csv syntax
}

#endif // UTILS_H
