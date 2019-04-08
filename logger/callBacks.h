#ifndef CALLBACKS_H
#define CALLBACKS_H


#include "utils.h"


void t1Callback()
{
    if(start)
    {
        switch(display.getPage())
        {
        case 0:
            displayMainPage();
            break;
        case 1:
            displayMotorsPage();
            break;
        case 2:
            displayInfoPage();
            break;
        default:
            break;
        }
    }
}


void t2Callback()
{
    Serial.println(millis());
    logToFile(micros() / 1000);

    // driver
    logToFile(throttle);
    logToFile(brake);
    logToFile(steering);
    
    // brakes
    logToFile(press_brake_front);
    logToFile(press_brake_rear);

    // imu
    logToFile(imu_time);
    logToFile(imu_general_status);
    logToFile(imu_general_status);

    // imu acc
    logToFile(acc_x);
    logToFile(acc_y);
    logToFile(acc_z);

    // imu gyro
    logToFile(gyro_x);
    logToFile(gyro_y);
    logToFile(gyro_z);

    // imu quaternions
    logToFile(quaternion_0);
    logToFile(quaternion_1);
    logToFile(quaternion_2);
    logToFile(quaternion_3);

    // imu eulers
    logToFile(roll);
    logToFile(pitch);
    logToFile(yaw);

    // imu velocity
    logToFile(velocity);

    // gps
    logToFile(gps_latitude);
    logToFile(gps_longitude);

    // suspensions
    logToFile(susp_fl);
    logToFile(susp_fr);
    logToFile(susp_rl);
    logToFile(susp_rr);

    // temperatures
    logToFile(temp_oil_1);
    logToFile(temp_oil_2);
    logToFile(temp_wat_1);
    logToFile(temp_wat_2);
    logToFile(core_temp_vcu);

    // amk
    // logToFile(amk_actual_values1_fl);
    // logToFile(amk_actual_values2_fl);
    // logToFile(amk_setpoints_1_fl);

    // logToFile(amk_actual_values1_fr);
    // logToFile(amk_actual_values2_fr);
    // logToFile(amk_setpoints_1_fr);

    logToFile(amk_actual_values1_rl);
    logToFile(amk_actual_values2_rl);
    logToFile(amk_setpoints_1_rl);

    logToFile(amk_actual_values1_rr);
    logToFile(amk_actual_values2_rr);
    logToFile(amk_setpoints_1_rr);

    // new line
    dataFile.print("\n");
}

void t3Callback()
{
    dataFile.close();
    dataFile = SD.open(fileName, FILE_WRITE);
}

void t5Callback()
{
    int page = display.getPage();
    page++;
    page = page%3;
    display.setPage(page);
    Serial.print(String(page));
}

#endif // CALLBACKS_H
