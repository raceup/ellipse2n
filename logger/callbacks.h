#ifndef CALLBACKS_H
#define CALLBACKS_H

#include "utils.h"

#define N_DATA_TO_LOG 20

void write2SDCallback()
{
    int data[N_DATA_TO_LOG] = {
        micros() / 1000,  // time
        imu_time,
        imu_general_status,
        imu_general_status,
        acc_x,  // imu acc
        acc_y,
        acc_z,
        gyro_x,  // imu gyro
        gyro_y,
        gyro_z,
        quaternion_0,  // imu quaternions
        quaternion_1,
        quaternion_2,
        quaternion_3,
        roll,  // imu eulers
        pitch,
        yaw,
        velocity,  // imu velocity
        gps_latitude,  // gps
        gps_longitude
    };

    for (int i = 0; i < N_DATA_TO_LOG; i++) {
        logToFile(data[i]);
    }

    // new line
    dataFile.print("\n");
}

void save2SDCallback()
{
    dataFile.close();
    dataFile = SD.open(fileName, FILE_WRITE);
}

#endif // CALLBACKS_H
